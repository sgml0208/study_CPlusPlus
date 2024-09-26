/*
 * @Description:       类与对象   https://www.bilibili.com/video/BV1et411b73Z/?p=99&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-09 22:04:21
 * @LastEditTime: 2024-07-10 23:52:44
 */

/*
三大特性: 继承、封装、多态

三种权限
    公共权限    public      类内可以访问    类外可以访问
    保护权限    protected   类内可以访问    类外不可访问  继承时子类可以访问父类的保护内容
    私有权限    private     类内可以访问    类外不可访问  继承时子类不可以访问父类的私有内容


*/

#include <iostream>
#include <string>
using namespace std;

class Student
{
public:
    // 属性
    string stu_name; // 姓名
    int stu_id;      // 学号
    // 行为
    void show_stu()
    {
        cout << "姓名为 " << stu_name << ", 学号为 " << stu_id << endl;
    }

    void setName(string name)
    {
        stu_name = name;
    }
};

// ------------------- struct和class的区别 ------------------------
/*
在C++中struct和class唯—的区别就在于默认的访问权限不同
    区别: struct默认权限为公共. class默认权限为私有
    struct也可以写类
*/
class C1
{
    int m_A;  // 默认为私有权限
};

struct S1
{
    int m_A;  // 默认为公共权限
};
// -----------------------------------------------------------------

class Person
{
private:
    string p_name;  // 姓名 可读可写
    int p_age = 13; // 年龄 只可读，默认13
    int p_id;       // id   只可写

public:  // 将成员属性设置为私有，防止外部访问，而通过将一些对属性进行操作的行为设置为公有，从而操作属性
    void setName(string name)  // 写姓名
    {
        if (name.length() > 10)   // 控制输入的数据规范性
        {
            cout << "名字过长！" << endl;
            return ;
        }
        p_name = name;
    }
    string getName()           // 读姓名
    {
        return p_name;
    }
    int getAge()                // 读年龄
    {
        return p_age;
    }
    void setID(int id)          // 写id
    {
        p_id = id;
    }

// ----------------------构造函数和析构函数---------------------------
/*
·构造函数:主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。
·析构函数:主要作用在于对象销毁前系统自动调用，执行一些清理工作。

C++利用了构造函数和析构函数解决上述问题，这两个函数将会被编译器自动调用，完成对象初始化和清理工作。对象的初始化和清理工作是编译器强制要我们做的事情，
因此如果我们不提供构造和析构，编译器会提供编译器提供的构造函数和析构函数是空实现。

构造函数可以有参数，因此可以发生重载；析构函数不可以有参数，因此不可以发生重载
程序在调用对象时候会自动调用构造函数，无须手动调用,而且只会调用一次
程序在对象销毁前会自动调用析构函数，无须手动调用,而且只会调用—次
*/
    // 无参构造函数(默认构造函数)
    Person()        
    {
        cout << "无参构造函数被调用（编译器自动调用）" << endl;
    }
    // 有参构造函数
    Person(int a)   
    {
        p_age = a; 
        cout << "有参构造函数被调用（编译器自动调用）, 年龄为: " << p_age << endl;
    }
    // 下面这种是拷贝构造函数，其余都是普通构造函数（按类型分的话）
    Person(const Person &p)   // p这个人不可被修改，以引用的方式传入
    {
        p_age = p.p_age; // 将传入人的年龄拷贝到自己身上
        cout << "拷贝构造函数被调用（编译器自动调用）年龄为: " << p_age  << endl;
    }
    ~Person()  // 析构函数
    {
        cout << "析构函数被调用（编译器自动调用）" << endl;
    }


};

// 构造函数的三种调用方式:
void test_diaoyong()
{
    // 1. 括号法
    Person p1;   // 不要写成 Person p1(); 这种写法编译器会认为是函数的声明，不会认为在创建对象
    // // 无参构造函数被调用（编译器自动调用）
    // // 析构函数被调用（编译器自动调用）
    Person p2(10);
    // // 有参构造函数被调用（编译器自动调用）, 年龄为: 10
    // // 析构函数被调用（编译器自动调用）
    Person p3(p1);
    // // 拷贝构造函数被调用（编译器自动调用）年龄为: 10
    // // 析构函数被调用（编译器自动调用）

    // 2. 显示法
    Person p4;               // 无参构造
    Person p5 = Person(10);  // 有参构造
    Person p6 = Person(p5);  // 拷贝构造

    Person(10);    // 匿名对象   调用有参构造  当前行执行结束后，系统会立即回收掉匿名对象，因为匿名对象在后续代码中无法使用
    
    // Person(p6); 错误！ 因为不可利用拷贝构造函数来初始化匿名对象，编译器会将 Person (p6) 看成 Person p6; 而上面145行有了P6,会报重定义错误！

    // 3. 隐式转换法
    Person p7 = 10;  // 相当于 Person p7 = Person(10); 调用有参构造函数
    Person p8 = p7;  // 调用拷贝构造函数

}

/*
C++中拷贝构造函数调用时机通常有三种情况：
    1· 使用一个已经创建完毕的对象来初始化—个新对象
    2· 值传递的方式给函数参数传值
    3· 以值方式返回局部对象
*/
// 2. 值传递的方式给函数参数传值
void doWork(Person p)
{
    
}
// 3· 以值方式返回局部对象
Person doWork2()   // 值返回，即拷贝一个副本返回
{
    Person p1;
    cout << "p1的地址为" << (int *)&p1 << endl;
    return Person(p1); 
}
void test_kaobei()
{
    // 1. 使用一个已经创建完毕的对象来初始化—个新对象
    // Person p1(20);
    // Person p2(p1);
    // cout << "p2的年龄为 " << p2.getAge() << endl;  // p2的年龄为 20
    
    // 2. 值传递的方式给函数参数传值
    // Person p3;
    // doWork(p3);

    // 3. 以值方式返回局部对象
    Person p4 = doWork2();
    cout << "p4的地址为" << (int *)&p4 << endl;   // p1和doWork2()返回的p1的地址不一样，不是同一个对象，是拷贝的
    
}
// -----------------------------------------------------------------
/*
构造函数调用规则如下:
    如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造
    如果用户定义拷贝构造函数，C++不会再提供其他构造函教
*/



int main()
{
    // 创建一个具体学生
    Student stu1;
    stu1.stu_name = "zhang san";
    stu1.stu_id = 101;
    stu1.show_stu(); // 姓名为 zhang san, 学号为 101
    Student stu2;
    stu2.setName("xiao hong");
    stu2.stu_id = 102;
    stu2.show_stu(); // 姓名为 xiao hong, 学号为 102

    // Person p1;
    // p1.setName("zhangsan");
    // cout << p1.getName() << endl;  // zhangsan
    /*
    构造函数被调用（编译器自动调用）
    zhangsan
    析构函数被调用（编译器自动调用） main函数执行结束，p1对象被销毁时执行析构函数
    */

    // test_diaoyong();

    test_kaobei();

    return 0;
}
