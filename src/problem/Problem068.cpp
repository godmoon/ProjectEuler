// Magic 5-gon ring
// Problem 68
// Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and each line adding to nine.
// 
// 
// Working clockwise, and starting from the group of three with the numerically lowest external node (4,3,2 in this example), each solution can be described uniquely. For example, the above solution can be described by the set: 4,3,2; 6,2,1; 5,1,3.
// 
// It is possible to complete the ring with four different totals: 9, 10, 11, and 12. There are eight solutions in total.
// 
// Total    Solution Set
// 9    4,2,3; 5,3,1; 6,1,2
// 9    4,3,2; 6,2,1; 5,1,3
// 10   2,3,5; 4,5,1; 6,1,3
// 10   2,5,3; 6,3,1; 4,1,5
// 11   1,4,6; 3,6,2; 5,2,4
// 11   1,6,4; 5,4,2; 3,2,6
// 12   1,5,6; 2,6,4; 3,4,5
// 12   1,6,5; 3,5,4; 2,4,6
// By concatenating each group it is possible to form 9-digit strings; the maximum string for a 3-gon ring is 432621513.
// 
// Using the numbers 1 to 10, and depending on arrangements, it is possible to form 16- and 17-digit strings. What is the maximum 16-digit string for a "magic" 5-gon ring?

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 68

#include <Template.h>

#include <numeric>
#include <algorithm>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 是否符合条件
    bool IsOk(const vector<uint32_t> &numVec)
    {
        // 要保证每一条边之和相等
        uint32_t numTotal = numVec[0] + numVec[1] + numVec[2];
        if (numTotal != numVec[3] + numVec[2] + numVec[4])
        {
            return false;
        }

        if (numTotal != numVec[5] + numVec[4] + numVec[6])
        {
            return false;
        }

        if (numTotal != numVec[7] + numVec[6] + numVec[8])
        {
            return false;
        }

        if (numTotal != numVec[9] + numVec[8] + numVec[1])
        {
            return false;
        }

        return true;
    }

    string GetSeqStr(const vector<uint32_t> &numVec)
    {
        vector<string> numSec;
        uint32_t firstIndex = 0;            // 找到首节点最小的索引
        uint32_t firstValue = -1;           // 找到首节点最小的值

    #define PUSH_BACK_TO_SEC(i1,i2,i3) {numSec.push_back(CppString::GetArgs("%d%d%d", numVec[i1], numVec[i2], numVec[i3]));\
            if(firstValue > numVec[i1])\
            {\
                firstValue = numVec[i1];\
                firstIndex = numSec.size() - 1;\
            }\
        }

        PUSH_BACK_TO_SEC(0, 1, 2);
        PUSH_BACK_TO_SEC(3, 2, 4);
        PUSH_BACK_TO_SEC(5, 4, 6);
        PUSH_BACK_TO_SEC(7, 6, 8);
        PUSH_BACK_TO_SEC(9, 8, 1);

    #undef PUSH_BACK_TO_SEC

        string result;
        for (uint32_t i = 0; i < numSec.size(); ++i)
        {
            result += numSec[(firstIndex + i) % numSec.size()];
        }

        return result;
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
    static const uint32_t NUM_SIZE = 16;        // 结果长度

    vector<uint32_t> numVec(10);
    iota(numVec.begin(), numVec.end(), 1);
    uint64_t maxNum = 0;

    while (next_permutation(numVec.begin(), numVec.end()))
    {
        if (IsOk(numVec))
        {
            string str = GetSeqStr(numVec);
            if (str.length() == NUM_SIZE)
            {
                // cout << str << endl;
                uint64_t currNum = CppString::FromString<uint64_t>(str);
                if (maxNum < currNum)
                {
                    maxNum = currNum;
                }
            }
        }
    }

    printf("符合条件的最大的序号为[%lu].\n", maxNum);
    return CppString::ToString(maxNum);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 68
[2016-12-15 18:06:55.262623]开始运行第68题.
符合条件的最大的序号为[6531031914842725].
[2016-12-15 18:06:55.280001]第68题运行完毕，结果[6531031914842725]: From start 17378 us,from last 17378 us
By Moon
*/
