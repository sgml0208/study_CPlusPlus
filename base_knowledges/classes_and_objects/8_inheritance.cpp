/*
 * @Description:        继承   https://www.bilibili.com/video/BV1et411b73Z/?p=127&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-20 09:20:07
 * @LastEditTime: 2025-02-12 20:38:16
 */

/*
继承的好处：减少重复代码

继承的语法:  class 子类 ∶ 继承方式 父类
继承方式一共有三种:
    ·公共继承
    ·保护继承
    ·私有继承

子类和父类中出现了同名成员变量或函数，调用子类的成员变量或函数方式为: 子类对象.成员变量/函数
                                   调用父类的成员变量或函数方式为: 子类对象.父类名称::成员变量/函数

总结:
    1.子类对象可以直接访问到子类中同名成员
    2.子类对象加作用域可以访问到父类同名成员
    3.当子类与父类拥有同名的成员函数，子类会隐藏父类中同名成员函数，加作用域可以访问到父类中同名函数

*/

// --------------------------- 继承方式 ---------------------------

#include <iostream>
#include <string>
using namespace std;

class BaseClass
{
public:
    int a;

protected:
    int b;

private:
    int c;
};

// 公共继承
class SonClass1 : public BaseClass
{
public:
    int my_data = 99;
    void func()
    {
        a = 1; // 父类中的公共权限成员到子类中依然是公共权限
        b = 2; // 父类中的保护权限成员到子类中依然是保护权限
        // c = 3;   // 父类中的私有权限成员子类访问不到
    }
};

void test1()
{
    SonClass1 s1;
    s1.a = 100;
    // s1.b = 200;   error: SonClass1类内可以访问保护权限变量b，但类外无法访问

    // 父类中的所有非静态成员属性(三个属性)都会被子类继承下来，只是父类中private私有成员被编译器隐藏了，无法访问
    cout << "sizeof SonClass1 = " << sizeof(SonClass1) << endl; // sizeof SonClass1 = 16
}

// 保护继承
class SonClass2 : protected BaseClass
{
public:
    void func()
    {
        a = 1; // 父类中的公共权限成员到子类中变成了保护权限
        b = 2; // 父类中的保护权限成员到子类中依然是保护权限
        // c = 3;   error: 父类中的私有权限成员子类访问不到
    }
};

void test2()
{
    SonClass2 s2;
    // s2.a = 100;   error: SonClass2类内可以访问保护权限变量a，但类外无法访问
    // s1.b = 200;   error: SonClass2类内可以访问保护权限变量b，但类外无法访问
}

// 私有继承
class SonClass3 : private BaseClass
{
public:
    void func()
    {
        a = 1; // 父类中的公共权限成员到子类中变成了私有权限
        b = 2; // 父类中的保护权限成员到子类中变成了私有权限
        // c = 3;   // 父类中的私有权限成员子类访问不到
    }
};

void test3()
{
    SonClass3 s3;
    // s3.a = 1000;   error: SonClass3类内可以访问保护私有变量a，但类外无法访问
    // s3.b = 2000;   error: SonClass3类内可以访问保护私有变量b，但类外无法访问
}

// --------------------------- 多继承 ---------------------------
// 实际开发过程中，不建议使用多继承
class Base1
{
public:
    int b_a;
    int b_b;
    Base1()
    {
        b_a = 1;
        b_b = 1;
    }
};

class Base2
{
public:
    int b_b;
    Base2()
    {
        b_b = 2;
    }
};

class Son : public Base1, public Base2 // 不指定public则不可访问Base2
{
public:
    int s_a, s_b;
    Son()
    {
        s_a = 5;
        s_b = 6;
    }
};

void test4()
{
    cout << "sizeof Son = " << sizeof(Son) << endl; // sizeof Son = 20 (B)
    Son s1;
    cout << s1.b_a << endl; // 1
    // 不同父类有同名属性
    cout << s1.Base1::b_b << endl; // 1
    cout << s1.Base2::b_b << endl; // 2
}

// 虚继承：解决菱形继承问题        虚基类: virtual 类名
// 菱形继承带来的主要问题是子类继承两份相同的数据，导致资源浪费以及毫无意义，利用虚继承可以解决菱形继承问题

int main()
{
    test1();

    test4();

    return 0;
}