#include "Branch.h"
#include <iostream>
using namespace std;

Branch::Branch(const string& branchName, int branchCapacity)
    : name(branchName), capacity(branchCapacity) {}


const Publication* Branch::findPublicationById(int id) const {
    for (const Publication& publication : catalog) {
        if (publication.getId() == id) {
            return &publication;
        }
    }
    return nullptr;
}

bool Branch::isFull() const {
    return static_cast<int>(catalog.size()) >= capacity;
}

string Branch::getName() const { return name; }
int Branch::getCapacity() const { return capacity; }
int Branch::getPublicationsCount() const { return static_cast<int>(catalog.size()); }

void Branch::printCatalog() const {
    cout << "=== Филиал \"" << name << "\" (изданий: " << catalog.size()
        << "/" << capacity << ") ===\n";
    if (catalog.empty()) {
        cout << " В филиале нет изданий.\n";
    }
    for (const Publication& publication : catalog) {
        publication.printShort();
    }
}

void Branch::printShort() const {
    cout << name << " (изданий: " << catalog.size() << "/" << capacity << ")\n";
}

int Branch::printOtherPublicationsBySamePublisher(const Publication& ref) const {
    int count = 0;
    for (const Publication& publication : catalog) {
        if (publication != ref && samePublisher(publication, ref)) {    //==
            cout << name << ":";
            publication.printShort();
            count++;
        }
    }
    return count;
}

int Branch::printPublicationsUpToYear(const Publication& ref) const {
    int count = 0;
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i] <= ref) {          // оператор <=
            cout << name << ":";
            catalog[i].printShort();
            count++;
        }
    }
    return count;
}

int Branch::printPublicationsAfterYear(const Publication& ref) const {
    int count = 0;
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i] > ref) {           // оператор >
            cout << name << ":";
            catalog[i].printShort();
            count++;
        }
    }
    return count;
}

Branch& Branch::operator+=(const Publication& publication) {
    if (isFull()) {
        cout << "Ошибка: филиал \"" << name << "\" переполнен.\n";
        return *this;
    }
    catalog.push_back(publication);
    cout << "Издание \"" << publication.getTitle() << "\" добавлено в филиал \"" << name << "\".\n";
    return *this;
}

Branch& Branch::operator-=(const Publication& publication) {
    for (size_t i = 0; i < catalog.size(); ++i) {
        if (catalog[i] == publication) {   // ==
            catalog.erase(catalog.begin() + i);
            cout << "Издание \"" << publication.getTitle() << "\" удалено из филиала \"" << name << "\".\n";
            return *this;
        }
    }
    cout << "Ошибка: такого издания нет в филиале \"" << name << "\".\n";
    return *this;
}
