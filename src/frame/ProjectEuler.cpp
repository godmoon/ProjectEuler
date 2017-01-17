#include "ProjectEuler.h"

#include <unistd.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <map>

#include <CppString.h>
#include <CppTime.h>
#include <CppLog.h>

#include "Problem.h"

using namespace std;

CppLog cppLog;

void ShowHelp(const char *programName)
{
    cout << CppString::GetArgs("用法：%s 题目编号\n", programName);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        ShowHelp(argv[0]);
        exit(0);
    }

    for (int32_t i = 1; i < argc; ++i)
    {
        if (i>1)
        {
            cout << endl;
        }

        uint32_t problemNo = CppString::FromString<uint32_t>(argv[i]);

        Problem *problemInstance = Problem::GetProblem(problemNo);
        if (problemInstance == NULL)
        {
            cerr << CppString::GetArgs("没有第%u题\n", problemNo);
            exit(-1);
        }

        CppShowTimer timer;
        cout << timer.Start(CppString::GetArgs("开始运行第%u题.", problemNo)) << endl;
        string result = problemInstance->Run();
        cout << timer.Record(CppString::GetArgs("第%u题运行完毕，结果[\033[32m%s\033[0m]", problemNo, result.c_str())) << endl;
        cout << "By Moon" << endl;
    }
}
