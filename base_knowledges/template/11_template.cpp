/*
 * @Description:            模板
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-01 12:28:06
 * @LastEditTime: 2024-10-01 22:26:54
 */

/*
C++提供两种模板机制:    函数模板和类模板

函数模板作用:   建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个虚拟的类型来代表。

语法：
    template<typename T>    typename—: 表示其后面的符号是一种数据类型，可以用class代替 == template<class T>
    函数声明或定义               T:     通用的数据类型，名称可以替换，通常为大写字母

注意： 使用模板时必须确定出通用数据类型T，并且能够推爭出一致的类型
*/

#include <iostream>
#include <string>
using namespace std;

void swapInt(int &a, int &b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void swapDouble(double &a, double &b)
{
    double temp;
    temp = a;
    a = b;
    b = temp;
}

// 函数模板
template <typename T> // 声明一个模板
void mySwap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

void test1()
{
    int a = 1;
    int b = 2;
    cout << "a = " << a << ", b = " << b << endl;
    mySwap(a, b); // 模板自动推导数据的类型(a,b 必须是同一类型)
    cout << "a = " << a << ", b = " << b << endl;

    double da = 1.11;
    double db = 2.22;
    cout << "da = " << da << ", db = " << db << endl;
    mySwap<double>(da, db); // 指定模板的数据的类型，可以实现 add<int>(10, 'c'): 109，即实现隐式类型转换
    cout << "da = " << da << ", db = " << db << endl;
}

// 模板局限性：模板并不是万能的，有些特定数据类型(例如自定义的数据类型)，需要用具体化方式做特殊实现
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }
    string m_name;
    int m_age;
};

template<class T>
// 如果将参数定义为值传递bool myCompare(T a, T b)，编译器会尝试复制 Person 对象，这可能会导致错误，特别是如果 Person 类中
// 包含指针或其他不能被复制的资源。按值传递对象也会增加不必要的开销，因为每个函数调用都会复制对象。通过引用传递参数可以避免这种开销
bool myCompare(T &a, T &b) // 若传入的是Person类型，判断不了两个对象是否相等
{
    if (a == b)
        return true;
    else
        return false;
}

template <> bool myCompare(Person &p1, Person &p2)  // 函数重载，对于特定数据类型比较需要具体代码实现
{
    if (p1.m_name == p2.m_name && p1.m_age == p2.m_age)
        return true;
    else
        return false;
}

void test2()
{
    Person p1("Jack", 12);
    Person p2("Tom", 12);
    bool ans;
    ans = myCompare(p1, p2);
    if (ans)
        cout << "==" << endl;
    else
        cout << "!=" << endl;    // !=
}

int main()
{

    test1();
    test2();

    return 0;
}
