#ifndef MAIN_CPP_SUFFIX_TREE_H
#define MAIN_CPP_SUFFIX_TREE_H
#include <iostream>
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

    int suffix_length(node *node);
    void build(string data);
    void del(node *node);
    void update_tree(int index);
    void print(node *start, int lvl);
    bool find(string text);
};
#endif
