#ifndef __TEST_H__
#define __TEST_H__     

#include <stdio.h>

class Test {
protected:
    static int failedNum;
    static int totalNum;
public:
    static void check(bool expr, const char *func, const char  *filename, size_t lineNum); 
    static void showFinalResults();
    virtual void runAllTests() = 0;
};

#endif