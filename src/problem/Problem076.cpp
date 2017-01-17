// Counting summations
// Problem 76
// It is possible to write five as a sum in exactly six different ways:
// 
// 4 + 1
// 3 + 2
// 3 + 1 + 1
// 2 + 2 + 1
// 2 + 1 + 1 + 1
// 1 + 1 + 1 + 1 + 1
// 
// How many different ways can one hundred be written as a sum of at least two positive integers?

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 76

#include <thread>
#include <list>
#include <atomic>

#include <Template.h>

#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    /** 获得组合数
    *
    * @param    uint32_t remainValue
    * @param    uint32_t maxValue
    * @retval   uint32_t
    * @author   moontan
    */
    uint32_t Count(uint32_t remainValue, uint32_t maxValue)
    {
        // INFOR_LOG("%u,%u开始.", remainValue, maxValue);
        if (remainValue == 0)
        {
            // INFOR_LOG("%u,%u,count[%u].", remainValue, maxValue, 0);
            return 1;
        }

        if (maxValue > remainValue)
        {
            maxValue = remainValue;
        }

        uint32_t count = 0;
        for (uint32_t i = 1; i <= maxValue; ++i)
        {
            count += Count(remainValue - i, i);
        }

        // INFOR_LOG("%u,%u,count[%u].", remainValue, maxValue, count);
        return count;
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
    static const uint32_t NUM = 100;
    uint32_t result = Count(NUM, NUM - 1);

    printf("N=[%u]时,总共有[%u]种分法.\n", NUM, result);
    return CppString::ToString(result);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
 ./ProjectEuler 76
[2016-12-22 12:52:51.945177]开始运行第76题.
N=[100]时,总共有[190569291]种分法.
[2016-12-22 12:52:56.436532]第76题运行完毕，结果[190569291]: From start 4491355 us,from last 4491355 us
By Moon
*/
