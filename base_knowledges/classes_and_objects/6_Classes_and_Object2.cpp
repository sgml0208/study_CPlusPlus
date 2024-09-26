/*
 * @Description:      类与对象    https://www.bilibili.com/video/BV1et411b73Z/?p=111&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-16 07:10:10
 * @LastEditTime: 2024-07-17 23:16:16
 */


#include <iostream>
#include <string>
using namespace std;

// ----------------- 用 初始化列表 来初始化属性 ---------------------------
class Person1
{
public:
    int m_A, m_B, m_C;
    
    // Person1() : m_A(10), m_B(20), m_C(30)
    // {

    // }
    // == 
    Person1(int a, int b, int c) : m_A(a), m_B(b), m_C(c)
    {
 
    }
};

void test1()
{
    // Person p;
    Person1 p(1, 2, 3);
    cout << "m_A = " << p.m_A << endl;  // 10   1
    cout << "m_B = " << p.m_B << endl;  // 20   2
    cout << "m_C = " << p.m_C << endl;  // 30   3
}

// --------------------------------------------------------------------

// --------------------------- 类对象作为类成员 ------------------------
class Phone
{
public:
    string p_name;
    Phone(string name)
    {
        p_name = name;
        cout << "Phone的构造函数已调用" << endl;
    }
    ~Phone()
    {
        cout << "Phone的析构函数已调用" << endl;
    }
};

class Person2
{
public:
    string m_name;
    Phone m_phone;   // Phone类对象作为Person类成员
    // m_phone是类对象                                       == Phone m_phone = phone_name  创建对象时的隐式转换法
    Person2(string name, string phone_name) : m_name(name), m_phone(phone_name)
    {
        cout << "Person的构造函数已调用" << endl;
    }
    ~Person2()
    {
        cout << "Person的析构函数已调用" << endl;
    }

};

void test2()
{
    Person2 p("张三", "华为");
    cout << p.m_name << " 的手机品牌是 " << p.m_phone.p_name << endl;  // 错误写法：p.m_phone
}

// --------------------------------------------------------------------

// ------------------------------ 静态成员 -----------------------------
/*
静态成员分为:
    静态成员变量
        。所有对象共享同一份数据，即静态成员变量不属于某一个对象
        。在编译阶段分配内存
        。类内声明，类外初始化，必须有初始值
        。类外无法访问类内私有的静态成员变量
    静态成员函数
        。所有对象共享同一个函数
        。静态成员函数只能访问静态成员变量

*/
class Person3
{
public:
    static int m_A;  // 类内声明
    int m_c = 2;

    // 静态成员函数
    static void func()
    {
        m_A = 111;  // 静态成员函数可以访问静态成员变量
        // m_c = 222; // error！！！
        cout << "静态成员函数已调用" << endl;
    }
private:
    static int m_B;

};

int Person3::m_A = 100;  // 类外初始化
int Person3::m_B = 300;  // 类外初始化

void test3()
{
    Person3 p;
    cout << p.m_A << endl;    // 100

    Person3 p2;
    p2.m_A = 200;
    cout << p.m_A << endl;    // 200  说明静态成员变量m_A是共享数据
    cout << p2.m_A << endl;   // 200

    // 通过类名访问静态成员变量
    cout << Person3::m_A << endl;  // 200

    //cout << Person3::m_B << endl;  // 报错！

    // 访问静态成员函数
    p.func();           // 静态成员函数已调用
    Person3::func();    // 静态成员函数已调用
}

// --------------------------------------------------------------------

// --------------------------- c++对象模型 -----------------------------
class Person4
{
    int m_A;                // 非静态成员变量，属于类的对象，
    static int m_B;         // 静态成员变量，不属于类的对象，不占用类对象的空间
    void func(){}           // 非静态成员函数，不属于类的对象，不占用类对象的空间
    static void func2(){}   // 静态成员函数，不属于类的对象，不占用类对象的空间

};
int Person4::m_B = 1;

void test4()
{
    Person4 p;
    cout << "size of p = " << sizeof(p) << endl;  
    // class Person4类内无代码时: size of p = 1, 因为c++编译器会给每个空对象也分配一个字节空间，以区分空对象占内存的位置，每个空对象应该有一个独一无二的内存地址
    // class Person4类内有 int m_A; 时，size of p = 4，对象不为空，则按照实际大小分配内存
    // class Person4类内有143、144、145行时，size of p = 4，不变，上面已解释
}

// --------------------------------------------------------------------

// ---------------------------- this指针 -------------------------------
/*
    this指针的作用：
        1. 解决名称冲突
        2. 返回对象本身用 *this
*/
class Person5
{
public:
    int age;
    Person5(int age)
    {
        // this指针指向被调用的成员函数所属的对象
        this->age = age;    // 解决名称冲突
    }

    // 返回对象本体，则这里应写成 Person5&，若是 Person5 则返回的是一个新的对象，就不是原对象
    Person5& add_age(Person5 &p)
    {
        this->age += p.age;

        // this是指向对象p2的指针，而*this指向的就是p2这个对象本体
        return *this;  
    }

};

void test5()
{
    Person5 p(18);
    cout << "p年龄为" << p.age << endl;    // p年龄为18

    Person5 p2(19);

    // 当为 void add_age(Person5 &p){...}时
    // p2.add_age(p);
    // cout << "p2相加后的年龄为 " << p2.age << endl;  // p2相加后的年龄为 37

    // 当为 Person5& add_age(Person5 &p){...}时，则可以写成
    p2.add_age(p).add_age(p).add_age(p);  // 后面可以一直继续下去
    cout << "p2相加后的年龄为 " << p2.age << endl;  // p2相加后的年龄为 73  == 19 + 18 * 3

    // 若是 Person5 add_age(Person5 &p){...}，则  p2.add_age(p).add_age(p).add_age(p) 结果为37，因为调用add_age()返回时一直在创建新的对象，每次都是新对象的19加上对象p的18
}

// --------------------------------------------------------------------

// ------------------------- const修饰成员函数 -------------------------
/*
常函数:
    成员函数后加const后我们称为这个函数为常函数
    常函数内不可以修改成员属性
    成员属性声明时加关键字mutable后，在常函数中依然可以修改
常对象:
    声明对象前加const称该对象为常对象
    常对象只能调用常函数
*/
class Person6
{
public:
    int m_A = 100;
    mutable int m_B = 300;
    // 在成员函数后面加const，修饰的是this指针，让指针指向的值也不可以修改
    void show() const   // 常函数
    {   // this指针的本质是指针常量(指针的指向是不可修改的，即始终指向该类创建的某个对象)
        // m_A = 200;  // 等价于this.m_A = 200   error
        m_B = 333;  // mutable修饰的变量在常函数中也能修改其值
        cout << "show函数已调用" << endl;
    }
    void func()
    {
        m_A = 111;
        cout << "func函数已调用" << endl;
    }
    
};

void test6()
{
    const Person6 p;   // 常对象
    // p.m_A = 200;    // error  常对象的属性值不可修改
    p.m_B = 333;       // mutable修饰的可以修改
    p.show();          // show函数已调用
    // p.func();       // 常对象只能调用常函数,不可调用普通成员函数，因为普通成员函数可以修改非mutable属性值
}

// --------------------------------------------------------------------

// ------------------------------- 友元 ------------------------------- 
/*  友元的目的就是让一个函数或者类访问另一个类中私有成员
友元的三种实现：
    全局函数做友元
    类做友元
    成员函数做友元

关键字：friend

*/
class Building
{
    // 全局函数做友元，可以访问私有成员
    friend void myFriend(Building &building);
    // 类做友元，可以访问私有成员
    friend class goodFriend;
    // 成员函数做友元，可以访问私有成员             有点问题！！！https://www.bilibili.com/video/BV1et411b73Z?p=120&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
    // friend void goodFriend::visit_friend();
public:
    string living_room;

    Building()
    {
        living_room = "客厅";
        my_room = "卧室";
    }

private:
    string my_room;
};

// 全局函数做友元
void myFriend(Building &building)    // 添加262行成为友元函数，才能访问私有成员my_room
{   
    cout << "我的朋友正在参观" << building.living_room << endl; // 我的朋友正在参观客厅
    cout << "我的好朋友正在参观" << building.my_room << endl;   // 我的好朋友正在参观卧室
}

void test7()
{
    Building building;
    myFriend(building);    
}

// 类作友元
class goodFriend
{
public:
    Building *building;
    goodFriend()  // 构造函数
    {
        building = new Building();    // 在堆区创建一个Building对象，返回的是一个指针，所以要用指针接收
    }
    void visit()
    {
        cout << "我的朋友正在参观" << building->living_room << endl; // 我的朋友正在参观客厅
        cout << "我的好朋友正在参观" << building->my_room << endl;   // 我的好朋友正在参观卧室
    }
    // 成员函数作友元(假设该类不是友元类)   有点问题！！！看视频没怎么懂
    // void visit_friend()
    // {
    //     cout << "我的朋友正在参观" << building->living_room << endl; // 我的朋友正在参观客厅
    //     cout << "我的好朋友正在参观" << building->my_room << endl;   // 我的好朋友正在参观卧室
    // }
};

void test8()
{
    goodFriend gf;
    gf.visit();
}


int main()
{
    test1();

    test2();
    /* 内层构造函数先调用，外层析构函数先调用：
        Phone的构造函数已调用
        Person的构造函数已调用
        张三 的手机品牌是 华为
        Person的析构函数已调用
        Phone的析构函数已调用
    */

    test3();

    test4();

    test5();

    test6();

    test7();

    test8();


    return 0;
}
