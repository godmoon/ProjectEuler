// Totient maximum
// Problem 69
// Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of numbers less than n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
// 
// n    Relatively Prime    φ(n)   n/φ(n)
// 2    1                   1       2
// 3    1,2                 2       1.5
// 4    1,3                 2       2
// 5    1,2,3,4             4       1.25
// 6    1,5                 2       3
// 7    1,2,3,4,5,6         6       1.1666...
// 8    1,3,5,7             4       2
// 9    1,2,4,5,7,8         6       1.5
// 10   1,3,7,9             4       2.5
// It can be seen that n=6 produces a maximum n/φ(n) for n ≤ 10.
// 
// Find the value of n ≤ 1,000,000 for which n/φ(n) is a maximum.

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 69

#include <Template.h>

#include <CppMath.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 欧拉函数，直接按照定义解决吧，性能不给力
    uint32_t Phi(uint32_t n)
    {
        uint32_t result = 1;        // 至少有个1
        for (uint32_t i = 2; i < n; ++i)
        {
            if (CppMath::GCD(i, n) == 1)
            {
                ++result;
            }
        }

        return result;
    }

    // 使用欧拉函数的性质计算欧拉函数，具体算法可以参考维基百科:
    // https://zh.wikipedia.org/wiki/%E6%AC%A7%E6%8B%89%E5%87%BD%E6%95%B0
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
    static const uint32_t COUNT = 1000000;

    double maxNDivPhiN = 0;
    uint32_t maxN = 0;

    for (uint32_t n = 2; n <= COUNT; ++n)
    {
        uint32_t phiN = PhiWithAlgo(n);
        if (n % 10000 == 0)
        {
            cout << n << ":" << phiN << endl;
        }

        double nDivPhiN = (double)n / phiN;
        if (maxNDivPhiN < nDivPhiN)
        {
            maxNDivPhiN = nDivPhiN;
            maxN = n;
        }
    }

    printf("当n为[%u]时,n/phi(n)值最大,为[%.3f].\n", maxN, maxNDivPhiN);
    return CppString::ToString(maxN);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 69
[2016-12-16 11:19:20.841588]开始运行第69题.
10000:4000
20000:8000
30000:8000
40000:16000
50000:20000
60000:16000
70000:24000
80000:32000
90000:24000
100000:40000
110000:40000
120000:32000
130000:48000
140000:48000
150000:40000
160000:64000
170000:64000
180000:48000
190000:72000
200000:80000
210000:48000
220000:80000
230000:88000
240000:64000
250000:100000
260000:96000
270000:72000
280000:96000
290000:112000
300000:80000
310000:120000
320000:128000
330000:80000
340000:128000
350000:120000
360000:96000
370000:144000
380000:144000
390000:96000
400000:160000
410000:160000
420000:96000
430000:168000
440000:160000
450000:120000
460000:176000
470000:184000
480000:128000
490000:168000
500000:200000
510000:128000
520000:192000
530000:208000
540000:144000
550000:200000
560000:192000
570000:144000
580000:224000
590000:232000
600000:160000
610000:240000
620000:240000
630000:144000
640000:256000
650000:240000
660000:160000
670000:264000
680000:256000
690000:176000
700000:240000
710000:280000
720000:192000
730000:288000
740000:288000
750000:200000
760000:288000
770000:240000
780000:192000
790000:312000
800000:320000
810000:216000
820000:320000
830000:328000
840000:192000
850000:320000
860000:336000
870000:224000
880000:320000
890000:352000
900000:240000
910000:288000
920000:352000
930000:240000
940000:368000
950000:360000
960000:256000
970000:384000
980000:336000
990000:240000
1000000:400000
当n为[510510]时,n/phi(n)值最大,为[5.539].
[2016-12-16 11:19:22.123897]第69题运行完毕，结果[510510]: From start 1282309 us,from last 1282309 us
By Moon
*/
