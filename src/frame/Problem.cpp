#include "Problem.h"

Problem::Problem()
{
}

Problem::~Problem()
{
}

Problem * Problem::GetProblem(uint32_t problemNo)
{
    if (ProblemMap == NULL)
    {
        return NULL;
    }

    map<uint32_t, Problem*>::iterator findResult = ProblemMap->find(problemNo);
    if (findResult == ProblemMap->end())
    {
        return NULL;
    }

    return findResult->second;
}

map<uint32_t, Problem*> *Problem::ProblemMap;
