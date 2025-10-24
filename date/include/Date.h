#include <iostream>
 
using namespace std;


class Date
{
    public:
        //获取某年某月对应的天数
        int GetMonthDay(int year, int month) const;
        //构造函数
        Date(int year=1, int month=1, int day=1);
        //拷贝构造函数
        Date(const Date &d);
        //析构函数
        ~Date();
        //比较两个日期是否相等
        bool operator==(const Date &d) const;
        // d1 > d2 ?
        bool operator>(const Date &d) const;
        // d1 < d2 ?
        bool operator<(const Date &d) const;
        // d1 <= d2 ?
        bool operator<=(const Date &d) const;
        // d1 >= d2 ?
        bool operator>=(const Date &d) const;
        // d1 != d2 ?
        bool operator!=(const Date &d) const;
        // 日期加天数(不修改原日期)
        Date operator+(int day) const;
        // 日期加天数(修改原日期)
        Date& operator+=(int day);
        // 日期减天数(不修改原日期)
        Date operator-(int day) const;
        // 日期减天数(修改原日期)
        Date& operator-=(int day);
        // 把d2赋值给d1
        Date& operator=(const Date &d);
        // ++d;
        Date& operator++();
        // d++
        Date operator++(int);
        // --d
        Date& operator--();
        //d--
        Date operator--(int);
        //日期减日期，返回两者相差天数
        int operator-(const Date &d) const;
        // &操作符重载
        Date* operator&();
        //const &操作符重载
        const Date* operator&() const;
        //打印日期信息
        void Print() const;

    private:
        int _year;
        int _month;
        int _day;

        // Time _t1;
};