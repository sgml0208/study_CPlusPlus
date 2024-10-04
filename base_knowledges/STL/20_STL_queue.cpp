/*
 * @Description:                    queue容器；先进先出      队列
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 09:48:23
 * @LastEditTime: 2024-10-04 19:28:40
 */


/*
queue容器：队尾进队头出     只有队头和队尾能被外界访问，因此不允许有遍历行为

构造函数:
queue<T> que;               queue采用模板类实现，queue对象的默认构造形式
queue(const queue &que);    拷贝构造函数

赋值操作:
queue& operator=(const queue &que);  重载等号操作符

数据存取:
push(elem);     往队尾添加元素
pop();          从队头移除第一个元素
back();         返回最后一个元素
front();        返回第一个元素

大小操作:   
empty();        判断堆栈是否为空
size();         返回栈的大小
*/


#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

void test()
{
    queue<int> q;
    
    //入队
    q.push(1);
    q.push(2);
    q.push(3);    
    
    cout << "队列的大小为: " << q.size() << endl;   // 队列的大小为: 3
    cout << "队头元素为: " << q.front() << endl;    // 队头元素为: 1
    cout << "队尾元素为: " << q.back() << endl;     // 队尾元素为: 3

    cout << "元素出队顺序为: ";        // 元素出队顺序为: 1 2 3 
    while (!q.empty())
    {
        cout << q.front() << ' ';
        q.pop();
    }
    cout << endl;
}

int main()
{
    test();

    return 0;
}