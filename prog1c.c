#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


#define MAXPOINTS 100          /* 記憶する点の数 */
GLint point[MAXPOINTS] [2];    /* 座標を記録する配列 */
int pointnum = 0;              /* 記憶した座標の数 */
int rubberband = 0;            /* ラバーバンドの消去 */

void display(void)
{
  int i;

  glClear(GL_COLOR_BUFFER_BIT);

  /* 記録したデータで線を描く */
  if(pointnum > 1){
    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (i = 0; i < pointnum; ++i){
      glVertex2iv(point[i]);
    }
    glEnd();
  }
  glFlush();
}

void resize(int w, int h)
{
  /* ウィンドウ全体をビューポートにする */
  glViewport(0, 0, w, h);

  /* 変換行列の初期化 */
  glLoadIdentity();

  /* スクリーン上の座標系をマウス座標系と一致させる */
  glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
  switch(button){
  case GLUT_LEFT_BUTTON:
  /* ボタンを操作した位置の記録 */
    point[pointnum][0] = x;
    point[pointnum][1] = y;

    if (state == GLUT_UP) {
    /* ボタンを押した位置から離した位置まで線を引く */
      glColor3d(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex2iv(point[pointnum -1]); /* 一つ前は押した位置 */
      glVertex2iv(point[pointnum]); /* 今の位置は離した位置 */
      glEnd();
      glFlush();

      /* マウスを動かしていない場合はラバーバンドの消去をしない */
      rubberband = 0;
    }
    else {
    }
    if (pointnum < MAXPOINTS -1) ++pointnum;
    break;
  case GLUT_MIDDLE_BUTTON:
    
    break;
  case GLUT_RIGHT_BUTTON:
    
    break;
  default:
    break;
  }
}

void motion (int x, int y)
{
  static GLint savepoint[2];    /* 以前のラバーバンドの端点 */
  
  /* 論理演算機能 ON */
  glEnable(GL_COLOR_LOGIC_OP);
  glLogicOp(GL_INVERT);

  glBegin(GL_LINES);
  if(rubberband) {
  /* 以前のラバーバンドを消す */
  glVertex2iv(point[pointnum -1]);
  glVertex2iv(savepoint);
  }
  /* 新規ラバーバンドの描画 */
  glVertex2iv(point[pointnum -1]);
  glVertex2i(x, y);
  glEnd();

  glFlush();

  /* 論理演算機能 OFF */
  glLogicOp(GL_COPY);
  glDisable(GL_COLOR_LOGIC_OP);

  /* 描画したラバーバンドの端点を記録 */
  savepoint[0] = x;
  savepoint[1] = y;

  /* 描画したラバーバンドを次のタミングで消す */
  rubberband = 1;
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':  /* '\033' は escキーを表す ASCIIコード */
    exit(0);
  default:
    break;
  }
}


void init(void)
{
  glClearColor(0.8392, 0.9137, 0.7924, 1.0);
}

int main(int argc, char *argv[])
{
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640,480);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
