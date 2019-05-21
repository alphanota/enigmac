//
// Created by angel on 5/19/19.
//

#include "Result.h"

Result::Result(const std::string &setting, double result, int bin) : setting(setting), result(result), bin(bin) {}

bool Result::operator<(const Result &rhs) const {
    return result > rhs.result;
}