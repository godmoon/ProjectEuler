// Prime summations
// Problem 77
// It is possible to write ten as the sum of primes in exactly five different ways:
// 
// 7 + 3
// 5 + 5
// 5 + 3 + 2
// 3 + 3 + 2 + 2
// 2 + 2 + 2 + 2 + 2
// 
// What is the first value which can be written as the sum of primes in over five thousand different way

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 77

#include <unordered_map>
#include <thread>
#include <list>
#include <atomic>
#include <mutex>

#include <Template.h>

#include <CppMath.h>
#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处


    /** 获得素数组合数
    *
    * @param    uint32_t remainValue
    * @param    uint32_t maxValue
    * @retval   uint32_t
    * @author   moontan
    */
    uint32_t PrimeCount(uint32_t remainValue, uint32_t maxValue)
    {
        //INFOR_LOG("%u,%u开始.", remainValue, maxValue);
        if (remainValue == 0)
        {
            //INFOR_LOG("%u,%u,count[%u].", remainValue, maxValue, 0);
            return 1;
        }

        static unordered_map<uint64_t, uint32_t> resultCache;
        static mutex mapLock;
        static CppMathPrimeWithCache primeWithCache;

        unique_lock<mutex> lock(mapLock);
        auto cacheIt = resultCache.find((static_cast<uint64_t>(remainValue) << 32) + maxValue);
        if (cacheIt != resultCache.end())
        {
            return cacheIt->second;
        }

        lock.unlock();

        if (maxValue > remainValue)
        {
            maxValue = remainValue;
        }

        uint32_t count = 0;

        if (maxValue >= 2)
        {
            count += PrimeCount(remainValue - 2, 2);
        }

        for (uint32_t i = 3; i <= maxValue; i += 2)
        {
            // 排除非素数
            if (!primeWithCache.IsPrime(i))
            {
                continue;
            }

            count += PrimeCount(remainValue - i, i);
        }

        //INFOR_LOG("%u,%u,count[%u].", remainValue, maxValue, count);

        lock.lock();
        resultCache[(static_cast<uint64_t>(remainValue) << 32) + maxValue] = count;
        lock.unlock();
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
    static const uint32_t THREAD_COUNT = 7;
    static const uint32_t COUNT = 5000;
    list<thread> threads;
    uint32_t resultN = -1;
    uint32_t resultCount = 0;
    atomic<uint32_t> currN(2);

    for (uint32_t i = 0; i < THREAD_COUNT; ++i)
    {
        thread th([&](uint32_t threadId)
        {
            uint32_t result;
            uint32_t n;
            while (resultN == static_cast<uint32_t>(-1))
            {
                n = currN.fetch_add(1);
                result = PrimeCount(n, n - 1);
                DEBUG_LOG("[%u]有[%u]种素数分解方法.", n, result);

                if (result > COUNT && resultN > n)
                {
                    resultN = n;
                    resultCount = result;
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


    printf("N=[%u]时,总共有[%u]种素数分法,这是首个大于%u种分法的.\n", resultN, resultCount, COUNT);
    return CppString::ToString(resultCount);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 77
[2016-12-22 17:16:03.145237]开始运行第77题.
[2016-12-22 17:16:03.145472][DEBUG]Problem077.cpp:125|[2]有[0]种素数分解方法.
[2016-12-22 17:16:03.145509][DEBUG]Problem077.cpp:125|[3]有[0]种素数分解方法.
[2016-12-22 17:16:03.145516][DEBUG]Problem077.cpp:125|[4]有[1]种素数分解方法.
[2016-12-22 17:16:03.145520][DEBUG]Problem077.cpp:125|[5]有[1]种素数分解方法.
[2016-12-22 17:16:03.145523][DEBUG]Problem077.cpp:125|[6]有[2]种素数分解方法.
[2016-12-22 17:16:03.145526][DEBUG]Problem077.cpp:125|[7]有[2]种素数分解方法.
[2016-12-22 17:16:03.145530][DEBUG]Problem077.cpp:125|[9]有[4]种素数分解方法.
[2016-12-22 17:16:03.145534][DEBUG]Problem077.cpp:125|[10]有[5]种素数分解方法.
[2016-12-22 17:16:03.145539][DEBUG]Problem077.cpp:125|[11]有[5]种素数分解方法.
[2016-12-22 17:16:03.145544][DEBUG]Problem077.cpp:125|[12]有[7]种素数分解方法.
[2016-12-22 17:16:03.145548][DEBUG]Problem077.cpp:125|[13]有[8]种素数分解方法.
[2016-12-22 17:16:03.145566][DEBUG]Problem077.cpp:125|[8]有[3]种素数分解方法.
[2016-12-22 17:16:03.145638][DEBUG]Problem077.cpp:125|[14]有[10]种素数分解方法.
[2016-12-22 17:16:03.145688][DEBUG]Problem077.cpp:125|[15]有[12]种素数分解方法.
[2016-12-22 17:16:03.145696][DEBUG]Problem077.cpp:125|[16]有[14]种素数分解方法.
[2016-12-22 17:16:03.145701][DEBUG]Problem077.cpp:125|[17]有[16]种素数分解方法.
[2016-12-22 17:16:03.145706][DEBUG]Problem077.cpp:125|[18]有[19]种素数分解方法.
[2016-12-22 17:16:03.145711][DEBUG]Problem077.cpp:125|[19]有[22]种素数分解方法.
[2016-12-22 17:16:03.145716][DEBUG]Problem077.cpp:125|[20]有[26]种素数分解方法.
[2016-12-22 17:16:03.145730][DEBUG]Problem077.cpp:125|[22]有[35]种素数分解方法.
[2016-12-22 17:16:03.145739][DEBUG]Problem077.cpp:125|[23]有[39]种素数分解方法.
[2016-12-22 17:16:03.145748][DEBUG]Problem077.cpp:125|[24]有[46]种素数分解方法.
[2016-12-22 17:16:03.145739][DEBUG]Problem077.cpp:125|[21]有[30]种素数分解方法.
[2016-12-22 17:16:03.145770][DEBUG]Problem077.cpp:125|[27]有[67]种素数分解方法.
[2016-12-22 17:16:03.145779][DEBUG]Problem077.cpp:125|[28]有[77]种素数分解方法.
[2016-12-22 17:16:03.145786][DEBUG]Problem077.cpp:125|[29]有[86]种素数分解方法.
[2016-12-22 17:16:03.145792][DEBUG]Problem077.cpp:125|[30]有[98]种素数分解方法.
[2016-12-22 17:16:03.145801][DEBUG]Problem077.cpp:125|[31]有[110]种素数分解方法.
[2016-12-22 17:16:03.145808][DEBUG]Problem077.cpp:125|[32]有[124]种素数分解方法.
[2016-12-22 17:16:03.145816][DEBUG]Problem077.cpp:125|[33]有[140]种素数分解方法.
[2016-12-22 17:16:03.145824][DEBUG]Problem077.cpp:125|[34]有[157]种素数分解方法.
[2016-12-22 17:16:03.145830][DEBUG]Problem077.cpp:125|[35]有[175]种素数分解方法.
[2016-12-22 17:16:03.145838][DEBUG]Problem077.cpp:125|[36]有[197]种素数分解方法.
[2016-12-22 17:16:03.145847][DEBUG]Problem077.cpp:125|[37]有[218]种素数分解方法.
[2016-12-22 17:16:03.145857][DEBUG]Problem077.cpp:125|[38]有[244]种素数分解方法.
[2016-12-22 17:16:03.145868][DEBUG]Problem077.cpp:125|[39]有[272]种素数分解方法.
[2016-12-22 17:16:03.145877][DEBUG]Problem077.cpp:125|[40]有[302]种素数分解方法.
[2016-12-22 17:16:03.145900][DEBUG]Problem077.cpp:125|[41]有[335]种素数分解方法.
[2016-12-22 17:16:03.145914][DEBUG]Problem077.cpp:125|[42]有[372]种素数分解方法.
[2016-12-22 17:16:03.145934][DEBUG]Problem077.cpp:125|[43]有[412]种素数分解方法.
[2016-12-22 17:16:03.145946][DEBUG]Problem077.cpp:125|[44]有[456]种素数分解方法.
[2016-12-22 17:16:03.145956][DEBUG]Problem077.cpp:125|[45]有[504]种素数分解方法.
[2016-12-22 17:16:03.145980][DEBUG]Problem077.cpp:125|[46]有[557]种素数分解方法.
[2016-12-22 17:16:03.146008][DEBUG]Problem077.cpp:125|[47]有[613]种素数分解方法.
[2016-12-22 17:16:03.146020][DEBUG]Problem077.cpp:125|[48]有[677]种素数分解方法.
[2016-12-22 17:16:03.146030][DEBUG]Problem077.cpp:125|[49]有[744]种素数分解方法.
[2016-12-22 17:16:03.146042][DEBUG]Problem077.cpp:125|[50]有[819]种素数分解方法.
[2016-12-22 17:16:03.146053][DEBUG]Problem077.cpp:125|[51]有[899]种素数分解方法.
[2016-12-22 17:16:03.146064][DEBUG]Problem077.cpp:125|[52]有[987]种素数分解方法.
[2016-12-22 17:16:03.146076][DEBUG]Problem077.cpp:125|[53]有[1082]种素数分解方法.
[2016-12-22 17:16:03.146088][DEBUG]Problem077.cpp:125|[54]有[1186]种素数分解方法.
[2016-12-22 17:16:03.146102][DEBUG]Problem077.cpp:125|[55]有[1298]种素数分解方法.
[2016-12-22 17:16:03.146115][DEBUG]Problem077.cpp:125|[56]有[1420]种素数分解方法.
[2016-12-22 17:16:03.146128][DEBUG]Problem077.cpp:125|[57]有[1552]种素数分解方法.
[2016-12-22 17:16:03.146143][DEBUG]Problem077.cpp:125|[58]有[1695]种素数分解方法.
[2016-12-22 17:16:03.146156][DEBUG]Problem077.cpp:125|[59]有[1849]种素数分解方法.
[2016-12-22 17:16:03.146177][DEBUG]Problem077.cpp:125|[60]有[2018]种素数分解方法.
[2016-12-22 17:16:03.146192][DEBUG]Problem077.cpp:125|[61]有[2197]种素数分解方法.
[2016-12-22 17:16:03.146210][DEBUG]Problem077.cpp:125|[62]有[2394]种素数分解方法.
[2016-12-22 17:16:03.146236][DEBUG]Problem077.cpp:125|[63]有[2605]种素数分解方法.
[2016-12-22 17:16:03.146274][DEBUG]Problem077.cpp:125|[64]有[2833]种素数分解方法.
[2016-12-22 17:16:03.146317][DEBUG]Problem077.cpp:125|[65]有[3079]种素数分解方法.
[2016-12-22 17:16:03.146354][DEBUG]Problem077.cpp:125|[66]有[3344]种素数分解方法.
[2016-12-22 17:16:03.146374][DEBUG]Problem077.cpp:125|[67]有[3629]种素数分解方法.
[2016-12-22 17:16:03.146403][DEBUG]Problem077.cpp:125|[68]有[3936]种素数分解方法.
[2016-12-22 17:16:03.146423][DEBUG]Problem077.cpp:125|[69]有[4268]种素数分解方法.
[2016-12-22 17:16:03.146442][DEBUG]Problem077.cpp:125|[70]有[4624]种素数分解方法.
[2016-12-22 17:16:03.146461][DEBUG]Problem077.cpp:125|[71]有[5006]种素数分解方法.
[2016-12-22 17:16:03.147250][DEBUG]Problem077.cpp:125|[26]有[60]种素数分解方法.
[2016-12-22 17:16:03.147297][DEBUG]Problem077.cpp:125|[25]有[52]种素数分解方法.
N=[71]时,总共有[5006]种素数分法,这是首个大于5000种分法的.
[2016-12-22 17:16:03.147544]第77题运行完毕，结果[5006]: From start 2307 us,from last 2307 us
By Moon
*/
