/*
 * @Description:                    string容器
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-03 13:56:55
 * @LastEditTime: 2024-10-03 16:04:06
 */

/*
string和char*区别:
    char*  是一个指针 (C语言的字符串)
    string 是一个类，类内部封装了char*，管理这个字符串，是一个char*型的容器。
特点:
    string 类内部封装了很多成员方法
    例如:查找find，拷贝copy，删除delete，替换replace，插入insert
    string管理char*所分配的内存，不用担心复制越界和取值越界等，由类内部进行负责
*/

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

/*
构造函数原型:   用于初始化操作
string();                       //创建一个空的字符串 例如: string str;
string(const char* s);          //使用字符串s初始化
string(const string& str);      //使用一个string对象初始化另一个string对象  拷贝构造
string(int n,char c);           //使用n个字符c初始化
*/
void test1()
{
    string s1; // 默认构造函数
    const char *s2 = "hello world";
    string s3(s2);
    cout << "s3 = " << s3 << endl; // s3 = hello world
    string s4(s3);                 // 括号法，拷贝构造
    cout << "s4 = " << s4 << endl; // s4 = hello world
    string s5(10, '-');
    cout << "s5 = " << s5 << endl; // s5 =  ----------
    cout << s3.at(1) << endl;      // e     == s3[1]
}

/*
赋值操作:
赋值的函数原型:
string& operator=(const char* s);       //char*类型字符串 赋值给当前的字符串
string& operator=(const string &s);     //把字符串s赋给当前的字符串
string& operator=(char c);              //字符赋值给当前的字符串
string& assign(const char *s);          //把字符串s赋给当前的字符串
string& assign(const char *s, int n);   //把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s);        //把字符串s赋给当前字符串
string& assign(int n, char c);          //用n个字符c赋给当前字符串
*/
void test2()
{
    string s1;
    s1 = "hello world!";
    cout << "s1 = " << s1 << endl;
    string s2;
    s2 = s1;
    cout << "s2 = " << s2 << endl;
    string s3;
    s3 = 'a';
    cout << "s3 = " << s3 << endl; // a
    string s4;
    s4.assign("hello C++!");
    cout << "s4 = " << s4 << endl; // s4 = hello C++!
    string s5;
    s5.assign(s4, 8);
    cout << "s5 = " << s5 << endl; // s5 = +!
    s5.assign("hello C++!", 8);
    cout << "s5 = " << s5 << endl; // s5 = hello C+
    string s6;
    s6.assign(10, 'a'); // s6 = aaaaaaaaaa
    cout << "s6 = " << s6 << endl;
}

/*
string字符串拼接:
string& operator+=(const char* str);                //重载+=操作符
string& operator+=(const char c);                   //重载+=操作符
string& operator+=(const string& str);              //重载+=操作符
string& append(const char *s);                      //把字符串s连接到当前字符串结尾
string& append(const char *s, int n);               //把字符串s的前n个字符连接到当前字符申结尾
string& append(const string &s);                    //同operator+=(const string& str)
string& append(const string &s，int pos，int n);    //字符串s中从pos开始的n个字符连接到字符串结尾
*/
void test3()
{
    string s1 = "我";
    s1 += "爱玩游戏";
    cout << "s1 = " << s1 << endl; // s1 = 我爱玩游戏
    s1 += '!';
    cout << "s1 = " << s1 << endl; // s1 = 我爱玩游戏!
    string s2 = " and you?";
    s1 += s2;
    cout << "s1 = " << s1 << endl; // s1 = 我爱玩游戏! and you?
    string s3 = "I ";
    s3.append("want to go to NanJing");
    cout << "s3 = " << s3 << endl; // s3 = I want to go to NanJing
    s3.append(" where are you going?", 8);
    cout << "s3 = " << s3 << endl; // s3 = I want to go to NanJing where a
    s3.append(s2, 5, 3);
    cout << "s3 = " << s3 << endl; // s3 = I want to go to NanJing where ayou
}

/*
string查找和替换:
int find(const string& str,int pos=0)const;         //查找str第一次出现位置,从pos开始查找
int find(const char*s,int pos =0)const;             //查找s第一次出现位置,从pos开始查找
int find(const char* s,int pos, int n)const;        //从pos位置查找s的前n个字符第一次位置
int find(const char c,int pos =0)const;             //查找字符c第一次出现位置
int rfind(const string& str,int pos =npos)const;    //查找str最后一次位置,从pos开始查找
int rfind(const char*s,int pos =npos)const;         //查找s最后一次出现位置,从pos开始查找
int rfind(const char*s,int pos,int n)const;         //从pos查找s的前n个字符最后一次位置
int rfind(const char c,int pos=0)const;             //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos,int n,const char* s);       //替换从pos开始的n个字符为字符串s
*/
void test4()
{
    string s1 = "hello world, hello tomorrow";
    int pos = s1.find("hello");      // 从左往右开始找
    cout << "pos = " << pos << endl; // pos = 0   没找到返回-1
    pos = s1.rfind("hello");         // 从右往左开始找
    cout << "pos = " << pos << endl; // pos = 13
    string s2 = "China!";
    s1.replace(6, s2.length(), s2);
    cout << "after replace s1 = " << s1 << endl; // after replace s1 = hello China! hello tomorrow
}


/*
string比较:
比较方式: 字符串比较是按字符的ASCII码进行对比
= 返回 0
> 返回 1
< 返回 -1

函数原型:
int compare(const string &s)const; // 与字符串s比较   通常用于比较两个字符串是否相等   
int compare(const char *s)const;   // 与字符串s比较
*/
void test5()
{
    string s1 = "hello world";
    string s2 = "hello tomorrow";
    int ans = s1.compare(s2);           
    cout << "ans = " << ans << endl;     // ans = 1    w > t  
}


/*
string插入和删除:
函数原型:
string& insert(int pos,const char*s);       //插入字符串
string& insert(int pos,const string& str);  //插入字符串
string& insert(int pos,int n, char c);      //在指定位置插入n个字符c
string& erase(int pos,int n=npos);          //删除从Pos开始的n个字符
*/
void test6()
{
    string s1 = "hello world";
    string s2 = " hello tomorrow";
    s1.insert(s1.length(), s2);
    cout << "s1 = " << s1 << endl;     // s1 = hello world hello tomorrow
    s1.insert(s1.length(), 5, '$');
    cout << "s1 = " << s1 << endl;     // s1 = hello world hello tomorrow$$$$$
    s1.erase(s1.length()-4, '$');
    cout << "s1 = " << s1 << endl;     // s1 = hello world hello tomorrow$
    s1.erase(s1.length()-10, 5);       // 从倒数第10个字符开始删，删掉5个字符
    cout << "s1 = " << s1 << endl;     // s1 = hello world hellorrow$
}


/*
string子串:
函数原型:
string substr(int pos0,int n=npos) const;    //返回由pos开始的n个字符组成的字符串
*/
void test7()
{
    string s1 = "hello world";
    string substr = s1.substr(4, 6);           // 从第4个字符开始的6个字符
    cout << "substr = " << substr << endl;     // substr = o worl
}


int main()
{
    test1();

    test2();

    test3();

    test4();

    test5();

    test6();

    test7();

    return 0;
}
