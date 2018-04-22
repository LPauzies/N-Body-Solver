#ifndef BODY_HPP
#define BODY_HPP

#include <math.h>
#include <iostream>

using namespace std;

class Body{
    private:
        double masse;
        double x;
        double y;
        double z;
        double v_x;
        double v_y;
        double v_z;
        double f_x;
        double f_y;
        double f_z;
        const float deltat = 0.01;
        // const double G = 6.673 * pow(10,-11);
        const double G = 1;
    public:
        /* Constructor */
        Body();
        Body(
            double masse,
            double x, double y, double z,
            double v_x, double v_y, double v_z);
        /* Destructor */
        ~Body();
        /* Getter and Setter */
        double getMasse() const;
        void setMasse(double masse);
        double getX() const;
        void setX(double x);
        double getY() const;
        void setY(double y);
        double getZ() const;
        void setZ(double z);
        double getV_X() const;
        void setV_X(double v_x);
        double getV_Y() const;
        void setV_Y(double v_y);
        double getV_Z() const;
        void setV_Z(double v_z);
        double getForce() const;
        void setForce(double force);
        double getF_X() const;
        void setF_X(double f_x);
        double getF_Y() const;
        void setF_Y(double f_y);
        double getF_Z() const;
        void setF_Z(double f_z);
        void updateForce(Body particules);
        /* Update Fonction */

        void updateSpeed();
        void updatePosition();
        double calcForce2Body(Body particles);
        /* ostream and istream */
        friend ostream & operator<<(ostream & out, const Body & b);
        friend istream & operator>>(istream & in, Body & b);
        /* Copy operator */
        Body & operator=(const Body & b);
        /* Equal/Not equal operator */
        bool operator!=(const Body & b);
        bool operator==(const Body & b);
};

#endif
