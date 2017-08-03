#ifndef _CALCULATION_H
#define _CALCULATION_H

#include <string>

using namespace std;

// #define OX 0   // 位置ベクトル x
// #define OY 0   // 位置ベクトル y
#define MM 10 // マレットの質量
#define PM 10  // パックの質量
#define MR 5   // マレット半径
#define PR 3   // パック半径
#define E  0.75 // 反発係数
#define MU 0.2 // 動摩擦係数
#define G 9.80665 // 重力加速度
#define PI 3.14159

using namespace std;

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

    double afterSpeedOnFriction ( string target, double now_v );

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

};

#endif
