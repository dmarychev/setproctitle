#ifndef __UNIT_ACCEPTANCE_TEST_H__
#define __UNIT_ACCEPTANCE_TEST_H__

#include <cxxtest/TestSuite.h>

class AcceptanceTest : public CxxTest::TestSuite
{

public:
    void testOne()
    {
        TS_ASSERT(true);
    }

    void testTwo()
    {
        TS_ASSERT(true);
    }
};

#endif //__UNIT_ACCEPTANCE_TEST_H__
