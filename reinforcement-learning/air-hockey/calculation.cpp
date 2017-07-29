#include "calculation.h"
#include <math.h>
#include <string>


using namespace std;

// K = (1/2)mv^2
double Pysics::pysicalEnergy( string target, double m, double v ) {
    return ( 0.5 ) * m * ( pow( v, 2.0 ) );
}

double Pysics::pysicalEnergy( double k, string target, double v ) {
    return ( 2.0 * k ) / ( pow( v, 2.0 ) );
}

double Pysics::pysicalEnergy( double k, double m, string target ) {
    return sqrt( ( 2.0 * k ) / m );
}

// F = μN (動摩擦力)
double Pysics::dynamicFriction( string target, double mu, double n ) {
    return mu * n;
}

double Pysics::dynamicFriction( double f, string target, double n ) {
    return f / n;
}

double Pysics::dynamicFriction( double f, double mu, string target ) {
    return f / mu;
}


// v = v_0 + at
double Pysics::acceleratedMotionExceptY( string target, double initialV, double a, double t ) {
    return initialV + ( a * t );
}

double Pysics::acceleratedMotionExceptY( double v, string target, double a, double t ) {
    return v - ( a * t );
}

double Pysics::acceleratedMotionExceptY( double v, double initialV, string target, double t ) {
    return ( v - initialV ) / t;
}

double Pysics::acceleratedMotionExceptY( double v, double initialV, double a, string target ) {
    return ( v - initialV ) / a;
}


// y  = v_0t + (1/2)at^2
double Pysics::acceleratedMotionExceptV( string target, double initialV, double a, double t ) {
    return initialV + ( ( 0.5 ) * a * pow( t, 2.0 ) );
}

double Pysics::acceleratedMotionExceptV( double y, string target, double a, double t ) {
    return  ( (2 * y) - ( a * pow( t, 2.0) ) ) / ( 2.0 * t );
}

double Pysics::acceleratedMotionExceptV( double y, double initialV, string target, double t ) {
    return ( 2 * ( y - ( initialV * t ) ) ) / ( pow( t, 2.0 ) );
}

void Pysics::acceleratedMotionExceptV( double sol[2], double y, double initialV, double a, string target ) {
    sol[0] = ( - initialV + sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
    sol[1] = ( - initialV - sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
}


// v^2 = v_0^2 + 2ay
double Pysics::acceleratedMotionExceptT( string target, double initialV, double a, double y ) {
    return sqrt( pow( initialV, 2.0 ) + ( 2 * a * y ) );
}

double Pysics::acceleratedMotionExceptT( double v, string target, double a, double y ) {
    return sqrt ( pow( v, 2.0 ) - ( 2 * a * y ) );
}

double Pysics::acceleratedMotionExceptT( double v, double initialV, string target, double y ) {
    return ( ( v + initialV ) * ( v - initialV ) ) / ( 2 * y );
}

double Pysics::acceleratedMotionExceptT( double v, double initialV, double a, string target ) {
    return ( ( v + initialV ) * ( v - initialV ) ) / ( 2 * a );
}

// 弾性衝突後の速さ
double Pysics::afterElasticCollisionV( double e, double v ) {
    return -e * v;
}

double Math::distanceBetweenTwoPoints( double xa, double ya, double xb, double yb ) {
    return sqrt( pow( xb - xa, 2.0 ) + pow( yb - ya, 2.0 ) );
}
