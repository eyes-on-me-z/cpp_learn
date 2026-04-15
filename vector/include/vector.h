#pragma once
#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
class my_vector
{
    public:
        typedef T* iterator;
        typedef const T* const_iterator;

    public:
 
        my_vector()
                : _start(nullptr)
                , _finish(nullptr)
                , _capacity(nullptr)
        {}

        // my_vector(const my_vector<T> &v)
        // {
        //     _start = new T[v.capacity()];
        //     memcpy(_start, v._start, sizeof(T) * (v.size()));
        //     _finish = _start + v.size();
        //     _capacity = _start + v.capacity();
        // }
        my_vector(const my_vector<T> &v)
                : _start(nullptr)
                , _finish(nullptr)
                , _capacity(nullptr)
        {
            resize(v.capacity());
            _finish = _start;
            for (const auto &e : v)
            {
                *_finish = e;
                _finish++;
            }
        }

        ~my_vector()
        {
            delete[] _start;
            _start = nullptr;
            _finish = nullptr;
            _capacity = nullptr; 
        }

        // 尾插
        void push_back(T val)
        {
            size_t sz = size();
            size_t capa = capacity();
            if (sz == capa)
            {
                size_t newcapa = capa ? 2 * capa : 2;
                reserve(newcapa);
            }
            _start[sz] = val;
            _finish++;
        }

        // 尾删
        void pop_back()
        {
            assert(size());
            _finish--;
        }

        // 插入
        void insert(iterator pos, const T &val)
        {
            assert(_start <= pos && pos <= _finish);
            int len = pos - _start;
            int sz = size();
            int capa = capacity();
            if (sz == capa)
            {
                int newcapa = sz ? 2 * sz : 2;
                reserve(newcapa);
            }
            if (sz == len)
            {
                *_finish = val;
                _finish++;
                return;
            }
            while(sz > len)
            {
                _start[sz] = _start[sz - 1];
                sz--;
            }
            _start[sz] = val;
            _finish++;
        }

        // 擦除
        iterator erase(iterator pos)
        {
            iterator ret = pos;
            assert(_start <= pos && pos < _finish); 
            iterator tail = end() - 1;
            while(pos < tail)
            {
                *pos = *(pos + 1);
                pos++;
            }
            _finish--;

            return ret;
        }

        void resize(size_t n, const T &val = T())
        {
            assert(n >= 0);
            if (n <= size())
            {
                _finish = _start + n;
            }
            else
            {
                if (n > capacity())
                {
                    reserve(n);
                }
                while((_finish - _start) != n)
                {
                    *_finish = val;
                    _finish++;
                }
            }
        }

        // []操作符重载
        T& operator[](int i)
        {
            assert(i >= 0 && i < size());
            return _start[i];
        }
        const T& operator[](int i) const
        {
            assert(i >= 0 && i < size());
            return _start[i];
        }
        
        // =操作符重载
        my_vector<T>& operator=(my_vector<T> v)
        {
            swap(_start, v._start);
            swap(_finish, v._finish);
            swap(_capacity, v._capacity);

            return *this;
        }
        // my_vector<T>& operator=(const my_vector<T> &v)
        // {
        //     if (this != &v)
        //     {
        //         iterator tmp = new T[v.capacity()];
        //         memcpy(tmp, v._start, sizeof(T) * v.size());
        //         delete[] _start;
        //         _start = tmp;
        //         _finish = _start + v.size();
        //         _capacity = _start + v.capacity();
        //     }

        //     return *this;
        // }

        // 开n个空间，若空间足够则不开
        void reserve(size_t n)
        {
            if(n > capacity())
            {
                T *tmp = new T[n];
                size_t sz = size();
                if (_start)
                {
                    // memcpy(tmp, _start, sizeof(T) * sz); // 浅拷贝
                    for (int i = 0; i < sz; i ++)   // 深拷贝
                    {
                        tmp[i] = _start[i];
                    }
                    delete[] _start;
                }
                _start = tmp;
                _finish = _start + sz;
                _capacity = _start + n;
            }
        }

        // 返回begin()迭代器
        iterator begin()
        {
            return _start;
        }
        const_iterator begin() const
        {
            return _start;
        }

        // 返回end()迭代器
        iterator end()
        {
            return _finish;
        }
        const_iterator end() const
        {
            return _finish;
        }

        // 返回有效数据个数
        size_t size() const
        {
            return _finish - _start;
        }

        // 返回有效空间
        size_t capacity() const
        {
            return _capacity - _start;
        }

    private:

        iterator _start;
        iterator _finish;
        iterator _capacity;
};