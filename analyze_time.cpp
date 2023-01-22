#include "analyze_time.h"

void analyze_time(int count_of_runs, unsigned int rand_seed){
    random_device generate;
    unsigned int seed;

    if (rand_seed == 0){
        seed = generate();
    }
    else {
        seed = rand_seed;
    }

    mt19937 random(seed);
    uniform_int_distribution<> number(0,25);

    cout << "generation_seed: " << seed << endl;
    for(int i = 0; i < count_of_runs; i++){
        suffix_tree a;
        string test_string;
        string alphabet = "abcdefghijklmnopqrstuvwxyz";

        for (int k = 0; k < i; k++){
            test_string += alphabet[number(random)];
        }

        auto start = chrono::steady_clock::now();
        a.build(test_string);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << i << "  " << time << endl;
    }

}