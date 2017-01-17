// Square root digital expansion
// Problem 80
// It is well known that if the square root of a natural number is not an integer, then it is irrational. The decimal expansion of such square roots is infinite without any repeating pattern at all.
// 
// The square root of two is 1.41421356237309504880..., and the digital sum of the first one hundred decimal digits is 475.
// 
// For the first one hundred natural numbers, find the total of the digital sums of the first one hundred decimal digits for all the irrational square root

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 80

#include <Template.h>

#include <CppLog.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 长除式除法，算法来源于维基百科：https://zh.wikipedia.org/wiki/%E5%B9%B3%E6%96%B9%E6%A0%B9
    string LongSqrt(uint64_t num)
    {
        string numStr = CppString::ToString(num);

        // 首先将要开平方根的数从小数点分别向右及向左每两个位一组分开
        // 如98765.432内小数点前的65是一组，87是一组，9是一组，小数点后的43是一组
        // 之后是单独一个2，要补一个0而得20是一组。如1 04.85 73得四组，顺序为1' 04. 85' 73'
        vector<uint8_t> numBy2;
        for (uint64_t numBak = num; numBak != 0; numBak /= 100)
        {
            numBy2.push_back(numBak % 100);
        }

        auto numIt = numBy2.rbegin();
        uint32_t currNum = *numIt;
        for (; numIt != numBy2.rend(); ++numIt)
        {
            // 将最左的一组的数减去最接近又少于它的平方数，并将该平方数的开方（应该是个位数）记下
            
        }
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
    return CppString::ToString(0);
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
