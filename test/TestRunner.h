#include <stdio.h>
#include <string.h>
#if ! WINDOWS
#include <unistd.h>
#endif
#include "PlatformUtilities.h"
#include "CharString.h"

#ifndef __func__
#define __func__ __FUNCTION__
#endif

#define ANSI_COLOR_BLACK   "[30m"
#define ANSI_COLOR_RED     "[31m"
#define ANSI_COLOR_GREEN   "[32m"
#define ANSI_COLOR_YELLOW  "[33m"
#define ANSI_COLOR_BLUE    "[34m"
#define ANSI_COLOR_MAGENTA "[35m"
#define ANSI_COLOR_CYAN    "[36m"
#define ANSI_COLOR_WHITE   "[37m"
#define ANSI_COLOR_RESET   "[0m"

#define _assert(condition) { \
  if(!(condition)) { \
    printTestFail(); \
    printf("    at %s(), line %d\n", __func__, __LINE__); \
    return 1; \
  } \
}

#define _assertFalse(condition) _assert((condition) == false)
#define _assertIsNull(condition) _assert((condition) == NULL)
#define _assertNotNull(condition) _assert((condition) != NULL)

#define _assertIntEquals(condition, expected) { \
  int result = condition; \
  if(result != expected) { \
    printTestFail(); \
    printf("    at %s(), line %d. Expected %d, got %d.\n", __func__, __LINE__, expected, result); \
    return 1; \
  } \
}

#define _assertDoubleEquals(condition, expected) { \
  double result = condition; \
  if(result != expected) { \
    printTestFail(); \
    printf("    at %s(), line %d. Expected %g, got %g.\n", __func__, __LINE__, expected, result); \
    return 1; \
  } \
}

#define _assertCharStringEquals(result, expected) { \
  if(!isCharStringEqualToCString(result, expected, false)) { \
    printTestFail(); \
    printf("    at %s(), line %d. Expected %s, got %s.\n", __func__, __LINE__, expected, result->data); \
    return 1; \
  } \
}

typedef boolByte (*TestCaseExecFunc)(void* testCase);
typedef struct {
  char* name;
  char* filename;
  int lineNumber;
  TestCaseExecFunc testCaseFunc;
  boolByte result;
} TestCaseMembers;
typedef TestCaseMembers* TestCase;

typedef struct {
  char* name;
  LinkedList testCases;
} TestSuiteMembers;
typedef TestSuiteMembers* TestSuite;

void addTestToTestSuite(TestSuite testSuite, TestCase testCase);
void executeTestSuite(TestSuite testSuite);

void printTestSuiteResult(TestSuite testSuite);
void printTestSuccess(void);
void printTestFail(void);

TestSuite newTestSuite(char* name);
TestCase newTestCase(char* name, char* filename, int lineNumber, TestCaseExecFunc testCaseFunc);


#define addTest(testSuite, name, testCaseFunc) { \
  addTestToTestSuite(testSuite, newTestCase(name, __FILE__, __LINE__, testCaseFunc}); \
}

#define _runTest(testName, test, setup, teardown) \
  { \
    int result; \
    printTestStarted(testName); \
    setup(); \
    result = test(); \
    if(!result) { \
      testsPassed++; \
      printTestSuccess(); \
    } else { \
      testsFailed++; \
    } \
    teardown(); \
  }

#if WINDOWS
#define FILE_BASENAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#else
#define FILE_BASENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif

#define _startTestSection() \
  { \
    printf("Running tests in %s\n", FILE_BASENAME); \
  }

extern int testsPassed;
extern int testsFailed;

static void emptySetup(void) { }
static void emptyTeardown(void) { }

static void printTestStarted(const char* testName) {
  printf("  %s: ", testName);
}
