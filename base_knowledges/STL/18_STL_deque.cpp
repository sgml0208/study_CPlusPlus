/*
 * @Description:                    deque容器: 双端数组,可以实现对头和尾的插入删除等操作
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-03 20:52:49
 * @LastEditTime: 2024-10-04 19:30:27
 */

/*
deque容器: 无容量概念,因为deque容量无限制

deque与vector区别:
vector对于头部的插入删除效率低，数据量越大，效率越低
deque相对而言，对头部的插入删除速度回比vector快
vector访问元素时的速度会比deque快,这和两者内部实现有关
*/

#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
using namespace std;

template <class T>
void printDeque(const deque<T> &v)
{
    // 方法1:
    // for (typename deque<T>::const_iterator it = v.begin(); it != v.end(); it++)
    //     cout << *it << " ";
    // cout << endl;

    // 方法2: 使用auto(c++11标准): auto关键字会自动推导出正确的迭代器类型
    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << " ";
    cout << endl;
}

/*
deque构造函数:
deque<T> deqT;              默认构造形式
deque(beg, end);            构造函数将[beg, end)区间中的元素拷贝给本身。
deque(n, elem);             构造函数将n个elem拷贝给本身
deque(const deque &deg);    拷贝构造函数
*/
void test1()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
        d1.push_back(i);
    printDeque(d1); // 0 1 2 3 4 5 6 7 8 9   == printDeque<int>(d1);

    deque<int> d2(d1.begin(), d1.end());
    printDeque(d2); // 0 1 2 3 4 5 6 7 8 9

    deque<char> d3(10, '@');
    printDeque(d3); // @ @ @ @ @ @ @ @ @ @

    deque<int> d4(d2);
    printDeque(d4); // 0 1 2 3 4 5 6 7 8 9
}

/*
deque容器赋值操作:
deque& operator (const deque &deg);     重载等号操作符
assign(beg, end);                       将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);                        将n个elem拷贝赋值给本身。
*/
void test2()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
        d1.push_back(i);
    printDeque(d1); // 0 1 2 3 4 5 6 7 8 9

    deque<int> d2;
    d2 = d1;
    printDeque(d2); // 0 1 2 3 4 5 6 7 8 9

    deque<int> d3;
    d3.assign(10, 100);
    printDeque(d3); // 100 100 100 100 100 100 100 100 100 100

    deque<int> d4;
    d4.assign(d1.begin(), d1.end());
    printDeque(d4); // 0 1 2 3 4 5 6 7 8 9
}

/*
deque容器大小操作:
deque.empty();              判断容器是否为空
deque.size();               返回容器中元素的个数
deque.resize(num);          重新指定容器的长度为num,若容器变长，则以默认值填充新位置,如果容器变短，则末尾超出容器长度的元素被删除。
deque.resize(num,elem);     重新指定容器的长度为num,若容器变长，则以elem值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除
*/
void test3()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
        d1.push_back(i);
    printDeque(d1); // 0 1 2 3 4 5 6 7 8 9

    if (!d1.empty())
        cout << "d1有数据" << endl; // d1有数据

    cout << "d1的元素个数(大小)为: " << d1.size() << endl; // d1的元素个数为: 10

    d1.resize(8);
    printDeque(d1); // 0 1 2 3 4 5 6 7

    d1.resize(12, -1);
    printDeque(d1); // 0 1 2 3 4 5 6 7 -1 -1 -1 -1
}

/*
deque容器插入和删除以及存取操作:
两端插入操作:
push_back(elem);            在容器尾部添加一个数据
push_front(elem);           在容器头部插入一个数据
pop_back();                 删除容器最后一个数据
pop_front();                删除容器第一个数据

指定位置操作:
insert(pos,elem);           在pos位置插入一个elem元素的拷贝，返回新数据的位置，
insert(pos,n,elem);         在poS位置插入n个elem数据，无返回值。
insert(pos,beg,end);        在pos位置插入[beg,end)区间的数据，无返回值,
clear();                    清空容器的所有数据
erase(beg,end);             删除[beg,end)区间的数据，返回下一个数据的位置
erase(pos);                 删除pos位置的数据，返回下一个数据的位置。

at(int idx);                返回索引idx所指的数据
operator[];                 返回索引idx所指的数据
front();                    返回容器中第一个数据元素
back();                     返回容器中最后一个数据元素
*/
void test4()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
        d1.push_back(i); // 尾插
    printDeque(d1);      // 0 1 2 3 4 5 6 7 8 9

    cout << d1.at(5) << endl;   // 5
    cout << d1[5] << endl;      // 5
    cout << d1.front() << endl; // 0
    cout << d1.back() << endl;  // 9

    d1.push_front(10); // 头插
    printDeque(d1);    // 10 0 1 2 3 4 5 6 7 8 9

    d1.pop_back();  // 尾删
    printDeque(d1); // 10 0 1 2 3 4 5 6 7 8

    d1.pop_front(); // 头删
    printDeque(d1); // 0 1 2 3 4 5 6 7 8

    d1.insert(d1.begin() + 3, 111);
    printDeque(d1); // 0 1 2 111 3 4 5 6 7 8

    d1.insert(d1.begin() + 3, 3, 666);
    printDeque(d1); // 0 1 2 666 666 666 111 3 4 5 6 7 8

    // 按区间插入
    deque<int> d2;
    d2.push_back(10);
    d2.push_back(20);
    d2.push_back(30);

    d1.insert(d1.begin() + 3, d2.begin(), d2.end());
    printDeque(d1); // 0 1 2 10 20 30 666 666 666 111 3 4 5 6 7 8

    d1.erase(d1.begin() + 3);
    printDeque(d1); // 0 1 2 20 30 666 666 666 111 3 4 5 6 7 8
    d1.erase(d1.begin() + 3, d1.begin() + 6);
    printDeque(d1); // 0 1 2 666 666 111 3 4 5 6 7 8
}


/*
deque容器排序:
sort(iterator beg, iterator end) //对beg和end区间内元素进行排序
*/
void test5()
{
    deque<int> d1;
    d1.push_back(234); 
    d1.push_back(4); 
    d1.push_back(24); 
    d1.push_front(53); 
    d1.push_front(13); 
    d1.push_front(452); 
    printDeque(d1);      // 452 13 53 234 4 24
    sort(d1.begin(), d1.end());    // 也支持vector容器排序
    printDeque(d1);      // 4 13 24 53 234 452
}

int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    return 0;
}