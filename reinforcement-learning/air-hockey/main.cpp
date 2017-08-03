#include <GLUT/glut.h>
#include <math.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "calculation.h"

#define WIDTH 388
#define LENGTH 732
#define OX 194
#define OY 366
#define TIME 1


double before_pack_pos[2] = { 0, 0 };
double pack_pos[2] = { 0, 0 };
double now_v[2] = { 0.5, 0.5 };

Math math;
Physics phy;

void launchPack( double pack_pos[2], double a[2] ){

    srand( ( unsigned ) time( NULL ) );
    pack_pos[0] = rand() % (OX - 48) + 24;
    pack_pos[1] = rand() % (OY - 48) + 24;
    // printf("%f",pack_pos[1]);
    //
    pack_pos[0] = rand() % 2 ? pack_pos[0] : -pack_pos[0];
    // pack_pos[1] = rand() % 2 ? pack_pos[1] : -pack_pos[1];
    //
    now_v[0] = rand() % 10 + 10;
    now_v[1] = rand() % 10 + 10;
    //
    now_v[0] = rand() % 2 ? now_v[0] : -now_v[0];
    // now_v[1] = rand() % 2 ? now_v[1] : -now_v[1];
    //
    // now_v[0] *= -1;
    now_v[1] *= -1;

    // pack_pos[1] = 100;
    // now_v[1] = 1;
    // now_v[0] = -100;
    // now_v[1] = -100;

    // printf("pack_pos[0] = %f, pack_pos[1] = %f, now_v[0] = %f, now_v[1] = %f\n",pack_pos[0],pack_pos[1],now_v[1],a[2]);

}

void movePack( double pack_pos[2] , double before_pack_pos[2]) {

    int quadrant = 0;

    // double now_physical_energy = 0.0;
    // double after_physical_energy = 0.0;
    double outside_energy = 0.0;

    // double formed_angle_x = 0.0;
    // double formed_angle_y = 0.0;
    double formed_angle = 0.0;

    double before_synthetic_v = 0.0;
    double after_synthetic_v = 0.0;

    double now_v_sign[2] = { 0.0, 0.0 };


    // double direction[2] = { 0.0, 0.0 };

    double dynamic_friction = phy.dynamicFriction( "F", MU, PM * G );

    before_pack_pos[0] = pack_pos[0];
    before_pack_pos[1] = pack_pos[1];

    pack_pos[0] = pack_pos[0] + now_v[0];
    pack_pos[1] = pack_pos[1] + now_v[1];


    if( pack_pos[0] > OX - 24 ) {
        pack_pos[0] = OX - 24;
    }

    else if( pack_pos[0] < -(OX - 24) ) {
        pack_pos[0] = -( OX - 24 );
    }

    if( pack_pos[1] > OY - 24 ) {
        pack_pos[1] = OY - 24;
    }

    else if( pack_pos[1] < -(OY - 24) ) {
        pack_pos[1] = -( OY - 24 );
    }

    // direction[0] = before_pack_pos[0] - pack_pos[0];
    // direction[1] = before_pack_pos[1] - pack_pos[1];

    before_synthetic_v = math.syntheticVector( now_v[0], now_v[1] );

    // now_physical_energy = phy.physicalEnergy( "K", PM, before_synthetic_v );

    if( pack_pos[0] == OX - 24 || pack_pos[0] == -( OX - 24 ) ) {
        now_v[0] = phy.afterElasticCollisionV( now_v[0], E );
    }

    if( pack_pos[1] == OY - 24 || pack_pos[1] == -( OY - 24 ) ) {
        now_v[1] = phy.afterElasticCollisionV( now_v[1], E );
    }

    now_v_sign[0] = now_v[0] > 0 ? 1.0 : -1.0;
    now_v_sign[1] = now_v[1] > 0 ? 1.0 : -1.0;

    // formed_angle_x = math.formedAngle( OX, 0, pack_pos[0], pack_pos[1] );
    // formed_angle_y = math.formedAngle( 0, OY, pack_pos[0], pack_pos[1] );

    formed_angle = math.formedAngle( OX, 0, pack_pos[0], pack_pos[1] );;

    // printf("formed_angle = %f\n",formed_angle);

    // printf("1: now_v[0] = %f, now_v[1] = %f\n", now_v[0], now_v[1]);

    // after_physical_energy = phy.physicalEnergy( "K", PM, before_synthetic_v );

    after_synthetic_v = phy.afterSpeedOnFriction( "v", before_synthetic_v );

    // printf("%f\n",after_synthetic_v);



    math.resolutionVector( after_synthetic_v, formed_angle, now_v, "x" );

    // math.resolutionVector( after_synthetic_v, formed_angle_y , now_v, "y" );

    // formed_angle_y == 0.0 ?
    //          :


    now_v[0] *= now_v_sign[0];
    now_v[1] *= now_v_sign[1];

    // printf("2: now_v[0] = %f, now_v[1] = %f\n\n", now_v[0], now_v[1]);


    // now_v[1] = phy.afterSpeedOnFriction( "v'_y",




    // now_v[0] = (pack_pos[0] == OX - 24 || pack_pos[0] == -( OX - 24 ) ) ? -now_v[0] * E : now_v[0];
    // now_v[1] = (pack_pos[1] == OY - 24 || pack_pos[1] == -( OY - 24 ) ) ? -now_v[1] * E : now_v[1];

    // printf("now_v[0] * 0.75 = %f, now_v[1] * 0.75 = %f\n",-now_v[0] * E,-now_v[1] * E);
    // printf("now_v[0] = %f, now_v[1] = %f\n",now_v[0],now_v[1]);
    // printf("move_dist[0] = %f, move_dist[1] = %f\n",move_dist[0],move_dist[1]);
    // printf("before_pack_pos[0] = %f, before_pack_pos[1] = %f\n",before_pack_pos[0],before_pack_pos[1]);
    // printf("v_direction[0] = %f, v_direction[1] = %f\n",v_direction[0],v_direction[1]);
    // printf("pack_pos[0] = %f, pack_pos[1] = %f\n\n\n",pack_pos[0],pack_pos[1]);
    glutPostRedisplay();
    // printf("pack_pos[0] = %f, pack_pos[1] = %f",pack_pos[0],pack_pos[1]);

}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1.0, 1.0, 1.0);
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);

    glVertex2d(-1.94, -3.66);
    glVertex2d(1.94, -3.66);
    glVertex2d(1.94, 3.66);
    glVertex2d(-1.94, 3.66);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2d(-1.94, 0.0);
    glVertex2d(1.94, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2d(-1.94, 0.0);
    glVertex2d(1.94, 0.0);
    glEnd();

    int i, n = 50;						// 分割数n
    double r = 0.2;				// 円周上の座標(x,y)と半径r
    double x = 0;
    double y = 0;
    // printf(" he (%f, %f)\n", pack_pos[0], pack_pos[1]);
    glBegin(GL_POLYGON);				// ポリゴンの頂点記述開始
    glColor4f(1.0, 0.0, 0.0, 0.0);  // 円の色(RGBA)
    // 円周上の座標(x,y)を計算して円を描画

    for (i = 0; i < n; i++) {

        x = r * cos(2.0 * PI * ((double)i/n) );
        y = r * sin(2.0 * PI * ((double)i/n) );

        // printf("x = %lf, y = %lf\n",x,y);

        glVertex2f( x + ( pack_pos[0] * 0.01 ), y + ( pack_pos[1] * 0.01 ) );		// 頂点の座標
    }
    glEnd();


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

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
    // printf("%lf",a);
    // pack_pos[0] = x;
    // pack_pos[1] = y;
    //
    // before_pack_pos[0] = x;
    // before_pack_pos[1] = y;


    switch (button) {
        case GLUT_LEFT_BUTTON:
        // printf("left");
        break;
        case GLUT_MIDDLE_BUTTON:
        // printf("middle");
        break;
        case GLUT_RIGHT_BUTTON:
        // printf("right");
        break;
        default:
        break;
    }

    // printf(" button is ");

    switch (state) {
        case GLUT_UP:
        printf("up");
        // movePack( pack_pos, before_pack_pos, move_dist );

        break;
        case GLUT_DOWN:
        printf("down");
        break;
        default:
        break;
    }

    printf(" at (%f, %f)\n", pack_pos[0], pack_pos[1]);
    // glutPostRedisplay();
}

void timer( int value ) {
    movePack( pack_pos, before_pack_pos );
    glutPostRedisplay();
    glutTimerFunc( TIME, timer, 0 );

}

int main(int argc, char *argv[])
{

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(388, 732);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    // glutMouseFunc(mouse);
    init();
    launchPack( pack_pos, now_v );
    glutTimerFunc( TIME, timer, 0 );
    glutMainLoop();


    return 0;
}
