// Powerful digit sum
// Problem 56
// Published on 07 November 2003 at 06:00 pm [Server Time]
// A googol (10^100) is a massive number: one followed by one-hundred zeros; 100^100 is almost unimaginably large: one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.
// 
// Considering natural numbers of the form, ab, where a, b < 100, what is the maximum digital sum ?
//
// 题目56：对于形如a的b次方的数字，找出最大的各位和。
// 一个googol(10^100)是一个巨大的数字：1后面跟着100个0；100^100几乎是不可想象的大：1后面跟着200个0。它们虽然很大，但是它们的各位数之和却只有1。
// 
// 考虑形如 ab 的数, 其中 a, b < 100，最大的各位和是多少？

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 56

#include <Template.h>

#include <CppBigNum.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    uint32_t GetSumOfDigit(const CppBigNum &bigNum)
    {
        const string &result = bigNum.Value();

        uint32_t sum = 0;
        for (string::const_iterator it = result.begin(); it != result.end(); ++it)
        {
            sum += *it - '0';
        }

        return sum;
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
    const uint32_t MAX_A = 99;      // 底数A的最大值
    const uint32_t MAX_B = 99;      // 指数B的最大值
    uint32_t maxSum = 0;            // 最大各位之和
    uint32_t maxA = 0;
    uint32_t maxB = 0;
    CppBigNum maxNum = 0;
    uint32_t currSum = 0;           // 当前各位之和

    for (uint32_t a = 0; a <= MAX_A; ++a)
    {
        CppBigNum bigNum(a);
        for (uint32_t b = 2; b <= MAX_B; ++b)
        {
            bigNum = bigNum * a;
            currSum = GetSumOfDigit(bigNum);

            if (currSum > maxSum)
            {
                maxA = a;
                maxB = b;
                maxNum = bigNum;
                maxSum = currSum;
            }
        }
    }

    cout << CppString::GetArgs("最大各位之和为%u,来源于%u^%u=%s\n", maxSum, maxA, maxB, maxNum.Value().c_str());
    return CppString::ToString(currSum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
[2014-07-15 15:36:55.925741]开始运行第56题
最大各位之和为972,来源于99^95=3848960788934848611927795802824596789608451156087366034658627953530148126008534258032267383768627487094610968554286692697374726725853195657679460590239636893953692985541958490801973870359499
[2014-07-15 15:36:56.032857]第56题运行完毕，结果[936]: From start 107116 us,from last 107116 us
By Moon
*/