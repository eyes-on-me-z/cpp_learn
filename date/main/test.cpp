#include "Date.h"

// // namespace N
// // {
// //     int a = 0;
// //     int b = 1;

// //     int Add(int a, int b)
// //     {
// //         return a + b;
// //     }
    
// //     struct Node
// //     {
// //         int val;
// //         struct Node *_next;
// //     };

// // }

// // using N::b;
// // using namespace N;

// // int main()
// // {
// //     std::cout << N::a << std::endl;
// //     // cout << b << endl;
// //     // cout << Add(a, b) << endl;
// //     return 0;
// // }

// #include <typeinfo>

// void Swap(int &a, int &b)
// {
//     int tmp = a;
//     a = b;
//     b = tmp;
// }

// int main()
// {
//     // int a = 10;
//     // int *p = &a;
//     // *p = 20;
//     // int& ra = a;
//     // cout << a << endl << ra << endl;

//     // int i = 0;
//     // double b = i;
//     // const double& di = i;

//     // cout << typeid(i).name() << endl;
//     // cout << typeid(b).name() << endl;

//     int a = 10;
//     int b = 20;
//     Swap(a, b);
//     cout << a << ' ' << b << endl;

//     return 0; 
// }

// class Stack
// {
//     public:
//         Stack(int n = 10)
//         {
//             _a = (int*)malloc(sizeof(int) * n);
//             _size = 0;
//             _capacity = n;
//         }

//         ~Stack()
//         {
//             free(_a);
//             _a = NULL;
//             _size = 0;
//             _capacity = 0;
//         }

//     private:
//         int *_a;
//         int _size;
//         int _capacity;
// };




// class Time
// {
//     public:
//         Time()
//         {
//             _hour = 0;
//             _minute = 0;
//             _second = 0;
//         }

//     private:
//         int _hour;
//         int _minute;
//         int _second;
// };



// class Stack
// {
//     public:
//         Stack(int n = 10)
//         {
//             _a = (int*)malloc(sizeof(int) * n);
//             _size = 0;
//             _capacity = n;
//         }

//         ~Stack()
//         {
//             free(_a);
//             _a = NULL;
//             _size = 0;
//             _capacity = 0;
//         }

//     private:
//         int *_a;
//         int _size;
//         int _capacity;
// };

void func(const Date &d)
{
    d.Print();
}

int main()
{
    // Date d1(2025, 10, 18);
    // d1.Init(2025, 10, 17);
    // d1.Print(); 

    // Date d2;
    // d2.Print();

    // Date d3(d1);
    // d3.Print();
 
    // Stack s1;
    // Stack s2;

    // Date d4 = d1 + 300;
    // d4.Print();
    // d1.Print(); 

    // d1 += 300;
    // d1.Print();

    // cout << (d1 == d2) << endl;
    // cout << d1.operator==(d2) << endl;
    // cout << (d1 > d2) << endl;

    // Date d1(2025, 10, 18);
    // d1.Print();

    // Date d2(d1 - 200);
    // d2.Print();
    // d1.Print();

    // d1 -= 200;
    // d1.Print();

    // Date d3;
    // d3 = d1;

    // d1 = d3 = d2; 
    // d1.Print();
    // d2.Print();
    // d3.Print();


    // Stack st1;
    // Stack st2(st1);
    
    // Stack st3(30);
    // st3 = st1;

    Date d1(2025, 10, 19);
    d1.Print();

    func(d1);

    // Date d2 = d1--;
    // d2.Print();

    // Date d3 = --d1;
    // d3.Print();

    Date d4(2024, 10, 19);
    
    int day = d1 - d4;
    cout << day << endl;

    cout << &d1 << endl;
    cout << &d4 << endl;

    return 0;
}