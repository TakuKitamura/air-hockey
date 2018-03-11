#ifndef _OBJECT_H
#define _OBJECT_H

#include <GLUT/glut.h>

class ObjectGl {

public:
    void rectangle( double x, double y, double red, double green, double blue, double width );
    void line( double xa, double ya, double xb, double yb, double red, double green, double blue, double width );
    void fillCircle( double a, double b, double r, double n, double red, double green, double blue );
};

#endif
