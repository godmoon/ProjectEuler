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

#include <CppMath.h>
#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    uint32_t SummationsCount(uint32_t n)
    {
        if (n == 1)
        {
            return 0;
        }

        if (n == 2)
        {
            return 1;
        }

        return 0;
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
    static const uint32_t THREAD_COUNT = 4;
    static const uint32_t COUNT = 1500000;
    list<thread> threads;
    atomic<uint32_t> resultSum(0);
    atomic<uint32_t> currN(3);

    for (uint32_t i = 0; i < THREAD_COUNT; ++i)
    {
        thread th([&](uint32_t threadId)
        {
            uint32_t n;
            while ((n = currN.fetch_add(1)) <= COUNT)
            {
                if (IsOneRightAngleTrianglePro(n))
                {
                    // DEBUG_LOG("%u", n);
                    ++resultSum;
                }

                if (n % 15000 == 0)
                {
                    DEBUG_LOG("线程[%u]完成计算[%u],目前结果[%u].", threadId, n, resultSum.load());
                }
            }
        }, i);

        threads.push_back(move(th));
    }

    // 等待线程完成
    for (auto &th : threads)
    {
        th.join();
    }

    printf("线长小于等于[%u]一共有[%u]种长度的线仅能组成1个整数直角三角形.\n", COUNT, resultSum.load());
    return CppString::ToString(resultSum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
*/
