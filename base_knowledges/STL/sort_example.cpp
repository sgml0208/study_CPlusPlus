/*
 * @Description:                    排序案例
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 16:47:17
 * @LastEditTime: 2024-10-04 17:01:14
 */

/*
list容器排序案例 对于自定义数据类型做排序:
按照年龄进行升序，如果年龄相同按照身高进行降序
*/

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

class Person
{
public:
    string m_name;
    int m_age;
    int m_height;

    Person(string name, int age, int height)
    {
        this->m_name = name;
        this->m_age = age;
        this->m_height = height;
    }
};

void printList(const list<Person> &l)
{
    for (auto it = l.begin(); it != l.end(); it++)
        cout << "name: " << (*it).m_name << "\tage: " << it->m_age << "\t\theight: " << it->m_height << endl;
}

// 指定排序规则
bool mySort(Person &p1, Person &p2)
{
    if (p1.m_age < p2.m_age)
        return true;
    else if (p1.m_age == p2.m_age)
    {
        if (p1.m_height >= p2.m_height)
            return true;
        else
            return false;    
    }
    else
        return false;
}

void test()
{
    list<Person> l;

    Person p1("Tom", 12, 175);
    Person p2("Jack", 14, 168);
    Person p3("Bob", 13, 172);
    Person p4("Alice", 11, 160);
    Person p5("John", 12, 166);
    Person p6("Linda", 14, 158);
    Person p7("Jim", 13, 165);

    l.push_back(p1);
    l.push_back(p2);
    l.push_back(p3);
    l.push_back(p4);
    l.push_back(p5);
    l.push_back(p6);
    l.push_back(p7);

    cout << "排序前: " << endl;
    printList(l);

    cout << endl
         << "排序后: " << endl;

    l.sort(mySort);
    printList(l);
}

int main()
{
    test();

    return 0;
}

/*
排序前: 
name: Tom       age: 12         height: 175
name: Jack      age: 14         height: 168
name: Bob       age: 13         height: 172
name: Alice     age: 11         height: 160
name: John      age: 12         height: 166
name: Linda     age: 14         height: 158
name: Jim       age: 13         height: 165

排序后: 
name: Alice     age: 11         height: 160
name: Tom       age: 12         height: 175
name: John      age: 12         height: 166
name: Bob       age: 13         height: 172
name: Jim       age: 13         height: 165
name: Jack      age: 14         height: 168
name: Linda     age: 14         height: 158
*/