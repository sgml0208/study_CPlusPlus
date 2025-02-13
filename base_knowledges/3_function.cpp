/*
 * @Description:         函数   https://www.bilibili.com/video/BV1et411b73Z?p=95&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-07-09 21:23:38
 * @LastEditTime: 2025-02-12 16:38:22
 */

#include <windows.h>
#include <iostream>
using namespace std;

// 默认参数
// 1.默认参数后的所有形参都应该设有默认值
void fun1(int a, int b = 10, int c = 20) // (int a, int b = 10, int c) c没有默认值，错误！！！
{
    cout << a + b + c << endl;
}

// 2.如果函数声明有默认参数，则函数实现不能带有默认参数，因为若两个都有，如果不一样，编译器不知道该用哪个
//   即函数声明和实现最多只能有一个带默认参数
void fun2(int a = 1, int b = 2);

// 函数的占位参数
void fun3(int a, int) // 第二个int就是占位用的  (int a, int = 10)占位参数还可以有默认值
{
    cout << "a为: " << a << endl; // a为: 11
}

// ------------------- 函数重载 ---------------------------
/*
函数重载作用:函数名可以相同，提高复用性

函数重载满足条件:
    ·同一个作用域下
    ·函数名称相同
    ·函数参数类型不同或者个数不同或者顺序不同

函数的返回值不可以作为函数重载的条件

*/
void fun_cz()
{
    cout << "函数重载，此时没有参数" << endl;
}

void fun_cz(int a)
{
    cout << "函数重载，有一个int型参数，值为：" << a << endl;
}

// 个数不同
void fun_cz(int a, int b)
{
    cout << "函数重载，有两个int型参数，值为：" << a << ' ' << b << "，和为：" << a + b << endl;
}

// 类型不同
void fun_cz(double a) // 这里float类型不行
{
    cout << "函数重载，有一个double型参数，值为：" << a << endl;
}
/*
如果你尝试添加一个接受 float 类型参数的版本： void fun_cz(float a);
这可能会导致问题，原因如下：
1. 隐式类型转换
C++中，float 类型可以隐式地转换为 double 类型，但 double 类型不能隐式地转换为 float 类型。因此，
当调用 fun_cz 并传递一个 float 类型的参数时，编译器会优先选择已经存在的 fun_cz(double a)，而不是新定义的 fun_cz(float a)。
2. 函数重载的歧义
如果同时存在 fun_cz(float a) 和 fun_cz(double a)，当调用 fun_cz 并传递一个 float 类型的参数时，编译器会面临选择问题：
float 可以隐式转换为 double，因此 fun_cz(double a) 也是合法的候选函数。这会导致函数调用的歧义，编译器无法确定应该调用哪一个版本。
    故通常不建议在函数重载中同时使用 float 和 double 类型的参数。
*/

// 参数顺序不同
void fun_cz(int a, double b)
{
    cout << "函数重载，有两个参数，值为：" << a << ' ' << b << "，和为：" << a + b << endl;
}

void fun_cz(double a, int b)
{
    cout << "函数重载，有两个参数，值为：" << a << ' ' << b << "，和为：" << a + b << endl;
}

// 函数重载的注意事项
// 1. 引用作为重载的条件
void fun_cz_quote(int &a)
{
    cout << "fun_cz_quote(int &a)被调用" << endl;
}

void fun_cz_quote(const int &a) // 与上面属于类型不同
{
    cout << "fun_cz_quote(const int &a)被调用" << endl;
}

int main()
{
    SetConsoleOutputCP(65001); // 设置控制台输出编码为UTF-8

    fun1(1);
    fun2();
    fun3(11, 2); // 2不写则报错，但是要有，目前用不到

    // 函数重载
    fun_cz();
    fun_cz(6);
    fun_cz(6, 8);
    fun_cz(3.7); // 这里float类型不行
    fun_cz(1, 3.3);
    fun_cz(3.3, 1);

    int d_quote = 12;
    fun_cz_quote(d_quote); // fun_cz_quote(int &a)被调用, 因为d_quote是一个变量
    fun_cz_quote(12);      // fun_cz_quote(const int &a)被调用

    return 0;
}

void fun2(int a, int b) // 如果函数声明有默认参数，则函数实现不能带有默认参数
{
    cout << a + b << endl;
}
