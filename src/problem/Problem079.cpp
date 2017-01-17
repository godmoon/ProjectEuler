// Passcode derivation
// Problem 79
// A common security method used for online banking is to ask the user for three random characters from a passcode. For example, if the passcode was 531278, they may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.
// 
// The text file, keylog.txt, contains fifty successful login attempts.
// 
// Given that the three characters are always asked for in order, analyse the file so as to determine the shortest possible secret passcode of unknown lengt
// 
// p079_keylog.txt
// 319
// 680
// 180
// 690
// 129
// 620
// 762
// 689
// 762
// 318
// 368
// 710
// 720
// 710
// 629
// 168
// 160
// 689
// 716
// 731
// 736
// 729
// 316
// 729
// 729
// 710
// 769
// 290
// 719
// 680
// 318
// 389
// 162
// 289
// 162
// 718
// 729
// 319
// 790
// 680
// 890
// 362
// 319
// 760
// 316
// 729
// 380
// 319
// 728
// 716

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 79

#include <Template.h>

#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处
    vector<uint16_t> keylog = {319,680,180,690,129,620,762,689,762,318,368,710,720,710,629,168,160,689,716,731,736,729,316,729,729,710,769,290,719,680,318,389,162,289,162,718,729,319,790,680,890,362,319,760,316,729,380,319,728,716};
}

using namespace GET_NAMESPACE_NAME(PROBLEM_NO);

/* 当前页面的构造函数，会在页面加载前调用，未请求的页面不会调用 */
GET_CLASS_NAME(PROBLEM_NO)::GET_CLASS_NAME(PROBLEM_NO)() : Problem()
{
}

/* 运行 */
string GET_CLASS_NAME(PROBLEM_NO)::Run()
{
    uint8_t numMap[10][10] = {0};
    uint8_t num[3];
    set<uint8_t> haveNumSet;      // 有的数字
    for (auto key_it = keylog.begin(); key_it != keylog.end(); ++key_it)
    {
        num[0] = *key_it % 10;
        num[1] = *key_it / 10 % 10;
        num[2] = *key_it / 100;

        haveNumSet.insert(num[0]);
        haveNumSet.insert(num[1]);
        haveNumSet.insert(num[2]);

        numMap[num[2]][num[1]]++;
        numMap[num[1]][num[0]]++;
    }

    multimap<uint8_t, uint8_t> sortedNum;
    for (uint8_t i = 0; i < 10; ++i)
    {
        uint32_t times = 0;
        for (uint8_t j = 0; j < 10; ++j)
        {
            if (numMap[i][j] > 0)
            {
                times++;
            }
            cout << (int)numMap[i][j] << " ";
        }
        cout << " : " << times << endl;

        sortedNum.insert(make_pair(times, i));
    }

    // 找最少非零数字的行
    string result;
    while (!haveNumSet.empty())
    {
        for (uint8_t i = 0; i < 10; ++i)
        {
            if (haveNumSet.find(i) == haveNumSet.end())
            {
                continue;
            }

            uint32_t times = 0;
            for (uint8_t j = 0; j < 10; ++j)
            {
                if (numMap[i][j] > 0)
                {
                    times++;
                }
            }

            if (times == 0)
            {
                result = CppString::ToString((int)i) + result;

                // 清除这个数字
                haveNumSet.erase(i);

                // 清除这一列的所有数字
                for (uint8_t j = 0; j < 10; ++j)
                {
                    numMap[j][i] = 0;
                }
            }
        }
    }

    return result;
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
./ProjectEuler 79
[2017-01-11 09:23:47.319562]开始运行第79题.
0 0 0 0 0 0 0 0 0 0  : 0
3 0 1 0 0 0 8 0 4 5  : 5
2 0 0 0 0 0 0 0 2 8  : 3
0 9 0 0 0 0 3 0 2 0  : 3
0 0 0 0 0 0 0 0 0 0  : 0
0 0 0 0 0 0 0 0 0 0  : 0
2 0 7 0 0 0 0 0 7 2  : 4
0 7 7 2 0 0 4 0 0 1  : 5
5 0 0 0 0 0 0 0 0 5  : 2
4 0 0 0 0 0 0 0 0 0  : 1
[2017-01-11 09:23:47.319728]第79题运行完毕，结果[73162890]: From start 166 us,from last 166 us
By Moon
*/
