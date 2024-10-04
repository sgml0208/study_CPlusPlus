/*
 * @Description:                    map容器
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 22:14:44
 * @LastEditTime: 2024-10-04 23:13:31
 */

/*
map中所有元素都是pair
pair中第一个元素为key(键值)，起到索引作用，第二个元素为value(实值)
所有元素都会根据元素的键值自动排序！！！
本质:
map/multimap属于关联式容器，底层结构是用二叉树实现

优点:
可以根据key值快速找到value值   性能高，效率高

map和multimap区别
map不允许容器中有重复key值元素
multimap允许容器中有重复key值元素
*/

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
using namespace std;

template <class T1, class T2>
void printMap(const map<T1, T2> &m)
{
    // 方法1:
    // for (typename map<T1, T2>::const_iterator it = m.begin(); it != m.end(); it++)
    //     cout << "key = " << it->first << "\t\tvalue = " << (*it).second << endl;
    // cout << endl;

    // 方法2: 使用auto(c++11标准): auto关键字会自动推导出正确的迭代器类型
    for (auto it = m.begin(); it != m.end(); it++)
        cout << "key = " << it->first << "\t\tvalue = " << (*it).second << endl;
    cout << endl;
}

template <class T1, class T2>
void printMultiMap(const map<T1, T2> &m)
{
    for (auto it = m.begin(); it != m.end(); it++)
        cout << "key = " << it->first << "\t\tvalue = " << (*it).second << endl;
    cout << endl;
}

/*
构造:
map<T1,T2> mp;          map默认构造函数
map(const map &mp);     拷贝构造函数
赋值:
map& operator=(const map &mp);      重载等号操作符
*/
void test1()
{
    map<int, int> m1;
    m1.insert(pair<int, int>(1, 11));
    m1.insert(pair<int, int>(3, 33));
    m1.insert(pair<int, int>(4, 44));
    m1.insert(pair<int, int>(2, 22));
    printMap(m1);
    /*
    key = 1         value = 11
    key = 2         value = 22
    key = 3         value = 33
    key = 4         value = 44
    */
    map<int, int> m2(m1);
    printMap(m2);

    map<int, int> m3;
    m3 = m2;
    printMap(m3);
}

/*
map容器大小和交换:
size();         返回容器中元素的数目
empty();        判断容器是否为空
swap(st);       交换两个集合容器
*/
void test2()
{
    map<int, int> m1;
    m1.insert(pair<int, int>(1, 11));
    m1.insert(pair<int, int>(3, 33));
    m1.insert(pair<int, int>(4, 44));
    m1.insert(pair<int, int>(2, 22));
    printMap(m1);
    /*
    key = 1         value = 11
    key = 2         value = 22
    key = 3         value = 33
    key = 4         value = 44
    */

    cout << "m1的大小为: " << m1.size() << endl;

    if (!m1.empty())
        cout << "m1不为空" << endl;

    map<int, int> m2;
    m2.insert(pair<int, int>(10, 18));
    m2.insert(pair<int, int>(30, 38));
    m2.insert(pair<int, int>(40, 48));
    m2.insert(pair<int, int>(20, 28));
    printMap(m2);
    /*
    key = 10                value = 18
    key = 20                value = 28
    key = 30                value = 38
    key = 40                value = 48
    */
    m1.swap(m2);
    printMap(m1);
    /*
    key = 10                value = 18
    key = 20                value = 28
    key = 30                value = 38
    key = 40                value = 48
    */
    printMap(m2);
    /*
    key = 1         value = 11
    key = 2         value = 22
    key = 3         value = 33
    key = 4         value = 44
    */
}

/*
map插入与删除:
insert(elem);       在容器中插入元素
clear();            清除所有元素
erase(pos);         删除pos迭代器所指的元素，返回下一个元素的迭代器
erase(beg, end);    删除区间[beg,end)的所有元素 ，返回下一个元素的迭代器
erase(key);         删除容器中值为key的元素
*/
void test3()
{
    map<int, int> m1;
    // 4种插入方式
    m1.insert(pair<int, int>(1, 11)); // 好
    m1.insert(make_pair(3, 33));      // 好
    m1.insert(map<int, int>::value_type(4, 44));
    m1[2] = 22;            // 不建议用于插入，主要用于当确定key存在时，取其对应的value
    cout << m1[5] << endl; // 0  由于没有key=5的数据，系统会创建一个值为0去与之匹配

    printMap(m1);
    /*
    key = 1         value = 11
    key = 2         value = 22
    key = 3         value = 33
    key = 4         value = 44
    key = 5         value = 0
    */

    m1.erase(m1.begin());
    printMap(m1);
    /*
    key = 2         value = 22
    key = 3         value = 33
    key = 4         value = 44
    key = 5         value = 0
    */
    m1.erase(3); // 删除key=3的数据，若输入的值key中没有，则不删任何数据
    printMap(m1);
    /*
    key = 2         value = 22
    key = 4         value = 44
    key = 5         value = 0
    */
}

/*
查找和统计：
find(key);      查找key是否存在,若存在，返回该键的元素的迭代器;若不存在，返回set.end()
count(key);     统计key的元素个数
*/
void test4()
{
    multimap<int, int> m1;
    m1.insert(pair<int, int>(1, 11));
    m1.insert(pair<int, int>(3, 33));
    m1.insert(pair<int, int>(4, 44));
    m1.insert(pair<int, int>(2, 22));
    m1.insert(pair<int, int>(3, 34));
    m1.insert(pair<int, int>(3, 35));

    multimap<int, int>::iterator pos = m1.find(3);
    if (pos != m1.end())
        cout << "找到了key = " << pos->first << " 的值为 value = " << pos->second << endl; // 找到了key = 3 的值为 value = 33
    else
        cout << "没找到" << endl;

    int num = m1.count(3);
    cout << "key = 3 的个数为 " << num << endl; // key = 3 的个数为 3
}

/*
map排序:
map容器默认排序规则为 按照key值进行 从小到大排序，掌握如何改变排序规则
利用仿函数，可以改变排序规则
*/
class MyCompare
{
public:
    bool operator()(int x, int y) const
    {
        return x > y;
    }
};

void test5()
{
    map<int, int, MyCompare> m1;
    m1.insert(pair<int, int>(1, 11));
    m1.insert(make_pair(3, 33));
    m1.insert(pair<int, int>(4, 44));
    m1.insert(make_pair(3, 33));
    m1.insert(pair<int, int>(2, 22));
    for (map<int, int, MyCompare>::iterator it = m1.begin(); it != m1.end(); it++)
        cout << "key = " << it->first << "\t\tvalue = " << it->second << endl;
    cout << endl;
    /*
    key = 4         value = 44
    key = 3         value = 33
    key = 2         value = 22
    key = 1         value = 11
    */
}

int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    return 0;
}
