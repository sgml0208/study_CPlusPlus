/*
 * @Description:                    类模板案例：实现一个通用数组类
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-02 20:05:26
 * @LastEditTime: 2025-02-13 20:27:48
 */

#pragma once
#include <string>
#include <iostream>
using namespace std;

template <class T>
class MyArray
{
private:
    T *pAddress;    // 指针指向堆区开辟的真实数组空间
    int m_capacity; // 数组容量
    int m_size;     // 数组大小

public:
    // 有参构造函数
    MyArray(int capacity) // 初始容量
    {
        cout << "调用有参构造函数" << endl;
        this->m_capacity = capacity;
        this->m_size = 0;                         // 数组中刚开始没有数据
        // this->pAddress = new T[this->m_capacity]; // error!!!
        pAddress = new T[this->m_capacity]; // 初始化时开辟数组空间
        /*
        this->在某些情况下是必要的，比如当成员变量和局部变量同名时，需要用this->来区分。但在代码中，pAddress没有
        局部变量同名，因此this->是多余的。直接写pAddress = new T[this->m_capacity];更简洁，也更符合常见的C++代码风格
        */
    }

    // 防止浅拷贝问题，提供拷贝构造函数
    MyArray(const MyArray &arr)
    {
        cout << "调用拷贝构造函数" << endl;
        this->m_capacity = arr.m_capacity;
        this->m_size = arr.m_size;
        // 浅拷贝操作
        // this->pAddress = arr.pAddress;  这里有问题，会导致堆区的数据重复释放
        // 深拷贝
        this->pAddress = new T[arr.m_capacity];
        // 将arr中的数据都拷贝过来
        for (int i = 0; i < this->m_size; i++)
            this->pAddress[i] = arr.pAddress[i];
    }

    // 重载operator= 防止浅拷贝带来的问题
    MyArray &operator=(const MyArray &arr)
    {
        cout << "调用重载operator=函数" << endl;
        // 先判断原来堆区是否有数据，若有先释放
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
            this->m_capacity = 0;
            this->m_size = 0;
        }

        // 深拷贝
        this->m_capacity = arr.m_capacity;
        this->m_size = arr.m_size;
        this->pAddress = new T[arr.m_capacity];
        // 将arr中的数据都拷贝过来
        for (int i = 0; i < this->m_size; i++)
            this->pAddress[i] = arr.pAddress[i];

        return *this;
    }

    // 尾插法插入数据
    void pushBack(const T &val)
    {
        // 先判断容量是否满了
        if (this->m_capacity == this->m_size)
        {
            cout << "数组已满，不能再插入数据!" << endl;
            return;
        }
        this->pAddress[this->m_size] = val;
        this->m_size++;
    }

    // 尾删法删除数据
    void popBack()
    {
        // 让用户访问不到最后一个元素，即为逻辑上的删除
        if (this->m_size == 0)
        {
            cout << "数组已为空，无法再删除元素!" << endl;
            return;
        }
        this->m_size--;
    }

    // 通过数组下标访问数组，重载operator[]
    T &operator[](int index)
    {
        return this->pAddress[index]; // 若返回的数据还需作为等号的左值存在，需要返回引用
    }

    // 返回数组的容量
    int getCapacity()
    {
        return this->m_capacity;
    }

    // 返回数组的大小
    int getSize()
    {
        return this->m_size;
    }

    ~MyArray()
    {
        cout << "调用析构函数" << endl;
        if (this->pAddress != NULL)
        {
            delete[] this->pAddress;
            this->pAddress = NULL;
        }
    }
};
