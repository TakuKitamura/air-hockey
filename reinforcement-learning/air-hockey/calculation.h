#ifndef _CALCULATION_H
#define _CALCULATION_H

#include <string>

using namespace std;

#define OX 0   // 位置ベクトル x
#define OY 0   // 位置ベクトル y
#define MM 100 // マレットの質量
#define PM 10  // パックの質量
#define MR 5   // マレット半径
#define PR 3   // パック半径
#define E  0.5 // 反発係数
#define MU 0.5 // 動摩擦係数

using namespace std;

class Pysics {

public:
    // K = (1/2)mv^2
    double pysicalEnergy( string target, double m, double v );
    double pysicalEnergy( double k, string target, double v );
    double pysicalEnergy( double k, double m, string target );

    // F = μN (動摩擦力)
    double dynamicFriction( string target, double mu, double n );
    double dynamicFriction( double f, string target, double n );
    double dynamicFriction( double f, double mu, string target );

    // v = v_0 + at
    double acceleratedMotionExceptY( string target, double initialV, double a, double t );
    double acceleratedMotionExceptY( double v, string target, double a, double t );
    double acceleratedMotionExceptY( double v, double initialV, string target, double t );
    double acceleratedMotionExceptY( double v, double initialV, double a, string target );

    // y  = v_0t + (1/2)at^2
    double acceleratedMotionExceptV( string target, double initialV, double a, double t );
    double acceleratedMotionExceptV( double y, string target, double a, double t );
    double acceleratedMotionExceptV( double y, double initialV, string target, double t );
    void acceleratedMotionExceptV( double sol[2], double y, double initialV, double a, string target );

    // v^2 = v_0^2 + 2ay
    double acceleratedMotionExceptT( string target, double initialV, double a, double y );
    double acceleratedMotionExceptT( double v, string target, double a, double y );
    double acceleratedMotionExceptT( double v, double initialV, string target, double y );
    double acceleratedMotionExceptT( double v, double initialV, double a, string target );

    // 弾性衝突後の速さ
    double afterElasticCollisionV( double e, double v );

};

class Math {

public:
    double distanceBetweenTwoPoints( double xa, double ya, double xb, double yb );

};

#endif
