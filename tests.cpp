#include "tests.h"

void test_ok(int test_number){
    ofstream result("../tests/result", ios_base::app);
    result << "test #" + to_string(test_number) << ": ok" << endl;
}

void test_failed(int test_number, int output){
    ofstream result("../tests/result", ios_base::app);
    vector<string> test = read_test(test_number);

    result << "test #" + to_string(test_number) << ": failed" << endl;
    result << "  str: " + test[0] << endl;
    result << "  substr: " + test[1] << endl;
    result << "  answer: " + test[2] << endl;
    result << "  output: " + to_string(output) << endl;
}

void run_test(string str, string substr, int answer, int test_number){
    suffix_tree a;
    a.build(str);

    if (a.find(substr) == answer) {
        test_ok(test_number);
    }
    else {
        test_failed(test_number, a.find(substr));
        exit(-1);
    }
}

vector<string> read_test(int test_number){
    vector<string> test;
    ifstream file("../tests/" + to_string(test_number));
    string line;

    if (file.is_open()){
        while(getline(file, line)){
            if (line.empty()) {
                test.push_back("");
            }
            else {
                test.push_back(line);
            }
        }
        return test;
    }
    return test;
}

void test_tree(){
    ofstream result("../tests/result");
    int test_number = 1;

    while(!read_test(test_number).empty()){
        vector<string> test = read_test(test_number);
        string str = test[0];
        string substr = test[1];
        int answer = stoi(test[2]);

        run_test(str, substr, answer, test_number);

        test_number++;
    }
}
