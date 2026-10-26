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
bool Book::operator<=(const Book& other) const { return year <= other.year; }
bool Book::operator>(const Book& other) const { return year > other.year; }

std::ostream& operator<<(std::ostream& out, const Book& book) {
    out << "ID: " << book.id << "\n";
    out << "Название: " << book.title << "\n";
    out << "Автор: " << book.author << "\n";
    out << "Год: " << book.year << "\n";
    return out;
}

std::istream& operator>>(std::istream& in, Book& book) {
    std::getline(in, book.title);
    std::getline(in, book.author);
    in >> book.year;
    in.ignore(1000, '\n');
    return in;
}


bool sameAuthor(const Book& a, const Book& b) {
    return a.author == b.author;
}
