/*
 * @Description:                    函数对象(仿函数)  谓词   内建函数对象
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-05 10:40:41
 * @LastEditTime: 2024-10-05 16:01:59
 */

/*
函数对象概念:
重载函数调用操作符的类，其对象常称为函数对象
函数对象使用重载的()时，行为类似函数调用，也叫仿函数

本质:
函数对象(仿函数)是一个类，不是一个函数

函数对象使用
特点:
#1. 函数对象在使用时，可以像普通函数那样调用,可以有参数，可以有返回值
#2. 函数对象超出普通函数的概念，函数对象可以有自己的状态
#3. 函数对象可以作为参数传递

*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional> // 使用内建函数对象
using namespace std;

class MyAdd
{
public:
    int operator()(int val1, int val2)
    {
        return val1 + val2;
    }
};

void test1()
{
    // #1
    MyAdd myAdd;                 // 创建函数对象
    cout << myAdd(1, 2) << endl; // 3
}

class MyPrint
{
public:
    int cnt;
    MyPrint()
    {
        this->cnt = 0;
    }
    void operator()(string t)
    {
        cout << t << endl;
        cnt++;
    }
};

void test2()
{
    // #2
    MyPrint myPrint;
    myPrint("hello");
    myPrint("world");
    myPrint("tomorrow");
    cout << "myPrint调用次数为: " << myPrint.cnt << endl; // myPrint调用次数为: 3
}

void doPrint(MyPrint &mp, string t)
{
    mp(t);
}

void test3()
{
    // #3
    MyPrint myPrint;
    doPrint(myPrint, "hello c++"); // hello c++
}

// ------------------------------------------------------

/*
谓词 _Pred ：
返回bool类型的仿函数称为谓词(重载()且返回值为bool)
如果operator()接受一个参数，那么叫做一元谓词
如果operator()接受两个参数，那么叫做二元谓词
*/
class GreaterThanFive
{
public:
    bool operator()(int val) // 一元谓词(一个参数)
    {
        return val > 5;
    }
};

void test4()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
        v.push_back(i);

    // 查找v中是否有>5的元素
    // find_if(v.begin(), v.end(), GreaterThanFive());   // GreaterThanFive()为匿名的函数对象
    // 或者==下面
    GreaterThanFive gt5;
    vector<int>::iterator it = find_if(v.begin(), v.end(), gt5);
    if (it == v.end())
        cout << "未找到大于5的数字!" << endl;
    else
        cout << "找到大于5的数字为: " << *it << endl; // 找到大于5的数字为: 6
}

class mySort
{
public:
    bool operator()(int x, int y) // 二元谓词(两个参数)
    {
        return x > y;
    }
};

void test5()
{
    vector<int> v;
    v.push_back(14);
    v.push_back(43);
    v.push_back(2);
    v.push_back(453);
    v.push_back(27);

    sort(v.begin(), v.end(), mySort());

    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
        cout << *it << ' ';
    cout << endl; // 453 43 27 14 2
}

// -----------------------------------------------

/*
内建函数对象:
分类:
    算术仿函数
    关系仿函数
    逻辑仿函数
用法:
这些仿函数所产生的对象，用法和一般函数完全相同
使用内建函数对象，需要引入头文件 #include<functional>

算数仿函数:
功能描述:
    实现四则运算
    其中negate是一元运算，其他都是二元运算
仿函数原型:
template<class T> T plus<T>          加法仿函数
template<class T> T minus<T>         减法仿函数
template<class T> T multiplies<T>    乘法仿函数
template<class T> T divides<T>       除法仿函数
template<class T> T modulus<T>       取模仿函数
template<class T> T negate<T>        取反仿函数
*/
void test6()
{
    negate<int> n;
    cout << "10取反为: " << n(10) << endl; // 10取反为: -10

    plus<int> p;                           // 不用写成plus<int, int>，只能同类型数据进行运算
    cout << "1 + 2 = " << p(1, 2) << endl; // 1 + 2 = 3
}

/*
关系仿函数:
template<class T> bool equal_to<T>          等于
template<class T> bool not equal_to<T>      不等于
template<class T> bool greater<T>           大于
template<class T> bool greater_equal<T>     大于等于
template<class T> bool less<T>              小于
template<class T> bool less_equal<T>        小于等于
*/
template<class T>
void printVector(const vector<T> &v)
{
    for (typename vector<T>::const_iterator it = v.begin(); it != v.end(); it++) // v1.begin()指向v1的第一个元素，v1.end()指向v1的最后一个元素的下一个位置
        cout << *it << " ";
    cout << endl;
}

void test7()
{
    vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    v.push_back(1);
    v.push_back(5);
    printVector(v); // 3 2 4 1 5

    sort(v.begin(), v.end(), greater<int>()); // 使用内建的函数对象
    printVector(v);                           // 5 4 3 2 1
}

/*
逻辑仿函数:       实际开发中几乎不用
template<class T> bool logical_and<T>       逻辑与
template<class T> bool logical_or<T>        逻辑或
template<class T> bool logical_not<T>       逻辑非
*/
void test8()
{
    vector<bool> v;
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    printVector(v); // 0 1 0 1

    vector<bool> v2;
    v2.resize(v.size());

    transform(v.begin(), v.end(), v2.begin(), logical_not<int>());
    printVector(v2);        // 1 0 1 0 
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
