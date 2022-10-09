//
// Created by Wang on 2/10/2022.
//

#ifndef PROJECT2_CALCULATION_H
#define PROJECT2_CALCULATION_H

#endif //PROJECT2_CALCULATION_H

using namespace std;
const int kVariableNum = 50;
const int kVariableNameLimit = 10;
const int kLineLimit = 100;

string Calculate(string s);

void Substitute(string &s, char (*name)[kVariableNameLimit], char (*value)[kLineLimit], int n);
