/*
 * @Description:                    pair对组
 * @Author:  shang guan meng luo
 * @version: 
 * @Date: 2024-10-04 20:57:15
 * @LastEditTime: 2024-10-04 20:57:19
 */


/*
pair对组: 
成对出现的数据，利用对组可以返回两个数据

创建：
pair<type, type> p(value1, value2);
pair<type,type> p = make_pair(value1,value2);
*/


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

 
void test()
{
    // 方式一：
    pair<string, int> p("Tom", 12);
    cout << "name: " << p.first << "   age: " << p.second << endl;    // name: Tom   age: 12

    // 方式二：
    pair<string, int> p2 = make_pair("Jack", 16);
    cout << "name: " << p2.first << "   age: " << p2.second << endl;  // name: Jack   age: 16
}

int main()
{
    test();


    return 0;
}