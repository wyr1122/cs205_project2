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
    char names[kVariableNum][kVariableNameLimit] = {0};
    char values[kVariableNum][kLineLimit] = {0};
    int cnt = 0;
    cin.getline(str, kLineLimit);
    while (strcmp(str, "end") != 0) {
        s = string(str);
        int m = s.find('=');
        if (m != string::npos) {
            if (cnt >= kVariableNum - 1) {
                cout << "capacity is full" << endl;
                continue;
            } else {
                if (m < kVariableNameLimit) {
                    bool change = false;
                    char name[kVariableNameLimit] = {0};
                    strncpy(name, str, m);
                    for (int i = 0; i < cnt; ++i) {
                        if (strcmp(names[i], name) == 0) {
                            strcpy(values[i], &str[m + 1]);
                            cout << "variable " << names[i] << " changed successfully (" << cnt << "/"
                                 << kVariableNum - 1
                                 << ")"
                                 << endl;
                            change = true;
                            break;
                        }
                    }
                    if (!change) {
                        strcpy(names[cnt], name);
                        strcpy(values[cnt], &str[m + 1]);
                        cout << "variable " << names[cnt] << " defined successfully (" << ++cnt << "/"
                             << kVariableNum - 1
                             << ")"
                             << endl;
                    }
                } else {
                    cout << "variable name too long" << endl;
                }
            }
        } else {
            result = Calculate(s, names, values, cnt);
            if (result[0] == 'E') {
                cout << "input is invalid!" << endl;
            } else {
                cout << "result is " << result << endl;
            }
        }
        cin.getline(str, kLineLimit);
    }
    cout << "end of program" << endl;
    return 0;
}