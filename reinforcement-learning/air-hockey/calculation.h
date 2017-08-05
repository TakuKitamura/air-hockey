#ifndef _CALCULATION_H
#define _CALCULATION_H

#include <string>

using namespace std;

#define G 9.80665 // 重力加速度
#define PI 3.14159

class Physics {

public:
    // K = (1/2)mv^2
    double physicalEnergy( string target, double m, double now_v );
    double physicalEnergy( double k, string target, double now_v );
    double physicalEnergy( double k, double m, string target );

    // F = μN (動摩擦力)
    double dynamicFriction( string target, double mu, double n );
    double dynamicFriction( double f, string target, double n );
    double dynamicFriction( double f, double mu, string target );

    // 変化前の運動エネルギー = 現在の運動エネルギー + 外力が物体にした仕事
    // double calculationDoneWork( string target, double now_physical_energy, double outside_energy );
    // double calculationDoneWork( double before_physical_energy, string target, double outside_energy );
    // double calculationDoneWork( double before_physical_energy, double now_physical_energy, string target );

    double afterSpeedOnFriction ( string target, double now_v, double mu );
    double afterSpeedOnFriction ( string target, double now_v, double mu, double mass_ratio );

    // v = v_0 + at
    double acceleratedMotionExceptY( string target, double initialV, double a, double t );
    double acceleratedMotionExceptY( double now_v, string target, double a, double t );
    double acceleratedMotionExceptY( double now_v, double initialV, string target, double t );
    double acceleratedMotionExceptY( double now_v, double initialV, double a, string target );

    // y  = v_0t + (1/2)at^2
    double acceleratedMotionExceptV( string target, double initialV, double a, double t );
    double acceleratedMotionExceptV( double y, string target, double a, double t );
    double acceleratedMotionExceptV( double y, double initialV, string target, double t );
    void acceleratedMotionExceptV( double sol[2], double y, double initialV, double a, string target );

    // v^2 = v_0^2 + 2ay
    double acceleratedMotionExceptT( string target, double initialV, double a, double y );
    double acceleratedMotionExceptT( double now_v, string target, double a, double y );
    double acceleratedMotionExceptT( double now_v, double initialV, string target, double y );
    double acceleratedMotionExceptT( double now_v, double initialV, double a, string target );

    // 弾性衝突後の速さ
    double afterElasticCollisionV( double now_v, double e );

};

class Math {

public:
    double distanceBetweenTwoPoints( double xa, double ya, double xb, double yb );

    double innerProduct( double xa, double ya, double xb, double yb );

    double formedAngle( double xa, double ya, double xb, double yb );

    double syntheticVector ( double a, double b );

    void resolutionVector ( double vector_size, double cos_theta, double v[2], string axis);

    void dividingPoint ( double m, double n, double xa, double ya, double xp, double yp, double v[2] );

};

#endif
