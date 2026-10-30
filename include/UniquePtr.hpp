#pragma once

#include <cstddef>

template <typename T>
class UniquePtr
{
   private:
    T* ptr_;

   public:
    explicit UniquePtr(T* p = nullptr) : ptr_(p)
    {
    }

    ~UniquePtr()
    {
        delete ptr_;
    }

    UniquePtr(const UniquePtr&) = delete;

    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() const
    {
        return *ptr_;
    }

    T* operator->() const
    {
        return ptr_;
    }

    T* get() const
    {
        return ptr_;
    }

    T* release()
    {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* p = nullptr)
    {
        if (ptr_ != p)
        {
            delete ptr_;
            ptr_ = p;
        }
    }
};

template <typename T>
class UniquePtr<T[]>
{
   private:
    T* ptr_;

   public:
    explicit UniquePtr(T* p = nullptr) : ptr_(p)
    {
    }

    ~UniquePtr()
    {
        delete[] ptr_;
    }

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_)
    {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept
    {
        if (this != &other)
        {
            delete[] ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator[](size_t i) const
    {
        return ptr_[i];
    }

    T* get() const
    {
        return ptr_;
    }

    T* release()
    {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* p = nullptr)
    {
        if (ptr_ != p)
        {
            delete[] ptr_;
            ptr_ = p;
        }
    }
};