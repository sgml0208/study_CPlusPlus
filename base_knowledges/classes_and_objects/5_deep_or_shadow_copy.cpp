/*
 * @Description:         深拷贝与浅拷贝
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-11 22:42:59
 * @LastEditTime: 2024-07-11 23:23:06
 */
/*
浅拷贝: 简单的赋值拷贝操作              可能带来的问题就是：堆区的内容重复释放，深拷贝则可以解决这个问题
深拷贝: 在堆区重新申请空间，进行拷贝操作

注意：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题
*/

#include <iostream>
#include <string>
using namespace std;

class Person
{
public:  
    int p_age;
    int *p_height;
    // 无参构造函数(默认构造函数)
    Person()        
    { 
        cout << "无参构造函数被调用（编译器自动调用）" << endl;
    }
    // 有参构造函数
    Person(int age, int height)   
    {
        p_age = age; 
        p_height = new int(height);   // 堆区数据   new int()：返回的是int *类型
        cout << "有参构造函数被调用（编译器自动调用）, 年龄为: " << p_age << endl;
    }

    //深拷贝构造函数
    Person(const Person &p)   // p这个人不可被修改，以引用的方式传入
    {
        
        p_age = p.p_age; // 将传入人的年龄拷贝到自己身上
        // p_height = p.p_height; // 编译器默认实现这个代码

        // 深拷贝操作       *: 解引用
        p_height = new int(*p.p_height);  // 在堆区开辟一个新空间，内容为要拷贝的数据，这样就有两个空间存了一样的值，不同Person对象的析构函数释放空间时就会释放自己的空间
                                          // 从而避免了浅拷贝操作时堆区内容重复释放的错误
        cout << "拷贝构造函数被调用（编译器自动调用）年龄为: " << p_age  << endl;
    }
    
    // ~Person()  // 析构函数   浅拷贝用
    // {
    //     cout << "析构函数被调用（编译器自动调用）" << endl;
    // }

    ~Person()  // 析构函数   深拷贝用
    {
        // 将堆区开辟的数据空间释放掉
        if(p_height != NULL){
            delete p_height;
            p_height = NULL; // 防止野指针
        }
        cout << "析构函数被调用（编译器自动调用）" << endl;
    }


};

// void test01()
// {
//     Person p1(18);
//     cout << "p1的年龄为 " << p1.p_age << endl;

//     Person p2(p1);        // 这里没有提供拷贝构造函数(上面拷贝构造函数还没写时)，但是编译器默认会提供浅拷贝操作
//     cout << "p2的年龄为 " << p2.p_age << endl;

// }

void test02()
{
    Person p1(18, 170);
    cout << "p1的年龄为 " << p1.p_age << endl;

    Person p2(p1);        
    cout << "p2的年龄为 " << p2.p_age << endl;

}

int main(int argc, char const *argv[])
{
    //test01();
    test02();

    
    return 0;
}
