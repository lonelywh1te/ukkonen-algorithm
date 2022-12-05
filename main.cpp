#include <iostream>
#include <fstream>
#include <sstream>
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
                if (active_length == suffix_length(finded_node)){
                    active_node = finded_node;
                    active_length = 0;
                    active_edge = -1;
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
//            for(int k = 0; k < lvl; k++){
//                cout << "-----";
//            }
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
};

int main(){

}