#pragma once
#include <iostream>
#include <string>
#include "Book.h"
#include "Collection.h"
#include "LibraryItem.h"
#include "Magazine.h"
#include "Newspaper.h"

class Branch {
private:
    std::string name;
    int capacity;

    Collection<Book> books;
    Collection<Newspaper> newspapers;
    Collection<Magazine> magazines;

    void printLine(const LibraryItem& item) const;

    template <typename T>
    void printList(const Collection<T>& list) const;
    template <typename T>
    int printUpToYear(const Collection<T>& list, const LibraryItem& ref) const;
    template <typename T>
    int printAfterYear(const Collection<T>& list, const LibraryItem& ref) const;
    template <typename T>
    void printTerms(const Collection<T>& list) const;

public:
    Branch(const std::string& branchName, int branchCapacity);

    LibraryItem* findItemById(int id);

    bool isFull() const;
    std::string getName() const;
    int getCapacity() const;
    int getItemsCount() const;

    const Collection<Book>& getBooks() const;
    const Collection<Newspaper>& getNewspapers() const;
    const Collection<Magazine>& getMagazines() const;

    void printCatalog() const;
    int printItemsUpToYear(const LibraryItem& ref) const;
    int printItemsAfterYear(const LibraryItem& ref) const;
    void printLoanTerms() const;

    Branch& operator+=(const Book& book);
    Branch& operator+=(const Newspaper& paper);
    Branch& operator+=(const Magazine& magazine);
    Branch& operator-=(int id);

    friend std::ostream& operator<<(std::ostream& out, const Branch& branch) {
        out << branch.name << " (изданий: " << branch.getItemsCount()
            << "/" << branch.capacity << ")";
        return out;
    }
};