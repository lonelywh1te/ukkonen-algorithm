#ifndef MAIN_CPP_SUFFIX_TREE_H
#define MAIN_CPP_SUFFIX_TREE_H
#include <iostream>
#include <map>
#include "tests.h"
#include "analyze_time.h"

using namespace std;

struct suffix_tree {
private:
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

    node *last_created = nullptr;
    void del(node *node);
    void update_tree(int index);
    int suffix_length(node *node);

public:
    node *root = new node(-1, nullptr, nullptr, -1);
    void build(string data);
    void print(node *start, int lvl);
    int find(string text);
};
#endif
