#ifndef _TESTER_WINDOWS_H_
#define _TESTER_WINDOWS_H_
#include "AVLTree.h"
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <cstdlib>
#include "timer.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <random>

bool test1(int max);
bool test2(int max);
bool test3(int max);
bool test4(int max);
bool test5(int max);
bool test6(int max);
bool test7(int max);
bool test8(int max);
bool test9(int max);
bool test10(int max);

int tester(void);

extern Timer timer;

const int numTests = 10;

extern std::map<EmployeeInfo, int> Map;
const int maxRecords = 2500000000;

typedef bool (*TestPtr)(int);



#endif //_TESTER_WINDOWS_H_
