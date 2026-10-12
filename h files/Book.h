#pragma once
#include <iostream>
#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;

public:
    Book(int bookId, const std::string& bookTitle, const std::string& bookAuthor);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;

    void printShort() const;

    bool operator==(const Book& other) const;
    bool operator<(const Book& other) const;

    friend std::ostream& operator<<(std::ostream& out, const Book& book) {
        out << "ID: " << book.id << "\n";
        out << "Название: " << book.title << "\n";
        out << "Автор: " << book.author << "\n";
        return out;
    }

    friend std::istream& operator>>(std::istream& in, Book& book) {
        std::getline(in, book.title);
        std::getline(in, book.author);
        return in;
    }

    friend bool sameAuthor(const Book& a, const Book& b);
};

bool sameAuthor(const Book& a, const Book& b);
