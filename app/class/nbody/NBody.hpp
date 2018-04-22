#ifndef NBODY_HPP
#define NBODY_HPP

#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include "../sockets/Sockets.cpp"
#include "../body/Body.hpp"

using namespace std;

class NBody{
    private:
        vector<Body> bodyVector;
        bool socketBool;
        Sockets * m_sockets;
    public:
        NBody(vector<Body> bodyVector_, bool socketBool_, string adresse, int port);
        ~NBody();
        vector<Body> getBodyVector() const;
        void setBodyVector(vector<Body> bodyVector);
        void updateNBody();
        void show();
        string toJSON();
        void exportJSON(const string &filename);
        string toCSV();
        void exportCSV(const string &filename);
        string toGNUPLOT2D();
        void exportGNUPLOT2D(const string &filename);
        string toGNUPLOT3D();
        void exportGNUPLOT3D(const string &filename);
};

#endif
