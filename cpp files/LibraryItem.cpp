#include "LibraryItem.h"
using namespace std;

LibraryItem::LibraryItem(int itemId, const string& itemTitle, int itemYear)
    : id(itemId), title(itemTitle), year(itemYear) {}

LibraryItem::~LibraryItem() {}

int LibraryItem::getId() const { return id; }
string LibraryItem::getTitle() const { return title; }
int LibraryItem::getYear() const { return year; }
void LibraryItem::setTitle(const string& newTitle) { title = newTitle; }
void LibraryItem::setYear(int newYear) { year = newYear; }

string LibraryItem::getType() const { return "Издание"; }
int LibraryItem::getLoanDays() const { return 14; }

void LibraryItem::printInfo(ostream& out) const {
    out << "ID: " << id << "\n";
    out << "Название: " << title << "\n";
    out << "Год: " << year << "\n";
}

void LibraryItem::readFrom(istream& in) {
    cout << "Название: ";
    getline(in, title);
    cout << "Год издания: ";
    year = readNumber(in);
}

bool LibraryItem::operator==(const LibraryItem& other) const { return id == other.id; }
bool LibraryItem::operator!=(const LibraryItem& other) const { return !(*this == other); }
bool LibraryItem::operator<(const LibraryItem& other) const { return year < other.year; }
bool LibraryItem::operator>(const LibraryItem& other) const { return year > other.year; }
bool LibraryItem::operator<=(const LibraryItem& other) const { return year <= other.year; }
bool LibraryItem::operator>=(const LibraryItem& other) const { return year >= other.year; }

ostream& operator<<(ostream& out, const LibraryItem& item) {
    item.printInfo(out);
    return out;
}

istream& operator>>(istream& in, LibraryItem& item) {
    item.readFrom(in);
    return in;
}
