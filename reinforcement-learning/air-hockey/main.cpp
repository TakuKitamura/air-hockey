#include <math.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "calculation.h"
#include "object.h"


#define TIME 1

double pack_pos[2] = { 0.0, 0.0 };
double mallet_pos[2] = { 0.0, 0.0 };
double pack_now_v[2] = { 0.0, 0.0 };
double mallet_now_v[2] = { 0.0, 0.0 };

Math math;
Physics phy;
ObjectGl table;
ObjectGl pack;
ObjectGl mallet;

void launchPack( double pack_pos[2], double a[2] ){

    srand( ( unsigned ) time( NULL ) );
    pack_pos[0] = rand() % (OX - 48) + ( PR + ( TLW / 2 ) );
    pack_pos[1] = rand() % (OY - 48) + ( PR + ( TLW / 2 ) );

    pack_pos[0] = rand() % 2 ? pack_pos[0] : -pack_pos[0];

    pack_now_v[0] = rand() % 10 + 10;
    pack_now_v[1] = rand() % 10 + 10;
    //
    pack_now_v[0] = rand() % 2 ? pack_now_v[0] : -pack_now_v[0];
    pack_now_v[1] *= -1;

}

void updatePackPos( double pack_pos[2] ) {

    double outside_energy = 0.0;

    double formed_angle = 0.0;

    double before_synthetic_v = 0.0;
    double after_synthetic_v = 0.0;

    double pack_now_v_sign[2] = { 0.0, 0.0 };

    double distance_pack_to_mallet = 0.0;

    pack_pos[0] = pack_pos[0] + pack_now_v[0];
    pack_pos[1] = pack_pos[1] + pack_now_v[1];


    if( pack_pos[0] > OX - ( PR + ( TLW / 2 ) ) ) {
        pack_pos[0] = OX - ( PR + ( TLW / 2 ) );
    }

    else if( pack_pos[0] < -(OX - ( PR + ( TLW / 2 ) )) ) {
        pack_pos[0] = -( OX - ( PR + ( TLW / 2 ) ) );
    }

    if( pack_pos[1] > OY - ( PR + ( TLW / 2 ) ) ) {
        pack_pos[1] = OY - ( PR + ( TLW / 2 ) );
    }

    else if( pack_pos[1] < -(OY - ( PR + ( TLW / 2 ) )) ) {
        pack_pos[1] = -( OY - ( PR + ( TLW / 2 ) ) );
    }

    before_synthetic_v = math.syntheticVector( pack_now_v[0], pack_now_v[1] );

    if( pack_pos[0] == OX - ( PR + ( TLW / 2 ) ) || pack_pos[0] == -( OX - ( PR + ( TLW / 2 ) ) ) ) {
        pack_now_v[0] = phy.afterElasticCollisionV( pack_now_v[0], E );
    }

    if( pack_pos[1] == OY - ( PR + ( TLW / 2 ) ) || pack_pos[1] == -( OY - ( PR + ( TLW / 2 ) ) ) ) {
        pack_now_v[1] = phy.afterElasticCollisionV( pack_now_v[1], E );
    }

    pack_now_v_sign[0] = pack_now_v[0] > 0 ? 1.0 : -1.0;
    pack_now_v_sign[1] = pack_now_v[1] > 0 ? 1.0 : -1.0;

    formed_angle = math.formedAngle( OX, 0, pack_pos[0], pack_pos[1] );;

    after_synthetic_v = phy.afterSpeedOnFriction( "v", before_synthetic_v, MU );

    math.resolutionVector( after_synthetic_v, formed_angle, pack_now_v, "x" );


    pack_now_v[0] *= pack_now_v_sign[0];
    pack_now_v[1] *= pack_now_v_sign[1];

    distance_pack_to_mallet = math.distanceBetweenTwoPoints( pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1] );

    if( distance_pack_to_mallet <= PR + MR + 3.0 ) {
        // printf("HELLO!!!\n");
        pack_now_v[0] = -( pack_now_v[0] + 1 );
        pack_now_v[1] = -( pack_now_v[1] + 1 );
    }

    glutPostRedisplay();

}

void updateMalletPos( double mallet_pos[2], double x, double y) {

    mallet_pos[0] = x;
    mallet_pos[1] = y;

    if( mallet_pos[0] > OX - ( MR + ( TLW / 2 ) ) ) {
        mallet_pos[0] = OX - ( MR + ( TLW / 2 ) );
    }

    else if( mallet_pos[0] < -(OX - ( MR + ( TLW / 2 ) ) ) ) {
        mallet_pos[0] = -( OX - ( MR + ( TLW / 2 ) ) );
    }

    if( mallet_pos[1] < -(OY - ( MR + ( TLW / 2 ) ) ) ) {
        mallet_pos[1] = -( OY - ( MR + ( TLW / 2 ) ) );
    }

    else if( mallet_pos[1] > -( MR + ( TLW / 2 ) ) ) {
        mallet_pos[1] = -( MR + ( TLW / 2 ) ) ;
    }
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    table.rectangle(
        1.94, 3.66,
        0.0, 1.0, 0.0,
        TLW );

    table.line(
        -1.94, 0.0,
        1.94, 0.0,
        0.0, 1.0, 0.0,
        TLW
    );

    pack.fillCircle(
        pack_pos[0] * 0.01, pack_pos[1] * 0.01,
        PR * 0.01,
        50,
        1.0, 0.0, 0.0
    );

    mallet.fillCircle(
        mallet_pos[0] * 0.01, mallet_pos[1] * 0.01,
        MR * 0.01,
        50,
        1.0, 1.0, 1.0
    );

    glFlush();
}

void resize(int w, int h)
{
    /* ウィンドウ全体をビューポートにする */
    glViewport(0, 0, w, h);

    /* 変換行列の初期化 */
    glLoadIdentity();

    /* スクリーン上の表示領域をビューポートの大きさに比例させる */
    glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);

}

void mouse(int button, int state, int x, int y) {

    if(button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            updateMalletPos( mallet_pos ,x - OX, -( y - OY ) );
            launchPack( pack_pos, pack_now_v );
        }
    }
}

void motion(int x, int y) {
    updateMalletPos( mallet_pos ,x - OX, -( y - OY ) );
}

void timer( int value ) {
    updatePackPos( pack_pos );
    glutPostRedisplay();
    glutTimerFunc( TIME, timer, 0 );

}

int main(int argc, char *argv[])
{

    glutInitWindowPosition(100, 100);
    glutInitWindowSize( TW , TL );

    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    updateMalletPos( mallet_pos , 0.0 , -( OY / 2.0 ) );

    glutTimerFunc( TIME, timer, 0 );
    glutMainLoop();


    return 0;
}
