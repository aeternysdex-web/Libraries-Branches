#include "Book.h"
#include "InvalidDataException.h"
#include "InvalidOperationException.h"
using namespace std;

Book::Book(int bookId, const string& bookTitle, int bookYear,
    const string& bookAuthor, const string& bookGenre, int bookPageCount)
    : LibraryItem(bookId, bookTitle, bookYear),
    author(bookAuthor), genre(bookGenre), pageCount(bookPageCount) {}

string Book::getAuthor() const { return author; }
string Book::getGenre() const { return genre; }
int Book::getPageCount() const { return pageCount; }

string Book::getType() const { return "Книга"; }

int Book::getLoanDays() const {
    if (pageCount > 500) {
        return 21;
    }
    else {
        return 14;
    }
}

void Book::printInfo(ostream& out) const {
    LibraryItem::printInfo(out);
    out << "Автор: " << author << "\n";
    out << "Жанр: " << genre << "\n";
    out << "Страниц: " << pageCount << "\n";
}

void Book::readFrom(istream& in) {
    LibraryItem::readFrom(in);
    cout << "Автор: ";
    string newAuthor;
    getline(in, newAuthor);
    if (newAuthor.empty()) throw InvalidDataException("автор не может быть пустым");
    cout << "Жанр: ";
    string newGenre;
    getline(in, newGenre);
    if (newGenre.empty()) throw InvalidDataException("жанр не может быть пустым");
    cout << "Количество страниц: ";
    int newPageCount = readNumber(in);
    if (newPageCount <= 0) throw InvalidDataException("количество страниц должно быть больше 0");
    author = newAuthor;
    genre = newGenre;
    pageCount = newPageCount;
}

double Book::calculateLossCost(int currentYear, ostream& out) const {
    const double BASE_PRICE = 20.0;
    double k = 1.0;
    out << "Базовая цена книги: " << BASE_PRICE << " руб.\n";
    out << "Коэффициент ценности (чем реже издание, тем он больше): 1.0 для обычной книги\n";
    if (pageCount > 500) {
        k += 0.3;
        out << "  +0.3: толстая книга(больше 500 стр.), дороже заменить\n";
    }
    if (currentYear - getYear() > 100) {
        k += 1.0;
        out << "  +1.0: раритет(старше 100 лет)\n";
    }
    out << "Итоговый коэффициент: " << k << "\n";
    double cost = BASE_PRICE * k;
    out << "Стоимость утери: " << BASE_PRICE << " x " << k << " = " << cost << " руб.\n";
    return cost;
}

bool Book::canFinishInLoanPeriod(int pagesPerDay) const {
    if (pagesPerDay <= 0) {
        throw InvalidOperationException("скорость чтения должна быть больше 0 страниц в день");
    }
    return pageCount <= pagesPerDay * getLoanDays();
}

