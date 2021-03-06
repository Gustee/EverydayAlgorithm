/***************************************************************************************************
 * 【问题提出】
 *      著名历史学家Josephus（约瑟夫）经历了这么一段经历，在罗马人占领乔塔帕特后，40个犹太人和Josephus躲在
 *  一个山洞中。40个犹太人决定宁死也不被敌人抓到，于是决定集体自杀。大家经过讨论，决定了一个自杀方式，41个人围
 *  成一个圆圈，由第1个人开始报数，每报数到3的人就必须自杀，然后再由下一个人重新开始报数，知道所有人都自杀身亡
 *  为止。然而Josephus并不像遵从这个规则，不想自杀。于是Josephus先假装同意该方案，然后坐到大家围成圆圈的第31
 *  个为止，最后逃过了这场死亡游戏.
 *
 * 【相关概念】
 *      约瑟夫环（约瑟夫问题）是一个数学的应用问题：已知n个人（以编号1，2，3...n分别表示）围坐在一张圆桌
 *  周围。从编号为k的人开始报数，数到m的那个人出列；他的下一个人又从1开始报数，数到m的那个人又出列；依此规
 *  律重复下去，直到圆桌周围的人全部出列。给定总人数n 以及 号m,输出最后出列人的编号。
 *
 * 【相关题目】
 *  2014年华为上机题
 *  华中科技大学复试上机题
 *
 * 【算法设计】
 * 算法一: 用链表模拟整个报数过程 复杂度O(nm)
 *
 * 算法二: 用数组模拟整个报数过程 复杂度O(nm)
 *
 * 算法三: 找出数学递推公式
 *    对于给出的n个人，每k个人退出一个，第一次退出第m个人的约瑟夫环：
 *    首先考虑从0开始编号，从第k个开始退出的情况。(因为用到取余操作,会有余数0, 所以从0开始编号)则第k人退出后，
 * 约瑟夫环变为了：给出 n – 1 个人，每隔 k 个人退出一个的新约瑟夫环问题。给新环重新编号，与旧环建立的映射为：
 *  旧环编号    新环编号
 *   k      =>  0
 *  k+1     =>  1
 *  k+2        2…
 *
 *  k+n-2   => n-2
 * 假设 n-1 个人的约瑟夫环退出的人的编号为 x ， 那么该人在 n 个人的环中的编号应该是 (x + k) % n (这个n是指旧环中元素个数)
 *
 *【递推公式】
 * 设f[n]表示再旧环中的编号,f[n-1]表示在新环中的比编号，K表示每K个人出列一个人,则由上可得到递推式：
 * f[n] = (f[n-1] + k) % n
 *
 * 那么一个人的约瑟夫环的人必然是赢家，且编号为0，即: f[1] = 0
 * 　　
 * *******************************************************************************************************/

#include <iostream>
using namespace std;

// 算法二: 利用数组
void josephusArray(int n, int m)
{
    int jos[n];
    for(int j =0 ;j<n ;j++)     jos[j] = 0;
    int count = 0;      // 每报数到第m个元素时,出列
    int people = 0;     // 已经出列的人数
    int i = 0;          // 从0开始报数

    while(people<n)     // 如果没有都出列则一直循环
    {
        if(jos[i] == 0)
            count++;
        i++;            // 累加
        if(count >= m)  // 如果累计到了m次,表示报了m个人了
        {
            jos[(i-1)%n] = -1;
            people ++;
            count = 0;
            cout << i << " ";
        }
        i = i % n;
    }
}

// 算法三: 利用递推公式
int josephusMath(int n, int m)
{
    int i, s = 0;

    // 整个递推过程如下
    // f(2) = {f(1) + m} % 2;
    // f(3) = {f(2) + m} % 3;
    // ...
    // f(n) = {f(n-1) + m} %n;

    for(i =2 ; i<=n ;i++)
    {
        s = (s + m ) % i;
    }
    return s+1;
}

int main()
{
    int n = 15;
    int m = 3;
    cout << "Josephus Ring (" << n << "," << m << ")" << endl;

    cout << "算法二(时间复杂度O (mn)):\n整个环的出列顺序为:\n";
    josephusArray(n,m);

    cout << "\n\n算法三(时间复杂度O (n):\n最后退出的编号为:" << josephusMath(n, m) << endl;

    return 0;
}