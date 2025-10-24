#include "Date.h"


int Date::GetMonthDay(int year, int month) const
{
    static int MonthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
    {
        return 29;
    }
    
    return MonthDays[month];
}

Date::Date(int year, int month, int day)
{
    if (year >= 1 && month >= 1 && month <= 12 && day >= 1 && day <= GetMonthDay(year, month))
    {
        _year = year;
        _month = month;
        _day = day;
    }
    else 
    {
        cout << "非法日期" << endl;
    }
}

Date::Date(const Date &d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;
}

Date::~Date()
{
    cout << "~Date" << endl;
}

bool Date::operator==(const Date &d) const
{
    return _year == d._year
        && _month == d._month
        && _day == d._day;
}
bool Date::operator>(const Date &d) const
{
    if (_year > d._year)
        return true;
    else if (_year == d._year && _month > d._month)
        return true;
    else if (_year == d._year && _month == d._month && _day > d._day)
        return true;
    else 
        return false;
}
bool Date::operator<(const Date &d) const
{
    return !(*this > d || *this == d);
}
bool Date::operator<=(const Date &d) const
{
    return !(*this > d);
}
bool Date::operator>=(const Date &d) const
{
    return !(*this < d);
}
bool Date::operator!=(const Date &d) const
{
    return !(*this == d);
}
Date Date::operator+(int day) const
{
    // Date ret(*this);
    // int total = ret._day + day;
    // while(total > ret.GetMonthDay(ret._year, ret._month))
    // {
    //     total -= ret.GetMonthDay(ret._year, ret._month);
    //     if (ret._month == 12)
    //     {
    //         ret._year += 1;
    //         ret._month = 1;
    //     }
    //     else
    //     {
    //         ret._month += 1;
    //     }
    // }
    // ret._day = total;

    // return ret;

    Date ret = *this;
    ret += day;
        
    return ret;
}
Date& Date::operator+=(int day)
{
    if (day < 0)
    {
        return *this -= (-day);
    }
    int total = _day + day;
    while(total > GetMonthDay(this->_year, this->_month))
    {
        total -= GetMonthDay(this->_year, this->_month);
        if (_month == 12)
        {
            _year += 1;
            _month = 1;
        }
        else
        {
            _month += 1;
        }
    }
    _day = total;

    return *this;
}
Date Date::operator-(int day) const
{
    // Date ret(*this);
    // int total = ret._day - day;
    // while(total <= 0)
    // {
    //     total += GetMonthDay(ret._year, ret._month > 1 ? ret._month - 1 : 12);
    //     ret._month--;
    //     if (ret._month == 0)
    //     {
    //         ret._year--;
    //         ret._month = 12;
    //     }
    // }
    // ret._day = total;

    // return ret;

    Date ret = *this;
    ret -= day;

    return ret;
}
Date& Date::operator-=(int day)
{
    if (day < 0)
    {
        return *this += (-day);
    }
    int total = _day - day;
    while(total <= 0)
    {
        total += GetMonthDay(_year, _month > 1 ? _month - 1 : 12);
        _month--;
        if (_month == 0)
        {
            _year--;
            _month = 12;
        }
    }
    _day = total;

    return *this; 
}
Date& Date::operator=(const Date &d)
{
    _year = d._year;
    _month = d._month;
    _day = d._day;

    return *this;
}
// ++d;
Date& Date::operator++()
{
    *this += 1;

    return *this;
}
// d++
Date Date::operator++(int)
{
    Date ret = *this;
    *this += 1;

    return ret;
}
// --d
Date& Date::operator--()
{
    *this -= 1;

    return *this;
}
//d--
Date Date::operator--(int)
{
    Date ret = *this;
    *this -= 1;

    return ret;
}
int Date::operator-(const Date &d) const
{
    int total = 0;
    int logo = 1;
    Date max = *this;
    Date min = d;
    if (max < min)
    {
        max = d;
        min = *this;
        logo = -1;
    }

    while(min < max)
    {
        ++min;
        total++;
    }

    return total * logo;
}
Date* Date::operator&()
{
    return this;
}
const Date* Date::operator&() const
{
    return this;
}

void Date::Print() const
{
    cout << _year << '-' << _month << '-' << _day << endl;
}