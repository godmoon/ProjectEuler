// Totient permutation
// Problem 70
// Euler's Totient function, φ(n) [sometimes called the phi function], is used to determine the number of positive numbers less than or equal to n which are relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively prime to nine, φ(9)=6.
// The number 1 is considered to be relatively prime to every positive number, so φ(1)=1.
// 
// Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of 79180.
// 
// Find the value of n, 1 < n < 107, for which φ(n) is a permutation of n and the ratio n/φ(n) produces a minimum.

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 70

#include <Template.h>

#include <CppMath.h>

#include <limits>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 欧拉函数，直接按照定义解决吧
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

    // 判断2个数的各个数字是否是重排的
    bool IsPermutation(uint32_t n1, uint32_t n2)
    {
        // 分别存储0-9的个数
        string str1(10, 0);
        string str2(10, 0);

        while (n1 > 0)
        {
            ++str1[n1 % 10];
            n1 /= 10;
        }

        while (n2 > 0)
        {
            ++str2[n2 % 10];
            n2 /= 10;
        }

        return str1 == str2;
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
    static const uint32_t COUNT = 10000000;

    double minNDivPhiN = (numeric_limits<double>::max)();
    uint32_t minN = 0;
    uint32_t minPhiN = 0;

    for (uint32_t n = 2; n <= COUNT; ++n)
    {
        uint32_t phiN = PhiWithAlgo(n);
        if (n % 100000 == 0)
        {
            cout << n << ":" << phiN << endl;
        }

        // 不是重排数，跳过
        if (!IsPermutation(phiN, n))
        {
            continue;
        }

        double nDivPhiN = (double)n / phiN;
        if (minNDivPhiN > nDivPhiN)
        {
            minNDivPhiN = nDivPhiN;
            minN = n;
            minPhiN = phiN;
        }
    }

    printf("当n为[%u]时,phi(n)为[%u], n/phi(n)值最小,为[%.3f].\n", minN, minPhiN, minNDivPhiN);
    return CppString::ToString(minN);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 70
[2016-12-16 11:39:15.304590]开始运行第70题.
100000:40000
200000:80000
300000:80000
400000:160000
500000:200000
600000:160000
700000:240000
800000:320000
900000:240000
1000000:400000
1100000:400000
1200000:320000
1300000:480000
1400000:480000
1500000:400000
1600000:640000
1700000:640000
1800000:480000
1900000:720000
2000000:800000
2100000:480000
2200000:800000
2300000:880000
2400000:640000
2500000:1000000
2600000:960000
2700000:720000
2800000:960000
2900000:1120000
3000000:800000
3100000:1200000
3200000:1280000
3300000:800000
3400000:1280000
3500000:1200000
3600000:960000
3700000:1440000
3800000:1440000
3900000:960000
4000000:1600000
4100000:1600000
4200000:960000
4300000:1680000
4400000:1600000
4500000:1200000
4600000:1760000
4700000:1840000
4800000:1280000
4900000:1680000
5000000:2000000
5100000:1280000
5200000:1920000
5300000:2080000
5400000:1440000
5500000:2000000
5600000:1920000
5700000:1440000
5800000:2240000
5900000:2320000
6000000:1600000
6100000:2400000
6200000:2400000
6300000:1440000
6400000:2560000
6500000:2400000
6600000:1600000
6700000:2640000
6800000:2560000
6900000:1760000
7000000:2400000
7100000:2800000
7200000:1920000
7300000:2880000
7400000:2880000
7500000:2000000
7600000:2880000
7700000:2400000
7800000:1920000
7900000:3120000
8000000:3200000
8100000:2160000
8200000:3200000
8300000:3280000
8400000:1920000
8500000:3200000
8600000:3360000
8700000:2240000
8800000:3200000
8900000:3520000
9000000:2400000
9100000:2880000
9200000:3520000
9300000:2400000
9400000:3680000
9500000:3600000
9600000:2560000
9700000:3840000
9800000:3360000
9900000:2400000
10000000:4000000
当n为[8319823]时,phi(n)为[8313928], n/phi(n)值最小,为[1.001].
[2016-12-16 11:39:50.049979]第70题运行完毕，结果[8319823]: From start 34745389 us,from last 34745389 us
By Moon
*/
