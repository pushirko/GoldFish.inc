/*
=== TIPS FOR INCLUDE===
#ifndef **_H
#define **_H
#endif
すまん、適当な自分用のメモです汗。多重定義によるエラー防止。ヘッダファイル作る時に使う。
上記文を最初に書いておくと、"**.h"を多重定義(同じヘッダファイルを何回も読む事)をさせないよう設定出来る。
======
--*/

#include "QtOpenGL"
#include "gl/GL.h"
#include "gl/GLU.h"

/*
=== ABOUT GL INCLUDE ===
#include <~~~>   ,    <~~~> is "GLU.h" or "glu.h" or "gl/GLU.h" or "gl/glu.h" or "GL/GLU.h" etc.
It depends on your environment, but maybe Qt supported any word above for this matter.
======
--*/

/*
===ABOUT USING GLU.H FUNCTION (ERROR FACTOR OF THIS PROJECT)===
"glu~~"という関数が使えない理由は、glu.hが読み込まれていないから。
解決方法:"QtOpenGL"と"glu.h"をインクルードする。
"QtOpenGL"をインクルードすると、openGLライブラリ("GL.h","GLU.h"?)を強制的にすべて読み込ませる事が出来る。
本当は"QtOpenGL"が無くても、"test0518.pro"の内部でopenGL使うよ！と言っておけばopenGLライブラリの読み込みは不要な筈なのだが…謎。
詳細な理由はQtソースを確認しないと分からないが、こうしておけば"gl.h"や"glu.h"を多重定義する事なくインクルード出来る。
======
--*/


#include "canvaswidget.h"
CanvasWidget::CanvasWidget(QWidget *parent, const char *name) : QGLWidget(parent){}

void CanvasWidget::initializeGL(){
    int width = geometry().width();
    int height = geometry().height();
    /*------
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-width *0.5, width*0.5, -height* 0.5, height* 0.5, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
   */
}
void CanvasWidget::resizeGL( int width, int height ){
    glViewport(0,0,width,height);
}
void CanvasWidget::paintGL(){
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor4f(1.0f,0.0f,0.0f,1.0f);
    glBegin(GL_TRIANGLES);
      glVertex3f( -100.0f, 100.0f, 0.0f);
      glVertex3f(-100.0f,-100.0f, 0.0f);
      glVertex3f( 100.0f,-100.0f, 0.0f);
    glEnd();
}
