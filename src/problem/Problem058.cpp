// Spiral primes
// Problem 58
// Published on 05 December 2003 at 06:00 pm[Server Time]
// Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
// 
// 37 36 35 34 33 32 31
// 38 17 16 15 14 13 30
// 39 18  5  4  3 12 29
// 40 19  6  1  2 11 28
// 41 20  7  8  9 10 27
// 42 21 22 23 24 25 26
// 43 44 45 46 47 48 49
// 
// It is interesting to note that the odd squares lie along the bottom right diagonal, but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime; that is, a ratio of 8 / 13 ≈ 62 % .
// 
// If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals first falls below 10 % ?
// 
// 题目58：考察螺旋网格中对角线上质数的数量。
// 从1开始逆时针旋转，可以得到一个边长为7的螺旋正方形。
// 
// 37 36 35 34 33 32 31
// 38 17 16 15 14 13 30
// 39 18  5  4  3 12 29
// 40 19  6  1  2 11 28
// 41 20  7  8  9 10 27
// 42 21 22 23 24 25 26
// 43 44 45 46 47 48 49
// 
// 有趣的是奇数的平方数都处于右下对角线上。更有趣的是，对角线上的13个数字中有8个质数，其百分比是8 / 13 ≈ 62 % 。
// 
// 如果在上面的螺旋正方形上再加一层，可以得到一个边长为9的螺旋正方形。如果这个过程继续，到螺旋正方形的边长为多少时，对角线上的质数百分比第一次降到10%以下？

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 58

#include <Template.h>

#include <CppMath.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    /* 获得指定索引的对角线数值 */
    uint32_t GetNum(uint32_t index)
    {
        // 对角线的值可以这样看，第n圈的值分别为：
        // 0: 1
        // 1 : 3 5 7 9
        // 2 : 13 17 21 25
        // 3 : 31 37 43 49
        // 每行的两个相邻值相差2*n
        // 每行第一个值也是前一行最后一个值+2*n

        static vector<uint32_t> numList;
        uint32_t row;
        uint32_t currSize;

        while (index >= (currSize = numList.size()))
        {
            if (currSize != 0)
            {
                row = (currSize + 3) >> 2;                          // 行号row=(index+3)/4
                numList.push_back(*numList.rbegin() + (row << 1));    // a[n]=a[n-1]+row*2
            }
            else
            {
                numList.push_back(1);       // a[0]=1
            }
        }

        return numList[index];
    }
}

using namespace GET_NAMESPACE_NAME(PROBLEM_NO);

/* 当前页面的构造函数，会在页面加载前调用，未请求的页面不会调用 */
GET_CLASS_NAME(PROBLEM_NO)::GET_CLASS_NAME(PROBLEM_NO)() : Problem()
{
    /* TODO */
}

/* 运行 */
string GET_CLASS_NAME(PROBLEM_NO)::Run()
{
    uint32_t currNum = 1;           // 当前的数字，第一个初始化为1
    uint32_t primerNumCount = 0;    // 质数个数
    const double PERCENT = 0.1f;
    uint32_t i = 1;                 // n为对角线的数字编号，也代表了数字个数-1

    for (;; ++i)
    {
        currNum = GetNum(i);
        if (CppMath::IsPrime(currNum))
        {
            ++primerNumCount;
        }
         
        // cout << CppString::GetArgs("%u:%u:%u:%u/%u=%.2f%%\n", i % 4 == 0, i, currNum, primerNumCount, i + 1, primerNumCount / (double)(i + 1) * 100);

        // 每行最后一个数值,计算比例
        if (i % 4 == 0 && primerNumCount / (double)(i + 1) < PERCENT)
        {
            break;
        }
    }

    // 边长 = row * 2 + 1 = (i + 3) / 4 * 2 + 1 = (((i + 3) >> 2) << 1) + 1，注意这里不能把/4*2写成/2，因为/4的时候会约掉一些数
    return CppString::ToString((((i + 3) >> 2) << 1) + 1);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 58
[2014-07-19 13:33:39.413737]开始运行第58题
[2014-07-19 13:33:39.719024]第58题运行完毕，结果[26241]: From start 305287 us,from last 305287 us
By Moon
*/
