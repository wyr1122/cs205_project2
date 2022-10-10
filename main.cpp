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
    char str[kLineLimit];
    string s, result;
    char name[kVariableNum][kVariableNameLimit] = {0};
    char value[kVariableNum][kLineLimit] = {0};
    int cnt = 0;
    while (cnt < kVariableNum) {
        cin.getline(str, kLineLimit);
        s = string(str);
        int m = s.find('=');
        if (m != string::npos) {
            strncpy(name[cnt], str, m);
            strcpy(value[cnt], &str[m + 1]);
            cnt++;
        } else {
            result = Calculate(s, name, value, cnt);
            if (result[0] == 'E') {
                cout << "input is invalid!" << endl;
            } else {
                cout << result << endl;
                break;
            }
        }
    }
}