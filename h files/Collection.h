#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

template <typename T>
class Collection {
private:
    static constexpr std::size_t START_CAPACITY = 4;

    std::unique_ptr<std::unique_ptr<T>[]> data = std::make_unique<std::unique_ptr<T>[]>(START_CAPACITY);
    std::size_t count = 0;
    std::size_t capacity = START_CAPACITY;

    void grow();

public:
    Collection() = default;

    Collection(const Collection&) = delete;
    Collection& operator=(const Collection&) = delete;

    bool add(std::unique_ptr<T> item);
    bool removeAt(int index);
    T* get(int index) const;

    template <typename Predicate>
    int findIndex(Predicate pred) const;

    int getCount() const;
    void clear();
    void print(std::ostream& out) const;
};

template <typename T>
void Collection<T>::grow() {
    std::size_t newCapacity = capacity * 2;
    auto newData = std::make_unique<std::unique_ptr<T>[]>(newCapacity);
    for (std::size_t i = 0; i < count; ++i) {
        newData[i] = std::move(data[i]);
    }
    data = std::move(newData);
    capacity = newCapacity;
}

template <typename T>
bool Collection<T>::add(std::unique_ptr<T> item) {
    if (item == nullptr) return false;
    if (count == capacity) {
        grow();
    }
    data[count] = std::move(item);
    ++count;
    return true;
}

template <typename T>
bool Collection<T>::removeAt(int index) {
    if (index < 0 || static_cast<std::size_t>(index) >= count) return false;
    auto position = static_cast<std::size_t>(index);
    data[position].reset();
    for (std::size_t i = position; i + 1 < count; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --count;
    return true;
}

template <typename T>
T* Collection<T>::get(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= count) return nullptr;
    return data[static_cast<std::size_t>(index)].get();
}

template <typename T>
template <typename Predicate>
int Collection<T>::findIndex(Predicate pred) const {
    for (std::size_t i = 0; i < count; ++i) {
        if (pred(*data[i])) return static_cast<int>(i);
    }
    return -1;
}

template <typename T>
int Collection<T>::getCount() const { return static_cast<int>(count); }

template <typename T>
void Collection<T>::clear() {
    data = std::make_unique<std::unique_ptr<T>[]>(START_CAPACITY);
    capacity = START_CAPACITY;
    count = 0;
}

template <typename T>
void Collection<T>::print(std::ostream& out) const {
    if (count == 0) {
        out << "(коллекция пуста)\n";
        return;
    }
    for (std::size_t i = 0; i < count; ++i) {
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