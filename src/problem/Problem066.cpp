// Diophantine equation
// Problem 66
// Consider quadratic Diophantine equations of the form:
// 
// x^2 – Dy^2 = 1
// 
// For example, when D=13, the minimal solution in x is 6492 – 13×1802 = 1.
// 
// It can be assumed that there are no solutions in positive integers when D is square.
// 
// By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:
// 
// 3^2 – 2×2^2 = 1
// 2^2 – 3×1^2 = 1
// 9^2 – 5×4^2 = 1
// 5^2 – 6×2^2 = 1
// 8^2 – 7×3^2 = 1
// 
// Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.
// 
// Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.

#ifdef PROBLEM_NO
#undef PROBLEM_NO
#endif // PROBLEM_NO
#define PROBLEM_NO 66

#include <Template.h>

#include <CppMath.h>
#include <CppBigNum.h>

using namespace std;

namespace GET_NAMESPACE_NAME(PROBLEM_NO)
{
    // 当前模块用到的全局变量和全局函数放在此处

    // 对于给定的D，找到最小的x(x>1)，使得x^2 = D * y ^ 2 + 1
    CppBigNum FindMinX(CppBigNum d)
    {
        for (CppBigNum x = 2;; ++x)
        {
            if (x % 1000 == 0)
            {
                printf("D[%s],x[%s]\n", d.Value().c_str(), x.Value().c_str());
            }
            CppBigNum dy2 = x * x - 1;

            // 如果计算的d * y ^ 2不能整除d，跳过
            if (dy2 % d != 0)
            {
                continue;
            }

            CppBigNum y2 = dy2 / d;

            // 如果计算出来的y2开方后是整数，那么这个x符合要求
            CppBigNum y = y2.Sqrt();
            if (y * y == y2)
            {
                return x;
            }
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
    static const uint64_t COUNT = 100;
    CppBigNum maxX = 0;
    CppBigNum maxD = 0;

    for (uint64_t d = 1; d <= COUNT; ++d)
    {
        // 排除D为平方数的结果，此时无解
        if (CppMath::IsIntegerSquare(d))
        {
            continue;
        }

        CppBigNum minX = FindMinX(d);
        printf("D[%lu]对应的minX[%s].\n", d, minX.Value().c_str());
        if (minX > maxX)
        {
            maxX = minX;
            maxD = d;
        }
    }

    printf("符合条件的最大的X[%s],对应的D[%s].\n", maxX.Value().c_str(), maxD.Value().c_str());
    return CppString::ToString(maxX.Value());
}

/* 析构函数：做当前页面的一些资源释放工作 */
GET_CLASS_NAME(PROBLEM_NO)::~GET_CLASS_NAME(PROBLEM_NO)()
{
    /* TODO */
}

/*

*/
