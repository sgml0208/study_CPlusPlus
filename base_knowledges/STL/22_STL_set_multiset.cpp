/*
 * @Description:                    set / multiset 容器 : 集合
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 17:05:49
 * @LastEditTime: 2024-10-04 21:25:58
 */

/*
set/multiset属于关联式容器，底层结构是用二叉树实现。

所有元素都会在插入时自动被排序

set和multiset区别:
    set不允许容器中有重复的元素
    multiset允许容器中有重复的元素


*/

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
using namespace std;

template <class T>
void printSet(const set<T> &s)
{
    // 方法1:
    // for (typename set<T>::const_iterator it = s.begin(); it != s.end(); it++)
    //     cout << *it << " ";
    // cout << endl;

    // 方法2: 使用auto(c++11标准): auto关键字会自动推导出正确的迭代器类型
    for (auto it = s.begin(); it != s.end(); it++)
        cout << *it << " ";
    cout << endl;
}

template <class T>
void printMultiSet(const multiset<T> &s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        cout << *it << " ";
    cout << endl;
}

/*
构造和赋值：

*/
void test1()
{
    set<int> s1;

    // 插入数据只有insert方式
    s1.insert(12);
    s1.insert(5);
    s1.insert(167);
    s1.insert(76);
    s1.insert(76);
    s1.insert(9);
    s1.insert(5);

    printSet(s1); // 5 9 12 76 167   直接排好序和去重了

    multiset<int> ms1;
    // 插入数据只有insert方式
    ms1.insert(12);
    ms1.insert(5);
    ms1.insert(167);
    ms1.insert(76);
    ms1.insert(76);
    ms1.insert(9);
    ms1.insert(5);

    printMultiSet(ms1); // 5 5 9 12 76 76 167

    set<int> s2(s1);
    set<int> s3;
    s3 = s1;
    printSet(s2); // 5 9 12 76 167
    printSet(s3); // 5 9 12 76 167
}

/*
set大小和交换:
size();         返回容器中元素的数目
empty();        判断容器是否为空
swap(st);       交换两个集合容器
*/
void test2()
{
    set<int> s1;
    s1.insert(12);
    s1.insert(5);
    s1.insert(167);
    s1.insert(76);
    s1.insert(76);
    s1.insert(9);
    s1.insert(5);
    printSet(s1); // 5 9 12 76 167

    cout << "s1的大小为: " << s1.size() << endl; // s1的大小为: 5

    if (!s1.empty())
        cout << "s1不为空" << endl; // s1不为空

    set<int> s2;
    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    s2.insert(4);
    printSet(s2); // 1 2 3 4

    s1.swap(s2);
    printSet(s1); // 1 2 3 4
    printSet(s2); // 5 9 12 76 167
}

/*
set插入和删除, 查找和统计
insert(elem);       在容器中插入元素
clear();            清除所有元素
erase(pos);         删除pos迭代器所指的元素，返回下一个元素的迭代器
erase(beg, end);    删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器
erase(elem);        删除容器中值为elem的元素

find(key);          查找key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end()
count(key);         统计key的元素个数
*/
void test3()
{
    set<int> s1;
    s1.insert(1);
    s1.insert(2);
    s1.insert(3);
    s1.insert(4);
    printSet(s1); // 1 2 3 4

    s1.erase(2);
    printSet(s1); // 1 3 4

    set<int>::iterator pos = s1.find(3);
    if (pos != s1.end())
        cout << "找到元素: " << *pos << endl; // 找到元素: 3
    else
        cout << "未找到该元素" << endl;

    multiset<int> ms1;
    ms1.insert(12);
    ms1.insert(5);
    ms1.insert(167);
    ms1.insert(76);
    ms1.insert(76);
    ms1.insert(9);
    ms1.insert(5);
    int num = ms1.count(76);
    cout << num << endl; // 2
}

/*
set和multiset的区别:
set不可以插入重复数据，而multiset可以
set插入数据的同时会返回插入结果，表示插入是否成功
multiset不会检测数据，因此可以插入重复数据
*/
void test4()
{
    // 判断set插入是否成功
    set<int> s1;
    pair<set<int>::iterator, bool> ret = s1.insert(1);
    if (ret.second)                             // 取bool的结果
        cout << "第一次插入数据成功！" << endl; // 第一次插入数据成功！
    else
        cout << "第一次插入数据失败！" << endl;

    ret = s1.insert(1);
    if (ret.second) // 取bool的结果
        cout << "第二次插入数据成功！" << endl;
    else
        cout << "第二次插入数据失败！" << endl; // 第二次插入数据失败！ 所以set不允许插入重复的值

    multiset<int> ms1;
    ms1.insert(1);
    ms1.insert(1);
    printMultiSet(ms1); // 1 1    所以multiset允许插入重复的值
}

/*
set排序:
set容器默认排序规则为从小到大，掌握如何改变排序规则
主要技术点:
利用仿函数(本质是一个类型)，可以改变排序规则
*/
class MyCompare
{
public:
    bool operator()(int val1, int val2) const   // 重载了 ()
    {
        return val1 > val2;
    }
};

void test5()
{
    set<int> s1;
    s1.insert(12);
    s1.insert(5);
    s1.insert(167);
    s1.insert(76);
    s1.insert(76);
    s1.insert(9);
    s1.insert(5);
    printSet(s1); // 5 9 12 76 167

    // 指定排序规则为从大到小
    set<int, MyCompare> s2; // MyCompare为仿函数(本质是一个类型)，这里不能放函数名
    s2.insert(12);
    s2.insert(5);
    s2.insert(167);
    s2.insert(76);
    s2.insert(76);
    s2.insert(9);
    s2.insert(5);
    for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
        cout << *it << ' ';
    cout << endl; // 167 76 12 9 5
}

/*
set对自定义数据进行排序: 都会指定排序规则
*/
class Person
{
public:
    string m_name;
    int m_age;

    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }
};

class ComparePerson
{
public:
    bool operator()(const Person &p1, const Person &p2) const
    {
        return p1.m_age > p2.m_age;
    }
};

void test6()
{
    set<Person, ComparePerson> s1;
    Person p1("Tom", 12);
    Person p2("Jack", 14);
    Person p3("Bob", 13);
    Person p4("Alice", 11);
    Person p5("John", 12);

    s1.insert(p1);
    s1.insert(p2);
    s1.insert(p3);
    s1.insert(p4);
    s1.insert(p5);

    for (set<Person, ComparePerson>::iterator it = s1.begin(); it != s1.end(); it++)
        cout << "name: " << it->m_name << "   age: " << it->m_age << endl;
/*
name: Jack   age: 14
name: Bob   age: 13
name: Tom   age: 12
name: Alice   age: 11
*/
}

int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    test6();

    return 0;
}