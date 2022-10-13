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
    string str, result;
    string names[kVariableNum];
    string values[kVariableNum];
    int cnt = 0;
    cout << "hello" << endl;
    getline(cin, str);
    while (str != "bye") {
        if (str.empty()) {
            getline(cin, str);
            continue;
        }
        int m = str.find('=');
        if (m != string::npos) {
            if (cnt >= kVariableNum - 1) {
                cout << "capacity is full" << endl;
                continue;
            } else {
                bool change = false;
                string name;
                string value;
                name = str.substr(0, m);
                if (!IsValidVariableName(name)) {
                    cout << "name """ << name << """ is invalid" << endl;
                    getline(cin, str);
                    continue;
                }
                value = Calculate(str.substr(m + 1), {}, {}, 0);
                if (value[0] == 'E' || value.empty()) {
                    cout << "invalid expression" << endl;
                } else {
                    for (int i = 0; i < kFunctions->length(); ++i) {
                        if (name == kFunctions[i]) {
                            cout << "name """ << name << """ is occupied" << endl;
                            change = true;
                            break;
                        }
                    }
                    if (change) {
                        break;
                    }
                    for (int i = 0; i < cnt; ++i) {
                        if (name == names[i]) {
                            values[i] = value;
                            cout << "variable """ << names[i] << """ changed to " << value << " successfully (" << cnt
                                 << "/"
                                 << kVariableNum - 1
                                 << ")"
                                 << endl;
                            change = true;
                            break;
                        }
                    }
                    if (!change) {
                        names[cnt] = name;
                        values[cnt] = value;
                        cout << "variable """ << names[cnt] << """ defined as " << value << " successfully (" << ++cnt
                             << "/"
                             << kVariableNum - 1
                             << ")"
                             << endl;
                    }
                }
            }
        } else {
            result = Calculate(str, names, values, cnt);
            if (result[0] == 'E') {
                cout << "invalid expression" << endl;
            } else {
                cout << "result is " << result << endl;
            }
        }
        getline(cin, str);
    }
    cout << "bye" << endl;
    return 0;
}