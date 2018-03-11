#include <math.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include "calculation.h"
#include "object.h"


#define MM 20 // マレットの質量
#define PM 10 // パックの質量

#define MR 20 // マレット半径
#define PR 15 // パック半径

#define TLW 4 // テーブル線の幅
#define TG 0.7 // ゴール幅

#define E 0.5 // テーブルの壁と、マレットの反発係数
#define MU 0.0001 // 動摩擦係数

#define OX 194 // 横幅
#define OY 366 // 縦幅

#define INTERVAL 1 // タイマー間隔

// void launchPack();
void putPack();
void updatePack();
void updateMallet( double x, double y, double click_count );

// 通常はグローバル変数は、関数に、引数として渡すのが望ましい
// ただ、このプログラムでは、openglを用いていて、グラフィックリソースを操作するためグローバル変数を使う
double pack_pos[2] = { 0.0, 0.0 };
double mallet_pos[2] = { 0.0, 0.0 };
double pack_now_v[2] = { 0.0, 0.0 };
double mallet_now_v[2] = { 0.0, 0.0 };

Math math;
Physics phy;
ObjectGl table;
ObjectGl pack;
ObjectGl mallet;

// void launchPack() {
//
//     srand( ( unsigned ) time( NULL ) );
//     pack_pos[0] = rand() % (OX - 48) + ( PR + ( TLW / 2 ) );
//     pack_pos[1] = rand() % (OY - 48) + ( PR + ( TLW / 2 ) );
//     pack_pos[0] = rand() % 2 ? pack_pos[0] : -pack_pos[0];
//
//     pack_now_v[0] = rand() % 5 + 10;
//     pack_now_v[1] = rand() % 5 + 10;
//     //
//     pack_now_v[0] = rand() % 2 ? pack_now_v[0] : -pack_now_v[0];
//     pack_now_v[1] *= -1;
//
// }

void putPack() {
    pack_pos[0] = 0.0;
    pack_pos[1] = -80.0;
    pack_now_v[0] = 0.0;
    pack_now_v[1] = 0.0;
}

void updatePack() {

    double after_synthetic_vx = 0.0;
    double after_synthetic_vy = 0.0;

    double pack_now_v_sign[2] = { 0.0, 0.0 };

    double distance_pack_to_mallet = 0.0;

    double difference = 0.0;

    // パックの位置を更新
    pack_pos[0] += pack_now_v[0];
    pack_pos[1] += pack_now_v[1];

    // パックの存在範囲を制限
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

    // パックからマレットまでの距離
    distance_pack_to_mallet = math.distanceBetweenTwoPoints( pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1] );

    // パックが、マレットに接触していないとき
    if ( distance_pack_to_mallet > PR + MR ) {

        // テーブルの壁にパックが接触したときの処理
        if( pack_pos[0] == OX - ( PR + ( TLW / 2 ) ) || pack_pos[0] == -( OX - ( PR + ( TLW / 2 ) ) ) ) {
            pack_now_v[0] = phy.afterElasticCollisionV( pack_now_v[0], E );
        }

        if( pack_pos[1] == OY - ( PR + ( TLW / 2 ) ) || pack_pos[1] == -( OY - ( PR + ( TLW / 2 ) ) ) ) {
            pack_now_v[1] = phy.afterElasticCollisionV( pack_now_v[1], E );
        }
    }

    // パックが、マレットに接触したとき
    else {

        // マレットの半径＋パックの半径ーパックからマレットまでの距離
        difference = MR + PR - distance_pack_to_mallet;

        // パックが、マレットに入り込まないようにする処理
        // 内分点計算
        math.dividingPoint( distance_pack_to_mallet, difference, mallet_pos[0], mallet_pos[1], pack_pos[0], pack_pos[1], pack_pos );

        // 動いているマレットが、パックを押し出すとき
        if( mallet_now_v[0] != 0.0 && mallet_now_v[1] != 0.0 ) {
            pack_now_v[0] = mallet_now_v[0];
            pack_now_v[1] = mallet_now_v[1];
        }

        // 止まっているマレットに、パックが衝突するとき
        // 要修正！！
        else {
            pack_now_v[0] = phy.afterElasticCollisionV( pack_now_v[0], E );
            pack_now_v[1] = phy.afterElasticCollisionV( pack_now_v[1], E );
        }
    }

    // パックの速さの方向を保存
    pack_now_v_sign[0] = pack_now_v[0] > 0 ? 1.0 : -1.0;
    pack_now_v_sign[1] = pack_now_v[1] > 0 ? 1.0 : -1.0;

    // パックが、マレットに接触していないとき
    if ( distance_pack_to_mallet > PR + MR ) {

        // 摩擦が有る状況下でのパックの速さ計算
        after_synthetic_vx = phy.afterSpeedOnFriction( "v", pack_now_v[0], MU );
        after_synthetic_vy = phy.afterSpeedOnFriction( "v", pack_now_v[1], MU );
    }

    // パックが、マレットに接触したとき
    else {
        // 摩擦が有る状況下でのパックの速さ計算
        after_synthetic_vx = phy.afterSpeedOnFriction( "v", pack_now_v[0], MU , ( MM + PM ) / PM );
        after_synthetic_vy = phy.afterSpeedOnFriction( "v", pack_now_v[1], MU , ( MM + PM ) / PM );
    }

    // パックの速さの方向を合わせる
    pack_now_v[0] = after_synthetic_vx * pack_now_v_sign[0];
    pack_now_v[1] = after_synthetic_vy * pack_now_v_sign[1];

    // パックの速さが微小のとき、動きを自然にするための処理
    if ( math.syntheticVector( pack_now_v[0], pack_now_v[1] ) <= 1.0 ) {
        pack_now_v[0] = 0.0;
        pack_now_v[1] = 0.0;
    }

    // パックの存在範囲を制限
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

    // パックが四隅にあるときの処理
    if( pack_pos[0] == OX - ( PR + ( TLW / 2 ) ) && pack_pos[1] == OY - ( PR + ( TLW / 2 ) ) && distance_pack_to_mallet <= PR + MR ) {
        difference = MR + PR - distance_pack_to_mallet;
        math.dividingPoint ( distance_pack_to_mallet, difference, pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1], mallet_pos );
    }

    else if( pack_pos[0] == OX - ( PR + ( TLW / 2 ) ) && pack_pos[1] == - (OY - ( PR + ( TLW / 2 ) ) ) && distance_pack_to_mallet <= PR + MR ) {
        difference = MR + PR - distance_pack_to_mallet;
        math.dividingPoint ( distance_pack_to_mallet, difference, pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1], mallet_pos );
    }

    else if( pack_pos[0] == - ( OX - ( PR + ( TLW / 2 ) ) ) && pack_pos[1] == OY - ( PR + ( TLW / 2 ) ) && distance_pack_to_mallet <= PR + MR ) {
        difference = MR + PR - distance_pack_to_mallet;
        math.dividingPoint ( distance_pack_to_mallet, difference, pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1], mallet_pos );
    }

    else if( pack_pos[0] == - ( OX - ( PR + ( TLW / 2 ) ) ) && pack_pos[1] == - ( OY - ( PR + ( TLW / 2 ) ) ) && distance_pack_to_mallet <= PR + MR ) {
        difference = MR + PR - distance_pack_to_mallet;
        math.dividingPoint ( distance_pack_to_mallet, difference, pack_pos[0], pack_pos[1], mallet_pos[0], mallet_pos[1], mallet_pos );
    }

    // パックがゴールに入ったときの処理
    // if( pack_pos[1] == OY - ( PR + ( TLW / 2 ) ) ) {
    //     if( pack_pos[0] <= TG * 100 && pack_pos[0] >= -( TG * 100 ) ) {
    //         putPack();
    //     }
    // }
    //
    // else if( pack_pos[1] == -( OY - ( PR + ( TLW / 2 ) ) ) ) {
    //     if( pack_pos[0] <= TG * 100 && pack_pos[0] >= -( TG * 100 ) ) {
    //         putPack();
    //     }
    // }
}

void updateMallet( double x, double y, double click_count ) {

    double before_mallet_pos[2] = { 0.0, 0.0 };
    double after_mallet_pos[2] = { 0.0, 0.0 };

    // 現在のマレットの位置を保存
    before_mallet_pos[0] = mallet_pos[0];
    before_mallet_pos[1] = mallet_pos[1];

    // マレットの位置を、マウスが押された座標にする
    mallet_pos[0] = x;
    mallet_pos[1] = y;

    // マレットの存在範囲を制限
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

    // マレットの位置を更新した後の、座標を保存
    after_mallet_pos[0] = mallet_pos[0];
    after_mallet_pos[1] = mallet_pos[1];

    // クリック回数により、処理を分岐
    if(click_count == 0) {

        // マレットの、速さ増加分を保存
        mallet_now_v[0] = after_mallet_pos[0] - before_mallet_pos[0];
        mallet_now_v[1] = after_mallet_pos[1] - before_mallet_pos[1];
    }

    else {
        // マレットの速さ初期化
        mallet_now_v[0] = 0.0;
        mallet_now_v[1] = 0.0;
    }
}


void display()
{

    // 画面をクリアする
    glClear(GL_COLOR_BUFFER_BIT);

    // テーブルの外枠を描く
    table.rectangle(
        OX / 100.0, OY / 100.0,
        0.0, 1.0, 0.0,
        TLW );


    // ゴール線を描く
    table.line(
        TG, OY / 100.0 - 0.01,
        -TG, OY / 100.0 - 0.01,
        1.0, 0.0, 1.0,
        TLW
    );

    // ゴール線を描く
    table.line(
        TG, -( OY / 100.0 - 0.01 ),
        -TG, -( OY / 100.0 - 0.01 ),
        1.0, 0.0, 1.0,
        TLW
    );

    // テーブルの中央線を描く
    table.line(
        -OX / 100.0, 0.0,
        OX / 100.0, 0.0,
        0.0, 1.0, 0.0,
        TLW
    );

    // パックを描く
    pack.fillCircle(
        pack_pos[0] * 0.01, pack_pos[1] * 0.01,
        PR * 0.01,
        50,
        1.0, 0.0, 0.0
    );

    // マレットを描く
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
    // ウィンドウ全体をビューポートにする
    glViewport(0, 0, w, h);

    // 変換行列の初期化
    glLoadIdentity();

    // スクリーン上の表示領域をビューポートの大きさに比例させる
    glOrtho(-w / 200.0, w / 200.0, -h / 200.0, h / 200.0, -1.0, 1.0);

}

void mouse(int button, int state, int x, int y) {

    // マウスの左ボタンが押されたとき
    if(button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // マレットの位置を、クリックした座標に更新
            updateMallet( x - OX, -( y - OY ), 1 );
        }

        printf("x = %d, y = %d\n",x - OX,y - OY);
    }

    // マウスの右ボタンが押されたとき
    if(button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_DOWN) {
            // マレットの位置を、クリックした座標に更新
            updateMallet( x - OX, -( y - OY ), 1 );

            // パックを再配置
            putPack();
        }
    }
}

void motion(int x, int y) {

    // マウスが動いたときにその座標へ、マレットの位置を更新
    updateMallet( x - OX, -( y - OY ), 0 );
}

void timer( int value ) {

    // 1ミリ秒ごとに、処理を繰り返す

    // パックの位置を更新
    updatePack();

    // 画面を更新
    glutPostRedisplay();

    // 再びtimer関数を再帰的に呼び出す
    glutTimerFunc( INTERVAL, timer, 0 );

}

void resistPackTracs() {

    int i = 0;
    int j = 0;
    int k = 0;

    double formed_angle = 0.0;

    pack_pos[1] = 0;

    for( i = -OX + PR; i <= OX - PR; i++ ) {

        pack_pos[0] = i;
        // printf("pack_pos[0] = %f, pack_pos[1] = %f\n",pack_pos[0],pack_pos[1]);
        for( j = 0; j <= OY; j++ ) {
            formed_angle = math.formedAngle( -OX, 0, -OX, j );
            pack_now_v[0] = PR * formed_angle;
            pack_now_v[1] = PR * sqrt( 1.0 - pow( formed_angle, 2.0 ) );
            printf("pack_now_v[0] = %f, pack_now_v[1] = %f\n",pack_now_v[0],pack_now_v[1]);
            // while( pack_now_v[0] != 0.0 && pack_now_v[1] != 0.0 ) {
            //     updatePack();
            //     // printf("pack_now_v[0] = %f, pack_now_v[1] = %f\n",pack_now_v[0],pack_now_v[1]);
            // }
        }

    }

    for( i = -OX + PR; i <= OX - PR; i++ ) {

        pack_pos[0] = i;
        // printf("pack_pos[0] = %f, pack_pos[1] = %f\n",pack_pos[0],pack_pos[1]);
        for( j = -OX; j <= OX; j++ ) {

            if( j < 0 ) {

            }

            else {

            }
            // formed_angle = math.formedAngle(
            pack_now_v[0] = j;
            pack_now_v[1] = OY;
            // while( pack_now_v[0] != 0.0 && pack_now_v[1] != 0.0 ) {
            //     updatePack();
            //     // printf("pack_now_v[0] = %f, pack_now_v[1] = %f\n",pack_now_v[0],pack_now_v[1]);
            // }
        }

    }

    for( i = -OX + PR; i <= OX - PR; i++ ) {

        pack_pos[0] = i;
        // printf("pack_pos[0] = %f, pack_pos[1] = %f\n",pack_pos[0],pack_pos[1]);
        for( j = 0; j <= OY; j++ ) {
            pack_now_v[0] = OX;
            pack_now_v[1] = j;
            // while( pack_now_v[0] != 0.0 && pack_now_v[1] != 0.0 ) {
            //     updatePack();
            //     // printf("pack_now_v[0] = %f, pack_now_v[1] = %f\n",pack_now_v[0],pack_now_v[1]);
            // }
        }

    }
}

    // srand( ( unsigned ) time( NULL ) );
    //
    // pack_pos[0] = 0;
    //
    // pack_now_v[0] = 10;
    // pack_now_v[1] = -10;

int main(int argc, char *argv[]) {

    int mode = 0;

    if( mode == 0 ) {

        // ウィンドウ表示に関し、必要な処理
        glutInitWindowPosition(100, 100);
        glutInitWindowSize( OX * 2.0 , OY * 2.0 );

        glutCreateWindow(argv[0]);
        glutDisplayFunc(display);
        glutReshapeFunc(resize);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);

        // パックを配置
        putPack();

        // マレットの位置を初期化
        updateMallet( 0.0 , -( OY / 2.0 ), 1 );

        // timer関数を再帰的に呼び出す
        glutTimerFunc( INTERVAL, timer, 0 );
        glutMainLoop();

    }

    else if( mode == 1 ) {

        // パックを配置
        resistPackTracs();
    }


    return 0;
}
