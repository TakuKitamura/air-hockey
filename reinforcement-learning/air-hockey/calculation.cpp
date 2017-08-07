#include "calculation.h"
#include <math.h>
#include <string>
#include <cstdio>

using namespace std;

// K = (1/2)mv^2
// double Physics::physicalEnergy( string target, double m, double now_v ) {
    // return ( 0.5 ) * m * ( pow( now_v, 2.0 ) );
// }

// double Physics::physicalEnergy( double k, string target, double now_v ) {
    // return ( 2.0 * k ) / ( pow( now_v, 2.0 ) );
// }

// double Physics::physicalEnergy( double k, double m, string target ) {
    // return sqrt( ( 2.0 * k ) / m );
// }

// F = μN (動摩擦力)
// double Physics::dynamicFriction( string target, double mu, double n ) {
    // return mu * n;
// }

// double Physics::dynamicFriction( double f, string target, double n ) {
    // return f / n;
// }

// double Physics::dynamicFriction( double f, double mu, string target ) {
    // return f / mu;
// }

// 摩擦があるときの、速さを求める
double Physics::afterSpeedOnFriction( string target, double now_v, double mu ) {

    // 平方根が存在しない時
    if( 2 * mu * G  > pow( now_v, 2.0 ) ) {
        // printf("NO SQUARE ROOT!\n");
        return 0.0;
    }

    return sqrt( pow( now_v, 2.0 ) - ( 2.0 * mu * G ) );
}

// mass_ratio = ( M + m ) / m
// 摩擦があるときの、速さを求める
double Physics::afterSpeedOnFriction( string target, double now_v, double mu, double mass_ratio ) {

    // 平方根が存在しない時
    if( 2 * mu * G  > mass_ratio * pow( now_v, 2.0 ) ) {
        // printf("NO SQUARE ROOT!\n");
        return 0.0;
    }

    return sqrt( ( mass_ratio * pow( now_v, 2.0 ) ) - ( 2.0 * mu * G ) );
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
// double Physics::acceleratedMotionExceptY( string target, double initialV, double a, double t ) {
    // return initialV + ( a * t );
// }

// double Physics::acceleratedMotionExceptY( double now_v, string target, double a, double t ) {
    // return now_v - ( a * t );
// }

// double Physics::acceleratedMotionExceptY( double now_v, double initialV, string target, double t ) {
    // return ( now_v - initialV ) / t;
// }

// double Physics::acceleratedMotionExceptY( double now_v, double initialV, double a, string target ) {
    // return ( now_v - initialV ) / a;
// }


// y  = v_0t + (1/2)at^2
// double Physics::acceleratedMotionExceptV( string target, double initialV, double a, double t ) {
//     return initialV + ( ( 0.5 ) * a * pow( t, 2.0 ) );
// }

// double Physics::acceleratedMotionExceptV( double y, string target, double a, double t ) {
//     return  ( (2 * y) - ( a * pow( t, 2.0) ) ) / ( 2.0 * t );
// }

// double Physics::acceleratedMotionExceptV( double y, double initialV, string target, double t ) {
//     return ( 2 * ( y - ( initialV * t ) ) ) / ( pow( t, 2.0 ) );
// }

// void Physics::acceleratedMotionExceptV( double sol[2], double y, double initialV, double a, string target ) {
//     sol[0] = ( - initialV + sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
//     sol[1] = ( - initialV - sqrt( pow( initialV, 2.0 ) + ( 2.0 * a * y ) ) ) / a;
// }


// v^2 = v_0^2 + 2ay
// double Physics::acceleratedMotionExceptT( string target, double initialV, double a, double y ) {
//     return sqrt( pow( initialV, 2.0 ) + ( 2 * a * y ) );
// }

// double Physics::acceleratedMotionExceptT( double now_v, string target, double a, double y ) {
//     return sqrt ( pow( now_v, 2.0 ) - ( 2 * a * y ) );
// }

// double Physics::acceleratedMotionExceptT( double now_v, double initialV, string target, double y ) {
//     return ( ( now_v + initialV ) * ( now_v - initialV ) ) / ( 2 * y );
// }

// double Physics::acceleratedMotionExceptT( double now_v, double initialV, double a, string target ) {
//     return ( ( now_v + initialV ) * ( now_v - initialV ) ) / ( 2 * a );
// }

// 弾性衝突後の速さ
double Physics::afterElasticCollisionV( double now_v, double e ) {
    return -e * now_v;
}

// 二点間の距離を求める
double Math::distanceBetweenTwoPoints( double xa, double ya, double xb, double yb ) {
    return sqrt( pow( xb - xa, 2.0 ) + pow( yb - ya, 2.0 ) );
}

// double Math::innerProduct( double xa, double ya, double xb, double yb ) {
//     return ( xa * xb ) + ( ya * yb );
// }

// ベクトルの大きさを求める
double Math::syntheticVector ( double a, double b ) {
    return sqrt( pow( a, 2.0 ) + pow( b, 2.0 ) );

}

// 0° <= θ <= 90°
// double Math::formedAngle( double xa, double ya, double xb, double yb ) {
//
//     double formed_angle =
//         Math::innerProduct( xa, ya, xb, yb ) /
//             ( Math::syntheticVector( xa, ya ) *
//                 Math::syntheticVector( xb , yb )
//             );
//
//     return formed_angle < 0 ? -formed_angle : formed_angle;
// }

// void Math::resolutionVector ( double vector_size, double cos_theta, double v[2], string axis) {
//
//     v[0] = vector_size * cos_theta;
//     v[1] = vector_size * sqrt( 1.0 - pow( cos_theta, 2.0 ) );
//
// }

// 内分点に関するものを計算
void Math::dividingPoint ( double m, double n, double xa, double ya, double xp, double yp, double v[2] ) {
    v[0] = ( ( ( m + n ) * xp ) - ( n * xa ) ) / m;
    v[1] = ( ( ( m + n ) * yp ) - ( n * ya ) ) / m;
}

// void Math::rotationalMovement ( double x, double y, double theta, double xo, double yo, double v[2] ) {
//     v[0] = xo + ( x * cos( theta ) ) - ( y * sin( theta ) );
//     v[1] = yo + ( x * sin( theta ) ) + ( y * cos( theta ) );
// }
