#ifndef _OBJECT_H
#define _OBJECT_H

#include <GLUT/glut.h>

#define MM 20 // マレットの質量
#define PM 10 // パックの質量
#define MR 30 // マレット半径
#define PR 20 // パック半径
#define TLW 4 // 線の幅
#define E  0.5 // テーブルの壁と、マレットの反発係数
#define MU 0.0001 // 動摩擦係数

#define OX 194 // 横幅
#define OY 366 // 縦幅

#define TG 1 // ゴール幅


class ObjectGl {

public:
    void rectangle( double x, double y, double red, double green, double blue, double width );
    void line( double xa, double ya, double xb, double yb, double red, double green, double blue, double width );
    void fillCircle( double a, double b, double r, double n, double red, double green, double blue );
};

#endif
