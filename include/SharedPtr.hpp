#pragma once

#include <cstddef>
#include <utility>

template <typename T>
class SharedPtr
{
   private:
    T* ptr_;
    size_t* count_;

    void Drop()
    {
        if (count_ != nullptr)
        {
            --(*count_);
            if (*count_ == 0)
            {
                delete ptr_;
                delete count_;
            }
        }
    }

   public:
    explicit SharedPtr(T* p = nullptr) : ptr_(p), count_(nullptr)
    {
        if (p != nullptr)
        {
            try
            {
                count_ = new size_t(1);
            }
            catch (...)
            {
                delete p;
                throw;
            }
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_)
    {
        if (count_ != nullptr)
        {
            ++(*count_);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_)
    {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            Drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_ != nullptr)
            {
                ++(*count_);
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            Drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr()
    {
        Drop();
    }

    void swap(SharedPtr& other) noexcept
    {
        std::swap(ptr_, other.ptr_);
        std::swap(count_, other.count_);
    }

    void reset(T* p = nullptr)
    {
        if (p == ptr_)
        {
            return;
        }
        SharedPtr tmp(p);
        swap(tmp);
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

    size_t use_count() const
    {
        return count_ != nullptr ? *count_ : 0;
    }
};

template <typename T>
class SharedPtr<T[]>
{
   private:
    T* ptr_;
    size_t* count_;

    void Drop()
    {
        if (count_ != nullptr)
        {
            --(*count_);
            if (*count_ == 0)
            {
                delete[] ptr_;
                delete count_;
            }
        }
    }

   public:
    explicit SharedPtr(T* p = nullptr) : ptr_(p), count_(nullptr)
    {
        if (p != nullptr)
        {
            try
            {
                count_ = new size_t(1);
            }
            catch (...)
            {
                delete[] p;
                throw;
            }
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_)
    {
        if (count_ != nullptr)
        {
            ++(*count_);
        }
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_)
    {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            Drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_ != nullptr)
            {
                ++(*count_);
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            Drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
        return *this;
    }

    ~SharedPtr()
    {
        Drop();
    }

    void swap(SharedPtr& other) noexcept
    {
        std::swap(ptr_, other.ptr_);
        std::swap(count_, other.count_);
    }

    void reset(T* p = nullptr)
    {
        if (p == ptr_)
        {
            return;
        }
        SharedPtr tmp(p);
        swap(tmp);
    }

    T& operator[](size_t i) const
    {
        return ptr_[i];
    }

    T* get() const
    {
        return ptr_;
    }

    size_t use_count() const
    {
        if (count_ == nullptr)
        {
            return 0;
        }
        return *count_;
    }
};