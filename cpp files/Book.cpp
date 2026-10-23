#include "Book.h"
using namespace std;

Book::Book(int bookId, const string& bookTitle, const string& bookAuthor, int bookYear)
    : id(bookId), title(bookTitle), author(bookAuthor), year(bookYear) {}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }

void Book::printShort() const {
    cout << " ID " << id << ": \"" << title << "\", " << author << ", " << year << " г.\n";
}

bool Book::operator==(const Book& other) const { return id == other.id; }
bool Book::operator!=(const Book& other) const { return !(*this == other); }
bool Book::operator<=(const Book& other) const { return year <= other.year; }
bool Book::operator>(const Book& other) const { return year > other.year; }

bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
