#ifndef ERROR_HPP
#define ERROR_HPP

#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <ctime>

using namespace std;

class Error {
  public:
    static void error(const string &filename, const string &error);
};

#endif
