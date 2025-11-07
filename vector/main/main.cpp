#include "vector.h"

void Test1()
{
    my_vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    my_vector<int>::iterator it = v1.begin();
    while(it != v1.end())
    {
        *it += 1;
        cout << *it << ' ';
        it++;
    }
    cout << endl;

    // for (auto& e : v1)
    // {
    //     e -= 1;
    //     cout << e << ' ';
    // }
    // cout << endl;

    // for (int i = 0; i < v1.size(); i++)
    // {
    //     cout << v1[i] << ' ';
    // }
    // cout << endl;

    // v1.pop_back();
    // for (int i = 0; i < v1.size(); i++)
    // {
    //     cout << v1[i] << ' ';
    // }
    // cout << endl;

    v1.insert(v1.end(), 5);
    v1.insert(v1.end(), 6);
    v1.insert(v1.end(), 7);
    v1.insert(v1.end(), 8);
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << ' ';
    }
    cout << endl;

    // my_vector<int>::iterator it1 = v1.begin();
    // while(it1 != v1.end())
    // {
    //     if (*it1 % 2 == 0)
    //     {
    //         it1 = v1.erase(it1);
    //     }
    //     else
    //     {
    //         it1++;
    //     }
    // }
    // for (int i = 0; i < v1.size(); i++)
    // {
    //     cout << v1[i] << ' ';
    // }
    // cout << endl;

    v1.resize(12, 1);
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << ' ';
    }
    cout << endl;

}

void Test2()
{
    my_vector<int> v1;
    v1.push_back(0);
    v1.push_back(1);
    v1.push_back(2);
    // v1.push_back(3);

    my_vector<int> v2(v1);
    cout << v2.size() << ' ' << v2.capacity() << endl;
    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << ' ';
    }
    cout << endl;

    my_vector<int> v3;
    v3 = v1;
    for (int i = 0; i < v3.size(); i++)
    {
        cout << v3[i] << ' ';
    }
    cout << endl;

}

int main()
{
    // Test1();
    Test2();
    return 0;
}