#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <chrono>
#include "windows.h"
#include <map>
using namespace std;

struct suffix_tree {
    struct node {
        int left, *right, suff_index;
        node *suff_link;
        map<char, node*> childs;

        node(int left, int *right, node *suffix_link, int suff_index) {
            this->left = left;
            this->right = right;
            this->suff_link = suffix_link;
            this->suff_index = suff_index;
        }
    };

    string str;

    node *active_node = nullptr;
    int active_edge = -1;
    int active_length = 0;
    int remainder = 0;
    int suff_end = -1;

    node *root = new node(-1, nullptr, nullptr, -1);
    node *last_created = nullptr;

    int suffix_length(node *node){
        return *node->right - node->left + 1;
    }

    void build(string data) {
        str = data + "$";
        active_node = root;

        for(int i = 0; i < str.length(); i++){
            update_tree(i);
        }
    }

    void del(node *node){
        for(auto i : node->childs){
            del(i.second);
        }
        if (node->suff_index == -1) delete node->right;
        delete node;
    }

    void update_tree(int index){
        last_created = nullptr;
        remainder++;
        suff_end++;

        while (remainder != 0){
            // задаем активное ребро
            if (active_length == 0) {
                active_edge = index;
            }
            // ищем ребенка(суффикс) который начинается на заданный символ
            auto finded_child = active_node->childs.find(str[active_edge]);
            node *finded_node = finded_child->second;

            // если нет такого суффикса который начинается на данный символ
            if (finded_child == active_node->childs.end()){
                node *added_letter = new node(index, &suff_end, root, index - remainder + 1);
                active_node->childs.insert(make_pair(str[index], added_letter));
                if (last_created != nullptr) {
                    last_created->suff_link = active_node;
                    last_created = nullptr;
                }
            }
            else {
                // если можем спуститься к ноде - спускаемся
                if (active_length >= suffix_length(finded_node)){
                    active_node = finded_node;
                    active_length -= suffix_length(finded_node);
                    active_edge += suffix_length(finded_node);
                    continue;
                }
                //если можем спуститься по ребру - спускаемся
                if (str[index] == str[finded_child->second->left + active_length]){
                    if (last_created != nullptr && active_node != root) last_created->suff_link = active_node;
                   active_length++;
                   break;
                }
                // деление ребра
                node *new_node = new node(finded_node->left, new int(finded_node->left + active_length - 1), root, -1);
                // создаем суффиксную ссылку
                if (last_created != nullptr) last_created->suff_link = new_node;
                active_node->childs[str[active_edge]] = new_node;
                finded_node->left += active_length;
                new_node->childs.insert(make_pair(str[index], new node(index, &suff_end, root, index - remainder + 1)));
                new_node->childs.insert(make_pair(str[finded_node->left], finded_node));
                last_created = new_node;
            }
            remainder--;

            if (active_length > 0 && active_node == root){
                active_length--;
                active_edge++;
            }
            else if (active_node != root){
                active_node = active_node->suff_link;
            }
        }
    }

    void print(node *start, int lvl) {
        // перебор нод
        for(auto i : start->childs){
            for(int k = 0; k < lvl; k++){
                cout << "-----";
            }
            // вывод суффикса
            for(int j = i.second->left; j <= *(i.second->right); j++){
                cout << str[j];
            }
            cout << endl;
            // спуск по детям
            if(!(start->childs.empty())){
                print(i.second, lvl+1);
            }
        }
    }

    bool find(string text){
        node *current_node = root;
        string finded_str = "";
        int depth_edge = 0;
        int total_depth = 0;

        // ищем ребро
        auto finded_edge = current_node->childs.find(text[0]);
        node *finded_node = finded_edge->second;

        while (text != finded_str){
            //если не находим
            if (finded_edge == current_node->childs.end()){
                return false;
            }
            //если нашли - спускаемся
            while (depth_edge <= suffix_length(finded_node)){
                if (finded_str == text) {
                    return true;
                }
                if (depth_edge != suffix_length(finded_node)) {
                    finded_str += str[finded_node->left + depth_edge];
                    depth_edge++;
                    continue;
                }
                break;
            }
            // спустились к концу ребра, смена вершины
            current_node = finded_node;
            total_depth += depth_edge;
            depth_edge = 0;
            finded_edge = current_node->childs.find(text[total_depth]);
            finded_node = finded_edge->second;
        }
    }
};

void generate_tests(int number_of_tests, unsigned long long int max_length){
    srand(time(nullptr));
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 1; i <= number_of_tests; i++){
        suffix_tree tree;
        string test_string = "";
        string test_substr;
        int start, length;

        for (int k = 0; k < rand() % max_length + 1; k++){
            test_string += alphabet[rand() % 26];
        }

        start = rand() % test_string.length();
        length = ((rand() % test_string.length()) + 1) - start;

        test_substr = test_string.substr(start, length);
        tree.build(test_string);
        if (tree.find(test_substr)) {
            cout << "[ TEST #" << i << " ]: OK" << endl;
            cout << "TESTING_STRING: " << test_string << endl;
            cout << "TESTING_SUBSTR: " << test_substr << endl;
        }
        else {
            cout << "[ TEST #" << i << " ]: FAIL" << endl;
            cout << "TESTING_STRING: " << test_string << endl;
            cout << "TESTING_SUBSTR: " << test_substr << endl;
            return;
        }
        tree.del(tree.root);
    }
}

void analyze_time(int count_runs){
    srand(time(nullptr));
    for(int i = 0; i < count_runs; i++){
        suffix_tree a;
        string test_string = "";
        string alphabet = "abcdefghijklmnopqrstuvwxyz";
        for (int k = 0; k < i; k++){
            test_string += alphabet[rand() % 26];
        }

        auto start = chrono::steady_clock::now();
        a.build(test_string);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << i << "            " << time << endl;
        a.del(a.root);
    }
}

int main(){
    generate_tests(10, 1000);
}