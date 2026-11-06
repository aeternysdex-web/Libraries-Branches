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
    ~Book() override = default;

    std::string getAuthor() const;
    std::string getGenre() const;
    int getPageCount() const;

    std::string getType() const override;
    int getLoanDays() const override;
    void printInfo(std::ostream& out) const override;
    void readFrom(std::istream& in) override;
    double calculateLossCost(int currentYear, std::ostream& out) const override;

    bool canFinishInLoanPeriod(int pagesPerDay) const; 


};

