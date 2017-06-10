#include "autotest.h"

int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
  totalNum++;

  if (!expr) {
    failedNum++;
    printf("test failed: %s in %s:%i\n", func, filename, lineNum);
  }
} 


void Test::showFinalResults() {
  if (failedNum)
    printf("Failed %i of %zu tests.\n", failedNum, totalNum);
  else
    printf("All tests passed.\n");
}
