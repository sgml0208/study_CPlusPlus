/*
 * @Description:                    员工分组案例
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-04 23:18:34
 * @LastEditTime: 2024-10-05 00:03:36
 */

/*
案例描述:
公司今天招聘了10个员工(ABCDEFGHIJ)，10名员工进入公司之后，需要指派员工在那个部门工作
员工信息有: 姓名 工资组成;部门分为:策划、美术、研发
随机给10名员工分配部门和工资
通过multimap进行信息的插入 key(部门编号) value(员工)
分部门显示员工信息
实现步骤:
1.创建10名员工，放到vector中
2.遍历vector容器，取出每个员工，进行随机分组
3.分组后，将员工部门编号作为key，具体员工作为value，放入到multimap容器中
4.分部门显示员工信息
*/

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#define Planner 0
#define Artist 1
#define Engineer 2

class Worker
{
public:
    string m_name;
    int m_salary;
    Worker() {};
    Worker(string name, int salary)
    {
        this->m_name = name;
        this->m_salary = salary;
    }
};

void createWorker(vector<Worker> &v)
{
    string nameSeed = "ABCDEFGHIJ";
    for (int i = 0; i < 10; i++)
    {
        Worker w;
        w.m_name = "员工";
        w.m_name += nameSeed[i];
        w.m_salary = rand() % 4000 + 4000; // 4000 ~ 7999
        v.push_back(w);                    // 将员工放入数组
    }
}

void setGroup(vector<Worker> &v, multimap<int, Worker> &m)
{
    // 遍历每个员工
    for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++)
    {
        // 生成随机部门编号
        int deptId = rand() % 3; // 0 1 2
        // 将员工分到该部门
        m.insert(make_pair(deptId, *it));
    }
}

void printWorker(const multimap<int, Worker> &m)
{
    cout << "策划部门员工信息: " << endl;
    multimap<int, Worker>::const_iterator pos = m.find(Planner); // 找到策划部门第一个员工
    int cnt = m.count(Planner);                                  // 统计策划部门的人数
    int index = 0;
    for (; pos != m.end() && index < cnt; pos++, index++)
        cout << "deptId: " << pos->first << "\tname: " << pos->second.m_name << "\tsalary: " << pos->second.m_salary << endl;

    cout << "美术部门员工信息: " << endl;
    pos = m.find(Artist);
    cnt = m.count(Artist); // 统计美术部门的人数
    index = 0;
    for (; pos != m.end() && index < cnt; pos++, index++)
        cout << "deptId: " << pos->first << "\tname: " << pos->second.m_name << "\tsalary: " << pos->second.m_salary << endl;

    cout << "研发部门员工信息: " << endl;
    pos = m.find(Engineer);
    cnt = m.count(Engineer); // 统计研发部门的人数
    index = 0;
    for (; pos != m.end() && index < cnt; pos++, index++)
        cout << "deptId: " << pos->first << "\tname: " << pos->second.m_name << "\tsalary: " << pos->second.m_salary << endl;
    /*
    name: 员工A     salary: 4041
    name: 员工B     salary: 6467
    name: 员工C     salary: 6334
    name: 员工D     salary: 6500
    name: 员工E     salary: 7169
    name: 员工F     salary: 7724
    name: 员工G     salary: 7478
    name: 员工H     salary: 5358
    name: 员工I     salary: 6962
    name: 员工J     salary: 4464

    策划部门员工信息:
    deptId: 0       name: 员工D     salary: 6500
    deptId: 0       name: 员工I     salary: 6962
    deptId: 0       name: 员工J     salary: 4464
    美术部门员工信息:
    deptId: 1       name: 员工C     salary: 6334
    deptId: 1       name: 员工E     salary: 7169
    deptId: 1       name: 员工G     salary: 7478
    研发部门员工信息:
    deptId: 2       name: 员工A     salary: 4041
    deptId: 2       name: 员工B     salary: 6467
    deptId: 2       name: 员工F     salary: 7724
    deptId: 2       name: 员工H     salary: 5358
    */
}

void test()
{
    vector<Worker> vw;
    // 创建员工
    createWorker(vw);
    // 员工分组
    multimap<int, Worker> mm; // <部门编号，员工>
    setGroup(vw, mm);
    // 显示员工信息
    printWorker(mm);
}

int main()
{
    test();

    return 0;
}