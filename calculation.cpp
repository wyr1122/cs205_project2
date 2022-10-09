//
// Created by Wang on 2/10/2022.
//
#include <string>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

bool IsValid(string &s) {
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] > '9' && s[i] != 'e' || s[i] < '0' && s[i] != '.' && s[i] != '-') {
            return false;
        }
    }
    return true;
}

void Substitute(string &s, char name[][10], char value[][100], int n) {
    for (int i = 0; i < n; ++i) {
        string name_str = string(name[i]);
        while (s.find(name_str) != string::npos) {
            int m = s.find(name_str);
            s.replace(m, name_str.length(), value[i]);
        }
    }
}

string Calculate(string s) {
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    int left;
    int cnt = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (cnt == 0) {
            if (s[i] == '(') {
                cnt = 1;
                left = i;
            }
        } else if (cnt == 1) {
            if (s[i] == '(') {
                cnt++;
            }
            if (s[i] == ')') {
                cnt = 0;
                s.replace(left, i - left + 1, Calculate(s.substr(left + 1, i - left - 1)));
            }
        } else {
            if (s[i] == ')') {
                cnt--;
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '+') {
            string s1 = Calculate(s.substr(0, i));
            string s2 = Calculate(s.substr(i + 1));
            if (s1.empty() || s2.empty()) {
                return "";
            } else {
                return Pls(s1, s2);
            }
        }
    }
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == '-') {
            string s1 = Calculate(s.substr(0, i));
            string s2 = Calculate(s.substr(i + 1));
            if (s1.empty() || s2.empty()) {
                return "";
            } else {
                return Mns(s1, s2);
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            string s1 = Calculate(s.substr(0, i));
            string s2 = Calculate(s.substr(i + 1));
            if (s1.empty() || s2.empty()) {
                return "";
            } else {
                return Mul(s1, s2);
            }
        }
    }
    if (IsValid(s)) {
        return s;
    } else {
        return "";
    }
}