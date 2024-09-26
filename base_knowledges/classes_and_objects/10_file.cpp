/*
 * @Description:       文件    https://www.bilibili.com/video/BV1et411b73Z?p=143&spm_id_from=pageDriver&vd_source=5c495e3ef87d1f3de4b8a79a6b9360a1
 * @Author:  shang guan meng luo
 * @version: 
 * @Date: 2024-07-21 15:06:57
 * @LastEditTime: 2024-07-21 16:24:34
 */

/*
文件类型分为两种:
    1.文本文件-文件以文本的ASCII码形式存储在计算机中
    2.二进制文件-文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂它们

操作文件的三大类:
    1. ofstream: 写操作
    2. ifstream: 读操作
    3. fstream:  读写操作

文件打开方式:
ios::in     为读文件而打开文件
ios::out    为写文件而打开文件
ios::ate    初始位置: 文件尾
ios::app    追加方式写文件
ios::trunc  如果文件存在先删除，再创建
ios::binary 二进制方式

注意: 文件打开方式可以配合使用，利用 | 操作符
例如: 用二进制方式写文件 ios::binary | ios::out

*/

#include <iostream>
#include <fstream>        // 文件读写操作
#include <string>
using namespace std;

// 向文件写数据
void WriteFile()    
{
    ofstream ofs;
    ofs.open("file1.txt", ios::out);
    ofs << "hello world!" << endl;
    ofs << "fighting!" << endl;
    ofs.close();
}

// 从文件读数据
void ReadFile()    
{
    ifstream ifs;
    ifs.open("file1.txt", ios::in);
    if(!ifs.is_open())
    {
        cout << "文件打开失败!" << endl;
        return ;
    }
    // 读数据方法一
    // char buf[1024] = {0};
    // while (ifs >> buf)  // 读到头时为false
    //     cout << buf << endl;
    /*
    hello
    world!
    fighting!
    */

    // 读数据方法二
    // char buf[1024] = {0};
    // while (ifs.getline(buf, sizeof(buf)))  // 读取sizeof(buf)大小的数据到buf中
    //     cout << buf << endl;
    /*
    hello world!
    fighting!
    */

    // 读数据方法三
    string buf;
    while (getline(ifs, buf))
        cout << buf << endl;
    /*
    hello world!
    fighting!
    */

   ifs.close();
}    


class Person
{
public:
    char name[64];     // 最好不要用string类型
    int age;
};

// 以二进制方式写数据
void Binary_WriteFile()
{
    ofstream ofs;
    ofs.open("file2.txt", ios::out | ios::binary);
    Person p = {"张三", 18};
    ofs.write((const char *)&p, sizeof(Person));
    ofs.close();
}

// 以二进制方式读数据
void Binary_ReadFile()
{
    ifstream ifs;
    ifs.open("file2.txt", ios::in | ios::binary);
    if(!ifs.is_open())
    {
        cout << "文件打开失败!" << endl;
        return ;
    }
    Person p;
    ifs.read((char *)&p, sizeof(Person));
    cout << "姓名：" << p.name << "  年龄：" << p.age << endl;  // 姓名：张三  年龄：18

    ifs.close();
}

int main()
{
    // WriteFile();

    ReadFile();

    // Binary_WriteFile();

    Binary_ReadFile();

    return 0;
}


