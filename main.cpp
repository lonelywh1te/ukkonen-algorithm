#include "suffix_tree.h"
using namespace std;

int main(){
    suffix_tree a;

    // построение дерева
    a.build("yourstring");

    // вывод дерева в консоль
    a.print(a.root, 0);

    // функция поиска подстроки
    a.find("string"); // true or false

}