#pragma once
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
    std::vector<Book> books;
    std::vector<Newspaper> newspapers;
    std::vector<Magazine> magazines;

    std::vector<const LibraryItem*> getAllItems() const;

    void printLine(const LibraryItem& item) const;

public:
    Branch(const std::string& branchName, int branchCapacity);

    LibraryItem* findItemById(int id);
    Book* findBookById(int id);
    Newspaper* findNewspaperById(int id);
    Magazine* findMagazineById(int id);

    const std::vector<Book>& getBooks() const;
    const std::vector<Newspaper>& getNewspapers() const;
    const std::vector<Magazine>& getMagazines() const;

    bool isFull() const;
    std::string getName() const;
    int getCapacity() const;
    int getItemsCount() const;

    void printCatalog() const;
    void printShort() const;
    int printOtherBooksBySameAuthor(const Book& ref) const;
    int printItemsUpToYear(const LibraryItem& ref) const;     
    int printItemsAfterYear(const LibraryItem& ref) const;    
    void printLoanTerms() const;                             

    void printInheritedFields() const; // унаследованные поля
    void printGetters() const; // унаследованные геттеры 

    Branch& operator+=(const Book& book);
    Branch& operator+=(const Newspaper& paper);
    Branch& operator+=(const Magazine& magazine);
    Branch& operator-=(int id);
};
