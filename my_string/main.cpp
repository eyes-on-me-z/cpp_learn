// #include "my_string.h"

// void Test()
// {
//     My_String s1;
//     My_String s2("hello");
//     My_String s3(s2);
//     My_String s4;
//     s4 = s3;

//     cout << s1.c_str() << endl;
//     cout << s2.c_str() << endl;
//     cout << s3.c_str() << endl;
//     cout << s4.c_str() << endl;

//     for (int i = 0; i < s2.size(); i++)
//     {
//         s2[i] += 1;
//         cout << s2[i] << ' ';
//     }
//     cout << endl;

// }

// int main()
// {
//     Test();
//     return 0;
// }


#include "my_string.h"

void Test()
{
    My_String s1;
    My_String s2("hello");
    My_String s3;
    My_String s4(s2);
    s1 = s3 = s2;

    for (int i = 0; i < s1.size(); i++)
    {
        s1[i] += 1;
        cout << s1[i] << ' ';
    }
    cout << endl;

    s2 += ' ';
    s2 += "world";

    cout << s2 << endl;
    cout << s2.c_str() << endl;

    s3.push_back(' ');
    s3.append("world");
    cout << s3.c_str() << endl;

    cout << s2 << s3 << endl;

    My_String::iterator it1 = s1.begin();
    while(it1 != s1.end())
    {
        cout << *it1 << ' ';
        it1++;
    }
    cout << endl;

    // 范围for是由迭代器支持的，也就是说，这段代码会被编译器替换成迭代器
    for (auto ch : s1)
    {
        cout << ch;
    }
    cout << endl;

    My_String s5("zeng");
    s5.insert(0, '-');
    s5.insert(5, '-');
    s5.insert(0, '-');

    s5.insert(7, "guang");
    cout << s5 << endl;

    My_String s6("chen");
    s6.insert(1, "mian");
    cout << s6 << endl;
    cout << s6.size() << ' ' << s6.capacity() << endl;

    s6.erase(1, 1);
    cout << s6 << endl;

}

void Test_1()
{
    My_String s1("zeng");
    s1.resize(2, 'h');
    cout << s1 << endl;
}

void Test_2()
{
    My_String s1("hello world");
    int n = s1.find("ell", 5);
    cout << n << endl;

    My_String s2;
    cin >> s2;
    cout << s2 << endl;
}


int main()
{
    // Test();
    // Test_1();
    Test_2();
    return 0;
}