//
// Created by Wang on 2/10/2022.
//

#ifndef PROJECT2_CALCULATION_H
#define PROJECT2_CALCULATION_H


using namespace std;
const int kVariableNum = 51;
const int kFunctionNum = 1;
const string kFunctions[kFunctionNum] = {
        string("sqrt")
};

string Calculate(string, string[], string [], int n);

bool IsValidVariableName(string);

#endif //PROJECT2_CALCULATION_H
