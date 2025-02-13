/*
 * @Description:                    list容器：双向循环链表
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 09:57:44
 * @LastEditTime: 2025-02-13 13:33:10
 */

/*
由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，不支持随机访问，属于双向迭代器

list的优点:
采用动态存储分配，不会造成内存浪费和溢出
链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素
list的缺点:
链表灵活，但是空间(指针域)和 时间(遍历)额外耗费较大

List有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的

list和vector的区别:
vector是单向连续线性空间，list是双向链表
总结: STL中List和vector是两个最常被使用的容器，各有优缺点
*/

#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

template <class T>
void printList(const list<T> &l)
{
    // 方法1:
    // for (typename list<T>::const_iterator it = l.begin(); it != l.end(); it++)
    //     cout << *it << " ";
    // cout << endl;

    // 方法2: 使用auto(c++11标准): auto关键字会自动推导出正确的迭代器类型
    for (auto it = l.begin(); it != l.end(); it++)
        cout << *it << " ";
    cout << endl;
}

/*
list构造函数:
函数原型:
list<T> lst;            list采用模板类实现,对象的默认构造形式
list(beg,end);          构造函数将[beg, end)区间中的元素拷贝给本身
list(n,elem);           构造函数将n个elem拷贝给本身
list(const list &lst);  拷贝构造函数
*/
void test1()
{
    list<int> l1; // 默认构造函数
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    printList(l1); // 1 2 3

    list<int> l2(l1.begin(), l1.end()); // 区间构造
    printList(l2);                      // 1 2 3

    list<char> l3(10, 'a');
    printList(l3); // a a a a a a a a a a

    list<int> l4(l2);
    printList(l4); // 1 2 3
}

/*
list赋值与交换： 给list容器进行赋值，以及交换list容器
函数原型:
assign(beg, end);                   将[beg, end)区间中的数据拷贝赋值给本身
assign(n, elem);                    将n个elem拷贝赋值给本身
list& operator=(const list &lst);   重载等号操作符
swap(lst);                          将lst与本身的元素互换
*/
void test2()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    printList(l1); // 1 2 3

    list<int> l2;
    l2 = l1;
    printList(l2); // 1 2 3

    list<int> l3;
    l3.assign(l1.begin(), l1.end());
    printList(l3); // 1 2 3

    list<int> l4;
    l4.assign(10, 111);
    printList(l4); // 111 111 111 111 111 111 111 111 111 111

    l1.swap(l4);
    printList(l1); // 111 111 111 111 111 111 111 111 111 111
    printList(l4); // 1 2 3
}

/*
list大小操作:
size();             返回容器中元素的个数
empty();            判断容器是否为空
resize(num);        重新指定容器的长度为num，若容器变长，则以默认值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除。
resize(num, elem);  重新指定容器的长度为num，若容器变长，则以elem值填充新位置，如果容器变短，则末尾超出容器长度的元素被删除。
*/
void test3()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    printList(l1); // 1 2 3

    if (!l1.empty())
        cout << "l1有数据" << endl; // l1有数据

    cout << "l1的数据个数为: " << l1.size() << endl; // l1的数据个数为: 3

    l1.resize(10, 0);
    printList(l1); // 1 2 3 0 0 0 0 0 0 0
}

/*
list容器的插入和删除

push_back(elem);        在容器尾部加入一个元素
pop_back();             删除容器中最后一个元素
push_front(elem);       在容器开头插入一个元素
pop_front();            从容器开头移除第一个元素
insert(pos,elem);       在pos位置插elem元素的拷贝，返回新数据的位置。
insert(pos,n,elem);     在pos位置插入n个elem数据，无返回值。
insert(pos,beg,end);    在pos位置插入[beg,end)区间的数据，无返回值。
clear();                移除容器的所有数据
erase(beg,end);         删除[beg,end)区间的数据，返回下一个数据的位置。
erase(pos);             删除pos位置的数据，返回下一个数据的位置。
remove(elem);           删除容器中所有与elem值匹配的元素。
*/
void test4()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    printList(l1); // 1 2 3

    // cout << l1[1] << endl;    // error! 没有与这些操作数匹配的 "[]" 运算符 因为list底层用链表实现，不能用[]访问
    // cout << l1.at(1) << endl; // error!
    cout << "l1的第一个元素为: " << l1.front() << endl;  // l1的第一个元素为: 1
    cout << "l1的最后一个元素为: " << l1.back() << endl; // l1的最后一个元素为: 3

    l1.push_front(4);
    l1.push_front(5);
    printList(l1); // 5 4 1 2 3

    l1.pop_back();
    l1.pop_front();
    printList(l1); // 4 1 2

    l1.insert(l1.begin(), 5, 100);
    printList(l1); // 100 100 100 100 100 4 1 2

    list<int> l2;
    l2.push_back(11);
    l2.push_back(22);
    l2.push_back(33);

    l1.insert(l1.end(), l2.begin(), l2.end());
    printList(l1); // 100 100 100 100 100 4 1 2 11 22 33

    l1.erase(l1.begin());
    printList(l1); // 100 100 100 100 4 1 2 11 22 33

    l1.remove(100); // 删除容器中所有值为100的元素
    printList(l1);  // 4 1 2 11 22 33

    l1.clear();
    printList(l1); //
}

/*
list 反转和排序:
reverse()       反转链表
sort();         链表排序
*/
void test5()
{
    list<int> l1;
    l1.push_back(12);
    l1.push_back(5);
    l1.push_back(67);
    l1.push_back(342);
    l1.push_back(3);
    l1.push_back(64);
    cout << "反转前: ";
    printList(l1); // 反转前: 12 5 67 342 3 64

    l1.reverse();
    cout << "反转后: ";
    printList(l1); // 反转后: 64 3 342 67 5 12

    // sort(l1.begin(), l1.end()); error! 这是全局函数   所有不支持随机访问迭代器的容器不可以用标准算法
    l1.sort();                            // 成员函数
    cout << "排序后: ";
    printList(l1); // 排序后: 3 5 12 64 67 342
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