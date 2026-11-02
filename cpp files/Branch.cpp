#include "Branch.h"
#include <iostream>
using namespace std;

Branch::Branch(const string& branchName, int branchCapacity)
    : name(branchName), capacity(branchCapacity) {}

void Branch::printLine(const LibraryItem& item) const {
    cout << " [" << item.getType() << "] ID " << item.getId() << ": \""
         << item.getTitle() << "\", " << item.getYear() << " г.\n";
}

vector<const LibraryItem*> Branch::getAllItems() const {
    vector<const LibraryItem*> all;
    for (const Book& book : books) all.push_back(&book);
    for (const Newspaper& paper : newspapers) all.push_back(&paper);
    for (const Magazine& magazine : magazines) all.push_back(&magazine);
    return all;
}

Book* Branch::findBookById(int id) {
    for (Book& book : books) {
        if (book.getId() == id) return &book;
    }
    return nullptr;
}

Newspaper* Branch::findNewspaperById(int id) {
    for (Newspaper& paper : newspapers) {
        if (paper.getId() == id) return &paper;
    }
    return nullptr;
}

Magazine* Branch::findMagazineById(int id) {
    for (Magazine& magazine : magazines) {
        if (magazine.getId() == id) return &magazine;
    }
    return nullptr;
}

LibraryItem* Branch::findItemById(int id) {
    if (Book* book = findBookById(id)) return book;
    if (Newspaper* paper = findNewspaperById(id)) return paper;
    if (Magazine* magazine = findMagazineById(id)) return magazine;
    return nullptr;
}

const vector<Book>& Branch::getBooks() const { return books; }
const vector<Newspaper>& Branch::getNewspapers() const { return newspapers; }
const vector<Magazine>& Branch::getMagazines() const { return magazines; }

bool Branch::isFull() const { return getItemsCount() >= capacity; }
string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }

int Branch::getItemsCount() const {
    return static_cast<int>(books.size() + newspapers.size() + magazines.size());
}

void Branch::printCatalog() const {
    cout << "=== Филиал \"" << name << "\" (изданий: " << getItemsCount()
         << "/" << capacity << ") ===\n";
    if (getItemsCount() == 0) {
        cout << " В филиале нет изданий.\n";
    }
    for (const LibraryItem* item : getAllItems()) {
        printLine(*item);
    }
}

void Branch::printShort() const {
    cout << name << " (изданий: " << getItemsCount() << "/" << capacity << ")\n";
}

int Branch::printOtherBooksBySameAuthor(const Book& ref) const {
    int count = 0;
    for (const Book& book : books) {
        if (book != ref && sameAuthor(book, ref)) {   // оператор != (по id)
            cout << name << ":";
            printLine(book);
            count++;
        }
    }
    return count;
}

int Branch::printItemsUpToYear(const LibraryItem& ref) const {
    int count = 0;
    for (const LibraryItem* item : getAllItems()) {
        if (*item <= ref) {   
            cout << name << ":";
            printLine(*item);
            count++;
        }
    }
    return count;
}

int Branch::printItemsAfterYear(const LibraryItem& ref) const {
    int count = 0;
    for (const LibraryItem* item : getAllItems()) {
        if (*item > ref) {   
            cout << name << ":";
            printLine(*item);
            count++;
        }
    }
    return count;
}

// getLoanDays() виртуальный
void Branch::printLoanTerms() const {
    for (const LibraryItem* item : getAllItems()) {
        cout << name << ": [" << item->getType() << "] \"" << item->getTitle()
             << "\" - срок выдачи " << item->getLoanDays() << " дн.\n";
    }
}

void Branch::printInheritedFields() const {
    for (const LibraryItem* item : getAllItems()) {
        cout << "[" << item->getType() << ", " << name << "]\n" << *item << "\n";
    }
}

void Branch::printGetters() const {
    for (const LibraryItem* item : getAllItems()) {
        cout << "[" << item->getType() << ", " << name << "] getId(): " << item->getId()
             << " | getTitle(): " << item->getTitle() << " | getYear(): " << item->getYear() << "\n";
    }
}

Branch& Branch::operator+=(const Book& book) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    books.push_back(book);
    cout << "Добавлено: [" << book.getType() << "] \"" << book.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Newspaper& paper) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    newspapers.push_back(paper);
    cout << "Добавлено: [" << paper.getType() << "] \"" << paper.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator+=(const Magazine& magazine) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    magazines.push_back(magazine);
    cout << "Добавлено: [" << magazine.getType() << "] \"" << magazine.getTitle() << "\" в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator-=(int id) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() == id) {
            cout << "Удалено: [" << books[i].getType() << "] \"" << books[i].getTitle()
                 << "\" из филиала \"" << name << "\".\n";
            books.erase(books.begin() + i);
            return *this;
        }
    }
    for (size_t i = 0; i < newspapers.size(); ++i) {
        if (newspapers[i].getId() == id) {
            cout << "Удалено: [" << newspapers[i].getType() << "] \"" << newspapers[i].getTitle()
                 << "\" из филиала \"" << name << "\".\n";
            newspapers.erase(newspapers.begin() + i);
            return *this;
        }
    }
    for (size_t i = 0; i < magazines.size(); ++i) {
        if (magazines[i].getId() == id) {
            cout << "Удалено: [" << magazines[i].getType() << "] \"" << magazines[i].getTitle()
                 << "\" из филиала \"" << name << "\".\n";
            magazines.erase(magazines.begin() + i);
            return *this;
        }
    }
    cout << "Ошибка: такого издания нет в филиале \"" << name << "\".\n";
    return *this;
}
