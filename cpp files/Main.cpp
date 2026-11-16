#include <iomanip>
#include <iostream>
#include <string>
#include "Book.h"
#include "Branch.h"
#include "Collection.h"
#include "LibraryItem.h"
#include "Magazine.h"
#include "Newspaper.h"

using namespace std;
const int CURRENT_YEAR = 2026;

int readInt(const string& prompt) {
    cout << prompt;
    return readNumber(cin);
}

void printBranches(const Collection<Branch>& branches) {
    branches.print(cout); 
}

void showBranches(const Collection<Branch>& branches) {
    for (int i = 0; i < branches.getCount(); ++i) {
        branches.get(i)->printCatalog();
    }
}

LibraryItem* findItem(const Collection<Branch>& branches, int id) {
    for (int i = 0; i < branches.getCount(); ++i) {
        LibraryItem* item = branches.get(i)->findItemById(id);
        if (item != nullptr) return item;
    }
    return nullptr;
}

Book* findBook(const Collection<Branch>& branches, int id) {
    return dynamic_cast<Book*>(findItem(branches, id));
}

Newspaper* findNewspaper(const Collection<Branch>& branches, int id) {
    return dynamic_cast<Newspaper*>(findItem(branches, id));
}

Magazine* findMagazine(const Collection<Branch>& branches, int id) {
    return dynamic_cast<Magazine*>(findItem(branches, id));
}

void printFullInfo(const Collection<Branch>& branches, int id) {
    const LibraryItem* item = findItem(branches, id);
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    cout << "Тип: " << item->getType() << "\n" << *item;
}

void showItemInfo(const Collection<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    printFullInfo(branches, id);
}

void addItem(const Collection<Branch>& branches, int& nextId) {
    cout << "Что добавить? 1 - книга, 2 - газета, 3 - журнал: ";
    int type = readNumber(cin);
    if (type < 1 || type > 3) {
        cout << "Некорректный тип.\n";
        return;
    }
    cout << "В какой филиал добавить?\n";
    printBranches(branches);
    int choice = readInt("Номер филиала: ");
    if (choice < 1 || choice > branches.getCount()) {
        cout << "Некорректный номер.\n";
        return;
    }
    Branch& branch = *branches.get(choice - 1);
    if (branch.isFull()) {
        cout << "Филиал \"" << branch.getName() << "\" переполнен.\n";
        return;
    }

    if (type == 1) {
        Book book(nextId, "", 0, "", "", 0);
        cin >> book;
        branch += book;
    }
    else if (type == 2) {
        Newspaper paper(nextId, "", 0, 0, 0, "");
        cin >> paper;
        branch += paper;
    }
    else {
        Magazine magazine(nextId, "", 0, "", 0, "");
        cin >> magazine;
        branch += magazine;
    }
    nextId++;
}

void deleteItem(const Collection<Branch>& branches) {
    printBranches(branches);
    int choice = readInt("Из какого филиала удалить издание: ");
    if (choice < 1 || choice > branches.getCount()) {
        cout << "Некорректный номер.\n";
        return;
    }
    Branch& branch = *branches.get(choice - 1);
    branch.printCatalog();
    int id = readInt("Введите ID издания для удаления: ");
    branch -= id;
}

void showUpToYear(const Collection<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);
    int total = 0;
    for (int i = 0; i < branches.getCount(); ++i) {
        total += branches.get(i)->printItemsUpToYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showAfterYear(const Collection<Branch>& branches) {
    int year = readInt("Введите год: ");
    Book ref(0, "", year, "", "", 0);
    int total = 0;
    for (int i = 0; i < branches.getCount(); ++i) {
        total += branches.get(i)->printItemsAfterYear(ref);
    }
    if (total == 0) {
        cout << "Таких изданий нет.\n";
    }
}

void showLoanTerms(const Collection<Branch>& branches) {
    for (int i = 0; i < branches.getCount(); ++i) {
        branches.get(i)->printLoanTerms();
    }
}

void useBookMethod(const Collection<Branch>& branches) {
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

void useNewspaperMethod(const Collection<Branch>& branches) {
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

void useMagazineMethod(const Collection<Branch>& branches) {
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

void useInheritedSetter(const Collection<Branch>& branches) {
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

void payForLoss(const Collection<Branch>& branches) {
    showBranches(branches);
    int id = readInt("Введите ID издания: ");
    const LibraryItem* item = findItem(branches, id);
    if (item == nullptr) {
        cout << "Издание с таким ID не найдено.\n";
        return;
    }
    printLossPayment(*item);
}


void showBooksToFinish(const Collection<Branch>& branches) {
    int pages = readInt("Сколько страниц в день читает читатель: ");
    int total = 0;
    for (int i = 0; i < branches.getCount(); ++i) {
        const Branch& branch = *branches.get(i);
        cout << "--- " << branch.getName() << " ---\n";
        total += printIf(branch.getBooks(),
            [pages](const Book& book) { return book.canFinishInLoanPeriod(pages); }, cout);
    }
    if (total == 0) {
        cout << "Таких книг нет.\n";
    }
}

void showNewspapersToTakeHome(const Collection<Branch>& branches) {
    int total = 0;
    for (int i = 0; i < branches.getCount(); ++i) {
        const Branch& branch = *branches.get(i);
        cout << "--- " << branch.getName() << " ---\n";
        total += printIf(branch.getNewspapers(),
            [](const Newspaper& paper) { return paper.canTakeHome(CURRENT_YEAR); }, cout);
    }
    if (total == 0) {
        cout << "Таких газет нет.\n";
    }
}

void showMagazinesForAudience(const Collection<Branch>& branches) {
    string audience = Magazine::chooseAudience(cin);
    int total = 0;
    for (int i = 0; i < branches.getCount(); ++i) {
        const Branch& branch = *branches.get(i);
        cout << "--- " << branch.getName() << " ---\n";
        total += printIf(branch.getMagazines(),
            [&audience](const Magazine& magazine) { return magazine.suitableFor(audience); }, cout);
    }
    if (total == 0) {
        cout << "Таких журналов нет.\n";
    }
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
    cout << "13. Все книги, которые читатель успеет дочитать\n";
    cout << "14. Все газеты, которые можно взять домой\n";
    cout << "15. Все журналы для выбранной аудитории\n";
    cout << "0. Выход\n";
    cout << "=====================================\n";
}

int main() {
    cout << fixed << setprecision(2);

    Collection<Branch> branches;
    branches.add(make_unique<Branch>("Филиал №1", 10));
    branches.add(make_unique<Branch>("Филиал №2", 10));
    Branch& first = *branches.get(0);
    Branch& second = *branches.get(1);

    int nextId = 1;
    first += Book(nextId++, "Война и мир", 1869, "Л.Н. Толстой", "Роман", 1225);
    first += Book(nextId++, "Мастер и Маргарита", 1967, "М.А. Булгаков", "Роман", 480);
    first += Book(nextId++, "Евгений Онегин", 1833, "А.С. Пушкин", "Роман в стихах", 224);
    first += Book(nextId++, "Тихий Дон", 1940, "М.А. Шолохов", "Роман", 1240);
    first += Newspaper(nextId++, "Звязда", 2026, 210, 25000, "Издательский дом «Звязда»");
    first += Newspaper(nextId++, "Минский листок", 1895, 12, 300, "Редакция «Минского листка»");
    first += Magazine(nextId++, "Мурзилка", 1924, "Детская литература", 1, "дети");
    first += Magazine(nextId++, "Юность", 1975, "Литература", 12, "подростки");

    second += Book(nextId++, "Анна Каренина", 1877, "Л.Н. Толстой", "Роман", 864);
    second += Book(nextId++, "Воскресение", 1899, "Л.Н. Толстой", "Роман", 480);
    second += Book(nextId++, "Маленький принц", 1943, "А. де Сент-Экзюпери", "Сказка", 96);
    second += Magazine(nextId++, "Наука и жизнь", 2025, "Наука", 7, "взрослые");
    second += Magazine(nextId++, "Здоровье", 2023, "Медицина", 1, "пенсионеры");
    second += Newspaper(nextId++, "Советская Беларусь", 2025, 99, 80000, "Редакция СБ");
    second += Newspaper(nextId++, "Вечерний Минск", 2024, 45, 500, "Редакция «Вечернего Минска»");
    second += Newspaper(nextId++, "Знамя юности", 1968, 134, 150000, "Редакция «Знамя юности»");

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
        case 13: showBooksToFinish(branches); break;
        case 14: showNewspapersToTakeHome(branches); break;
        case 15: showMagazinesForAudience(branches); break;
        case 0: cout << "Завершение работы.\n"; break;
        default: cout << "Такого пункта меню нет.\n";
        }
    } while (choice != 0);

    return 0;
}
