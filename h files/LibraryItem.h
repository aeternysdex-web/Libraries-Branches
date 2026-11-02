#pragma once
#include <iostream>
#include <string>

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
    virtual ~LibraryItem();

    int getId() const;
    std::string getTitle() const;
    int getYear() const;
    void setTitle(const std::string& newTitle);
    void setYear(int newYear);

    virtual std::string getType() const;
    virtual int getLoanDays() const;
    void printInfo(std::ostream& out) const;
    void readFrom(std::istream& in);

    bool operator==(const LibraryItem& other) const;
    bool operator!=(const LibraryItem& other) const;
    bool operator<(const LibraryItem& other) const;
    bool operator>(const LibraryItem& other) const;
    bool operator<=(const LibraryItem& other) const;
    bool operator>=(const LibraryItem& other) const;
};

std::ostream& operator<<(std::ostream& out, const LibraryItem& item);
std::istream& operator>>(std::istream& in, LibraryItem& item);
