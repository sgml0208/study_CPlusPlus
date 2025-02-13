/*
 * @Description:                    vector容器    ------- STL中最常用的容器
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-03 11:41:57
 * @LastEditTime: 2025-02-13 10:14:54
 */

/*
容 器:  vector
算 法:  for_each
迭代器: vector<int>::iterator

vector原理：当插入数据原数组大小不够时，会去内存中根据某种算法找一片新的空间，先将原数组中的数据
            拷贝过去，再将要插入的数据插入新内存的vector数组中。
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void myPrint(int val)
{
    cout << val << endl;
}

// vector容器存放内置数据类型
void test1()
{
    // 默认构造函数
    vector<int> v1;
    // 插入数据
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    // 通过迭代器访问数据
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) // v1.begin()指向v1的第一个元素，v1.end()指向v1的最后一个元素的下一个位置
        cout << *it << " ";
    cout << endl;

    // 方法二
    for_each(v1.begin(), v1.end(), myPrint);

    // 通过区间方式进行构造
    vector<int> v2(v1.begin(), v1.end()); // 和v1一模一样

    // 通过n个m元素构造
    vector<int> v3(10, 1); // v3的数据是10个1

    // 拷贝构造
    vector<int> v4(v3);
}

// vector容器存放自定义数据类型
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

void test2()
{
    vector<Person> v2;
    Person p1("·zhangsan", 13);
    Person p2("lisi", 14);
    Person p3("wangwu", 15);

    v2.push_back(p1);
    v2.push_back(p2);
    v2.push_back(p3);

    for (vector<Person>::iterator it = v2.begin(); it != v2.end(); it++)
        cout << "name: " << (*it).m_name << "   age: " << (*it).m_age << endl; // == cout << "name: " << it->m_name << "   age: " << it->m_age << endl;
    cout << endl;
}

// vector容器嵌套容器
void test3()
{
    vector<vector<int>> v; // 之前相当于一维数组，现在是二维数组

    // 创建小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    for (int i = 0; i < 4; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 4);
        v3.push_back(i + 8);
    }

    // 将小容器中的数据放入大容器中
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    for (vector<vector<int>>::iterator it1 = v.begin(); it1 != v.end(); it1++)
    {
        for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); it2++)
            cout << *it2 << ' ';
        cout << endl;
    }
    // 0 1 2 3
    // 4 5 6 7
    // 8 9 10 11
}

// -----------------------------------------------------------------

void printVector(const vector<int> &v)
{
    for (vector<int>::const_iterator it = v.begin(); it != v.end(); it++) // v1.begin()指向v1的第一个元素，v1.end()指向v1的最后一个元素的下一个位置
        cout << *it << " ";
    cout << endl;
}

/*
vector赋值操作：
函数原型:
vector& operator=(const vector &vec);   重载等号操作符
assign(beg,end);                        将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);                        将n个elem拷贝赋值给本身

*/
void test4()
{
    vector<int> v1;
    // 插入数据
    for (int i = 0; i < 10; i++)
        v1.push_back(i);

    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    // 赋值
    vector<int> v2;
    v2 = v1;

    // assign
    vector<int> v3;
    v3.assign(v1.begin(), v1.end());
    printVector(v3); // 0 1 2 3 4 5 6 7 8 9

    vector<int> v4;
    v4.assign(10, 1);
    printVector(v4); // 1 1 1 1 1 1 1 1 1 1
}

/*
vector容量和大小：      capacity() >= size()
函数原型:
empty();                判断容器是否为空
capacity();             容器的容量
size();                 返回容器中元素的个数
resize(int num);        重新指定容器的长度为num，若容器变长，则以默认值填充新位置。如果容器变短，则末尾超出容器长度的元素被删除。
resize(int num, elem);  重新指定容器的长度为num，若容器变长，则以elem值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除
*/
void test5()
{
    vector<int> v1;
    // 插入数据
    for (int i = 0; i < 10; i++)
        v1.push_back(i);
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    if (!v1.empty())
        cout << "v1有数据" << endl; // v1有数据

    cout << "v1的容量为: " << v1.capacity() << endl; // v1的容量为: 16(STL内部算法决定的)
    cout << "v1的元素个数为: " << v1.size() << endl; // v1的元素个数为: 10

    v1.resize(8);
    printVector(v1); // 0 1 2 3 4 5 6 7

    v1.resize(12, -1);
    printVector(v1); // 0 1 2 3 4 5 6 7 -1 -1 -1 -1
}

/*
vector插入和删除：
push_back(ele);                                  尾部插入元素ele
pop_back();                                      删除最后一个元素
insert(const iterator pos, ele);                 迭代器指向位置pos插入元素ele
insert(const_iterator pos，int count,ele);       迭代器指向位置pos插入count个元素ele
erase(const iterator pos);                       删除迭代器指向的元素
erase(const iterator start,const iterator end);  删除选代器从start到end之间的元素
clear();                                         删除容器中所有元素
*/
void test6()
{
    vector<int> v1;
    // 插入数据
    for (int i = 0; i < 10; i++)
        v1.push_back(i);
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    // 返回vector容器中第一个元素
    cout << v1.front() << endl; // 0
    // 返回vector容器中最后一个元素
    cout << v1.back() << endl; // 9
    cout << v1.at(5) << endl;  // 5

    v1.pop_back();
    printVector(v1); // 0 1 2 3 4 5 6 7 8

    v1.insert(v1.begin(), 111);
    printVector(v1); // 111 0 1 2 3 4 5 6 7 8

    v1.insert(v1.begin() + 1, 3, 666);
    printVector(v1); // 111 666 666 666 0 1 2 3 4 5 6 7 8

    v1.erase(v1.begin() + 1);
    printVector(v1); // 111 666 666 0 1 2 3 4 5 6 7 8

    // 清空操作
    // v1.erase(v1.begin(), v1.end());
    // v1.clear();
}

/*
vector互换容器： 实现两个容器内元素进行互换
函数原型:
swap(vec);     将vec与本身的元素互换

互换容器用途：可以实现收缩内存空间
*/
void test7()
{
    cout << "交换前: " << endl;
    vector<int> v1;
    for (int i = 0; i < 10; i++)
        v1.push_back(i);
    printVector(v1); // 0 1 2 3 4 5 6 7 8 9

    vector<int> v2;
    for (int i = 10; i > 0; i--)
        v2.push_back(i);
    printVector(v2); // 10 9 8 7 6 5 4 3 2 1
    cout << "交换后: " << endl;
    v1.swap(v2);
    printVector(v1); // 10 9 8 7 6 5 4 3 2 1
    printVector(v2); // 0 1 2 3 4 5 6 7 8 9

    // 互换容器用途：可以实现收缩内存空间
    vector<int> v3;
    for (int i = 0; i < 100000; i++)
        v3.push_back(i);
    cout << "容器大小为100000时: " << endl;
    cout << "v3的容量为: " << v3.capacity() << endl; // v3的容量为: 131072
    cout << "v3的大小为: " << v3.size() << endl;     // v3的大小为: 100000
    // 重新设置大小
    v3.resize(10);
    cout << "容器大小为10时: " << endl;
    cout << "v3的容量为: " << v3.capacity() << endl; // v3的容量为: 131072
    cout << "v3的大小为: " << v3.size() << endl;     // v3的大小为: 10
    // 收缩内存方式1：
    vector<int>(v3).swap(v3); // !!!!!    vector<int> (v3) 表示匿名对象(新的)，再按照v3所用数据个数(这里是10个)来初始化容量和大小，然后与v3交换，交换之后，新的匿名对象及所占内存空间被系统回收
    cout << "收缩内存大小后: " << endl;
    cout << "v3的容量为: " << v3.capacity() << endl; // v3的容量为: 10
    cout << "v3的大小为: " << v3.size() << endl;     // v3的大小为: 10
    // 收缩内存方式2：
    // v3.shrink_to_fit();
    // cout << "v3的容量为: " << v3.capacity() << endl; // v3的容量为: 10
    // cout << "v3的大小为: " << v3.size() << endl;     // v3的大小为: 10
}

/*
vector预留空间: 减少vector在动态扩展容量时的扩展次数
函数原型:
reserve(int len);    容器预留len个元素长度，预留位置不初始化，元素不可访问。
*/
void test8()
{
    vector<int> v;

    // 刚开始直接预留内存空间,从而减少动态分配内存的次数
    // v.reserve(100000); // 加了这句,下面 数组初始化过程中动态分配内存的次数为: 1

    int num = 0; // 统计数组初始化过程中动态分配内存的次数
    int *p = NULL;
    for (int i = 0; i < 100000; i++)
    {
        v.push_back(i);
        if (p != &v[0])
        {
            p = &v[0];
            num++;
            cout << "第" << num << "次动态分配内存时 i = " << i << endl;
        }
    }
    cout << "数组初始化过程中动态分配内存的次数为: " << num << endl; // 18
    /*
    第1次动态分配内存时 i = 0
    第2次动态分配内存时 i = 1
    第3次动态分配内存时 i = 2
    第4次动态分配内存时 i = 4
    第5次动态分配内存时 i = 8
    第6次动态分配内存时 i = 16
    第7次动态分配内存时 i = 32
    第8次动态分配内存时 i = 64
    第9次动态分配内存时 i = 128
    第10次动态分配内存时 i = 256
    第11次动态分配内存时 i = 512
    第12次动态分配内存时 i = 1024
    第13次动态分配内存时 i = 2048
    第14次动态分配内存时 i = 4096
    第15次动态分配内存时 i = 8192
    第16次动态分配内存时 i = 16384
    第17次动态分配内存时 i = 32768
    第18次动态分配内存时 i = 65536
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

    test7();

    test8();

    return 0;
}
