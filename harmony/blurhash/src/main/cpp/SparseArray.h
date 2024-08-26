#ifndef SPARSEARRAY_H
#define SPARSEARRAY_H

#include <unordered_map>
#include <vector>

template <typename T>
class SparseArray {
private:
    std::unordered_map<int, T> data;

public:
    void set(int key, const T &value);
    T get(int key) const;
    void remove(int key);
    void clear();
    bool containsKey(int key) const;
};

#endif // SPARSEARRAY_H
