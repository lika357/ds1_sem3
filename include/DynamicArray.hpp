#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "UniquePtr.hpp"

template <typename T>
class DynamicArray
{
   private:
    UniquePtr<T[]> data_;
    size_t size_;

   public:
    DynamicArray() : data_(), size_(0)
    {
    }

    explicit DynamicArray(size_t n) : data_(nullptr), size_(n)
    {
        if (n > 0)
        {
            data_.reset(new T[n]());
        }
    }

    DynamicArray(const DynamicArray& other) : DynamicArray(other.size_)
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    DynamicArray(DynamicArray&& other) noexcept : data_(std::move(other.data_)), size_(other.size_)
    {
        other.size_ = 0;
    }

    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this != &other)
        {
            DynamicArray tmp(other);
            swap(tmp);
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        if (this != &other)
        {
            data_ = std::move(other.data_);
            size_ = other.size_;
            other.size_ = 0;
        }
        return *this;
    }

    void swap(DynamicArray& other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
    }

    T& operator[](size_t index)
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const
    {
        if (index >= size_)
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    size_t GetSize() const
    {
        return size_;
    }

    void Resize(size_t new_size)
    {
        if (new_size == size_)
        {
            return;
        }
        DynamicArray tmp(new_size);
        size_t count;
        if (size_ < new_size)
        {
            count = size_;
        }
        else
        {
            count = new_size;
        }
        for (size_t i = 0; i < count; ++i)
        {
            tmp.data_[i] = std::move(data_[i]);
        }
        swap(tmp);
    }
};