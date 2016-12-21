// Counting fractions
// Problem 72
// Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
// 
// If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
// 
// 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
// 
// It can be seen that there are 21 elements in this set.
// 
// How many elements would be contained in the set of reduced proper fractions for d ≤ 1,000,000?

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 72

#include <thread>
#include <list>
#include <atomic>

#include <Template.h>

#include <CppMath.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 使用欧拉函数的性质计算欧拉函数 
    uint32_t PhiWithAlgo(uint32_t n)
    {
        // 获得n的因数分解
        map<uint32_t, uint32_t> factors = CppMath::GetPrimerFactorNum(n);

        uint32_t result = 1;
        //printf("%u=1", n);
        for (auto factorIt = factors.begin(); factorIt != factors.end(); ++factorIt)
        {
            //printf("*%u^%u", factorIt->first, factorIt->second);
            result *= pow(factorIt->first, factorIt->second - 1) * (factorIt->first - 1);
        }
        //printf("\n");

        return result;
    }
}

using namespace GET_NAMESPACE_NAME(PROBLEM_NO);

/* 当前页面的构造函数，会在页面加载前调用，未请求的页面不会调用 */
GET_CLASS_NAME(PROBLEM_NO)::GET_CLASS_NAME(PROBLEM_NO)() : Problem()
{
}

/* 运行 */
string GET_CLASS_NAME(PROBLEM_NO)::Run()
{
    // 开THREAD_COUNT个线程做这件事
    static const uint32_t THREAD_COUNT = 7;
    static const uint32_t COUNT = 1000000;
    list<thread> threads;
    atomic<uint64_t> resultSum(0);
    atomic<uint32_t> currD(2);

    for (uint32_t i = 0; i < THREAD_COUNT; ++i)
    {
        thread th([&](uint32_t threadId)
        {
            uint32_t d;
            while ((d = currD.fetch_add(1)) <= COUNT)
            {
                // 霸蛮的计算方法，7个线程将近需要3小时
//                 if (d % 10000 == 0)
//                 {
//                     printf("线程[%u]正在计算[%u]\n", threadId, d);
//                 }
// 
//                 // 如果分母是2的倍数，就只算奇数好了
//                 if (d % 2 == 0)
//                 {
//                     for (uint32_t n = 1; n < d; n += 2)
//                     {
//                         // 非最简分数，跳过
//                         if (CppMath::GCD(n, d) != 1)
//                         {
//                             continue;
//                         }
// 
//                         ++resultSum;
//                     }
//                 }
//                 else
//                 {
//                     for (uint32_t n = 1; n < d; ++n)
//                     {
//                         // 非最简分数，跳过
//                         if (CppMath::GCD(n, d) != 1)
//                         {
//                             continue;
//                         }
// 
//                         ++resultSum;
//                     }
//                 }
//                 

                // 使用欧拉函数计算，不到一秒
                resultSum += PhiWithAlgo(d);
            }
        }, i);

        threads.push_back(move(th));
    }

    // 等待线程完成
    for (auto &th : threads)
    {
        th.join();
    }

    printf("分母<=[%u],一共有[%lu]个最简分数.\n", COUNT, resultSum.load());
    return CppString::ToString(resultSum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 72
[2016-12-16 14:08:37.407756]开始运行第72题.
分母<=[8],一共有[21]个最简分数.
[2016-12-16 14:08:37.407890]第72题运行完毕，结果[21]: From start 134 us,from last 134 us
By Moon

霸蛮的方法：
./ProjectEuler 72
[2016-12-16 15:48:44.084397]开始运行第72题.
线程[1]正在计算[10000]
线程[6]正在计算[20000]
线程[3]正在计算[30000]
线程[1]正在计算[40000]
线程[4]正在计算[50000]
线程[1]正在计算[60000]
线程[0]正在计算[70000]
线程[1]正在计算[80000]
线程[2]正在计算[90000]
线程[2]正在计算[100000]
线程[6]正在计算[110000]
线程[1]正在计算[120000]
线程[1]正在计算[130000]
线程[5]正在计算[140000]
线程[4]正在计算[150000]
线程[5]正在计算[160000]
线程[5]正在计算[170000]
线程[3]正在计算[180000]
线程[1]正在计算[190000]
线程[2]正在计算[200000]
线程[3]正在计算[210000]
线程[3]正在计算[220000]
线程[5]正在计算[230000]
线程[4]正在计算[240000]
线程[4]正在计算[250000]
线程[4]正在计算[260000]
线程[0]正在计算[270000]
线程[0]正在计算[280000]
线程[6]正在计算[290000]
线程[0]正在计算[300000]
线程[5]正在计算[310000]
线程[2]正在计算[320000]
线程[4]正在计算[330000]
线程[1]正在计算[340000]
线程[4]正在计算[350000]
线程[1]正在计算[360000]
线程[1]正在计算[370000]
线程[0]正在计算[380000]
线程[0]正在计算[390000]
线程[3]正在计算[400000]
线程[5]正在计算[410000]
线程[2]正在计算[420000]
线程[2]正在计算[430000]
线程[0]正在计算[440000]
线程[0]正在计算[450000]
线程[3]正在计算[460000]
线程[1]正在计算[470000]
线程[2]正在计算[480000]
线程[2]正在计算[490000]
线程[5]正在计算[500000]
线程[0]正在计算[510000]
线程[6]正在计算[520000]
线程[5]正在计算[530000]
线程[4]正在计算[540000]
线程[6]正在计算[550000]
线程[3]正在计算[560000]
线程[5]正在计算[570000]
线程[4]正在计算[580000]
线程[2]正在计算[590000]
线程[4]正在计算[600000]
线程[1]正在计算[610000]
线程[1]正在计算[620000]
线程[6]正在计算[630000]
线程[3]正在计算[640000]
线程[4]正在计算[650000]
线程[3]正在计算[660000]
线程[0]正在计算[670000]
线程[6]正在计算[680000]
线程[0]正在计算[690000]
线程[5]正在计算[700000]
线程[2]正在计算[710000]
线程[4]正在计算[720000]
线程[6]正在计算[730000]
线程[4]正在计算[740000]
线程[2]正在计算[750000]
线程[3]正在计算[760000]
线程[1]正在计算[770000]
线程[4]正在计算[780000]
线程[1]正在计算[790000]
线程[1]正在计算[800000]
线程[4]正在计算[810000]
线程[3]正在计算[820000]
线程[0]正在计算[830000]
线程[3]正在计算[840000]
线程[4]正在计算[850000]
线程[2]正在计算[860000]
线程[3]正在计算[870000]
线程[3]正在计算[880000]
线程[3]正在计算[890000]
线程[4]正在计算[900000]
线程[5]正在计算[910000]
线程[5]正在计算[920000]
线程[5]正在计算[930000]
线程[0]正在计算[940000]
线程[4]正在计算[950000]
线程[1]正在计算[960000]
线程[1]正在计算[970000]
线程[5]正在计算[980000]
线程[1]正在计算[990000]
线程[2]正在计算[1000000]
分母<=[1000000],一共有[303963552391]个最简分数.
[2016-12-16 18:18:58.927228]第72题运行完毕，结果[303963552391]: From start 9014842831 us,from last 9014842831 us
By Moon

使用欧拉函数计算：
./ProjectEuler 72
[2016-12-19 09:59:42.124717]开始运行第72题.
分母<=[1000000],一共有[303963552391]个最简分数.
[2016-12-19 09:59:42.444216]第72题运行完毕，结果[303963552391]: From start 319499 us,from last 319499 us
By Moon
*/
