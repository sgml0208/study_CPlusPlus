/*
 * @Description:                    STL案例
 * @Author:  shang guan meng luo
 * @version:
 * @Date: 2024-10-03 22:21:25
 * @LastEditTime: 2024-10-03 23:11:15
 */

/*
案例-评委打分
案例描述
有5名选手:选手ABCDE，10个评委分别对每一名选手打分，去除最高分，去除评委中最低分，取平均分。
实现步骤
1.创建五名选手，放到vector中
2.遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分打分存到deque容器中
3.sort算法对deque容器中分数排序，去除最高和最低分
4.deque容器遍历一遍，累加总分
5.获取平均分
*/

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <random>
#include <algorithm>
using namespace std;

class Player
{
public:
    string m_name;  // 选手姓名
    double m_score; // 选手获得的平均分

    Player(string name, double score)
    {
        this->m_name = name;
        this->m_score = score;
    }
};

void createPlayers(vector<Player> &players)
{
    for (int i = 0; i < 5; i++)
    {
        string name = "选手";
        name += 'A' + i;
        double score = 0; // 初始默认0分
        Player p(name, score);
        players.push_back(p);
    }
    // for (vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    //     cout << "name: " << (*it).m_name << "  score: " << (*it).m_score << endl;
}

void setAndShowScore(vector<Player> &players)
{
    // 初始化随机数生成器
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(9.0, 10.0);

    for (vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        // 将评委打的分放入deque容器
        deque<double> scores; // 随机生成10个裁判打的分
        for (int i = 0; i < 10; i++)
            scores.push_back(round(dis(gen) * 100) / 100); // 随机生成9-10之间的随机数,保留两位小数
        sort(scores.begin(), scores.end());
        scores.pop_back();
        scores.pop_front();
        double sum = 0;
        for (int i = 0; i < 8; i++)
            sum += scores[i];
        it->m_score = round((sum / 8) * 100) / 100;

        // showScore
        cout << "去掉最高分和最低分后 " << it->m_name << " 得分情况为: " << endl;
        for (deque<double>::iterator sc = scores.begin(); sc != scores.end(); sc++)
            cout << *sc << ' ';
        cout << endl << "average score: " << it->m_score << endl;
    }
}

void test()
{
    vector<Player> players; // 选手
    createPlayers(players);
    setAndShowScore(players);
}

int main()
{
    test();

    return 0;
}
