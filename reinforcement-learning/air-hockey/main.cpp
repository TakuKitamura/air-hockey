#include <GLUT/glut.h>
#include <math.h>
#include <cstdio>
#include <unistd.h>

#define WIDTH 388
#define LENGTH 732

int before_pack_pos[2] = { 0, 0 };
int pack_pos[2] = { 0, 0 };
double move_dist[2] = { 1.0, 1.0 };
int count[2] = { 1, 1 };

void movePack( int pack_pos[2] , int before_pack_pos[2], double move_dist[2]) {

    double ox = WIDTH / 2.0;
    double oy = LENGTH / 2.0;

    double v_direction[2] = { 0.0, 0.0 };

    before_pack_pos[0] = pack_pos[0];
    before_pack_pos[1] = pack_pos[1];

    pack_pos[0] = pack_pos[0] + count[0];
    pack_pos[1] = pack_pos[1] + count[1];

    v_direction[0] = pack_pos[0] - before_pack_pos[0];
    v_direction[1] = pack_pos[1] - before_pack_pos[1];


    count[0] = (pack_pos[0] == ox - 24 ||  -pack_pos[0] == ox - 24) ? -count[0] : count[0];
    count[1] = (pack_pos[1] == oy - 24 || -pack_pos[1] == oy - 24) ? -count[1] : count[1];

    // printf("v_direction[0] = %f, v_direction[1] = %f\n",v_direction[0],v_direction[1]);

    // move_dist[0] ++;
    // move_dist[1] ++;
    //
    // move_dist[0] = v_direction[0] == (ox / 2.0) - 20 ? -pack_pos[0] : pack_pos[0] + 1;//1
    //

    //
    // move_dist[1] = v_direction[1] == (oy / 2.0) - 20 ? -pack_pos[1] : pack_pos[1] + 1;//1
    printf("count[0] = %d, count[1] = %d\n",count[0],count[1]);
    printf("move_dist[0] = %f, move_dist[1] = %f\n",move_dist[0],move_dist[1]);
    printf("before_pack_pos[0] = %d, before_pack_pos[1] = %d\n",before_pack_pos[0],before_pack_pos[1]);
    printf("v_direction[0] = %f, v_direction[1] = %f\n",v_direction[0],v_direction[1]);
    printf("pack_pos[0] = %d, pack_pos[1] = %d\n\n\n",pack_pos[0],pack_pos[1]);
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
    // printf(" he (%d, %d)\n", pack_pos[0], pack_pos[1]);
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
    // printf("%lf",count);
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

    // printf(" at (%d, %d)\n", pack_pos[0], pack_pos[1]);
    // glutPostRedisplay();
}

void timer( int value ) {
    movePack( pack_pos, before_pack_pos, move_dist );
    glutPostRedisplay();
    glutTimerFunc( 1, timer, 0 );

}

int main(int argc, char *argv[])
{
    int i = 1000000;

    glutInitWindowPosition(100, 100);
    glutInitWindowSize(388, 732);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    // glutMouseFunc(mouse);
    init();
    glutTimerFunc( 1, timer, 0 );
    glutMainLoop();


    return 0;
}
