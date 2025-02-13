/*
 * @Description:                   stack容器：先进后出      栈
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 09:40:44
 * @LastEditTime: 2024-10-04 09:49:13
 */

/*
stack容器：
栈中只有顶端的元素才可以被外界使用，因此栈不允许有遍历行为

构造函数:
stack<T> stk;                       stack采用模板类实现，stack对象的默认构造形式
stack(const stack &stk);            拷贝构造函数

赋值操作:
stack& operator=(const stack &stk); 重载等号操作符

数据存取:
push(elem);     向栈顶添加元素
pop();          从栈顶移除第一个元素
top();          返回栈顶元素

大小操作:
empty();        判断堆栈是否为空
size();         返回栈的大小
*/

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
using namespace std;

void test()
{
    stack<int> s;

    // 入栈
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "栈的大小为: " << s.size() << endl; // 栈的大小为: 3

    while (!s.empty())
    {
        cout << "栈顶元素为: " << s.top() << endl;
        // 栈顶元素出栈
        s.pop();
    }

    // 栈顶元素为: 3
    // 栈顶元素为: 2
    // 栈顶元素为: 1
}

int main()
{
    test();

    return 0;
}