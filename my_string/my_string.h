#pragma once
#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;

class My_String
{
    public:
        // 定义迭代器
        typedef  char* iterator;
        iterator begin()
        {
            return _str;
        }
        iterator end()
        {
            return _str + _size;
        }
        //构造函数
        My_String(const char *str = "")
        {
            _str = new char[strlen(str) + 1];
            strcpy(_str, str);
            _size = strlen(str);
            _capacity = strlen(str);
        }
        //拷贝构造函数
        My_String(const My_String &s)
        {
            _str = new char[strlen(s._str) + 1];
            strcpy(_str, s._str);
            _size = strlen(s._str);
            _capacity = strlen(s._str);
        }
        //析构函数
        ~My_String()
        {
            delete[] _str;
            _str = nullptr; //不要忘记置空
            _size = 0;
            _capacity = 0;
        }
        // =操作符重载
        My_String& operator=(const My_String &s)
        {
            char *tmp = new char[strlen(s._str) + 1];
            strcpy(tmp, s._str);
            delete[] _str;
            _str = tmp;
            _size = strlen(s._str);
            _capacity = strlen(s._str);

            return *this;
        }
        // []操作符重载
        char& operator[](size_t i)
        {
            assert(0 <= i && i < _size);
            return _str[i];
        }
        const char& operator[](size_t i) const
        {
            assert(0 <= i && i < _size);
            return _str[i];
        }
        // += 操作符重载
        My_String& operator+=(const char ch)
        {
            push_back(ch);

            return *this;
        }
        My_String& operator+=(const char *s)
        {
            append(s);

            return *this;
        }
        // 返回有效数据个数
        size_t size() const
        {
            return _size;
        }
        // 返回可容纳有效数据个数
        size_t capacity() const
        {
            return _capacity;
        }
        // 返回首字符指针
        char* c_str()
        {
            return _str;
        }
        // 末尾追加单个字符
        void push_back(const char ch)
        {
            if (_size == _capacity)
            {
                ZengRong();
            }
            _str[_size] = ch;
            _size++;
            _str[_size] = '\0';
        }
        // 末尾追加字符串
        void append(const char *s)
        {
            if (strlen(s) + _size > _capacity)
            {
                int newcapacity = strlen(s) + _size;
                _capacity = newcapacity;
                char *tmp = new char[_capacity + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
            }
            strcpy(_str + _size, s);
            _size += strlen(s);
        }
        // 判断是否需要增容
        void ZengRong()
        {
            int newcapacity = (_capacity == 0 ? 2 : 2 * _capacity);
            _capacity = newcapacity;
            char *tmp = new char[_capacity + 1];
            strcpy(tmp, _str);
            delete[] _str;
            _str = tmp;
        }
        // 插入字符
        My_String& insert(size_t pos, char ch)
        {
            assert(pos <= _size);
            if (_size == _capacity)
            {
                ZengRong();
            }
            for(int i = (int)_size; i >= (int)pos; i--)
            {
                _str[i + 1] = _str[i];
            }
            _str[pos] = ch;
            _size++;

            return *this;
        }
        // 插入字符串
        My_String& insert(size_t pos, const char *s)
        {
            assert(pos <= _size);
            size_t len = strlen(s);
            if (len + _size > _capacity)
            {
                int newcapacity = len + _size;
                _capacity = newcapacity;
                char *tmp = new char[newcapacity + 1];
                strcpy(tmp, _str);
                delete[] _str;
                _str = tmp;
            }

            for (int i = (int)_size; i >= (int)pos; i--)
            {
                _str[len + i] = _str[i];
            }
            int index = 0;
            for (int i = (int)pos; i < (int)pos + (int)len; i++)
            {
                _str[i] = s[index];
                index++;
            }

            _size += len;

            return *this;
        }

        void resize(size_t n, char ch = '\0')
        {
            if (n <= _size)
            {
                _size = n;
                _str[_size] = '\0';
            }
            else
            {
                if (_capacity < n)
                {
                    _capacity = n;
                    char *tmp = new char[_capacity + 1];
                    strcpy(tmp, _str);
                    delete[] _str;
                    _str = tmp;
                }
                for (int i = _size; i <= n - 1; i++)
                {
                    _str[i] = ch;
                }
                _size = n;
                _str[n] = '\0';
            }
        }

        void erase(size_t pos, size_t len = npos)
        {
            assert(0 <= pos && pos < _size);
            if (len == npos)
            {
                _size = pos;
                _str[_size] = '\0';
            }
            else if (pos + len >= _size)
            {
                _size = pos;
                _str[_size] = '\0';
            }
            else
            {
                for (int i = pos + len; i < _size; i++)
                {
                    _str[i - len] = _str[i];
                }
                _size -= len;
                _str[_size] = '\0';
            }
        }

        size_t find(char ch, size_t pos = 0)
        {
            assert(pos < _size);
            while(pos < _size)
            {
                if (_str[pos] == ch)
                {
                    return pos;
                }
                pos++;
            }

            return -1;
        }
        size_t find(const char *str, size_t pos = 0)
        {
            // assert(pos < _size);
            // while(pos < _size)
            // {
            //     int i = pos;
            //     int j = 0;
            //     while(_str[i] && str[j])
            //     {
            //         if (_str[i] != str[j])
            //         {
            //             break;
            //         }
            //         i++;
            //         j++;
            //     }
            //     if (str[j] == '\0')
            //     {
            //         return pos;
            //     }
            //     else if (_str[i] == '\0')
            //     {
            //         return -1;
            //     }
            //     pos++;
            // }

            // return -1;

            assert(pos < _size);
            char *ret = strstr(_str + pos, str);
            if (ret == nullptr)
            {
                return -1;
            }
            else
            {
                return ret - _str;
            }
        }
        bool operator<(const My_String &s)
        {
            int ret = strcmp(_str, s._str);
            if (ret < 0)
            {
                return true;
            }

            return false;
        }
        bool operator>(const My_String &s)
        {
            return !(*this <= s);
        }
        bool operator==(const My_String &s)
        {
            int ret = strcmp(_str, s._str);
            if (ret == 0)
            {
                return true;
            }

            return false;
        }
        bool operator!=(const My_String &s)
        {
            return !(*this == s);
        }
        bool operator<=(const My_String &s)
        {
            return (*this < s || *this == s);
        }
        bool operator>=(const My_String &s)
        {
            return !(*this < s);
        }

    private:
        char *_str;
        size_t _size;
        size_t _capacity;

        static size_t npos;
};

size_t My_String::npos = -1;

// << 操作符重载
ostream& operator<<(ostream &out, const My_String &s)
{
    for (int i = 0; i < s.size(); i++)
    {
        cout << s[i];
    }

    return out;
}
// >> 操作符重载
istream& operator>>(istream &in, My_String &s)
{
    while(1)
    {
        char ch;
        ch = in.get();
        if (ch == '\n')
        {
            break;
        }
        else
        {
            s += ch;
        }
    }

    return in;
}