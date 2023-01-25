#include "analyze_time.h"

void analyze_time(string function, int count_of_runs, unsigned int rand_seed){
    random_device generate;
    unsigned int seed;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    if (rand_seed == 0){
        seed = generate();
    }
    else {
        seed = rand_seed;
    }

    mt19937 random(seed);
    uniform_int_distribution<> letter(0, 25);

    cout << "generation_seed: " << seed << endl;

    if (function == "build"){
        for(int i = 0; i < count_of_runs; i++){
            suffix_tree a;
            string test_string;

            for (int k = 0; k < i; k++){
                test_string += alphabet[letter(random)];
            }

            auto start = chrono::steady_clock::now();
            a.build(test_string);
            auto end = chrono::steady_clock::now();
            auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << i << "  " << time << endl;
        }
    }
    else if (function == "find"){
        for(int i = 0; i < count_of_runs; i++){
            suffix_tree a;
            string test_string;
            string rand_substring;
            uniform_int_distribution<> substr_pos(0,i);

            int rand = substr_pos(random);
            for (int k = 0; k < i; k++){
                test_string += alphabet[letter(random)];
            }
            a.build(test_string);
            rand_substring = test_string.substr(min(rand, i - rand), max(rand, i - rand*2));
            auto start_ukk = chrono::steady_clock::now();
            a.find(rand_substring);
            auto end_ukk = chrono::steady_clock::now();
            auto time_ukk = chrono::duration_cast<chrono::nanoseconds>(end_ukk - start_ukk).count();
            cout << i << " " << time_ukk << endl;
        }
    }
    else return;
}
