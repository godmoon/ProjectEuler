#include "Problem.h"

#include <iostream>

/**************************************************************************************/
/* 下面部分为框架，无需修改，如果需要修改，则复制一份到页面的.h文件中，需要保证最新   */
/**************************************************************************************/
class GET_CLASS_NAME(PROBLEM_NO) : public Problem
{
public:
    GET_CLASS_NAME(PROBLEM_NO)();
    virtual ~GET_CLASS_NAME(PROBLEM_NO)();

    /* 创建实例函数 */
    static Problem *CreatePage()
    {
        static GET_CLASS_NAME(PROBLEM_NO) instance;
        return &instance;
    }

    /* 获得题号 */
    virtual uint32_t GetProblemNo()
    {
        return PROBLEM_NO;
    }

    /* 运行 */
    virtual string Run();
};

class GET_REGISTER_NAME(PROBLEM_NO)
{
public:
    GET_REGISTER_NAME(PROBLEM_NO)()
    {
        if (Problem::ProblemMap == NULL)
        {
            Problem::ProblemMap = new map<uint32_t, Problem*>();
        }

        (*Problem::ProblemMap)[PROBLEM_NO] = GET_CLASS_NAME(PROBLEM_NO)::CreatePage();
    }
};

// 使用全局成员初始化调用默认构造函数来对页面类进行注册，实现反射，无需修改
GET_REGISTER_NAME(PROBLEM_NO) GET_INSTANCE_NAME(PROBLEM_NO);
