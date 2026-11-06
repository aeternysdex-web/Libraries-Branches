#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
#include "Branch.h"
#include "LibraryItem.h"
#include "Magazine.h"
#include "Newspaper.h"

using namespace std;
const int CURRENT_YEAR = 2026;

int readInt(const string& prompt) {
    cout << prompt;
    return readNumber(cin);
}

void printBranches(const vector<Branch>& branches) {
    for (size_t i = 0; i < branches.size(); ++i) {
        cout << i + 1 << ". ";
        branches[i].printShort();
    }
}

void showBranches(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printCatalog();
    }
}

LibraryItem* findItem(vector<Branch>& branches, int id) {
    for (Branch& branch : branches) {
        LibraryItem* item = branch.findItemById(id);
        if (item != nullptr) return item;
    }
    return nullptr;
}

Book* findBook(vector<Branch>& branches, int id) {
    return dynamic_cast<Book*>(findItem(branches, id));
}

Newspaper* findNewspaper(vector<Branch>& branches, int id) {
    return dynamic_cast<Newspaper*>(findItem(branches, id));
}

Magazine* findMagazine(vector<Branch>& branches, int id) {
    return dynamic_cast<Magazine*>(findItem(branches, id));
}

void printFullInfo(vector<Branch>& branches, int id) {
    LibraryItem* item = findItem(branches, id);
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << "Тип: " << item->getType() << "\n" << *item;
}

void showItemInfo(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    printFullInfo(branches, id);
}

void addItem(vector<Branch>& branches, int& nextId) {
    cout << "Что добавить? 1 - книга, 2 - газета, 3 - журнал: ";
    int type = readNumber(cin);
    if (type < 1 || type > 3) {
        cout << "Некорректный тип.\n";
        return;
    }
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

    if (type == 1) {
        Book book(nextId, "", 0, "", "", 0);
        cin >> book;
        branches[index] += book;
    }
    else if (type == 2) {
        Newspaper paper(nextId, "", 0, 0, 0, "");
        cin >> paper;
        branches[index] += paper;
    }
    else {
        Magazine magazine(nextId, "", 0, "", 0, "");
        cin >> magazine;
        branches[index] += magazine;
    }
    nextId++;
}

void deleteItem(vector<Branch>& branches) {
    printBranches(branches);
    int choice = readInt("Из какого филиала удалить издание: ");
    if (choice < 1 || choice > static_cast<int>(branches.size())) {
        cout << "Некорректный номер.\n";
        return;
    }
    int index = choice - 1;
    branches[index].printCatalog();
    int id = readInt("Введите ID издания для удаления: ");
    branches[index] -= id;
}

void showUpToYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printItemsUpToYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showAfterYear(const vector<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);
    int total = 0;
    for (const Branch& branch : branches) {
        total += branch.printItemsAfterYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showLoanTerms(const vector<Branch>& branches) {
    for (const Branch& branch : branches) {
        branch.printLoanTerms();
    }
}

void useBookMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID книги: ");
    const Book* book = findBook(branches, id);
    if (book == nullptr) {
        cout << "Книга с таким ID не найдена.\n";
        return;
    }
    int pages = readInt("Сколько страниц в день читает читатель: ");
    if (book->canFinishInLoanPeriod(pages)) {
        cout << "Читатель успеет дочитать книгу за срок выдачи (" << book->getLoanDays() << " дн.).\n";
    }
    else {
        cout << "Читатель НЕ успеет дочитать книгу за срок выдачи (" << book->getLoanDays() << " дн.).\n";
    }
}

void useNewspaperMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID газеты: ");
    const Newspaper* paper = findNewspaper(branches, id);
    if (paper == nullptr) {
        cout << "Газета с таким ID не найдена.\n";
        return;
    }
    if (paper->canTakeHome(CURRENT_YEAR)) {
        cout << "Номер можно взять домой.\n";
    }
    else {
        cout << "Номер домой брать нельзя (маленький тираж и/или старше 15 лет).\n";
    }
}

void useMagazineMethod(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID журнала: ");
    const Magazine* magazine = findMagazine(branches, id);
    if (magazine == nullptr) {
        cout << "Журнал с таким ID не найден.\n";
        return;
    }
    string audience = Magazine::chooseAudience(cin); // выбор из 4 вариантов
    if (magazine->suitableFor(audience)) {
        cout << "Журнал подходит для этой аудитории.\n";
    }
    else {
        cout << "Журнал не подходит для этой аудитории.\n";
    }
}

void useInheritedSetter(vector<Branch>& branches) {
    cout << "Изменение названия (setTitle() объявлен в LibraryItem и работает для любого издания).\n";
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    LibraryItem* item = findItem(branches, id);
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << "Новое название: ";
    string title;
    getline(cin, title);
    item->setTitle(title);
    cout << "\nПосле изменения:\n";
    printFullInfo(branches, id);
}

//расчёт выплаты за утерю
void printLossPayment(const LibraryItem& item) {
    cout << "\n" << item.getType() << " \"" << item.getTitle() << "\":\n";
    double pay = item.calculateLossCost(CURRENT_YEAR, cout);
    cout << ">>> К оплате: " << pay << " руб.\n";
}

void payForLoss(vector<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    LibraryItem* item = findItem(branches, id); 
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    printLossPayment(*item);
}

void printMenu() {
    cout << "\n========== Сеть библиотек ==========\n";
    cout << "1. Показать филиалы и издания в них\n";
    cout << "2. Информация об издании\n";
    cout << "3. Добавить издание\n";
    cout << "4. Удалить издание\n";
    cout << "5. Издания, выпущенные в указанном году и раньше\n";
    cout << "6. Издания, выпущенные после указанного года\n";
    cout << "7. Сроки выдачи изданий\n";
    cout << "8. Книга: успеет ли читатель дочитать\n";
    cout << "9. Газета: можно ли взять домой\n";
    cout << "10. Журнал: подходит ли аудитории\n";
    cout << "11. Изменить название издания\n";
    cout << "12. Выплата за утерю издания\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    cout << fixed << setprecision(2);

    vector<Branch> branches;
    branches.emplace_back("Филиал №1", 10);
    branches.emplace_back("Филиал №2", 10);

    int nextId = 1;
    branches[0] += Book(nextId++, "Война и мир", 1869, "Л.Н. Толстой", "Роман", 1225);
    branches[0] += Book(nextId++, "Мастер и Маргарита", 1967, "М.А. Булгаков", "Роман", 480);
    branches[0] += Book(nextId++, "Евгений Онегин", 1833, "А.С. Пушкин", "Роман в стихах", 224);
    branches[0] += Book(nextId++, "Тихий Дон", 1940, "М.А. Шолохов", "Роман", 1240);
    branches[0] += Newspaper(nextId++, "Звязда", 2026, 210, 25000, "Издательский дом «Звязда»");
    branches[0] += Newspaper(nextId++, "Минский листок", 1895, 12, 300, "Редакция «Минского листка»");
    branches[0] += Magazine(nextId++, "Мурзилка", 1924, "Детская литература", 1, "дети");
    branches[0] += Magazine(nextId++, "Юность", 1975, "Литература", 12, "подростки");

    branches[1] += Book(nextId++, "Анна Каренина", 1877, "Л.Н. Толстой", "Роман", 864);
    branches[1] += Book(nextId++, "Воскресение", 1899, "Л.Н. Толстой", "Роман", 480);
    branches[1] += Book(nextId++, "Маленький принц", 1943, "А. де Сент-Экзюпери", "Сказка", 96);
    branches[1] += Magazine(nextId++, "Наука и жизнь", 2025, "Наука", 7, "взрослые");
    branches[1] += Magazine(nextId++, "Здоровье", 2023, "Медицина", 1, "пенсионеры");
    branches[1] += Newspaper(nextId++, "Советская Беларусь", 2025, 99, 80000, "Редакция СБ");
    branches[1] += Newspaper(nextId++, "Вечерний Минск", 2024, 45, 500, "Редакция «Вечернего Минска»");
    branches[1] += Newspaper(nextId++, "Знамя юности", 1968, 134, 150000, "Редакция «Знамя юности»");

    int choice;
    do {
        printMenu();
        choice = readInt("Выберите пункт меню: ");
        switch (choice) {
        case 1: showBranches(branches); break;
        case 2: showItemInfo(branches); break;
        case 3: addItem(branches, nextId); break;
        case 4: deleteItem(branches); break;
        case 5: showUpToYear(branches); break;
        case 6: showAfterYear(branches); break;
        case 7: showLoanTerms(branches); break;
        case 8: useBookMethod(branches); break;
        case 9: useNewspaperMethod(branches); break;
        case 10: useMagazineMethod(branches); break;
        case 11: useInheritedSetter(branches); break;
        case 12: payForLoss(branches); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
