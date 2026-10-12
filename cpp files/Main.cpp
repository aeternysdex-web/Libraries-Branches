#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"

using namespace std;

int readInt(const string& prompt) {
    cout << prompt;
    int number;
    cin >> number;
    cin.ignore(1000, '\n');
    return number;
}

void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

const Book* findBook(const vector<Branch>& branches, int id) {
    for (const Branch& branch : branches) {
        const Book* book = branch.findBookById(id);
        if (book != nullptr) {
            return book;
        }
    }
    return nullptr;
}

void showBranches(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printCatalog();
    }
}

void showBookInfo(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена.\n";
        return;
    }
    cout << *book;                       // оператор <<
}

void addBook(vector<Branch>& branches, int& nextId) {
    Book book(nextId, "", "");
    cout << "Введите название и автора (каждое с новой строки):\n";
    cin >> book;                         // оператор >>

    cout << "В какой филиал добавить?\n";
    printBranches(branches);
    int choice = readInt("Номер филиала: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    if (branches[index].isFull()) {
        cout << "Филиал \"" << branches[index].getName() << "\" переполнен.\n";
        return;
    }
    branches[index] += book;             // оператор +=
    nextId++;
}

void deleteBook(vector<Branch>& branches) {
    printBranches(branches);
    int choice = readInt("Из какого филиала удалить книгу: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    branches[index].printCatalog();

    int id = readInt("Введите ID книги для удаления: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена.\n";
        return;
    }
    Book copy = *book;                  
    branches[index] -= copy;             // оператор -=
}

void showSameAuthor(const vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена.\n";
        return;
    }
    cout << "Другие книги автора " << book->getAuthor() << ":\n";
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printOtherBooksBySameAuthor(*book);
    }
    if (total == 0) {
        cout << "  Других книг этого автора нет.\n";
    }
}

void showNewest(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        cout << branch.getName() << ": ";
        const Book* newest = branch.newestBook();
        if (newest == nullptr) {
            cout << "книг нет\n";
        } else {
            cout << "последнее поступление - \"" << newest->getTitle()
                 << "\" (ID " << newest->getId() << ")\n";
        }
    }
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и книги в них\n";
    cout << "2. Информация о книге\n";
    cout << "3. Добавить книгу\n";
    cout << "4. Удалить книгу\n";
    cout << "5. Другие книги того же автора\n";
    cout << "6. Последнее поступление в каждом филиале\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 5);
    branches.emplace_back("Филиал №2", 5);

    int nextId = 1;
    branches[0].addBook(Book(nextId, "Война и мир", "Л.Н. Толстой"));
    nextId++;
    branches[0].addBook(Book(nextId, "Мастер и Маргарита", "М.А. Булгаков"));
    nextId++;
    branches[1].addBook(Book(nextId, "Евгений Онегин", "А.С. Пушкин"));
    nextId++;
    branches[1].addBook(Book(nextId, "Анна Каренина", "Л.Н. Толстой"));
    nextId++;
    cout << "Загружены тестовые данные: 2 филиала.\n";

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
            case 1: showBranches(branches); break;
            case 2: showBookInfo(branches); break;
            case 3: addBook(branches, nextId); break;
            case 4: deleteBook(branches); break;
            case 5: showSameAuthor(branches); break;
            case 6: showNewest(branches); break;
            case 0: cout << "Завершение работы.\n"; break;
            default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);
    return 0;
}
