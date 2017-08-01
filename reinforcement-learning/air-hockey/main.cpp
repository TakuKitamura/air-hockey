#include <GLUT/glut.h>
#include <math.h>
#include <cstdio>
#include <unistd.h>
#include "calculation.h"

#define WIDTH 388
#define LENGTH 732

double before_pack_pos[2] = { 0, 0 };
double pack_pos[2] = { 0, 0 };
double move_dist[2] = { 1.0, 1.0 };
double sign[2] = { 1.0, 1.0 };
double v_direction[2] = { 0.0, 0.0 };

Math math;

void movePack( double pack_pos[2] , double before_pack_pos[2], double move_dist[2]) {

    double ox = WIDTH / 2.0;
    double oy = LENGTH / 2.0;

    int quadrant = 0;

    before_pack_pos[0] = pack_pos[0];
    before_pack_pos[1] = pack_pos[1];

    pack_pos[0] = pack_pos[0] + sign[0];
    pack_pos[1] = pack_pos[1] + sign[1];

    // if ( pack_pos[0] > 0 && pack_pos[1] > 0 ) {
    //     quadrant = 1;
    // }
    //
    // else if ( pack_pos[0] < 0 && pack_pos[1] > 0 ) {
    //     quadrant = 2;
    // }
    //
    // else if ( pack_pos[0] < 0 && pack_pos[1] < 0 ) {
    //     quadrant = 3;
    // }
    //
    // else {
    //     quadrant = 4;
    // }
    //
    // if ( ( pack_pos[0] > ox - 24 ) && ( quadrant == 1 || quadrant == 4 ) ) {
    //     pack_pos[0] = ox - 24;
    // }
    //
    // else if ( ( -pack_pos[0] > ox - 24 ) && ( quadrant == 1 || quadrant == 4 ) ) {
    //     pack_pos[0] = -(ox - 24);
    // }
    //
    // if ( ( pack_pos[1] > ox - 24 ) && ( quadrant == 1 || quadrant == 2 ) ) {
    //     pack_pos[1] = ox - 24;
    // }
    //
    // else if ( ( -pack_pos[0] > ox - 24 ) && ( quadrant == 1 || quadrant == 4 ) ) {
    //     pack_pos[1] = -(ox - 24);
    // }


    // pack_pos[0] = ( ( pack_pos[0] > ox - 24 ||  -pack_pos[0] > ox - 24 ) && ( quadrant == 1 || quadrant == 4 ) ? ox - 24 : -( ox - 24 ));

    // pack_pos[1] = ( ( pack_pos[1] > oy - 24 ||  -pack_pos[1] > oy - 24 ) && ( quadrant == 1 || quadrant == 4 ) ? oy - 24 : -( oy -24 ));

    if ( pack_pos[0] > ox - 24 ) {
        pack_pos[0] = ox - 24;
    }

    else if ( pack_pos[0] < -(ox - 24) ) {
        pack_pos[0] = -( ox - 24 );
    }

    if ( pack_pos[1] > oy - 24 ) {
        pack_pos[1] = oy - 24;
    }

    else if ( pack_pos[1] < -(oy - 24) ) {
        pack_pos[1] = -( oy - 24 );
    }

    v_direction[0] = pack_pos[0] - before_pack_pos[0];
    v_direction[1] = pack_pos[1] - before_pack_pos[1];

    sign[0] = (pack_pos[0] == ox - 24 || pack_pos[0] == -( ox - 24 ) ) ? -sign[0] * E : sign[0];
    sign[1] = (pack_pos[1] == oy - 24 || pack_pos[1] == -( oy - 24 ) ) ? -sign[1] * E : sign[1];

    // printf("sign[0] * 0.75 = %f, sign[1] * 0.75 = %f\n",-sign[0] * E,-sign[1] * E);
    // printf("sign[0] = %f, sign[1] = %f\n",sign[0],sign[1]);
    // printf("move_dist[0] = %f, move_dist[1] = %f\n",move_dist[0],move_dist[1]);
    // printf("before_pack_pos[0] = %f, before_pack_pos[1] = %f\n",before_pack_pos[0],before_pack_pos[1]);
    // printf("v_direction[0] = %f, v_direction[1] = %f\n",v_direction[0],v_direction[1]);
    printf("pack_pos[0] = %f, pack_pos[1] = %f\n\n\n",pack_pos[0],pack_pos[1]);
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

        x = r * cos(2.0 * 3.14 * ((double)i/n) );
        y = r * sin(2.0 * 3.14 * ((double)i/n) );

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
    // printf("%lf",sign);
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
        // printf("up");
        // movePack( pack_pos, before_pack_pos, move_dist );

        break;
        case GLUT_DOWN:
        // printf("down");
        break;
        default:
        break;
    }

    // printf(" at (%f, %f)\n", pack_pos[0], pack_pos[1]);
    // glutPostRedisplay();
}

void timer( int value ) {
    movePack( pack_pos, before_pack_pos, move_dist );
    glutPostRedisplay();
    glutTimerFunc( 10, timer, 0 );

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
    glutTimerFunc( 10, timer, 0 );
    glutMainLoop();


    return 0;
}
