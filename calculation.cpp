//
// Created by Wang on 2/10/2022.
//
#include <string>
#include "arithmetic.h"
#include "calculation.h"

using namespace std;

void substitute(string &s, char name[][10], char value[][100], int n) {
    for (int i = 0; i < n; ++i) {
        string nameStr = string(name[i]);
        while (s.find(nameStr) != string::npos) {
            int m = s.find(nameStr);
            s.replace(m, nameStr.length(), value[i]);
        }
    }
}

string cal(string s) {
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
                s.replace(left, i - left + 1, cal(s.substr(left + 1, i - left - 1)));
            }
        } else {
            if (s[i] == ')') {
                cnt--;
            }
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '+') {
            string result = pls(cal(s.substr(0, i)), cal(s.substr(i + 1)));
            return result;
        }
    }
    for (int i = 1; i < s.length(); ++i) {
        if (s[i] == '-') {
            string result = mns(cal(s.substr(0, i)), cal(s.substr(i + 1)));
            return result;
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == '*') {
            string result = mul(cal(s.substr(0, i)), cal(s.substr(i + 1)));
            return result;
        }
    }
    return s;
}