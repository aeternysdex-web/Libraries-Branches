#include "Book.h"
using namespace std;

Book::Book(int bookId, const string& bookTitle, int bookYear,
           const string& bookAuthor, const string& bookGenre, int bookPageCount)
    : LibraryItem(bookId, bookTitle, bookYear),
      author(bookAuthor), genre(bookGenre), pageCount(bookPageCount) {
}

string Book::getAuthor() const { return author; }
string Book::getGenre() const { return genre; }
int Book::getPageCount() const { return pageCount; }
void Book::setAuthor(string_view newAuthor) { author = newAuthor; }
void Book::setGenre(string_view newGenre) { genre = newGenre; }
void Book::setPageCount(int newPageCount) { pageCount = newPageCount; }

string Book::getType() const { return "Книга"; }

int Book::getLoanDays() const {
    if (pageCount > 500) {
        return 21;
    } else {
        return 14;
    }
}

bool Book::canFinishInLoanPeriod(int pagesPerDay) const {
    if (pagesPerDay <= 0) return false;
    return pageCount <= pagesPerDay * getLoanDays();
}

bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
