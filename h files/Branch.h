#pragma once
#include <string>
#include <vector>
#include "Book.h"

class Branch {
private:
    std::string name;
    int capacity;
    std::vector<Book> catalog;

public:
    Branch(const std::string& branchName, int branchCapacity);

    const Book* findBookById(int id) const;
    bool isFull() const;

    std::string getName() const;
    int getCapacity() const;
    int getBooksCount() const;

    void printCatalog() const;
    void printShort() const;

    int printOtherBooksBySameAuthor(const Book& ref) const;
    int printBooksUpToYear(const Book& ref) const;    // год <= заданного
    int printBooksAfterYear(const Book& ref) const;   // год > заданного

    Branch& operator+=(const Book& book);
    Branch& operator-=(const Book& book);
};
