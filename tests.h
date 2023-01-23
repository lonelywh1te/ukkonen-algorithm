#ifndef MAIN_CPP_TESTS_H
#define MAIN_CPP_TESTS_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "suffix_tree.h"
using namespace std;

void run_test(string str, string substr, int answer, int test_number);
vector<string> read_test(int test_number);
void test_tree();

#endif //MAIN_CPP_TESTS_H
