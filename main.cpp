#include "suffix_tree.h"
using namespace std;

int main(){
    suffix_tree a;

    a.build("abxabx"); // построение дерева
    a.find("a"); // поиск подстроки. возвращает последнее вхождение
    a.print(a.root, 0); // вывод дерева
    analyze_time(1, 1234567890); // анализ времени работы алгоритма
}