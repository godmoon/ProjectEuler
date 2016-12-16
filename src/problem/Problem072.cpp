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
                if (d % 10000 == 0)
                {
                    printf("线程[%u]正在计算[%u]\n", threadId, d);
                }

                // 如果分母是2的倍数，就只算奇数好了
                if (d % 2 == 0)
                {
                    for (uint32_t n = 1; n < d; n += 2)
                    {
                        // 非最简分数，跳过
                        if (CppMath::GCD(n, d) != 1)
                        {
                            continue;
                        }

                        ++resultSum;
                    }
                }
                else
                {
                    for (uint32_t n = 1; n < d; ++n)
                    {
                        // 非最简分数，跳过
                        if (CppMath::GCD(n, d) != 1)
                        {
                            continue;
                        }

                        ++resultSum;
                    }
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


*/
