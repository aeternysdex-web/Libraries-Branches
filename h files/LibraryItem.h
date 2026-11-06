#pragma once
#include <iostream>
#include <string>
#include <string_view>
#include <compare>

inline int readNumber(std::istream& in) {
    int n = 0;
    if (!(in >> n)) {
        in.clear();
        n = 0;
    }
    in.ignore(1000, '\n');
    return n;
}

class LibraryItem {
private:
    int id;
    std::string title;
    int year;

public:
    LibraryItem(int itemId, const std::string& itemTitle, int itemYear);

    virtual ~LibraryItem() = default;

    int getId() const;
    std::string getTitle() const;
    int getYear() const;
    void setTitle(std::string_view newTitle);


    virtual std::string getType() const = 0;
    virtual int getLoanDays() const;                 
    virtual void printInfo(std::ostream& out) const; 
    virtual void readFrom(std::istream& in);       

    virtual double calculateLossCost(int currentYear, std::ostream& out) const = 0; 

    bool operator==(const LibraryItem& other) const;
    std::strong_ordering operator<=>(const LibraryItem& other) const;

    friend std::ostream& operator<<(std::ostream& out, const LibraryItem& item) {
        item.printInfo(out);
        return out;
    }
    friend std::istream& operator>>(std::istream& in, LibraryItem& item) {
        item.readFrom(in);
        return in;
    }
};
