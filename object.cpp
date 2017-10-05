#include "object.h"
#include "calculation.h"
#include <math.h>

using namespace std;

// 長方形を描く
void ObjectGl::rectangle( double x, double y, double red, double green, double blue, double width ) {

    glColor3d( red, green, blue );
    glLineWidth( width );
    glBegin(GL_LINE_LOOP);

    glVertex2d( -x, -y );
    glVertex2d( x, -y );
    glVertex2d( x, y) ;
    glVertex2d( -x, y );

    glEnd();
}

// 線分を描く
void ObjectGl::line( double xa, double ya, double xb, double yb, double red, double green, double blue, double width ) {

    glColor3d( red, green, blue );
    glLineWidth( width );
    glBegin(GL_LINE_LOOP);

    glVertex2d( xa, ya );
    glVertex2d( xb, yb );

    glEnd();
}

// 円を描く
void ObjectGl::fillCircle( double a, double b, double r, double n, double red, double green, double blue ) {

    double i = 0.0;

    double x = 0.0;
    double y = 0.0;

    glColor3d( red , green , blue );  // 円の色(RGBA)
    glBegin(GL_POLYGON);				// ポリゴンの頂点記述開始

    for (i = 0.0; i < n; i++) {

        x = r * cos(2.0 * PI * ( i / n ) );
        y = r * sin(2.0 * PI * ( i / n ) );

        glVertex2f( x + a, y + b );		// 頂点の座標
    }

    glEnd();
}
