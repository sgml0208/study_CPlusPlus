/*
 * @Description:          c++ 引用(别名):  数据类型 &别名 = 原名
 * @Author:  shang guan meng luo     https://www.bilibili.com/video/BV1et411b73Z?p=89&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @version:
 * @Date: 2024-07-09 07:16:27
 * @LastEditTime: 2025-02-12 16:06:35
 */

/*
注意：
    引用必须初始化
    引用在初始化后，不可以改变
    不可返回局部变量的引用
    引用必须引一块合法的内存空间  (int &d = 10; xxx)

引用的本质：在c++内部实现是一个指针常量(指针的指向不可修改，指向的值可以修改)
            == int * const ref = &a;
*/

#include <iostream>
using namespace std;

void swap_addr(int *a, int *b) // 地址传递
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_quote(int &a, int &b) // 引用传递
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

// 返回的是的引用
int &test1()
{
    static int t_a = 100; // 静态变量存放在全局区，全局区上的数据在程序结束后由系统释放
    return t_a;           // 返回的是a的引用
}

int main()
{
    int a = 10;
    int &b = a;                          // 即b为a的别名
    cout << b << endl;                   // 10
    cout << "a的地址为: " << &a << endl; // a的地址为：0x1e649ffd24
    cout << "b的地址为: " << &b << endl; // b的地址为：0x1e649ffd24
    b = 20;
    cout << a << endl; // 20

    // int &c;  // 错误：引用必须初始化
    int c = 30;
    b = c;             // 这是赋值操作，不是更改引用 !!!
    cout << b << endl; // 30
    cout << a << endl; // 30

    // ------------------------------

    int x = 10;
    int y = 20;

    // swap_addr(&x, &y);   // 地址传递
    swap_quote(x, y); // 引用传递

    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    // ------------------------------

    int &ref1 = test1(); // ref1 = t_a;

    cout << "ref1 = " << ref1 << endl; // 100  若test1函数中t_a是局部变量，这里输出正确，因为系统会保留一次局部变量的值
    // cout << "ref1 = " << ref1 << endl; // 100  若test1函数中t_a是局部变量，这里输出错误，因为局部变量a已经释放了(test1函数执行结束)

    test1() = 111; // 等价于 ref1 = t_a = 111   若函数的返回值是引用，则这个函数调用可以作为左值

    cout << "ref1 = " << ref1 << endl; // 111

    // ------------------------------

    // 常量引用
    // int &d = 10; // 错误：引用必须引一块合法的内存空间
    const int &d = 10;  // 等价于 int temp = 10; const int &d = temp;
    // d = 10; 错误，const修改表明不可修改其值


    return 0;
}

