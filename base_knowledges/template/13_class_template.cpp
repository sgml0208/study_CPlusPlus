/*
 * @Description:                    类模板
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-02 12:11:15
 * @LastEditTime: 2024-10-02 19:44:51
 */

/*
类模板作用:
    建立一个通用类，类中的成员 数据类型可以不具体制定，用一个虚拟的类型来代表。

注意：类模板没有自动类型推导的使用方式，只能手动指定数据类型
*/

#include <iostream>
#include <string>
#include "class_template.hpp"  // 若创建并引用的是class_template.h，则报错，因为.h中只有函数的声明，而类模板中成员函数的实现是在调用阶段
using namespace std;


// 全局函数 类外实现，需要让编译器提前知道这个函数的存在
template<class T1, class T2>  
class Person6;
// 全局函数
template<class T1, class T2>
void show66(Person6<T1, T2> p)     // 类模板中的函数的实现，不是普通函数的实现
{
    cout << "类外实现： name: " << p.m_name << "    age: " << p.m_age << endl;
}



// 类模板
template <class NameType, class AgeType = int> // 类模板在模板参数列表中可以有默认参数 #1
class Person
{
public:
    NameType m_name;
    AgeType m_age;

    Person(NameType name, AgeType age)
    {
        this->m_name = name;
        this->m_age = age;
    }

    void show() // 类模板中的成员函数只有在对象调用该函数时才会去创建
    {
        cout << this->m_name << "  " << this->m_age << endl;
    }
};

void test1()
{
    Person<string, int> p1("ZhangSan", 12);
    Person<char, int> p2('H', 13);
    p1.show();
    p2.show();
    Person<string> p3("Tom", 14); // #1
    p3.show();
}

// 1-指定传入的类型  -------- 最常用
void myPrint(Person<string, int> &p)
{
    cout << p.m_name << "  " << p.m_age << endl; // Jack  18
    p.show();                                    // Jack  18
}

// 2-参数模板化
template <class T1, class T2>
void myPrint2(Person<T1, T2> &p)
{
    p.show();
    // 查看T1，T2的数据类型
    cout << "T1的类型为" << typeid(T1).name() << endl; // T1的类型为NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    cout << "T2的类型为" << typeid(T2).name() << endl; // i(nt)
}

void test2()
{
    Person<string, int> p4("Jack", 18);
    myPrint(p4);
    myPrint2(p4);
}

// 3-整个类模板化
template <class T>
void myPrint3(T &p)
{
    p.show();
    cout << "T的类型为" << typeid(T).name() << endl; // T的类型为6PersonINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEiE
}

void test3()
{
    Person<string, int> p5("Bob", 6);
    myPrint3(p5);
}


/*
类模板与继承：
当类模板碰到继承时，需要注意一下几点:
    #1.当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型, 不然不知道继承父类需要多少内存空间
    #2.如果不指定，编译器无法给子类分配内存
    #3.如果想灵活指定出父类中T的类型，子类也需变为类模板
*/
template <class T>
class Father
{
public:
    T m;
    Father()
    {
        cout << "type(T): " << typeid(T).name() << endl;
    }
};

class Son : public Father<int> // #1
{
};

template <class T1, class T2>  // <子类, 父类> .
class Son2 : public Father<T2> // #3
{
public:
    T1 n;
    Son2()
    {
        cout << "type(T1): " << typeid(T1).name() << endl;
        cout << "type(T2): " << typeid(T2).name() << endl;
    }
};

void test4()
{
    Son2<int, char> s2; // 父类中的m是char类型，子类中的n是int类型
    /*
    type(T):  char
    type(T1): int
    type(T2): char
    */
}


/*
类模板成员函数类外实现
*/
template<class T1, class T2>
class Person2
{
public:
    T1 m_name;
    T2 m_age;
    Person2(T1 name, T2 age);
    
    void show();
    
};

template<class T1, class T2>    // 需要加
Person2<T1, T2>::Person2(T1 name, T2 age)
{
    this->m_name = name;
    this->m_age = age;
}

template<class T1, class T2>    // 需要加
void Person2<T1, T2>::show()
{
    cout << "name: " << this->m_name << "    age: " << this->m_age << endl;
}


void test5()
{
    Person2<string, int> p("Alice", 15);
    p.show();   // name: Alice    age: 15
}


/*
类模板分文件编写
    一般 .hpp文件就是类模板文件
*/
void test6()
{
    Person5<string, int> p("Hello", 5);
    p.show();   // name: Hello    age: 5
}


/*
类模板与友元函数
*/
template<class T1, class T2>
class Person6
{
private:
    T1 m_name;
    T2 m_age;
public:
    Person6(T1 name, T2 age)
    {
        this->m_name = name;
        this->m_age = age;
    }
    
    // 全局函数 类内实现 (建议写法)
    friend void show6(Person6<T1, T2> p)
    {
        cout << "name: " << p.m_name << "    age: " << p.m_age << endl;
    }
    
    // 全局函数 类外实现，需要让编译器提前知道这个函数的存在
    // friend void show66(Person6<T1, T2> p);    // 普通函数，不是类模板中的函数
    // 加一个空模板参数列表变成类模板中的函数
    friend void show66<>(Person6<T1, T2> p);
};

void test7()
{
    Person6<string, int> p("World", 25);
    show6(p);   // name: World    age: 25
}

// // 全局函数
// template<class T1, class T2>
// void show66(Person6<T1, T2> p)     // 类模板中的函数的实现，不是普通函数的实现
// {
//     cout << "类外实现： name: " << p.m_name << "    age: " << p.m_age << endl;
// }

void test8()
{
    Person6<string, int> p("Tomorrow", 16);
    show66(p);   // 类外实现： name: Tomorrow    age: 16
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











