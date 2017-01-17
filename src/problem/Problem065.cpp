#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 65

#include <Template.h>

#include <CppFraction.h>
#include <CppBigNum.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 获得e解开之后指定位置的分母常数部分，0表示第一个数字2，1表示后面的序列
    // e = [2; 1,2,1, 1,4,1, 1,6,1 , ... , 1,2k,1, ...].
    uint32_t GetConstant(uint32_t index)
    {
        if (index == 0)
        {
            return 2;
        }

        if (index % 3 == 1 || index % 3 == 0)
        {
            return 1;
        }

        // 这里不用把index-1，因为这种情况是%3==0的情况，在前面已经返回了1
        return (index / 3 + 1) * 2;
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
    static uint32_t COUNT = 100;
    CppFraction<CppBigNum> result(GetConstant(COUNT - 1));
    for (int32_t i = COUNT - 2; i > 0; --i)
    {
        printf("1 / (%s + %u) = ", result.ToString().c_str(), GetConstant(i));
        result = CppFraction<CppBigNum>(1) / (result + GetConstant(i));
        printf("%s\n", result.ToString().c_str());
    }

    // printf("%s + %u = ", result.ToString().c_str(), GetConstant(0));
    result += GetConstant(0);
    //printf("%s\n", result.ToString().c_str());
    printf("最终计算分数结果：%s\n", result.ToString().c_str());

    uint32_t sum = 0;
    string numerator = result.Numerator.Value();
    for (auto charIt = numerator.begin(); charIt != numerator.end(); ++charIt)
    {
        sum += *charIt - '0';
    }

    printf("分子各数字之和为：%u\n", sum);

    return CppString::ToString(sum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 65
[2016-06-18 14:49:08.918810]开始运行第65题.
最终计算分数结果：6963524437876961749120273824619538346438023188214475670667/2561737478789858711161539537921323010415623148113041714756
分子各数字之和为：272
[2016-06-18 14:49:09.421978]第65题运行完毕，结果[272]: From start 503168 us,from last 503168 us
By Moon
*/
