#ifndef __MYVECTOR_H__
#define __MYVECTOR_H__

#include <utility>
#include <vector>

template <typename DataType>
class MyVector {
private:
    size_t theSize;                         // Current size of the vector
    size_t theCapacity;                     // Current capacity of the vector
    DataType* data;                         // Pointer to the dynamically allocated array

public:
    static const size_t SPARE_CAPACITY = 16;   // Default spare capacity for resizing

    // Default constructor with optional initial size
    explicit MyVector(size_t initSize = 0) : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY} {
        data = new DataType[theCapacity];
    }

    // Copy constructor
    MyVector(const MyVector& rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, data{nullptr} {
        data = new DataType[theCapacity];
        for (int k = 0; k < theSize; ++k) {
            data[k] = rhs.data[k];
        }
    }

    // Move constructor
    MyVector(MyVector&& rhs) : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, data{rhs.data} {
        rhs.data = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    // Constructor from std::vector
    MyVector(const std::vector<DataType>& rhs) : theSize{rhs.size()}, theCapacity{rhs.size() + SPARE_CAPACITY}, data{new DataType[theCapacity]} {
        for (int k = 0; k < theSize; ++k) {
            data[k] = rhs[k];
        }
    }

    // Destructor
    ~MyVector() {
        delete[] data;
    };

    // Copy assignment operator
    MyVector& operator=(const MyVector& rhs) {
        MyVector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    // Move assignment operator
    MyVector& operator=(MyVector&& rhs) {
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        std::swap(data, rhs.data);
    }

    // Resize the vector to the given size
    void resize(size_t newSize) {
        if (newSize > theCapacity) {
            reserve(newSize * 2);
        }
        theSize = newSize;
    }

    // Reserve capacity for the vector
    void reserve(size_t newCapacity) {
        if (newCapacity < theSize) {
            return;
        }
        DataType* newArray = new DataType[newCapacity];
        for (int k = 0; k < theSize; ++k) {
            newArray[k] = std::move(data[k]);
        }
        theCapacity = newCapacity;
        std::swap(data, newArray);
        delete[] newArray;
    }

    // Access element at the specified index (non-const version)
    DataType& operator[](size_t index) {
        return data[index];
    }

    // Access element at the specified index (const version)
    const DataType& operator[](size_t index) const {
        return data[index];
    }

    // Check if the vector is empty
    bool empty() const {
        return size() == 0;
    }

    // Get the current size of the vector
    size_t size() const {
        return theSize;
    }

    // Get the current capacity of the vector
    size_t capacity() const {
        return theCapacity;
    }

    // Add an element to the end of the vector (const and non-const versions)
    void push_back(const DataType& x) {
        if (theSize == theCapacity) {
            reserve(2 * theCapacity + 1);
        }
        data[theSize++] = x;
    }

    void push_back(DataType&& x) {
        if (theSize == theCapacity) {
            reserve(2 * theCapacity + 1);
        }
        data[theSize++] = std::move(x);
    }

    // Append the contents of another vector to this vector
    MyVector<DataType>& append(MyVector<DataType>&& rhs) {
        if (theSize + rhs.size() > theCapacity) {
            reserve(theSize + rhs.size());
        }
        for (int k = 0; k < rhs.size(); ++k) {
            data[theSize + k] = std::move(rhs[k]);
        }
        theSize += rhs.size();
        rhs.theSize = 0;
        rhs.theCapacity = 0;
        rhs.data = nullptr;
        return *this;
    }

    // Remove the last element from the vector
    void pop_back() {
        --theSize;
    }

    // Access the last element of the vector (const version)
    const DataType& back() const {
        return data[theSize - 1];
    }

    // Iterator types
    typedef DataType* iterator;
    typedef const DataType* const_iterator;

    // Iterator pointing to the first element (non-const and const versions)
    iterator begin() {
        return &data[0];
    }

    const_iterator begin() const {
        return &data[0];
    }

    // Iterator pointing past the last element (non-const and const versions)
    iterator end() {
        return &data[size()];
    }

    const_iterator end() const {
        return &data[size()];
    }
};

#endif
