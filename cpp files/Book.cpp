#include "Book.h"

using namespace std;

Book::Book(int bookId, const string& bookTitle, const string& bookAuthor)
    : id(bookId), title(bookTitle), author(bookAuthor) {}

int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }

void Book::printShort() const {
    cout << "  ID " << id << ": \"" << title << "\", " << author << "\n";
}

bool Book::operator==(const Book& other) const { return id == other.id; }
bool Book::operator!=(const Book& other) const { return id != other.id; }
bool Book::operator<(const Book& other) const { return id < other.id; }

ostream& operator<<(ostream& out, const Book& book) {
    out << "ID: " << book.id << "\n";
    out << "Название: " << book.title << "\n";
    out << "Автор: " << book.author << "\n";
    return out;
}

istream& operator>>(istream& in, Book& book) {
    getline(in, book.title);
    getline(in, book.author);
    return in;
}

bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
