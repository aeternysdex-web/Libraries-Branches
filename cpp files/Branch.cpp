#include "Branch.h"
#include "InvalidDataException.h"
#include "LimitExceededException.h"
#include "DuplicateException.h"
#include "ObjectNotFoundException.h"
#include "InvalidOperationException.h"
#include <iostream>
using namespace std;

namespace {
    template <typename T>
    LibraryItem* findById(Collection<T>& list, int id) {
        int index = list.findIndex([id](const T& item) { return item.getId() == id; });
        return list.get(index);
    }

    template <typename T>
    bool removeById(Collection<T>& list, int id, const string& branchName) {
        int index = list.findIndex([id](const T& item) { return item.getId() == id; });
        if (index == -1) return false;

        const LibraryItem* item = list.get(index);
        cout << "Удалено: [" << item->getType() << "] \"" << item->getTitle()
            << "\" из филиала \"" << branchName << "\".\n";
        return list.removeAt(index);
    }
}

Branch::Branch(const string& branchName, int branchCapacity)
    : name(branchName), capacity(branchCapacity) {
    if (branchName.empty()) throw InvalidDataException("название филиала не может быть пустым");
    if (branchCapacity <= 0) throw InvalidDataException("вместимость филиала должна быть больше 0");
}

void Branch::printLine(const LibraryItem& item) const {
    cout << "  [" << item.getType() << "] ID " << item.getId() << ": \""
        << item.getTitle() << "\", " << item.getYear() << " г.\n";
}


template <typename T>
void Branch::printList(const Collection<T>& list) const {
    for (int i = 0; i < list.getCount(); ++i) {
        printLine(*list.get(i));
    }
}

template <typename T>
int Branch::printUpToYear(const Collection<T>& list, const LibraryItem& ref) const {
    int count = 0;
    for (int i = 0; i < list.getCount(); ++i) {
        const LibraryItem& item = *list.get(i);
        if (item <= ref) {
            cout << name << ":";
            printLine(item);
            count++;
        }
    }
    return count;
}

template <typename T>
int Branch::printAfterYear(const Collection<T>& list, const LibraryItem& ref) const {
    int count = 0;
    for (int i = 0; i < list.getCount(); ++i) {
        const LibraryItem& item = *list.get(i);
        if (item > ref) {
            cout << name << ":";
            printLine(item);
            count++;
        }
    }
    return count;
}

template <typename T>
void Branch::printTerms(const Collection<T>& list) const {
    for (int i = 0; i < list.getCount(); ++i) {
        const LibraryItem& item = *list.get(i);
        cout << name << ": [" << item.getType() << "] \"" << item.getTitle()
            << "\" - срок выдачи " << item.getLoanDays() << " дн.\n";
    }
}


LibraryItem* Branch::findItemById(int id) {
    LibraryItem* item = findById(books, id);
    if (item == nullptr) item = findById(newspapers, id);
    if (item == nullptr) item = findById(magazines, id);
    return item;
}

bool Branch::isFull() const { return getItemsCount() >= capacity; }
string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }

int Branch::getItemsCount() const {
    return books.getCount() + newspapers.getCount() + magazines.getCount();
}

const Collection<Book>& Branch::getBooks() const { return books; }
const Collection<Newspaper>& Branch::getNewspapers() const { return newspapers; }
const Collection<Magazine>& Branch::getMagazines() const { return magazines; }

void Branch::printCatalog() const {
    cout << "=== Филиал \"" << name << "\" (изданий: " << getItemsCount()
        << "/" << capacity << ") ===\n";
    if (getItemsCount() == 0) {
        cout << "  В филиале нет изданий.\n";
    }
    printList(books);
    printList(newspapers);
    printList(magazines);
}

int Branch::printItemsUpToYear(const LibraryItem& ref) const {
    return printUpToYear(books, ref) + printUpToYear(newspapers, ref)
        + printUpToYear(magazines, ref);
}

int Branch::printItemsAfterYear(const LibraryItem& ref) const {
    return printAfterYear(books, ref) + printAfterYear(newspapers, ref)
        + printAfterYear(magazines, ref);
}

void Branch::printLoanTerms() const {
    printTerms(books);
    printTerms(newspapers);
    printTerms(magazines);
}

Branch& Branch::operator+=(const Book& book) {
    if (isFull()) {
        throw LimitExceededException("филиал \"" + name + "\" переполнен ("
            + to_string(getItemsCount()) + "/" + to_string(capacity) + ")");
    }
    if (findItemById(book.getId()) != nullptr) {
        throw DuplicateException("издание с ID " + to_string(book.getId())
            + " уже есть в филиале \"" + name + "\"");
    }
    books.add(make_unique<Book>(book));
    cout << "Добавлено: [" << book.getType() << "] \"" << book.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Newspaper& paper) {
    if (isFull()) {
        throw LimitExceededException("филиал \"" + name + "\" переполнен ("
            + to_string(getItemsCount()) + "/" + to_string(capacity) + ")");
    }
    if (findItemById(paper.getId()) != nullptr) {
        throw DuplicateException("издание с ID " + to_string(paper.getId())
            + " уже есть в филиале \"" + name + "\"");
    }
    newspapers.add(make_unique<Newspaper>(paper));
    cout << "Добавлено: [" << paper.getType() << "] \"" << paper.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Magazine& magazine) {
    if (isFull()) {
        throw LimitExceededException("филиал \"" + name + "\" переполнен ("
            + to_string(getItemsCount()) + "/" + to_string(capacity) + ")");
    }
    if (findItemById(magazine.getId()) != nullptr) {
        throw DuplicateException("издание с ID " + to_string(magazine.getId())
            + " уже есть в филиале \"" + name + "\"");
    }
    magazines.add(make_unique<Magazine>(magazine));
    cout << "Добавлено: [" << magazine.getType() << "] \"" << magazine.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator-=(int id) {
    if (getItemsCount() == 0) {
        throw InvalidOperationException("нельзя удалить издание: филиал \"" + name + "\" пуст");
    }
    if (removeById(books, id, name) || removeById(newspapers, id, name) || removeById(magazines, id, name)) {
        return *this;
    }
    throw ObjectNotFoundException("издание с ID " + to_string(id) + " не найдено в филиале \"" + name + "\"");
}