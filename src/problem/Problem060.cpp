// Prime pair sets
// Problem 60
// Published on 02 January 2004 at 06:00 pm[Server Time]
// The primes 3, 7, 109, and 673, are quite remarkable.By taking any two primes and concatenating them in any order the result will always be prime.For example, taking 7 and 109, both 7109 and 1097 are prime.The sum of these four primes, 792, represents the lowest sum for a set of four primes with this property.
// Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.
// 
// 题目60：找出一个5个质数的集合，该集合中每两个质数相连接都能产生一个质数。
// 质数3, 7, 109, 和 673是值得注意的。将其中任意两个质数以任何顺序相连接产生的结果都是质数。例如，取7和109，连接而成的7109和1097都是质数。这四个质数的和是792，这也是满足这个性质的四个质数集合的最小总和。
// 找出满足这个性质的五个质数的集合中，集合数之和最小的。算出这个最小的和。

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 60

#include <Template.h>

#include <vector>
#include <hash_map>
#include <hash_set>

#include <CppMath.h>
#include <CppTime.h>

using namespace std;
using namespace __gnu_cxx;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处
    const uint32_t MAX_COUNT = 6;                       // 需要找的素数组元素个数
    const uint32_t MAX_FIND_PRIME = 10000000;           // 拼接而成的最大素数
    vector<uint32_t> primers;                           // 素数数组
    vector<uint32_t> primerIndexs;                      // 素数组索引
    hash_map<uint32_t, hash_set<uint32_t> > invalidIndexPair;   // 不能成为素数的索引对，前一个比后一个小

    /* 产生素数数组 */
    uint32_t GetPrimerByIndex(uint32_t index, const CppMathPrimeWithInit<MAX_FIND_PRIME> &primeWithInit)
    {
        // 如果数组为空，则从最小素数开始，否则从素数数组中最后一个素数+1开始
        if (primers.empty())
        {
            primers.push_back(CppMath::MIN_PRIMER);
        }

        // 得到下一个可能的素数，但是要排除2的情况
        uint32_t num = *primers.rbegin() + 2;
        if (num == 4)
        {
            --num;
        }

        while (primers.size() <= index)
        {
            while (true)
            {
                if (primeWithInit.IsPrime(num))
                {
                    primers.push_back(num);
                    num += 2;
                    break;
                }

                num += 2;
            }
        }

        return primers[index];
    }

    /* 判断给定的索引是否两两结合均为素数，如果OK，则返回-1，否则返回需要进位的索引
       这个索引为需要进位的值，这样可以保证最快速度迭代，具体算法如下
       假设primerIndexs含有4个元素，索引为0,1,2,3
       那么按照下面的顺序进行对比，如果失败，返回相应的索引：
       it2:it1，失败返回it1
       3:2，失败返回2
       3:1，失败返回1
       2:1，失败返回1
       3:0，失败返回0
       2:0，失败返回0
       1:0，失败返回0
       */
    int32_t Any2IsPrimer(const vector<uint32_t> &primerIndexs, const CppMathPrimeWithInit<MAX_FIND_PRIME> &primeWithInit)
    {
        hash_map<uint32_t, hash_set<uint32_t> >::const_iterator smallIt;

        for (vector<uint32_t>::const_reverse_iterator it1 = primerIndexs.rbegin() + 1; it1 != primerIndexs.rend(); ++it1)
        {
            for (vector<uint32_t>::const_reverse_iterator it2 = primerIndexs.rbegin(); it2 != it1; ++it2)
            {
                // 从cache表中寻找索引对，如果存在，则直接跳过
                smallIt = invalidIndexPair.find(*it1);
                if (smallIt != invalidIndexPair.end() && smallIt->second.find(*it2) != smallIt->second.end())
                {
                    return primerIndexs.size() - (it1 - primerIndexs.rbegin()) - 1;
                }

                // 如果素数数组不够，则产生
                uint32_t numSmall = GetPrimerByIndex(*it1, primeWithInit);
                uint32_t numBig = GetPrimerByIndex(*it2, primeWithInit);

                bool badResult = false;      // 非素数标志为true

                uint32_t concatNum = CppString::FromString<uint32_t>(CppString::GetArgs("%u%u", numSmall, numBig));
                if (!primeWithInit.IsPrime(concatNum))
                {
                    //cout << CppString::GetArgs("%u is not primer.\n", concatNum);
                    badResult = true;
                }
                else
                {
                    concatNum = CppString::FromString<uint32_t>(CppString::GetArgs("%u%u", numBig, numSmall));
                    if (!primeWithInit.IsPrime(concatNum))
                    {
                        //cout << CppString::GetArgs("%u is not primer.\n", concatNum);
                        badResult = true;
                    }
                }

                // 如果非素数，添加到cache表并且返回false
                if (badResult)
                {
                    invalidIndexPair[*it1];
                    invalidIndexPair[*it1].insert(*it2);

                    return primerIndexs.size() - (it1 - primerIndexs.rbegin()) - 1;
                }
            }
        }

        return -1;
    }

    /* 获得下一个素数索引组合，输入需要合法，即primerIndexs按索引由小到大排列 */
    void GetNextParam(vector<uint32_t> &primerIndexs, uint32_t index)
    {
        if (index >= primerIndexs.size())
        {
            cerr << CppString::GetArgs("index[%u]>=primerIndexs.size()[%u]", index, primerIndexs.size()) << endl;
            return;
        }

        uint32_t i = 0;
        for (vector<uint32_t>::iterator it = primerIndexs.begin() + index; it != primerIndexs.end(); ++it, ++i)
        {
            // 如果是最后一个值或者前一个值+1小于后一个值，将此值+1，否则迭代到下一个值
            if (it + 1 == primerIndexs.end() || *it + 1 < *(it + 1))
            {
                ++(*it);

                // DEBUG
//                 static CppShowTimer timer;
//                 if (!timer.IsStart())
//                 {
//                     cout << timer.Start("开始") << endl;
//                 }
// 
//                 if (it + 1 == primerIndexs.end())
//                 {
//                     cout << timer.Record(CppString::GetArgs("最大值计算到%u.", *it)) << endl;
//                 }

                return;
            }

            // 如果需要进位，将此值置为初始值
            *it = i;
        }
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
    CppMathPrimeWithInit<MAX_FIND_PRIME> primeWithInit;
    for (uint32_t i = 0; i < MAX_COUNT; ++i)
    {
        primerIndexs.push_back(i);
    }

    // DEBUG：用于输出素数索引表
    //     GetPrimerByIndex(200);
    //     for (uint32_t i = 0; i < 200;++i)
    //     {
    //         cout <<i<<":"<< primers[i] << endl;
    //     }

    // DEBUG：4个的情况
    //     primerIndexs[0] = 2;
    //     primerIndexs[1] = 3;
    //     primerIndexs[2] = 28;
    //     primerIndexs[3] = 121;
    int32_t index;

    while (true)
    {
        //         for (vector<uint32_t>::const_iterator it = primerIndexs.begin(); it != primerIndexs.end(); ++it)
        //         {
        //             cout << *it << " ";
        //         }
        //         cout << endl;

        index = Any2IsPrimer(primerIndexs, primeWithInit);
        if (index == -1)
        {
            break;
        }

        //  cout << "index=" << index << endl;
        GetNextParam(primerIndexs, index);
    }

    uint32_t sum = 0;
    for (vector<uint32_t>::const_iterator it = primerIndexs.begin(); it != primerIndexs.end(); ++it)
    {
        uint32_t primer = GetPrimerByIndex(*it, primeWithInit);
        cout << primer << " ";
        sum += primer;
    }

    cout << endl;
    cout << "和为" << sum << endl;
    return CppString::ToString(sum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 60
[2014-08-13 10:30:38.723412]开始运行第60题.
3 7 109 673
和为792
[2014-08-13 10:30:39.074903]第60题运行完毕，结果[792]: From start 351491 us,from last 351491 us
By Moon

./ProjectEuler 60
[2014-08-01 23:37:43.491309]开始运行第60题.
13 5197 5701 6733 8389
和为26033
[2014-08-01 23:42:16.356812]第60题运行完毕，结果[26033]: From start 272865503 us,from last 272865503 us
By Moon
*/
