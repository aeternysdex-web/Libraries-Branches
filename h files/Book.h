#pragma once
#include <iostream>
#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int year;

public:
    Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor, int bookYear);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;

    void printShort() const;

    bool operator==(const Book& other) const;   // равенство по id
    bool operator<=(const Book& other) const;   // по году
    bool operator>(const Book& other) const;    // по году

    friend std::ostream& operator<<(std::ostream& out, const Book& book) {
        out << "ID: " << book.id << "\n";
        out << "Название: " << book.title << "\n";
        out << "Автор: " << book.author << "\n";
        out << "Год: " << book.year << "\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Book& book) {
        std::getline(in, book.title);
        std::getline(in, book.author);
        in >> book.year;
        in.ignore(1000, '\n');
        return in;
    }

    friend bool sameAuthor(const Book& a, const Book& b);
};

bool sameAuthor(const Book& a, const Book& b);
