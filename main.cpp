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
    cout << "hello" << endl;
    cin.getline(str, kLineLimit);
    while (strcmp(str, "bye") != 0) {
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
                    string value;
                    strncpy(name, str, m);
                    value = Calculate(string(&str[m + 1]), {}, {}, 0);
                    if (value[0] == 'E' || value.empty()) {
                        cout << "invalid expression" << endl;
                    } else {
                        for (int i = 0; i < cnt; ++i) {
                            if (strcmp(names[i], name) == 0) {
                                strcpy(values[i], value.c_str());
                                cout << "variable " << names[i] << " changed to " << value << " successfully (" << cnt
                                     << "/"
                                     << kVariableNum - 1
                                     << ")"
                                     << endl;
                                change = true;
                                break;
                            }
                        }
                        if (!change) {
                            strcpy(names[cnt], name);
                            strcpy(values[cnt], value.c_str());
                            cout << "variable " << names[cnt] << " defined as " << value << " successfully (" << ++cnt
                                 << "/"
                                 << kVariableNum - 1
                                 << ")"
                                 << endl;
                        }
                    }
                } else {
                    cout << "variable name too long (" << m << "/" << kVariableNameLimit - 1 << ")" << endl;
                }
            }
        } else {
            result = Calculate(s, names, values, cnt);
            if (result[0] == 'E') {
                cout << "invalid expression" << endl;
            } else {
                cout << "result is " << result << endl;
            }
        }
        cin.getline(str, kLineLimit);
    }
    cout << "bye" << endl;
    return 0;
}