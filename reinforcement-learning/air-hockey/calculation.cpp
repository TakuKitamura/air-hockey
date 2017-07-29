#include "calculation.h"
#include <math.h>

// K = (1/2)mv^2
double pysicalEnergy( string target, double m, double v ) {
    return ( 1 / 2 ) * m * ( pow( v, 2.0 ) );
}

double pysicalEnergy( double k, string target, double v ) {
    return ( 2 * k ) / ( pow( v, 2.0 ) );
}

double pysicalEnergy( double k, double m, string target ) {
    return sqrt( ( 2 * k ) / m );
}

// F = μN (動摩擦力)
double dynamicFriction( string target, double mu, double n ) {
    return mu * n;
}

double dynamicFriction( double f, string target, double n ) {
    return f / n;
}

double dynamicFriction( double f, double mu, string target ) {
    return f / mu;
}


// v = v_0 + at
double acceleratedMotionExecptY( string target, double initialV, double a, double t ) {
    return initialV + ( a * t );
}

double acceleratedMotionExecptY( double v, string target, double a, double t ) {
    return v - ( a * t );
}

double acceleratedMotionExecptY( double v, double initialV, string target, double t ) {
    return ( v - initialV ) / t;
}

double acceleratedMotionExecptY( double v, double initialV, double a, string target ) {
    return ( v - initialV ) / a;
}


// y  = v_0t + (1/2)at^2
double acceleratedMotionExceptV( string target, double initialV, double a, double t ) {
    return initialV + ( ( 1 / 2 ) * a * pow( t, 2.0 ) );
}

double acceleratedMotionExceptV( double y, string target, double a, double t ) {
    return  ( (2 * y) - ( a * pow( t, 2.0) ) ) / ( 2 * t )
}

double acceleratedMotionExceptV( double y, double initialV, string target, double t ) {

    return ( 2 * ( y - ( initialV * t ) ) ) / ( pow( t, 2.0 ) );
}

double acceleratedMotionExceptV( double y, double initialV, double a, string target ) {
    return  sqrt( ( 2 * ( y - ( initialV * t ) ) ) / a );
}


// v^2 = v_0^2 + 2ay
double acceleratedMotionExceptT( string target, double initialV, double a, double y ) {
    return sqrt( pow( initialV, 2.0 ) + ( 2 * a * y ) );
}

double acceleratedMotionExceptT( double v, string target, double a, double y ) {
    return sqrt ( pow( v, 2.0 ) - ( 2 * a * y ) );
}

double acceleratedMotionExceptT( double v, double initialV, string target, double y ) {
    return ( ( v + initialV ) * ( v - initialV ) ) / ( 2 * y );
}

double acceleratedMotionExceptT( double v, double initialV, double a, string target ) {
    return ( ( v + initialV ) * ( v - initialV ) ) / ( 2 * a );
}


// 弾性衝突後の速さ
double afterElasticCollisionV( double e, double v ) {
    return -e * v;
}
