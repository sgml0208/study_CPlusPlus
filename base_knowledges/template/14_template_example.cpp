/*
 * @Description:                 类模板案例： 实现一个通用数组类
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-02 19:50:18
 * @LastEditTime: 2024-10-02 21:57:40
 */


/*
要求：
    可以对内置数据类型以及自定义数据类型的数据进行存储
    将数组中的数据存储到堆区
    构造函数中可以传入数组的容量
    提供对应的拷贝构造函数以及operator=防止浅拷贝问题
    提供尾插法和尾删法对数组中的数据进行增加和删除
    可以通过下标的方式访问数组中的元素
    可以获取数组中当前元素个数和数组的容量

*/



#include <iostream>
#include "myArray.hpp"

using namespace std;

void printArray(MyArray<int> &arr)
{
    for (int i = 0; i < arr.getSize(); i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void test()
{
    MyArray<int> arr1(10);
    // MyArray<int> arr2(arr1);     // 测试拷贝构造函数
    // MyArray<int> arr3(100);      // 测试operator=
    // arr3 = arr1;
    
    for (int i = 0; i < 5; i++)
        arr1.pushBack(i);           // 尾插法插入数据
    cout << "arr1的数据为: ";
    printArray(arr1);
    cout << "capacity: " << arr1.getCapacity() << endl;   // capacity: 10
    cout << "size: " <<arr1.getSize() << endl;        // size: 5
    
}


// 自定义数据类型
class Person
{
public:
    string m_name;
    int m_age;
    Person(){};   // 提供一个默认构造函数是个好习惯，因为它可以增加类的灵活性和易用性。
    // Person1() = default;  // c++11标准： 要求编译器生成默认构造函数
    Person(string name, int age)
    {
        this->m_age = age;
        this->m_name = name;
    }
    // 如果你没有定义任何构造函数，编译器会自动生成一个默认构造函数。
    // 但是，一旦定义了任何构造函数（比如有参构造函数），编译器就不会再自动生成默认构造函数了。
};

void printPerson(MyArray<Person> &arr)
{
    for (int i = 0; i < arr.getSize(); i++)
    {
        cout << "name: " << arr[i].m_name <<"   age: " << arr[i].m_age << endl;
    }
}

void test2()
{
    MyArray<Person> arr(12);   // 创建对象数组时，C++ 会尝试为每个数组元素调用默认构造函数，若编译器无法找到默认构造函数则报错
    Person p1("zhangsan", 11);
    Person p2("lisi", 22);
    Person p3("wangwu", 33);
    Person p4("zhaoliu", 44);

    arr.pushBack(p1);
    arr.pushBack(p2);
    arr.pushBack(p3);
    arr.pushBack(p4);

    printPerson(arr);
    cout << "capacity: " << arr.getCapacity() << endl;   // capacity: 12
    cout << "size: " << arr.getSize() << endl;        // size: 4
}

int main()
{
    test();

    test2();


    return 0;
}


