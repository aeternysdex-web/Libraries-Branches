#include "LibraryItem.h"
using namespace std;

LibraryItem::LibraryItem(int itemId, const string& itemTitle, int itemYear)
    : id(itemId), title(itemTitle), year(itemYear) {}

int LibraryItem::getId() const { return id; }
string LibraryItem::getTitle() const { return title; }
int LibraryItem::getYear() const { return year; }
void LibraryItem::setTitle(string_view newTitle) {
    if (newTitle.empty()) throw InvalidDataException("название не может быть пустым");
    title = newTitle;
}

int LibraryItem::getLoanDays() const { return 14; }

void LibraryItem::printInfo(ostream& out) const {
    out << "ID: " << id << "\n";
    out << "Название: " << title << "\n";
    out << "Год: " << year << "\n";
}

void LibraryItem::readFrom(istream& in) {
    cout << "Название: ";
    string newTitle;
    getline(in, newTitle);
    if (newTitle.empty()) throw InvalidDataException("название не может быть пустым");
    cout << "Год издания: ";
    int newYear = readNumber(in);
    if (newYear <= 0) throw InvalidDataException("год издания должен быть больше 0");
    title = newTitle;
    year = newYear;
}

bool LibraryItem::operator==(const LibraryItem& other) const { return id == other.id; }
strong_ordering LibraryItem::operator<=>(const LibraryItem& other) const { return year <=> other.year; }