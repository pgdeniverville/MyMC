#ifndef GUARD_Kinematics_h
#define GUARD_Kinematics_h

// class Kinematics
double pAbs (double,double,double,double);
double pt (double,double,double,double);
double calculatetheta (double,double,double,double);
double phi (double,double,double,double);
double invariantmass (double,double,double,double);
double lambda (double,double,double);
double TriangleFunc(double m1, double m2, double m3);
double TriangleFunc2(double m1, double m2, double m3);
//Turns a beta=speed/c into gamma
double beta_gamma(double beta);
//Calculates the angle between vectors 1 and 2.
double Angle_Spread(double x1, double y1, double z1, double x2, double y2, double z2);

namespace elastic_scattering{
    double Theta_from_E2f(double E2f, double E1i, double m1, double m2);
    double E2f_from_Theta(double theta2, double E1i, double m1, double m2);
    double E2fMax(double E1i, double m1, double m2);
    double E2fMin(double E1i, double m1, double m2);
}

#endif
