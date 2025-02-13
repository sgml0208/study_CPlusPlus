/*
 * @Description:                    STL常用算法
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-05 10:40:41
 * @LastEditTime: 2025-02-13 15:21:35
 */

/*
算法主要是由头文件<algorithm> <functional> <numeric>组成
<algorithm>是所有STL头文件中最大的一个，范围涉及到比较、 交换、查找、遍历操作、复制、修改等等
<numeric>体积很小，只包括几个在序列上面进行简单数学运算的模板函数
<functional>定义了一些模板类,用以声明函数对象。

常用算法有：
*/

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <numeric> // 算数生成算法
#include <algorithm>
#include <functional> // 使用内建函数对象
using namespace std;

/*
常用遍历算法:
for_each          遍历容器              用于容器中的每一个元素
transform         搬运容器到另一个容器中

for each(iterator beg,iterator end,func);  用于遍历算法 遍历容器元素
beg 开始迭代器
end 结束迭代器
func 函数或者函数对象

transform(iterator beg1, iterator end1, iterator beg2, _func);
beg1 源容器开始迭代器
end1 源容器结束迭代器
beg2 目标容器开始迭代器
_func 函数或者函数对象
*/
void printElement(int element)
{
    cout << element << " ";
}

// 仿函数
class MyPrint
{
public:
    void operator()(int val)
    {
        cout << val << ' ';
    }
};

class MyTransform
{
public:
    int operator()(int val)
    {
        return val + 100;
    }
};

void test1()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    // ------------for_each------------
    for_each(v.begin(), v.end(), printElement); // 0 1 2 3 4 5 6 7 8 9   第三个参数是处理单个元素的函数
    cout << endl;
    for_each(v.begin(), v.end(), MyPrint()); // 0 1 2 3 4 5 6 7 8 9
    cout << endl;

    // ------------transform------------
    vector<int> v2;
    v2.resize(v.size()); // 需要提前申请开辟空间 ！！！
    transform(v.begin(), v.end(), v2.begin(), MyTransform());
    for_each(v2.begin(), v2.end(), MyPrint()); // 100 101 102 103 104 105 106 107 108 109
    cout << endl;
}

/*
查找算法：
find(iterator beg, iterator end, value);        查找指定元素，找到返回指定元素的迭代器，找不到返回结束迭代器end()
find_if(iterator beg, iterator end, _Pred);     按条件查找元素
adjacent_find(iterator beg, iterator end);      查找相邻重复元素,返回相邻元素的第一个位置的迭代器，没找到返回结束迭代器end()
binary_search(iterator beg,iterator end, value); 二分查找法查找指定的元素，查到返回true 否则false
count(iterator beg,iterator end, value);        统计元素个数
count_if(iterator beg,iterator end,Pred);       按条件统计元素个数
*/
template <class T>
void printVector(const vector<T> &v)
{
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); it++) // v1.begin()指向v1的第一个元素，v1.end()指向v1的最后一个元素的下一个位置
        cout << *it << " ";
    cout << endl;
}

class Person // 自定义类型数据
{
public:
    string m_name;
    int m_age;
    Person() {};
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    bool operator==(const Person &p) // 查找自定义类型数据时需要重载==，不然下面案例find函数底层不知如何去对比Person数据类型
    {
        if (this->m_name == p.m_name && this->m_age == p.m_age)
            return true;
        else
            return false;
    }
};

class GreaterThan5
{
public:
    bool operator()(int val) // 一元谓词(一个参数)
    {
        return val > 5;
    }
};

class GreaterThan12
{
public:
    bool operator()(const Person &p) // 一元谓词(一个参数)
    {
        return p.m_age > 12;
    }
};

void test2()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);
    v.push_back(9);
    v.push_back(9);
    printVector(v); // 0 1 2 3 4 5 6 7 8 9 9 9

    // ------------find------------
    vector<int>::iterator pos1 = find(v.begin(), v.end(), 5);
    if (pos1 != v.end())
        cout << "找到了" << endl; // 找到了
    else
        cout << "没找到" << endl;

    vector<Person> p;
    Person p1("Tom", 12);
    Person p2("Bob", 13);
    Person p3("Jack", 14);
    Person p4("Alice", 15);
    Person p5("John", 11);

    p.push_back(p1);
    p.push_back(p2);
    p.push_back(p3);
    p.push_back(p4);
    p.push_back(p5);

    Person p6("Bob", 13);
    vector<Person>::iterator pos2 = find(p.begin(), p.end(), p5); // 看容器p中有没有p5这个人
    if (pos2 == p.end())
        cout << "没找到" << endl;
    else
        cout << "找到了" << endl;  // 找到了

    // ------------find_if------------
    vector<int>::iterator pos3 = find_if(v.begin(), v.end(), GreaterThan5());
    if (pos3 == v.end())
        cout << "没找到" << endl;
    else
        cout << "找到了" << endl;  // 找到了
    vector<Person>::iterator pos4 = find_if(p.begin(), p.end(), GreaterThan12()); // 看容器p中有没有age>12的人
    if (pos4 == p.end())
        cout << "没找到" << endl;
    else
        cout << "找到了" << endl;  // 找到了

    // ------------adjacent_find------------
    vector<int>::iterator pos5 = adjacent_find(v.begin(), v.end());
    if (pos5 == v.end())
        cout << "没找到" << endl;
    else
        cout << "找到了，第一个重复元素为 " << *pos5 << endl; // 找到了，第一个重复元素为 9

    // ------------binary_search(在无序序列中不可用)------------
    bool flag = binary_search(v.begin(), v.end(), 4);
    if (!flag)
        cout << "没找到" << endl;
    else
        cout << "找到了元素4" << endl; // 找到了元素4

    // ------------count------------
    int cnt1 = count(v.begin(), v.end(), 9);
    cout << "容器中9的个数为: " << cnt1 << endl; // 容器中9的个数为: 3

    // ------------count_if------------
    int cnt2 = count_if(v.begin(), v.end(), GreaterThan5());
    cout << "容器中大于5的数的个数为: " << cnt2 << endl; // 容器中大于5的数的个数为: 6
}

/*
排序算法:
sort(iterator beg, iterator end, _Pred);      对容器内元素进行排序
random_shuffle(iterator beg, iterator end);   洗牌 指定范围内的元素随机调整次序
merge(iterator beg1, iterator endl, iterator beg2, iterator end2, iterator dest);   容器元素合并，并存储到另一容器中
reverse(iterator beg, iterator end);          反转指定范围的元素
*/
class BigToSmall
{
public:
    bool operator()(int val1, int val2)
    {
        return val1 > val2;
    }
};

void test3()
{
    vector<int> v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(6);
    v.push_back(3);
    v.push_back(8);
    v.push_back(4);
    v.push_back(1);
    printVector(v); // 5 2 6 3 8 4 1

    // ------------sort------------
    sort(v.begin(), v.end());
    printVector(v); // 1 2 3 4 5 6 8

    // sort(v.begin(), v.end(), BigToSmall());
    sort(v.begin(), v.end(), greater<int>());
    printVector(v); // 8 6 5 4 3 2 1

    // ------------random_shuffle------------
    srand((unsigned int)time(NULL)); // 设置随机数种子  使得下面每次随机打乱的顺序不一样
    random_shuffle(v.begin(), v.end());
    printVector(v); // 3 6 1 5 8 2 4

    // ------------merge(合并的两个容器必须有序)------------
    sort(v.begin(), v.end());
    vector<int> v2;
    v2.push_back(2);
    v2.push_back(4);
    v2.push_back(6);
    v2.push_back(7);
    v2.push_back(9);
    printVector(v2);                     // 2 4 6 7 9
    vector<int> v_dest;                  // 目的容器
    v_dest.resize(v.size() + v2.size()); // 分配空间
    merge(v.begin(), v.end(), v2.begin(), v2.end(), v_dest.begin());
    printVector(v_dest); // 1 2 2 3 4 4 5 6 6 7 8 9

    // ------------reverse------------
    reverse(v_dest.begin(), v_dest.end());
    printVector(v_dest); // 9 8 7 6 6 5 4 4 3 2 2 1
}

/*
拷贝和替换算法:
copy(iterator beg,iterator end, iterator dest);        容器内指定范围的元素拷贝到另一容器中
replace(iterator beg,iterator end, oldValue,newValue); 将容器内指定范围的旧元素修改为新元素
replace_if(iterator beg,iterator end, _pred, newvalue);容器内指定范围满足条件的元素替换为新元素
swap(container c1,container c2);                       互换两个容器的元素
*/
void test4()
{
    vector<int> v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(6);
    v.push_back(3);
    v.push_back(8);
    v.push_back(6);
    v.push_back(1);
    printVector(v); // 5 2 6 3 8 6 1

    // ------------copy------------
    vector<int> v2;
    v2.resize(v.size()); // 老是忘!!!
    copy(v.begin(), v.end(), v2.begin());
    printVector(v2); // 5 2 6 3 8 6 1

    // ------------replace------------
    replace(v.begin(), v.end(), 6, 666);
    printVector(v); // 5 2 666 3 8 666 1

    // ------------replace_if------------
    replace_if(v.begin(), v.end(), GreaterThan5(), 100);
    printVector(v); // 5 2 100 3 100 100 1

    // ------------swap------------
    v.swap(v2);
    printVector(v);  // 5 2 6 3 8 6 1
    printVector(v2); // 5 2 100 3 100 100 1
}

/*
常用算数生成算法:    属于小型算法，使用时包含的头文件为 #include<numeric>
accumulate(iterator beg,iterator end, value);     计算区间内容器元素累计总和   value表示起始的累加值
fill(iterator beg, iterator end, value);          向容器中指定区间填充指定的value元素
*/
void test5()
{
    vector<int> v;
    v.push_back(5);
    v.push_back(2);
    v.push_back(6);
    v.push_back(3);
    v.push_back(8);
    v.push_back(6);
    v.push_back(1);
    printVector(v); // 5 2 6 3 8 6 1

    // ------------accumulate------------
    int total = accumulate(v.begin(), v.end(), 0); // value=0表示起始的累加值为0
    cout << "v_sum = " << total << endl;           // v_sum = 31

    // ------------fill------------
    fill(v.begin() + 2, v.end() - 3, 101);
    printVector(v); // 5 2 101 101 8 6 1
}

/*
集合算法:
set_intersection(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);    求两个容器的交集
set_union(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);           求两个容器的并集
set_difference(iterator beg1, iterator end1, iterator beg2, iterator end2, iterator dest);      求两个容器的差集
*/
void test6()
{
    vector<int> v1;
    v1.push_back(5);
    v1.push_back(2);
    v1.push_back(6);
    v1.push_back(3);
    v1.push_back(8);
    v1.push_back(6);
    v1.push_back(1);
    sort(v1.begin(), v1.end());
    printVector(v1); // 1 2 3 5 6 6 8
    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.push_back(3);
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(7);
    v2.push_back(9);
    printVector(v2); // 1 2 3 4 5 7 9

    // ------------set_intersection(两个集合必须有序)------------
    // set_intersection返回值是交集中最后一个元素的位置
    vector<int> v_dest1;
    v_dest1.resize(min(v1.size(), v2.size()));
    vector<int>::iterator itEnd1 = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v_dest1.begin());
    for_each(v_dest1.begin(), itEnd1, MyPrint()); // 1 2 3 5
    cout << endl;

    // ------------set_union(两个集合必须有序)------------
    // set_union返回值是交集中最后一个元素的位置
    vector<int> v_dest2;
    v_dest2.resize(v1.size() + v2.size());
    vector<int>::iterator itEnd2 = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v_dest2.begin());
    for_each(v_dest2.begin(), itEnd2, MyPrint()); // 1 2 3 4 5 6 6 7 8 9
    cout << endl;

    // ------------set_difference(两个集合必须有序)------------
    // set_difference返回值是交集中最后一个元素的位置
    vector<int> v_dest3;
    v_dest3.resize(max(v1.size(), v2.size()));
    cout << "v1和v2的差集: ";
    vector<int>::iterator itEnd3 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v_dest3.begin());
    for_each(v_dest3.begin(), itEnd3, MyPrint()); // v1和v2的差集: 6 6 8
    cout << endl;
    cout << "v2和v1的差集: ";
    itEnd3 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v_dest3.begin());
    for_each(v_dest3.begin(), itEnd3, MyPrint()); // v2和v1的差集: 4 7 9
    cout << endl;
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
