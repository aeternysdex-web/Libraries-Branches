#pragma once
#include <iostream>

template <typename T>
class Collection {
private:
    T** data;       
    int count;      
    int capacity;   

    static constexpr int START_CAPACITY = 4;  
    void grow();    

public:
    Collection();
    ~Collection();

    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;

    bool add(T* item);                
    bool removeAt(int index);         
    T* get(int index) const;    

    template <typename Predicate>
    int findIndex(Predicate pred) const;

    int getCount() const;           
    void clear();                    
    void print(std::ostream& out) const;  
};

template <typename T>
Collection<T>::Collection()
    : data(new T* [START_CAPACITY]), count(0), capacity(START_CAPACITY) {}

template <typename T>
Collection<T>::~Collection() {
    for (int i = 0; i < count; ++i) {
        delete data[i];
    }
    delete[] data;
}

template <typename T>
void Collection<T>::grow() {
    int newCapacity = capacity * 2;
    T** newData = new T * [newCapacity];
    for (int i = 0; i < count; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template <typename T>
bool Collection<T>::add(T* item) {
    if (item == nullptr) return false;
    if (count == capacity) {
        grow();
    }
    data[count] = item;
    ++count;
    return true;
}

template <typename T>
bool Collection<T>::removeAt(int index) {
    if (index < 0 || index >= count) return false;
    delete data[index];                       
    for (int i = index; i < count - 1; ++i) { 
        data[i] = data[i + 1];
    }
    --count;
    return true;
}

template <typename T>
T* Collection<T>::get(int index) const {
    if (index < 0 || index >= count) return nullptr;
    return data[index];
}

template <typename T>
template <typename Predicate>
int Collection<T>::findIndex(Predicate pred) const {
    for (int i = 0; i < count; ++i) {
        if (pred(*data[i])) return i;
    }
    return -1;
}

template <typename T>
int Collection<T>::getCount() const { return count; }

template <typename T>
void Collection<T>::clear() {
    for (int i = 0; i < count; ++i) {
        delete data[i];
    }
    delete[] data;
    capacity = START_CAPACITY;
    data = new T * [capacity];
    count = 0;
}

template <typename T>
void Collection<T>::print(std::ostream& out) const {
    if (count == 0) {
        out << "(коллекция пуста)\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        out << i + 1 << ". " << *data[i] << "\n";  
    }
}

template <typename T, typename Predicate>
int printIf(const Collection<T>& list, Predicate pred, std::ostream& out) {
    int found = 0;
    for (int i = 0; i < list.getCount(); ++i) {
        const T& item = *list.get(i);
        if (pred(item)) {
            out << item << "\n";
            ++found;
        }
    }
    return found;
}
