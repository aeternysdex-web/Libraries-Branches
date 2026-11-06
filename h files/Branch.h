#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Book.h"
#include "LibraryItem.h"
#include "Magazine.h"
#include "Newspaper.h"

class Branch {
private:
    std::string name;
    int capacity;
    std::vector<std::unique_ptr<LibraryItem>> items;

    void printLine(const LibraryItem& item) const;

public:
    Branch(const std::string& branchName, int branchCapacity);

    LibraryItem* findItemById(int id);

    bool isFull() const;
    std::string getName() const;
    int getCapacity() const;
    int getItemsCount() const;

    void printCatalog() const;
    void printShort() const;
    int printItemsUpToYear(const LibraryItem& ref) const;
    int printItemsAfterYear(const LibraryItem& ref) const;
    void printLoanTerms() const;

    Branch& operator+=(const Book& book);
    Branch& operator+=(const Newspaper& paper);
    Branch& operator+=(const Magazine& magazine);
    Branch& operator-=(int id);
};
