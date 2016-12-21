#ifndef _PROBLEM_H_
#define _PROBLEM_H_

#include <stdint.h>

#include <map>
#include <cstddef>
#include <iostream>
#include <string>

#include <CppString.h>
#include <CppLog.h>

extern CppLog cppLog;

using std::map;
using std::string;

#ifdef GET_STR
#undef GET_STR
#endif // GET_STR
#define GET_STR(tempname) #tempname

#ifdef TEXTCAT
#undef TEXTCAT
#endif // TEXTCAT
#define TEXTCAT(text1,text2) text1##text2

#ifdef TO_STR
#undef TO_STR
#endif // TO_STR
#define TO_STR(tempname) GET_STR(tempname)

#ifdef GET_CLASS_NAME
#undef GET_CLASS_NAME
#endif // GET_CLASS_NAME
#define GET_CLASS_NAME(tempname) TEXTCAT(Problem_,tempname)

#ifdef GET_REGISTER_NAME
#undef GET_REGISTER_NAME
#endif // GET_REGISTER_NAME
#define GET_REGISTER_NAME(tempname) TEXTCAT(Register_,tempname)

#ifdef GET_INSTANCE_NAME
#undef GET_INSTANCE_NAME
#endif // GET_INSTANCE_NAME
#define GET_INSTANCE_NAME(tempname) TEXTCAT(Instance_,tempname)

#ifdef GET_NAMESPACE_NAME
#undef GET_NAMESPACE_NAME
#endif // GET_NAMESPACE_NAME
#define GET_NAMESPACE_NAME(tempname) TEXTCAT(ns_,tempname)

class Problem
{
public:

    Problem();
    ~Problem();

    virtual uint32_t GetProblemNo() = 0;
    virtual string Run() = 0;
    static Problem *GetProblem(uint32_t problemNo);

    static map<uint32_t, Problem*> *ProblemMap;

private:

};

#endif
