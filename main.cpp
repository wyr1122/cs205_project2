//
// Created by Wang on 2/10/2022.
//

#include <string>
#include <iostream>
#include <cstring>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

int main() {
    char str[101] = {0};
    string s;
    char name[20][10] = {0};
    char value[20][100] = {0};
    int cnt = 0;
    for (int i = 0; i < 20; ++i) {
        cin.getline(str, 100);
        s = string(str);
        int m = s.find('=');
        if (m != string::npos) {
            strncpy(name[i], str, m);
            strncpy(value[i], &str[m + 1], 99 - m);
        } else {
            cnt = i;
            break;
        }
    }
    substitute(s, name, value, cnt);
    cout << cal(s);
}