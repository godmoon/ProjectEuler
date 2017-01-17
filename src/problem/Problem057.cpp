// Square root convergents
// Problem 57
// Published on 21 November 2003 at 06:00 pm[Server Time]
// It is possible to show that the square root of two can be expressed as an infinite continued fraction.
// 
// √ 2 = 1 + 1 / (2 + 1 / (2 + 1 / (2 + ...))) = 1.414213...
// 
// By expanding this for the first four iterations, we get :
// 
// 1 + 1 / 2 = 3 / 2 = 1.5
// 1 + 1 / (2 + 1 / 2) = 7 / 5 = 1.4
// 1 + 1 / (2 + 1 / (2 + 1 / 2)) = 17 / 12 = 1.41666...
// 1 + 1 / (2 + 1 / (2 + 1 / (2 + 1 / 2))) = 41 / 29 = 1.41379...
// 
// The next three expansions are 99 / 70, 239 / 169, and 577 / 408, but the eighth expansion, 1393 / 985, is the first example where the number of digits in the numerator exceeds the number of digits in the denominator.
// 
// In the first one - thousand expansions, how many fractions contain a numerator with more digits than denominator ?
// 
// 题目57：考察2的平方根的展开。
// 2的平方根可以被表示为无限延伸的分数：
// 
// √ 2 = 1 + 1 / (2 + 1 / (2 + 1 / (2 + ...))) = 1.414213...
// 
// 将其前四次迭代展开，我们得到：
// 
// 1 + 1 / 2 = 3 / 2 = 1.5
// 1 + 1 / (2 + 1 / 2) = 7 / 5 = 1.4
// 1 + 1 / (2 + 1 / (2 + 1 / 2)) = 17 / 12 = 1.41666...
// 1 + 1 / (2 + 1 / (2 + 1 / (2 + 1 / 2))) = 41 / 29 = 1.41379...
// 
// 接下来三次迭代的展开是99 / 70, 239 / 169, and 577 / 408, 但是第八次迭代的展开, 1393 / 985, 是第一个分子的位数超过分母的位数的例子。
// 
// 在前1000次迭代的展开中，有多少个的分子位数超过分母位数？

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 57

#include <Template.h>

#include <CppBigNum.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 此题可以寻找到规律，每次展开的值-1得：1/2,2/5,5/12,12/29,29/70,70/169,169/408,408/985
    // 可以看出
    // 对于n=0,a[0]的分子=1；对于n>0,a[n]的分子=a[n-1]的分母。
    // 对于n=0,a[0]的分母=2；对于n>0,a[n]的分母=a[n]的分子*2+a[n-1]的分子
    // 因此可以得到一个序列：1,2,5,12,29,...
    // n=0:a[0]=1
    // n=1:a[1]=2
    // n>=2;a[n]=a[n-1]*2+a[n-2]

    const uint32_t MAX_NUM = 1000;        // 最大数值计算分数数目

    /* 根据索引获得序列的值 */
    CppBigNum GetNumByIndex(uint32_t index)
    {
        static vector<CppBigNum> numArray(MAX_NUM + 1);
        static bool haveInit = false;
        if (!haveInit)
        {
            haveInit = true;
            numArray[0] = CppBigNum(1);
            numArray[1] = CppBigNum(2);
        }

        static uint32_t caledIndex = 1;              // 已经计算到的数列

        if (index > MAX_NUM + 1)
        {
            return -1;
        }

        while (caledIndex < index)
        {
            ++caledIndex;
            numArray[caledIndex] = numArray[caledIndex - 1] * 2 + numArray[caledIndex - 2];
        }

        return numArray[index];
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
    uint32_t resultNum = 0;         // 结果数目
    CppBigNum numerator;            // 分子
    CppBigNum denominator;          // 分母

    for (uint32_t i = 0; i < MAX_NUM; ++i)
    {
        denominator = GetNumByIndex(i + 1);             // 分母
        numerator = denominator + GetNumByIndex(i);     // 分子=分母+分母序列值的前一个序列值

        //cout << CppString::GetArgs("test[%u]:%s/%s\n", i, numerator.Value().c_str(), denominator.Value().c_str());

        if (numerator.Value().size() > denominator.Value().size())
        {
            ++resultNum;
            //cout << CppString::GetArgs("index[%u]:%s/%s\n", i, numerator.Value().c_str(), denominator.Value().c_str());
        }
    }

    return CppString::ToString(resultNum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
[2014-07-15 16:37:15.916222]开始运行第57题
[2014-07-15 16:37:15.941149]第57题运行完毕，结果[153]: From start 24927 us,from last 24927 us
By Moon
*/
