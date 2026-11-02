#pragma once
#include "LibraryItem.h"

class Book : public LibraryItem {
private:
    std::string author;
    std::string genre;
    int pageCount;

public:
    Book(int bookId, const std::string& bookTitle, int bookYear,
         const std::string& bookAuthor, const std::string& bookGenre, int bookPageCount);
    ~Book() override;

    std::string getAuthor() const;
    std::string getGenre() const;
    int getPageCount() const;
    void setAuthor(const std::string& newAuthor);
    void setGenre(const std::string& newGenre);
    void setPageCount(int newPageCount);

    std::string getType() const override;
    int getLoanDays() const override;
    bool canFinishInLoanPeriod(int pagesPerDay) const;
    friend bool sameAuthor(const Book& a, const Book& b);
};

bool sameAuthor(const Book& a, const Book& b);
