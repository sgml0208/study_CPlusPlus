/*
 * @Description:          运算符重载   https://www.bilibili.com/video/BV1et411b73Z/?p=121&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version: 
 * @Date: 2024-07-18 07:45:13
 * @LastEditTime: 2024-07-20 09:18:33
 */

// 运算符重载概念:对已有的运算符重新进行定义，赋予其另一种功能，以适应不同的数据类型

#include <iostream>
#include <string>
using namespace std;

// -------------------------- 加号运算符+ 重载 --------------------------
class Person1
{
public:
    int m_A;
    int m_B;

    // 成员函数重载 + 号
    // Person1 operator+(Person1 &p)
    // {
    //     Person1 temp;
    //     temp.m_A = this->m_A + p.m_A;
    //     temp.m_B = this->m_B + p.m_B;
    //     return temp;
    // }
};

// 全局函数重载 + 号
Person1 operator+(Person1 &p1, Person1 &p2)
{
    Person1 temp;
    temp.m_A = p1.m_A + p2.m_A;
    temp.m_B = p1.m_B + p2.m_B;
    return temp;
}

void test1()
{
    Person1 p1;
    p1.m_A = 10;
    p1.m_B = 11;
    Person1 p2;
    p2.m_A = 20;
    p2.m_B = 21;   

    Person1 p3 = p1 + p2;  // 成员函数重载的本质是：p3 = p1.operator+(p2)  全局函数重载的本质是：p3 = operator+(p1, p2)
    cout << "p3.m_A = " << p3.m_A << endl;
    cout << "p3.m_B = " << p3.m_B << endl;
}

// -------------------------- 左移运算符<< 重载 --------------------------
class Person2
{
public:
    int m_A;
    int m_B;

    // 一般不会用成员函数重载 << 号
};

// 全局函数重载 << 号    
ostream & operator<<(ostream &cout, Person2 &p)   // 本质：operator<<(cout, p) == cout << p;
{               // cout全局只有一个，必须以引用方式传进来   
    cout << "m_A = " << p.m_A << "  m_B = " << p.m_B;
    return cout;
}


void test2()
{
    Person2 p;
    p.m_A = 10;
    p.m_B = 11;
    cout << p << endl;   // m_A = 10  m_B = 11      链式法则
}

// -------------------------- 关系运算符== 重载 --------------------------
class Person3
{
public:
    string m_name;
    int m_age;

    Person3(string name, int age)
    {
        m_name = name;
        m_age = age;
    }

    // 成员函数重载 == 号，其余运算符号同理
    bool operator==(Person3 &p)
    {
        if(this->m_age == p.m_age && this->m_name == p.m_name)
            return true;
        else
            return false;
    }
};

// 全局函数重载 == 号    
// ...省略

void test3()
{
    Person3 p1("Tom", 18);
    Person3 p2("Bob", 20);
    Person3 p3("Bob", 20);
    if (p1 == p2)
        cout << "p1 == p2" << endl;
    else
        cout << "p1 != p2" << endl;   // p1 != p2
    if (p3 == p2)
        cout << "p3 == p2" << endl;   // p3 == p2
    else
        cout << "p3 != p2" << endl;
}

// -------------------------- 递增运算符++ 重载 --------------------------
class MyInteger
{
    friend ostream& operator<<(ostream& cout, MyInteger myint);

private:
    int m_num;

public:
    MyInteger()
    {
        m_num = 0;
    }
    // 重载 前置++ 运算符
    MyInteger& operator++()       // 返回引用！
    {
        // 先进行++，再返回自身数据
        m_num++;
        return *this;
    }

    // 重载 后置++ 运算符
    MyInteger operator++(int)       // 返回值！   int代表占位参数，表示后置
    {
        // 先记录当前数据，再加1，然后返回
        MyInteger temp = *this;
        m_num++;
        return temp;    // 局部变量temp在函数结束时就释放了，返回引用会报错
    }    
    
};

// 重载 << 运算符
ostream& operator<<(ostream& cout, MyInteger myNum)
{
    cout << myNum.m_num;
    return cout;
}

void test4()
{
    MyInteger myNum;
    // 前置递增
    cout << ++(++myNum) << endl;  // 2
    cout << myNum << endl;      // 函数返回引用结果为2，返回值则结果为1，因为引用是对同一数据进行操作，返回值则是创建了一个新对象
    // 后置递增
    cout << myNum++ << endl;    // 2
    cout << myNum << endl;      // 3
}

// -------------------------- 赋值运算符= 重载 --------------------------
class Person5
{
public:
    int *m_age;

    Person5(int age)
    {
        m_age = new int(age);   // 堆区手动申请内存，也需手动释放
    }
    ~Person5()
    {
        if(m_age != NULL)
        {
            delete m_age;
            m_age = NULL;
        }
    }
    // 赋值运算符重载
    Person5& operator=(Person5 &p)
    {
        // m_age = p.m_age // 这是编译器默认提供的浅拷贝
        // 应该先判断是否有属性在堆区，如果有先释放干净，然后再深拷贝
        if(m_age != NULL)
        {
            delete m_age;
            m_age = NULL;            
        }
        m_age = new int(*p.m_age);    // 深拷贝
        return *this;   // 返回自身  同时满足链式法则
    }


};

void test5()
{
    Person5 p1(18);
    Person5 p2(20);
    Person5 p3(30);

    p3 = p2 = p1;   // 链式法则

    // p2 = p1;  // 这样会使程序崩溃，因为这是浅拷贝，p1, p2指向同一快内存地址，都执行析构函数，内存释放了两遍

    cout << "p1的年龄为: " << *p1.m_age << endl;   // 18
    cout << "p2的年龄为: " << *p2.m_age << endl;   // 18
    cout << "p3的年龄为: " << *p3.m_age << endl;   // 18
}

// -------------------------- 函数调用运算符() 重载 --------------------------
class MyPrint
{
public:

    // 重载函数调用运算符() 
    void operator()(string test)
    {
        cout << test << endl;
    }

    int operator()(int n1, int n2)
    {
        return n1 + n2;
    } 

};

void outPrint(string test)
{
    cout << test << endl;
}

void test6()
{
    MyPrint myPrint;
    myPrint("hello world");  // hello world  很像函数调用
    outPrint("hello world"); // hello world  普通函数调用

    // 匿名对象MyPrint()
    cout << MyPrint()(1, 2) << endl;  // 3    == myPrint(1, 2)

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