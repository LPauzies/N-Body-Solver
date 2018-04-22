#ifndef READER_HPP
#define READER_HPP

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../body/Body.hpp"
#include "../nbody/NBody.hpp"
#include "../error/error.hpp"

using namespace std;

class Reader {
  private :
    string filepath;
  public :
    Reader(const string &filepath);
    ~Reader();
    const string getFilePath() const;
    vector<Body> readCSV() const;
    vector<Body> readJSON() const;
    vector<Body> readBodies() const;
};

#endif
