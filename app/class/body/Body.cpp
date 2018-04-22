#include "Body.hpp"

/*
 * Body class
 * @Author : Laurine Sorel
 */

/* Constructor */
Body::Body():
    masse(0),
    x(0),
    y(0),
    z(0),
    v_x(0),
    v_y(0),
    v_z(0),
    f_x(0),
    f_y(0),
    f_z(0){}

Body::Body(double masse, double x, double y, double z, double v_x, double v_y, double v_z):
    masse(masse),
    x(x),
    y(y),
    z(z),
    v_x(v_x),
    v_y(v_y),
    v_z(v_z),
    f_x(0),
    f_y(0),
    f_z(0){}

/* Destructor */
Body::~Body(){}

/* Getter and Setter */
double Body::getMasse() const{
    return masse;
}

void Body::setMasse(double masse_){
    masse = masse_;
}

double Body::getX() const{
    return x;
}

void Body::setX(double x_){
    x = x_;
}

double Body::getY() const{
    return y;
}

void Body::setY(double y_){
    y = y_;
}

double Body::getZ() const{
    return z;
}

void Body::setZ(double z_){
    z = z_;
}

double Body::getV_X() const{
    return v_x;
}

void Body::setV_X(double v_x_){
    v_x = v_x_;
}

double Body::getV_Y() const{
    return v_y;
}

void Body::setV_Y(double v_y_){
    v_y = v_y_;
}

double Body::getV_Z() const{
    return v_z;
}

void Body::setV_Z(double v_z_){
    v_z = v_z_;
}

double Body::getF_X() const{
    return f_x;
}

void Body::setF_X(double f_x_){
    f_x = f_x_;
}

double Body::getF_Y() const{
    return f_y;
}

void Body::setF_Y(double f_y_){
    f_y = f_y_;
}

double Body::getF_Z() const{
    return f_z;
}

void Body::setF_Z(double f_z_){
    f_z = f_z_;
}

/* Useful Fonction */

void Body::updateForce(Body particules){
    double r = sqrt(
        pow(particules.getX() - x, 2) +
        pow(particules.getY() - y, 2) +
        pow(particules.getZ() - z, 2));
    double normeF = (G * masse * particules.getMasse()) / pow(r, 2);
    f_x = f_x + (normeF * ((particules.getX() - x) / r));
    f_y = f_y + (normeF * ((particules.getY() - y) / r));
    f_z = f_z + (normeF * ((particules.getZ() - z) / r));
}

/* Change the speed vector thanks to the force */
void Body::updateSpeed(){
    v_x = v_x + ((f_x * deltat) / masse);
    v_y = v_y + ((f_y * deltat) / masse);
    v_z = v_z + ((f_z * deltat) / masse);
}

/* v_x is the new speed vector !
 * To use this method first of all launch the
 * updateSpeed method before
 */
void Body::updatePosition(){
    x = x + (v_x * deltat);
    y = y + (v_y * deltat);
    z = z + (v_z * deltat);
}

double Body::calcForce2Body(Body particles){
    double r = sqrt(
            pow(particles.getX() - x, 2) +
            pow(particles.getY() - y, 2) +
            pow(particles.getZ() - z, 2));
    return r;
}

ostream & operator<<(ostream & out, const Body & b){
    out << " Masse : " << b.masse << "\n";
    out << " Position (x, y, z) : (" << b.x << ", " << b.y << ", " << b.z << ")" << "\n";
    out << " Vitesse (v_x, v_y, v_z) : (" << b.v_x << ", " << b.v_y << ", " << b.v_z << ")" << "\n";
    out << " Force (f_x, f_y, f_z) : (" << b.f_x << ", " << b.f_y << ", " << b.f_z << ")" << "\n";
    return out;
}

istream & operator>>(istream & in, Body & b){
    if(!(in >> b.masse >> b.x >> b.y >> b.z >> b.v_x >> b.v_y >> b.v_z)){
        in.setstate(ios::failbit);
    }
    return in;
}

/* Operator Copy */
Body & Body::operator=(const Body & b){
    if (this != &b){
        masse = b.masse;
        x = b.x;
        y = b.y;
        z = b.z;
        v_x = b.v_x;
        v_y = b.v_y;
        v_z = b.v_z;
        // force = b.force;
        f_x = b.f_x;
        f_y = b.f_y;
        f_z = b.f_z;
    }
    return *this;
}
/* Operator Equal */
bool Body::operator==(const Body & b){
    return masse == b.getMasse() && x == b.getX() && y == b.getY()
        && z == b.getZ() && v_x == b.getV_X() && v_y == b.getV_Y()
        && v_z == b.getV_Z() && f_x == b.f_x && f_y == b.f_y && f_z == b.f_z;
        // force == b.getForce();
}

/* Operator Not Equal */
bool Body::operator!=(const Body & b){
    return masse != b.getMasse() || x != b.getX() || y != b.getY()
        || z != b.getZ()|| v_x != b.getV_X() || v_y != b.getV_Y()
        || v_z != b.getV_Z(); //|| f_x != b.f_x || f_y != b.f_y || f_z != b.f_z;
        // force != b.getForce();
}
