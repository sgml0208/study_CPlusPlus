/*
 * @Description:          程序的内存模型    https://www.bilibili.com/video/BV1et411b73Z?p=84&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version: 
 * @Date: 2024-07-02 16:48:20
 * @LastEditTime: 2024-07-09 07:14:58
 */

/*
内存分区模型
    C++程序在执行时，将内存大方向划分为4个区域：
    程序运行前：
        在程序编译后，生成了exe可执行程序，未执行该程序前分为两个区域
        1.代码区:
            存放CPU执行的机器指令，由操作系统进行管理的
            代码区是共享，共享的目的是对于频繁被执行的程序，只需要在内存中有一份代码即可
            代码区是只读，使其只读的原因是防止程序意外地修改了它的指令
        2.全局区:
            存放全局变量、静态变量、字符串常量、其他常量、
            该区域的数据在程序结束后由操作系统释放.
        程序运行后：
            栈区:由编译器自动分配释放,存放函数的参数值,局部变量等，不可返回局部变量的地址
            堆区︰由程序员分配和释放,若程序员不释放,程序结束时由操作系统回收
    
    
内存四区意义:
    不同区域存放的数据，赋予不同的生命周期,给我们更大的灵活编程

*/

// -------------------- new关键字 -------------------------

#include <iostream>
using namespace std;

int * func1()
{
    // 将数据开辟到堆区
    int * p = new int(10);  // *p = 10    !!!!!
    return p;   // 返回数据的地址
}

int * func2()
{
    // 创建10个数据的数组
    int * arr = new int[10];  // arr[10]   !!!!!
    for (int i = 0; i < 10; i++)
        arr[i] = i + 10;
    return arr;   // 返回数组的首地址
}


int main()
{
    int *d = func1();
    cout << *d << "的地址为：" << d << endl;
    delete d;  // 释放指针p所指的空间

    int *arr = func2();
    cout << "数组的数据为：";
    for (int i = 0; i < 10; i++)
        cout << arr[i] << ' ';
    cout << endl;
    delete[] arr;  // 释放数组空间
    
    return 0;
}

















