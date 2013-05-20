/*
コンパイル方法：
gcc ito2.c -o ito2 -O3 -I/usr/X11R6/include -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXext -lX11 -lm
 */

#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
//#include <GLUT/gl.h>
//#include <GLUT/glu.h>
#include <math.h>
#define ESCKEY 27  /* Escキーのコード */
#define N 50
#define SPEED 0.0008

double absolute(double);
int equal(double, double);

double movey = 0., sy = 0., ay = -0.000001;
double ito[N], harix = 2.0, hariy = 0.0;
int chien = 0, count = 0, flag = 1;
  /* global変数として定義 */

void display( void ){ /* 描画定義 */
  int i;
  char str[100];
  void *font = GLUT_BITMAP_HELVETICA_18;

  glClear( GL_COLOR_BUFFER_BIT );  /* 画面のクリア */

  glColor3f( 1.0, 1.0, 1.0 ); /* 糸の描画 */
  glBegin( GL_LINE_STRIP ); 
  for(i = 0; i < N-1; i++){
    glVertex2d( i*-1.0/N, ito[i] );
  }
  glEnd(); 

  glColor3f( 0.5, 0.5, 0.5 ); /* 描画色をr=1,g=1,b=1(つまり白色)に設定 */
  glBegin( GL_POLYGON ); /* ポリゴンの描画開始 */
    glVertex3f( harix+0.01, hariy+0.1, 0.0 ); /* 右上頂点 */
    glVertex3f( harix-0.01, hariy+0.1, 0.0 ); /* 左上頂点 */
    glVertex3f( harix-0.01, -1.0, 0.0 ); /* 左下頂点 */
    glVertex3f( harix+0.01, -1.0, 0.0 ); /* 右下頂点 */
    /* x,y座標のみ利用(z=0)して2次元図形を表現 */
  glEnd(); /* ポリゴンの描画終了 */

  glColor3f( 0.0, 0.0, 0.0 ); /* 描画色をr=1,g=1,b=1(つまり白色)に設定 */
  glBegin( GL_POLYGON ); /* ポリゴンの描画開始 */
    glVertex3f( harix+0.005, hariy+0.08, 0.0 ); /* 右上頂点 */
    glVertex3f( harix-0.005, hariy+0.08, 0.0 ); /* 左上頂点 */
    glVertex3f( harix-0.005, hariy-0.08, 0.0 ); /* 左下頂点 */
    glVertex3f( harix+0.005, hariy-0.08, 0.0 ); /* 右下頂点 */
    /* x,y座標のみ利用(z=0)して2次元図形を表現 */
  glEnd(); /* ポリゴンの描画終了 */

  sprintf(str, "count:%03d", count);
  glColor3f( 1.0, 1.0, 1.0 ); /* 糸の描画 */
  glRasterPos3f(0.0, 0.9, 0.0);
  {
    char* p = str;
    while(*p){
      glutBitmapCharacter(font, *p);
      ++p;
    }
  }
  glutSwapBuffers(); /* 描画処理を完了させ、描画対象フレームバッファを入替
			(ここで初めて画面に表示される) */
}

void idle( void ){  /* キーが押されていない場合の処理 */
  int i;

  sy += ay;
  movey += sy;
  if(equal(harix, 0) && flag){
    count++;
    flag = 0;
  }
  if(sy < -SPEED) sy = -SPEED;
  if(sy >  SPEED) sy =  SPEED;
  if(harix < -1.0){
    harix = 1.0;
    hariy = -sy*1000;
    flag = 1;
  }
  if(movey < -1 || movey > 1 ||
     (equal(harix, 0) && absolute(movey-hariy) > 0.08)){
    for(i = 0; i < N; i++) ito[i] = 0;
    sy = 0;
    harix = 2.;
    hariy = 0.;
    movey = 0.;
    count = 0;
    flag = 1;
  }

  ito[0] = movey;
  chien++;
  if(chien == 3000/N){
    chien = 0;
    for(i = N-2; i >= 0; i--)
      ito[i+1] = ito[i];
    harix-=1.0/N;
  }
  
  glutPostRedisplay(); /* 再描画命令 */
}


void myKbd( unsigned char key, int x, int y ){ /* キーボード割り込みの処理 */
  switch( key ){ /* keyが押されたキーボードのコードを表す */
    case ESCKEY: /* Escキーが押された場合 */
      exit(0);
    case 'r': /* rキーが押された場合 */
      ay = -ay;
  }
  
  glutPostRedisplay(); /* 再描画命令 */
}


void myKbdup( unsigned char key, int x, int y ){ /* キーボード割り込みの処理 */
  switch( key ){
    case 'r':
      ay = -ay;
  }
  
  glutPostRedisplay(); /* 再描画命令 */
}


void myInit ( char *progname ){ /* 描画ウィンドウ等の初期設定 */
  int width = 500, height = 500; /* ウィンドウサイズ用変数 */
  int i;
  for(i = 0; i < N; i++)
    ito[i] = 0.0;

  glutInitWindowPosition( 0, 0 ); /* ウィンドウの左上の位置 */
  glutInitWindowSize( width, height ); /* ウィンドウのピクセル数(サイズ) */
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA ); 
    /* ウィンドウのモード(ダブルバッファ、RGBA) */
  glutCreateWindow( progname ); /* ウィンドウをオープンする関数 */
  glClearColor ( 0.0, 0.0, 0.0, 1.0 ); /* ウィンドウの背景色の設定(黒) */
  glutKeyboardFunc( myKbd ); 
  glutKeyboardUpFunc( myKbdup ); 
    /* キーボード割り込みがあった場合の実行関数(mykbd)の指定 */

  glMatrixMode( GL_PROJECTION ); /* 描画モード */
  glLoadIdentity();
  glOrtho( -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 ); /* 描画範囲：(-1,1)〜(1,-1) */

  glutIgnoreKeyRepeat(GL_TRUE);
}

double absolute(double a){
  if(a < 0.0)
    return -a;
  else return  a;
}

int equal(double a, double b){
  if(absolute(b-a) < 1.0e-7)
    return 1;
  else return 0;
}

int main( int argc, char** argv ){
  glutInit( &argc, argv ); /* システム初期化 */
  myInit( argv[0] ); /* ユーザ指定の初期化 */
  glutDisplayFunc( display ); /* 描画(1回) */
  glutIdleFunc( idle ); /* キー割り込みがない場合の処理を指定 */
  glutMainLoop(); /* 無限ループ(キー割り込み待ち) */
  return( 0 );
}
