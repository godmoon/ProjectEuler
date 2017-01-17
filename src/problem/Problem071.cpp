// Ordered fractions
// Problem 71
// Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.
// 
// If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:
// 
// 1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8
// 
// It can be seen that 2/5 is the fraction immediately to the left of 3/7.
// 
// By listing the set of reduced proper fractions for d ≤ 1,000,000 in ascending order of size, find the numerator of the fraction immediately to the left of 3/7.

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 71

#include <Template.h>

#include <CppMath.h>

#include <limits>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处


}

using namespace GET_NAMESPACE_NAME(PROBLEM_NO);

/* 当前页面的构造函数，会在页面加载前调用，未请求的页面不会调用 */
GET_CLASS_NAME(PROBLEM_NO)::GET_CLASS_NAME(PROBLEM_NO)() : Problem()
{
}

/* 运行 */
string GET_CLASS_NAME(PROBLEM_NO)::Run()
{
    static const uint32_t COUNT = 1000000;

    double MAX_VALUE = 3.0 / 7;
    double maxResult = 0;
    uint32_t maxN = 0;
    uint32_t maxD = 0;

    for (uint32_t d = 2; d <= COUNT; ++d)
    {
        if (d % 10000 == 0)
        {
            printf("正在计算[%u]\n", d);
        }

        uint32_t N = MAX_VALUE * d + 1;
        for (uint32_t n = MAX_VALUE * d - 1; n <= N; ++n)
        {
            double value = (double)n / d;
            if (value >= MAX_VALUE)
            {
                continue;
            }

            if (value <= maxResult)
            {
                continue;
            }

            // 非最简分数，跳过
            if (CppMath::GCD(n, d) != 1)
            {
                continue;
            }

            maxResult = value;
            maxN = n;
            maxD = d;
        }
    }

    printf("当n/d为[%u/%u]时,获得小于3/7的最大值[%3lf].\n", maxN, maxD, maxResult);
    return CppString::ToString(maxN);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 71
[2016-12-16 14:02:33.094557]开始运行第71题.
正在计算[10000]
正在计算[20000]
正在计算[30000]
正在计算[40000]
正在计算[50000]
正在计算[60000]
正在计算[70000]
正在计算[80000]
正在计算[90000]
正在计算[100000]
正在计算[110000]
正在计算[120000]
正在计算[130000]
正在计算[140000]
正在计算[150000]
正在计算[160000]
正在计算[170000]
正在计算[180000]
正在计算[190000]
正在计算[200000]
正在计算[210000]
正在计算[220000]
正在计算[230000]
正在计算[240000]
正在计算[250000]
正在计算[260000]
正在计算[270000]
正在计算[280000]
正在计算[290000]
正在计算[300000]
正在计算[310000]
正在计算[320000]
正在计算[330000]
正在计算[340000]
正在计算[350000]
正在计算[360000]
正在计算[370000]
正在计算[380000]
正在计算[390000]
正在计算[400000]
正在计算[410000]
正在计算[420000]
正在计算[430000]
正在计算[440000]
正在计算[450000]
正在计算[460000]
正在计算[470000]
正在计算[480000]
正在计算[490000]
正在计算[500000]
正在计算[510000]
正在计算[520000]
正在计算[530000]
正在计算[540000]
正在计算[550000]
正在计算[560000]
正在计算[570000]
正在计算[580000]
正在计算[590000]
正在计算[600000]
正在计算[610000]
正在计算[620000]
正在计算[630000]
正在计算[640000]
正在计算[650000]
正在计算[660000]
正在计算[670000]
正在计算[680000]
正在计算[690000]
正在计算[700000]
正在计算[710000]
正在计算[720000]
正在计算[730000]
正在计算[740000]
正在计算[750000]
正在计算[760000]
正在计算[770000]
正在计算[780000]
正在计算[790000]
正在计算[800000]
正在计算[810000]
正在计算[820000]
正在计算[830000]
正在计算[840000]
正在计算[850000]
正在计算[860000]
正在计算[870000]
正在计算[880000]
正在计算[890000]
正在计算[900000]
正在计算[910000]
正在计算[920000]
正在计算[930000]
正在计算[940000]
正在计算[950000]
正在计算[960000]
正在计算[970000]
正在计算[980000]
正在计算[990000]
正在计算[1000000]
当n/d为[428570/999997]时,获得小于3/7的最大值[0.428571].
[2016-12-16 14:02:36.251258]第71题运行完毕，结果[428570]: From start 3156701 us,from last 3156701 us
By Moon
*/
