#pragma once
#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
struct __list_node
{
    __list_node<T>* _prev;
    __list_node<T>* _next;
    T _data;

    __list_node(const T& val = T())
                : _prev(nullptr)
                , _next(nullptr)
                , _data(val)
    {}
};

template <class T, class Ref, class Ptr>
struct __list_iterator
{
    typedef __list_node<T> Node;
    typedef __list_iterator<T, Ref, Ptr> Self;
    Node* _node;

    __list_iterator(Node* node)
                : _node(node)
    {}

    Ref operator*()
    {
        return _node->_data;
    }

    // 前置++
    Self& operator++()
    {
        _node = _node->_next;

        return *this;
    }

    // 后置++
    Self operator++(int)
    {
        Self ret = *this;
        _node = _node->_next;

        return ret;
    }

    // 前置--
    Self& operator--()
    {
        _node = _node->_prev;

        return *this;
    }

    // 后置--
    Self operator--(int)
    {
        Self ret = *this;
        _node = _node->_prev;

        return ret;
    }

    Ptr operator->()
    {
        return &_node->_data;
    }

    bool operator!=(const Self& it)
    {
        return _node != it._node;
    }
};

template <class T>
class my_list
{
    typedef __list_node<T> Node;
    
    public:
        typedef __list_iterator<T, T&, T*> iterator;
        typedef __list_iterator<T, const T&, const T*> const_iterator;

        // 构造函数
        my_list()
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }
 
        // 拷贝构造函数
        my_list(const my_list<T>& lt)
        {
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
            Node* cur = _head;
            Node* lt_cur = lt._head->_next;

            while(lt_cur != lt._head)
            {
                Node* tmp = new Node(lt_cur->_data);
                cur->_next = tmp;
                tmp->_prev = cur;
                tmp->_next = _head;
                _head->_prev = tmp;
 
                lt_cur = lt_cur->_next;
                cur = cur->_next;
            }
        }

        my_list<T>& operator=(my_list<T> lt)
        {
            swap(_head, lt._head);

            return *this;
        } 

        iterator begin()
        {
            return iterator(_head->_next);
        }
        const_iterator begin() const
        {
            return const_iterator(_head->_next);
        }

        iterator end()
        {
            return iterator(_head);
        }
        const_iterator end() const
        {
            return const_iterator(_head);
        }

        // 尾插
        void push_back(const T& val)
        {
            Node* newhead = new Node(val);
            Node* tail = _head->_prev;
            
            tail->_next = newhead;
            newhead->_prev = tail;
            newhead->_next = _head;
            _head->_prev = newhead;
        }

        // 尾删
        void pop_back()
        {
            assert(_head != _head->_next);
            Node* tail = _head->_prev->_prev;
            delete tail->_next;
            tail->_next = _head;
            _head->_prev = tail;
        }

        // 头插
        void push_front(const T& val)
        {
            Node* newnode = new Node(val);
            Node* second = _head->_next;

            _head->_next = newnode;
            newnode->_prev = _head;
            newnode->_next = second;
            second->_prev = newnode;
        }

        // 头删
        void pop_front()
        {
            assert(_head != _head->_next);
            Node* cur = _head->_next->_next;
            delete cur->_prev;
            _head->_next = cur;
            cur->_prev = _head;
        }

        void insert(iterator pos, const T& val)
        {
            Node* tmp = new Node(val);
            Node* next = pos._node;
            Node* prev = (--pos)._node;

            prev->_next = tmp;
            tmp->_prev = prev;
            tmp->_next = next;
            next->_prev = tmp;
        }

        void erase(iterator pos)
        {
            assert(pos != end());
            Node* prev = pos._node->_prev;
            Node* cur = pos._node;
            Node* next = pos._node->_next;

            delete cur;
            prev->_next = next;
            next->_prev = prev;
        }

        void clear()
        {
            iterator it = begin();
            while(it != end())
            {
                erase(it++);
            }
        }

        ~my_list()
        {
            clear();
            delete _head;
            _head = nullptr;
        }

    private:

        Node* _head;
};