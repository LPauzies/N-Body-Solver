#include "NBody.hpp"
#include <omp.h>

NBody::NBody(vector<Body> bodyVector_, bool socketBool_, string adresse, int port){
    bodyVector = bodyVector_;
    socketBool = socketBool_;
    if (socketBool){
        m_sockets = new Sockets(adresse, port);
        m_sockets->sendNbParticules(bodyVector.size());
    }
}

NBody::~NBody(){
    bodyVector.erase(bodyVector.begin() + bodyVector.size());
    if (socketBool)
        m_sockets->close();
}

vector<Body> NBody::getBodyVector() const{
    return bodyVector;
}

void setBodyVector(vector<Body> bodyVector){
    bodyVector = bodyVector;
}

void NBody::updateNBody(){
    vector<Body> bodyVectorCopy = bodyVector;
    double forceT;
    int n = bodyVector.size();
    omp_set_num_threads(4);
    # pragma omp parallel
    {
        # pragma omp for collapse(1)
        for (int i = 0; i < n; i++) {
            bodyVector[i].setF_X(0.0);
            bodyVector[i].setF_Y(0.0);
            bodyVector[i].setF_Z(0.0);
            for (int j = 0; j < n; j++) {
                if (bodyVector[i] != bodyVector[j]) {
                    bodyVector[i].updateForce(bodyVectorCopy[j]);
                }
            }
            bodyVector[i].updateSpeed();
            bodyVector[i].updatePosition();
            if (socketBool)
                # pragma omp critical
                m_sockets->sendStructPosition(bodyVector[i].getX(), bodyVector[i].getY(), bodyVector[i].getZ());
        }
    }
}

void NBody::show() {
    cout << "========== NBody show ==========\n" << endl;
    for (vector<Body>::iterator it = bodyVector.begin(); it != bodyVector.end(); it++) {
        cout << *it << endl;
    }
    cout << "=================================\n" << endl;
}

string NBody::toJSON() {
    string data;
    unsigned int cpt = 0;
    /* Format string */
    data += "{\n\t\"Bodies\": [";
    for (vector<Body>::iterator it = bodyVector.begin(); it != bodyVector.end(); it++) {
        string body;
        body += "\n\t\t{ \"mass\":";
        body += to_string(it->getMasse());
        body += ", \"x\":";
        body += to_string(it->getX());
        body += ", \"y\":";
        body += to_string(it->getY());
        body += ", \"z\":";
        body += to_string(it->getZ());
        body += ", \"v_x\":";
        body += to_string(it->getV_X());
        body += ", \"v_y\":";
        body += to_string(it->getV_Y());
        body += ", \"v_z\":";
        body += to_string(it->getV_Z());
        body += " }";
        if (cpt != bodyVector.size()-1) {
            body += ",";
        }
        cpt++;
        data += body;
    }
    data += "\n\t]\n}";
    /* End format string */
    return data;
}

void NBody::exportJSON(const string &filename) {
    string data;
    data = toJSON();
    ofstream ofs(filename,ios::out | ios::trunc);
    if (ofs) {
        ofs << data;
    }
    ofs.close();
}

string NBody::toCSV() {
    string data;
    int n = bodyVector.size();
    for (vector<Body>::iterator it = bodyVector.begin(); it != bodyVector.end(); it++) {
        string body;
        body += to_string(it->getMasse());
        body += " ";
        body += to_string(it->getX());
        body += " ";
        body += to_string(it->getY());
        body += " ";
        body += to_string(it->getZ());
        body += " ";
        body += to_string(it->getV_X());
        body += " ";
        body += to_string(it->getV_Y());
        body += " ";
        body += to_string(it->getV_Z());
        body += "\n";
        data += body;
    }
    return data;
}

void NBody::exportCSV(const string &filename) {
    string data;
    data = toCSV();
    ofstream ofs(filename,ios::out | ios::trunc);
    if (ofs) {
        ofs << data;
    }
    ofs.close();
}

string NBody::toGNUPLOT2D() {
    string data;
    for (vector<Body>::iterator it = bodyVector.begin(); it != bodyVector.end(); it++) {
        string body;
        body += to_string(it->getX());
        body += " ";
        body += to_string(it->getY());
        body += "\n";
        data += body;
    }
    return data;
}

void NBody::exportGNUPLOT2D(const string &filename) {
    string data;
    data = toGNUPLOT2D();
    ofstream ofs;
    ofs.open(filename,ios::out | ios::app);
    if (ofs) {
        ofs << data;
    }
    ofs.close();
}

string NBody::toGNUPLOT3D() {
    string data;
    for (vector<Body>::iterator it = bodyVector.begin(); it != bodyVector.end(); it++) {
        string body;
        body += to_string(it->getX());
        body += " ";
        body += to_string(it->getY());
        body += " ";
        body += to_string(it->getZ());
        body += "\n";
        data += body;
    }
    return data;
}

void NBody::exportGNUPLOT3D(const string &filename) {
    string data;
    data = toGNUPLOT3D();
    ofstream ofs;
    ofs.open(filename,ios::out | ios::app);
    if (ofs) {
        ofs << data;
    }
    ofs.close();
}
