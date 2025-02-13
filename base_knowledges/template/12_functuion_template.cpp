/*
 * @Description:               函数模板
 * @Author:  shang guan meng luo
 * @version: 
 * @Date: 2024-10-01 13:12:15
 * @LastEditTime: 2025-02-13 19:37:58
 */


#include <iostream>
using namespace std;

template<class T>
void mySwap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template<class T>
// 在C++中，数组作为函数参数时，会自动退化为指向数组首元素的指针
// 参数T arr[]实际上并不是传递数组本身，而是传递了一个指向数组首元素的指针。因此，即使没有使用引用，数组的内容也会被正确访问和修改
void printArr(T arr[], int len)  // == void printArr(T* arr, int len);
{
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

template<class T>
void mySelectSort(T arr[], int len)      // 函数模板实现选择排序
{
    for (int i = 0; i < len; i++)
    {
        int max = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[max] < arr[j])
                max = j;
        }
        if (max != i)
            mySwap(arr[max], arr[i]);
    }

}

void test1()
{
    char charArr[] = "ghabwfjsvxc";
    int len = sizeof(charArr) / sizeof(char);
    mySelectSort(charArr, len);
    printArr(charArr, len);
}

void test2()
{
    int intArr[] = {9, 3, 7, 4, 8, 1, 2, 6, 5};
    int len = sizeof(intArr) / sizeof(int);
    mySelectSort(intArr, len);
    printArr(intArr, len);
}




/*
普通函数与函数模板的调用规则:
    1.如果函数模板和普通函数都可以实现，优先调用普通函数
    2.可以通过空模板参数列表来强制调用函数模板
    3.函数模板也可以发生重载
    4.如果函教模板可以产生更好的匹配,优先调用函数模板

总结:既然提供了函数模板，最好就不要提供普通函数，否则容易出现二义性 
*/

void myPrint(int a, int b)
{
    cout << "调用的是普通函数" << endl;
}

template<class T>
void myPrint(T a, T b)
{
    cout << "调用的是模板" << endl;
}

template<class T>
void myPrint(T a, T b, T c)
{
    cout << "调用的是函数重载的模板" << endl;
}

void test3()
{
    int a = 11;
    int b = 22;
    int c = 33;
    myPrint(a, b);         // 调用的是普通函数              符合第1条
    myPrint<int>(a, b);    // 调用的是模板
    myPrint<>(a, b);       // 调用的是模板                  符合第2条
    myPrint(a, b, c);      // 调用的是函数重载的模板         符合第3条

    char c1 = 'a';
    char c2 = 'b';
    myPrint(c1, c2);       // 调用的是模板，普通函数也可以调用，因为可以隐式转换，将char转成int，但是函数模板更匹配，符合第4条
}


int main()
{
    test1();
    test2();
    test3();

    return 0;
}