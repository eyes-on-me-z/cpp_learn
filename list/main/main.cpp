#include "list.h"

void print_list(const my_list<int>& l)
{
    my_list<int>::const_iterator it = l.begin();
    while(it != l.end())
    {
        cout << *it << ' ';
        ++it;
    }
    cout << endl;
}

void Test1()
{
    my_list<int> l1;
    l1.push_back(0);
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    print_list(l1);

    l1.pop_back();
    l1.pop_back();
    l1.pop_back();
    print_list(l1);

    l1.push_front(10);
    l1.push_front(9);
    l1.push_front(8);
    l1.push_front(7);
    print_list(l1);
 
    l1.pop_front();
    l1.pop_front();
    l1.pop_front();
    print_list(l1);
}

void Test2()
{
    my_list<int> lt1;
    lt1.push_back(1);
    lt1.push_back(2);
    lt1.push_back(3);
    lt1.push_back(4);
    lt1.push_back(5);
    print_list(lt1);

    my_list<int> lt2(lt1);
    print_list(lt2);

    lt2.insert(lt2.end(), 6);
    lt2.insert(lt2.end(), 7);
    lt2.insert(lt2.end(), 8);
    lt2.insert(lt2.end(), 9);
    print_list(lt2);


}

int main()
{
    // Test1();
    Test2();
    return 0;
}   