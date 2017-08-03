#include "calculation.h"
#include <math.h>
#include <string>
#include <cstdio>

using namespace std;

// K = (1/2)mv^2
double Physics::physicalEnergy( string target, double m, double now_v ) {
    return ( 0.5 ) * m * ( pow( now_v, 2.0 ) );
}

double Physics::physicalEnergy( double k, string target, double now_v ) {
    return ( 2.0 * k ) / ( pow( now_v, 2.0 ) );
}

double Physics::physicalEnergy( double k, double m, string target ) {
    return sqrt( ( 2.0 * k ) / m );
}

// F = μN (動摩擦力)
double Physics::dynamicFriction( string target, double mu, double n ) {
    return mu * n;
}

double Physics::dynamicFriction( double f, string target, double n ) {
    return f / n;
}

double Physics::dynamicFriction( double f, double mu, string target ) {
    return f / mu;
}

double Physics::afterSpeedOnFriction ( string target, double now_v ) {
    
    // 平方根が存在しない時
    if( 2 * MU * G  > pow( now_v, 2 ) ) {
        // printf("NO SQUARE ROOT!\n");
        return 0.0;
    }

    return sqrt( pow( now_v, 2 ) - ( 2 * MU * G ) );
}

// 変化前の運動エネルギー = 現在の運動エネルギー + 外力が物体にした仕事
// double calculationDoneWork( string target, double now_physical_energy, double outside_energy ) {
//     return now_physical_energy + outside_energy;
// }
//
// double calculationDoneWork( double before_physical_energy, string target, double outside_energy ) {
//     return before_physical_energy - outside_energy;
// }

// double calculationDoneWork( double before_physical_energy, double now_physical_energy, string target ) {
//     return before_physical_energy - now_physical_energy;
// }

// double calculationAfterSpeed ( string target, double now_v ) {
//     return sqrt ( pow( now_v, 2 ) - ( 2 * MU * G ) );
// }

// v = v_0 + at
double Physics::acceleratedMotionExceptY( string target, double initialV, double a, double t ) {
    return initialV + ( a * t );
}

double Physics::acceleratedMotionExceptY( double now_v, string target, double a, double t ) {
    return now_v - ( a * t );
}

double Physics::acceleratedMotionExceptY( double now_v, double initialV, string target, double t ) {
    return ( now_v - initialV ) / t;
}

double Physics::acceleratedMotionExceptY( double now_v, double initialV, double a, string target ) {
    return ( now_v - initialV ) / a;
}


// y  = v_0t + (1/2)at^2
double Physics::acceleratedMotionExceptV( string target, double initialV, double a, double t ) {
    return initialV + ( ( 0.5 ) * a * pow( t, 2.0 ) );
}

double Physics::acceleratedMotionExceptV( double y, string target, double a, double t ) {
    return  ( (2 * y) - ( a * pow( t, 2.0) ) ) / ( 2.0 * t );
}

double Physics::acceleratedMotionExceptV( double y, double initialV, string target, double t ) {
    return ( 2 * ( y - ( initialV * t ) ) ) / ( pow( t, 2.0 ) );
}

void Physics::acceleratedMotionExceptV( double sol[2], double y, double initialV, double a, string target ) {
    sol[0] = ( - initialV + sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
    sol[1] = ( - initialV - sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
}


// v^2 = v_0^2 + 2ay
double Physics::acceleratedMotionExceptT( string target, double initialV, double a, double y ) {
    return sqrt( pow( initialV, 2.0 ) + ( 2 * a * y ) );
}

double Physics::acceleratedMotionExceptT( double now_v, string target, double a, double y ) {
    return sqrt ( pow( now_v, 2.0 ) - ( 2 * a * y ) );
}

double Physics::acceleratedMotionExceptT( double now_v, double initialV, string target, double y ) {
    return ( ( now_v + initialV ) * ( now_v - initialV ) ) / ( 2 * y );
}

double Physics::acceleratedMotionExceptT( double now_v, double initialV, double a, string target ) {
    return ( ( now_v + initialV ) * ( now_v - initialV ) ) / ( 2 * a );
}

// 弾性衝突後の速さ
double Physics::afterElasticCollisionV( double now_v, double e ) {
    return -e * now_v;
}

double Math::distanceBetweenTwoPoints( double xa, double ya, double xb, double yb ) {
    return sqrt( pow( xb - xa, 2.0 ) + pow( yb - ya, 2.0 ) );
}

double Math::innerProduct( double xa, double ya, double xb, double yb ) {
    return ( xa * xb ) + ( ya * yb );
}

// 0° <= θ <= 90°
double Math::formedAngle( double xa, double ya, double xb, double yb ) {

    double formed_angle = cos(
        Math::innerProduct( xa, ya, xb, yb ) /
            ( Math::distanceBetweenTwoPoints( xa , xb , 0 , 0 ) *
            Math::distanceBetweenTwoPoints( 0 , 0 , xb , xb )
            )
    );

    return formed_angle < 0 ? -formed_angle : formed_angle;
}

double Math::syntheticVector ( double a, double b ) {
    return sqrt( pow( a, 2.0 ) + pow( b, 2.0 ) );

}

void Math::resolutionVector ( double vector_size, double cos_theta, double v[2], string axis) {

    // printf("vector_size = %f, cos_theta = %f, v[0] = %f, v[1] = %f\n", vector_size, cos_theta, v[0], v[1]);

    v[0] = v[0] < 0 ? v[0] * -1.0 : v[0];
    v[1] = v[1] < 0 ? v[1] * -1.0 : v[1];
    // printf("sin = %f, cos = %f", 1.0 - pow( cos_theta, 2.0 ), cos_theta);
    // if( axis == "x" ) {
    //     v[0] = vector_size * cos_theta;
    //     v[1] = vector_size * sqrt ( 1.0 - pow( cos_theta, 2.0 ) );
    // }
    //
    // else {
    //     v[0] = vector_size * sqrt ( 1.0 - pow( cos_theta, 2.0 ) );
    //     v[1] = vector_size * cos_theta;
    // }

    v[0] = vector_size * cos_theta;
    v[1] = vector_size * sqrt ( 1.0 - pow( cos_theta, 2.0 ) );





}
