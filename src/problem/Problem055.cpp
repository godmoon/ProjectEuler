// Lychrel numbers  
//     Problem 55  
//     If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.  
//  
//     Not all numbers produce palindromes so quickly. For example,  
//  
//     349 + 943 = 1292,  
//     1292 + 2921 = 4213  
//     4213 + 3124 = 7337  
//  
//     That is, 349 took three iterations to arrive at a palindrome.  
//  
//     Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome. A number that never forms a palindrome through the reverse and add process is called a Lychrel number. Due to the theoretical nature of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise. In addition you are given that for every number below ten-thousand, it will either (i) become a palindrome in less than fifty iterations, or, (ii) no one, with all the computing power that exists, has managed so far to map it to a palindrome. In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome: 4668731596684224866951378664 (53 iterations, 28-digits).  
//  
//     Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.  
//  
//     How many Lychrel numbers are there below ten-thousand?  
//  
// NOTE: Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.  
//  
// 题目55:10000以下有多少Lychrel数？  
//     我们将47与它的逆转相加，47 + 74 = 121, 可以得到一个回文。  
//  
//     并不是所有数都能这么快产生回文，例如：  
//  
//     349 + 943 = 1292,  
//     1292 + 2921 = 4213  
//     4213 + 3124 = 7337  
//  
//     也就是说349需要三次迭代才能产生一个回文。  
//  
//     虽然还没有被证明，人们认为一些数字永远不会产生回文，例如196。那些永远不能通过上面的方法（逆转然后相加）产生回文的数字叫做Lychrel数。因为这些数字的理论本质，同时也为了这道题，我们认为一个数如果不能被证明的不是Lychrel数的话，那么它就是Lychre数。此外，对于每个一万以下的数字，你还有以下已知条件：这个数如果不能在50次迭代以内得到一个回文，那么就算用尽现有的所有运算能力也永远不会得到。10677是第一个需要50次以上迭代得到回文的数，它可以通过53次迭代得到一个28位的回文：4668731596684224866951378664。  
//  
//     令人惊奇的是，有一些回文数本身也是Lychrel数，第一个例子是4994。  
//  
//     10000以下一共有多少个Lychrel数？  

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 55

#include <Template.h>
#include <CppBigNum.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处
    inline bool IsPalindromeNum(const CppBigNum &bigNum)
    {
        return bigNum == bigNum.Reverse();
    }

    //************************************  
    // Method:    IsLychrelNum  
    // Access:    public  
    // Describe:  判断是否是Lychrel数  
    // Parameter: uint32_t num  
    // Returns:   bool  
    //************************************  
    bool IsLychrelNum(uint32_t num)
    {
        const uint32_t MAX_LOOP = 50;   // 最多加50次  

        CppBigNum bigNum(num);

        for (uint32_t i = 0; i < MAX_LOOP; ++i)
        {
            bigNum += bigNum.Reverse();

            if (IsPalindromeNum(bigNum))
            {
                return false;
            }
        }

        return true;
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
    const uint32_t MAX_NUM = 10000;
    uint32_t lychrelNumCount = 0;

    for (uint32_t i = 1; i < MAX_NUM; ++i)
    {
        if (IsLychrelNum(i))
        {
            ++lychrelNumCount;
        }
        //         else  
        //         {  
        //             cout << i << endl;  
        //         }  
    }

    cout << CppString::GetArgs("%u以内的Lychrel数有%u个\n", MAX_NUM, lychrelNumCount);

    return CppString::ToString(lychrelNumCount);
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*
[2014-07-15 12:46:29.351511]开始运行第55题
10000以内的Lychrel数有249个
[2014-07-15 12:46:29.521588]第55题运行完毕: From start 170077 us,from last 170077 us
By Moon
*/