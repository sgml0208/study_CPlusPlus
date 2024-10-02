/*
 * @Description:                类模板文件
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-02 19:10:48
 * @LastEditTime: 2024-10-02 19:14:55
 */

// .hpp文件一般是.h和.cpp文件(声明与实现)的结合

#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class T1, class T2>
class Person5
{
public:
    T1 m_name;
    T2 m_age;
    Person5(T1 name, T2 age);
    
    void show();
    
};

template<class T1, class T2>    // 需要加
Person5<T1, T2>::Person5(T1 name, T2 age)
{
    this->m_name = name;
    this->m_age = age;
}

template<class T1, class T2>    // 需要加
void Person5<T1, T2>::show()
{
    cout << "name: " << this->m_name << "    age: " << this->m_age << endl;
}
