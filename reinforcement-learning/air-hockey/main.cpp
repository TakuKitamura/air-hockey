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


double before_pack_pos[2] = { 0, 0 };
double pack_pos[2] = { 0, 0 };
double a[2] = { 0.5, 0.5 };
double v_direction[2] = { 0.0, 0.0 };

Math math;

void launchPack( double pack_pos[2], double a[2] ){

    srand( ( unsigned ) time( NULL ) );
    pack_pos[0] = rand() % (OX - 48) + 24;
    pack_pos[1] = rand() % (OY - 48) + 24;
    printf("%f",pack_pos[1]);
    //
    pack_pos[0] = rand() % 2 ? pack_pos[0] : -pack_pos[0];
    // pack_pos[1] = rand() % 2 ? pack_pos[1] : -pack_pos[1];
    //
    a[0] = rand() % 10 + 1;
    a[1] = rand() % 10 + 1;
    //
    a[0] = rand() % 2 ? a[0] : -a[0];
    // a[1] = rand() % 2 ? a[1] : -a[1];
    //
    // a[0] *= -1;
    a[1] *= -1;

    // pack_pos[1] = 100;
    // a[1] = 1;
    // a[0] = -100;
    // a[1] = -100;

    printf("pack_pos[0] = %f, pack_pos[1] = %f, a[0] = %f, a[1] = %f\n",pack_pos[0],pack_pos[1],a[1],a[2]);

}

void movePack( double pack_pos[2] , double before_pack_pos[2]) {


    int quadrant = 0;

    before_pack_pos[0] = pack_pos[0];
    before_pack_pos[1] = pack_pos[1];

    pack_pos[0] = pack_pos[0] + a[0];
    pack_pos[1] = pack_pos[1] + a[1];


    if ( pack_pos[0] > OX - 24 ) {
        pack_pos[0] = OX - 24;
    }

    else if ( pack_pos[0] < -(OX - 24) ) {
        pack_pos[0] = -( OX - 24 );
    }

    if ( pack_pos[1] > OY - 24 ) {
        pack_pos[1] = OY - 24;
    }

    else if ( pack_pos[1] < -(OY - 24) ) {
        pack_pos[1] = -( OY - 24 );
    }

    v_direction[0] = pack_pos[0] - before_pack_pos[0];
    v_direction[1] = pack_pos[1] - before_pack_pos[1];

    a[0] = (pack_pos[0] == OX - 24 || pack_pos[0] == -( OX - 24 ) ) ? -a[0] * E : a[0];
    a[1] = (pack_pos[1] == OY - 24 || pack_pos[1] == -( OY - 24 ) ) ? -a[1] * E : a[1];

    // printf("a[0] * 0.75 = %f, a[1] * 0.75 = %f\n",-a[0] * E,-a[1] * E);
    // printf("a[0] = %f, a[1] = %f\n",a[0],a[1]);
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
    glutTimerFunc( 1, timer, 0 );

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
    launchPack( pack_pos, a );
    glutTimerFunc( 1, timer, 0 );
    glutMainLoop();


    return 0;
}
