/*
 * @Description:      多态     https://www.bilibili.com/video/BV1et411b73Z?p=135
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-21 09:33:18
 * @LastEditTime: 2024-07-24 07:31:19
 */

/*
多态是C++面向对象三大特性之一
多态分为两类
    静态多态: 函数重载和运算符重载属于静态多态，复用函数名
    动态多态: 派生类和虚函数实现运行时多态
静态多态和动态多态区别:
    ·静态多态的函数地址早绑定: 编译阶段 确定函数地址
    ·动态多态的函数地址晚绑定: 运行阶段 确定函数地址

动态多态满足的条件：
    有类的继承关系；
    子类重写父类的虚函数。

动态多态的调用：使用父类的指针或引用来执行子类对象

重写：函数的返回值类型、函数名、参数列表完全相同

多态好处：
    组织结构清晰
    代码可读性强
    利于前期和后期的扩展和维护
*/

#include <iostream>
#include <string>
using namespace std;

class Animal
{
public:
    // 1---
    // void speak()
    // {
    //     cout << "动物在说话" << endl;
    // }

    // 2---  虚函数：实现地址晚绑定
    virtual void speak()
    {
        cout << "动物在说话" << endl;
    }
};

class Cat : public Animal
{
public:
    void speak()
    {
        cout << "小猫在说话" << endl;
    }
};

// 1--- 地址早绑定，在编译阶段确定函数地址
// void doSpeak(Animal &animal)  // Animal &animal，确定执行Animal中的函数
// {
//     animal.speak();
// }

// 2--- 地址晚绑定，在运行阶段确定函数地址
void doSpeak(Animal &animal) // Animal &animal，运行时传入的是Cat类对象，所以执行Cat中的函数
{
    animal.speak();
}

void test1()
{
    Cat cat;
    doSpeak(cat);
}

// -------------------------- 多态案例：计算器类 ------------------------------
// 抽象计算类
class AbstractCalculator
{
public:
    int num1, num2;
    virtual int calc()
    {
        return 0;
    }
};

// 加法类
class Add : public AbstractCalculator
{
    int calc() // virtual int calc()  virtual可写可不写
    {
        return num1 + num2;
    }
};

// 减法类
class Sub : public AbstractCalculator
{
    int calc()
    {
        return num1 - num2;
    }
};

// 乘法类
class Mul : public AbstractCalculator
{
    int calc()
    {
        return num1 * num2;
    }
};

// 除法类
class Div : public AbstractCalculator
{
    int calc()
    {
        if (num2 == 0)
            return -1;
        else
            return num1 / num2;
    }
};

void test2()
{
    // 多态使用条件：父类指针或者引用指向子类对象
    // 加法运算
    AbstractCalculator *abs = new Add;
    abs->num1 = 1;
    abs->num2 = 2;
    cout << abs->num1 << " + " << abs->num2 << " = " << abs->calc() << endl; // 1 + 2 = 3
    delete abs;                                                              // 释放堆区的数据，但是指针还在

    // 减法运算
    abs = new Sub;
    abs->num1 = 10;
    abs->num2 = 2;
    cout << abs->num1 << " - " << abs->num2 << " = " << abs->calc() << endl; // 10 - 2 = 8
    delete abs;                                                              // 释放堆区的数据，但是指针还在

    // 乘法运算
    abs = new Mul;
    abs->num1 = 3;
    abs->num2 = 4;
    cout << abs->num1 << " * " << abs->num2 << " = " << abs->calc() << endl; // 3 * 4 = 12
    delete abs;                                                              // 释放堆区的数据，但是指针还在

    // 除法运算
    abs = new Div;
    abs->num1 = 42;
    abs->num2 = 6;
    int res = abs->calc();
    if (res == -1)
        cout << "被除数不能为0!" << endl;
    else
        cout << abs->num1 << " / " << abs->num2 << " = " << res << endl; // 42 / 6 = 7
    delete abs;                                                          // 释放堆区的数据，但是指针还在
}

// ---------------------------- 纯虚函数和抽象类 ------------------------------
/*
    在多态中，通常父类中虚函数的实现是毫无意义的，主要都是调用子类重写的内容，因此可以将虚函数改为纯虚函数
    纯虚函数语法: virtual 返回值类型函数名〔参数列表) = 0;
    当类中有了纯虚函数，这个类也称为抽象类

抽象类特点:
    抽象类无法实例化对象
    子类必须重写抽象类中的纯虚函数，否则也属于抽象类

*/

class Base1
{
public:
    // 纯虚函数 (只要有一个纯虚函数，这个类称为抽象类)
    virtual void func() = 0;
};

class Son1 : public Base1
{
public:
    void func()
    {
        cout << "抽象类的子类必须重写抽象类中的纯虚函数，否则也属于抽象类，无法实例化对象" << endl;
    }
};

void test3()
{
    // Base1 b;  // 抽象类无法实例化对象

    Base1 *b = new Son1;
    b->func();
    delete b;
}

// ---------------------------- 虚析构和纯虚析构 ------------------------------
/*
    多态使用时，如果子类中有属性开辟到堆区，那么父类指针在释放时无法调用到子类的析构代码
    解决方式: 将父类中的析构函数改为虚析构或者纯虚析构

虚析构和纯虚析构共性:
    ·可以解决父类指针释放子类对象
    ·都需要有具体的函数实现

虚析构和纯虚析构区别:
    如果是纯虚析构，该类属于抽象类，无法实例化对象

利用虚析构可以解决父类指针释放子类对象时不干净的问题

总结:
    1.虚析构或纯虚析构就是用来解决通过父类指针释放子类对象
    2.如果子类中没有堆区数据，可以不写为虚析构或纯虚析构
    3.拥有纯虚析构函数的类也属于抽象类

*/

class Animal2
{
public:
    virtual void speak() = 0; // 纯虚函数
    Animal2()
    {
        cout << "Animal2的构造函数调用!" << endl;
    }

    // 虚析构函数
    // 不写virtual，子类中析构函数不可执行，堆区申请的内存得不到释放，造成内存泄漏
    // virtual ~Animal2()
    // {
    //     cout << "Animal2的虚析构函数调用!" << endl;
    // }

    // 纯虚析构函数声明
    virtual ~Animal2() = 0;
};

// 纯虚析构函数实现
Animal2::~Animal2()
{
    cout << "Animal2的纯虚析构函数调用!" << endl;
}

class Cat2 : public Animal2
{
public:
    string *c_name; // 开辟在堆区
    Cat2(string name)
    {
        cout << "Cat2的构造函数调用!" << endl;
        c_name = new string(name);
    }
    void speak()
    {
        cout << *c_name << "小猫在说话" << endl;
    }
    ~Cat2()
    {
        if (c_name != NULL)
        {
            cout << "Cat2的析构函数调用!" << endl;
            delete c_name;
            c_name = NULL;
        }
    }
};

void test4()
{
    Animal2 *animal = new Cat2("lala");
    animal->speak(); // lala小猫在说话
    delete animal;
}

int main()
{
    test1();

    test2();

    test3();

    test4();

    return 0;
}