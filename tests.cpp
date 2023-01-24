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

void generate_tests(int count_of_tests){
    ofstream result("../tests/result", ios_base::app);
    result << endl << "GENERATED TESTS" << endl;

    random_device generate;
    unsigned long long seed = generate();
    result << "seed: " << seed << endl << endl;
    mt19937 random(seed);
    uniform_int_distribution<> letter(0,25);
    uniform_int_distribution<> string_length(1,100000);

    for(int i = 1; i <= count_of_tests; i++){
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        suffix_tree a;
        string test_string;
        int str_length = string_length(random);
        string rand_substring;
        uniform_int_distribution<> substr_index(0,str_length);
        int rand_index = substr_index(random);

        for (int k = 0; k < str_length; k++){
            test_string += alphabet[letter(random)];
        }
        a.build(test_string);

        rand_substring = test_string.substr(min(rand_index, str_length - rand_index), max(rand_index, str_length - rand_index * 2));

        int output = a.find(rand_substring);
        if (output != -1){
            test_ok(i);
        }
        else {
            result << "test #" + to_string(i) << ": failed" << endl;
            result << "  str: " + test_string << endl;
            result << "  substr: " + rand_substring << endl;
            result << "  output: " + to_string(output) << endl;
            exit(-1);
        }
    }
}

void test_tree(){
    ofstream result("../tests/result");
    int test_number = 1;
    // проверка ручных тестов
    while(!read_test(test_number).empty()){
        vector<string> test = read_test(test_number);
        string str = test[0];
        string substr = test[1];
        int answer = stoi(test[2]);

        run_test(str, substr, answer, test_number);

        test_number++;
    }
    // проверка автоматических тестов
    generate_tests(100);
}
