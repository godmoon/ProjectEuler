// Coin partitions
// Problem 78
// Let p(n) represent the number of different ways in which n coins can be separated into piles. For example, five coins can be separated into piles in exactly seven different ways, so p(5)=7.
// 
// OOOOO
// OOOO   O
// OOO   OO
// OOO   O   O
// OO   OO   O
// OO   O   O   O
// O   O   O   O   O
// Find the least value of n for which p(n) is divisible by one millio

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 78

#include <unordered_map>
#include <thread>
#include <list>
#include <atomic>
#include <mutex>

#include <Template.h>

#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处
    static const uint32_t COUNT_MOD = 1000000;
    static const uint32_t MAX_VALUE = 30000;       // 预计计算规模，用于缓存
    static vector<vector<uint32_t>> resultCacheVec;

    uint32_t Count(uint64_t remainValue, uint64_t maxValue)
    {
        // INFOR_LOG("%u,%u开始.", remainValue, maxValue);
        if (remainValue <= 1 || maxValue <= 1)
        {
            // INFOR_LOG("%u,%u,count[%u].", remainValue, maxValue, 0);
            return 1;
        }

        // 用map加锁做缓存太慢了
        // static unordered_map<uint64_t, uint64_t> resultCache;
        // static mutex mapLock;

        if (maxValue > remainValue)
        {
            maxValue = remainValue;
        }

        if (resultCacheVec[remainValue][maxValue] != 0)
        {
            return resultCacheVec[remainValue][maxValue];
        }

        //         unique_lock<mutex> lock(mapLock);
        //         auto cacheIt = resultCache.find((static_cast<uint64_t>(remainValue) << 32) + maxValue);
        //         if (cacheIt != resultCache.end())
        //         {
        //             return cacheIt->second;
        //         }
        // 
        //         lock.unlock();

        uint64_t count = 0;
        for (uint64_t i = 1; i <= maxValue; ++i)
        {
//             if (remainValue - i > i)
//             {
// 
//             }
            count += Count(remainValue - i, i);

            // 记录这个count，它是Count(remainValue,i)的结果
//             lock.lock();
//             resultCache[(static_cast<uint64_t>(remainValue) << 32) + i] = count;
//             lock.unlock();

            resultCacheVec[remainValue][maxValue] = count;

            if (count >= COUNT_MOD)
            {
                count %= COUNT_MOD;
            }
        }

        //         lock.lock();
        //         resultCache[(static_cast<uint64_t>(remainValue) << 32) + maxValue] = count;
        //         lock.unlock();

        resultCacheVec[remainValue][maxValue] = count;

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
    // 开THREAD_COUNT个线程做这件事
    static const uint32_t THREAD_COUNT = 1;
    list<thread> threads;
    uint64_t resultN = -1;
    atomic<uint64_t> currN(2);

    // 初始化缓存
    resultCacheVec.resize(MAX_VALUE + 1);
    for (uint32_t i = 0; i <= MAX_VALUE; ++i)
    {
        resultCacheVec[i].resize(i + 1);
    }

    for (uint64_t i = 0; i < THREAD_COUNT; ++i)
    {
        thread th([&](uint64_t threadId)
        {
            uint32_t result;
            uint64_t n;
            while (resultN == static_cast<uint64_t>(-1))
            {
                n = currN.fetch_add(1);
                result = Count(n, n);
                if (n < 100)
                {
                    DEBUG_LOG("[%lu]的分法数 %% %u为[%lu].", n, COUNT_MOD, result);
                }

                if (result == COUNT_MOD && resultN > n)
                {
                    resultN = n;
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

    printf("N=[%lu]时,分法数能被%u整除.\n", resultN, COUNT_MOD);
    return CppString::ToString(resultN);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
*/
