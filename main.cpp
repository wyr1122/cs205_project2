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
    const int kVariableNum = 50;
    char str[101] = {0};
    string s, result;
    char name[kVariableNum][10] = {0};
    char value[kVariableNum][100] = {0};
    int cnt = 0;
    while (cnt < kVariableNum) {
        cin.getline(str, 100);
        s = string(str);
        int m = s.find('=');
        if (m != string::npos) {
            strncpy(name[cnt], str, m);
            strncpy(value[cnt], &str[m + 1], 99 - m);
            cnt++;
        } else {
            Substitute(s, name, value, cnt);
            result = Calculate(s);
            if (result.empty()) {
                cout << "input is invalid!" << endl;
            } else {
                cout << result << endl;
                break;
            }
        }
    }
}