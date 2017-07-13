#include <GL/glut.h>
#include <stdlib.h>

double C256 (double d)
{
  return  d / 255;
}

GLdouble vertex[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 }
};

int face[][4] = {
  { 0, 1, 2, 3 }, /* A-B-C-D を結ぶ面 */
  { 1, 5, 6, 2 }, /* B-F-G-C を結ぶ面 */
  { 5, 4, 7, 6 }, /* F-E-H-G を結ぶ面 */
  { 4, 0, 3, 7 }, /* E-A-D-H を結ぶ面 */
  { 4, 5, 1, 0 }, /* E-F-B-A を結ぶ面 */
  { 3, 2, 6, 7 }  /* D-C-G-H を結ぶ面 */
};

GLdouble normal[][3] = {
  { 0.0, 0.0,-1.0 },
  { 1.0, 0.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  {-1.0, 0.0, 0.0 },
  { 0.0,-1.0, 0.0 },
  { 0.0, 1.0, 0.0 }
};

GLdouble color[][3] = {
  { 0.7176, 0.1568, 0.1803 }, /* 茜色 */
  { 0.7647, 0.8470, 0.1450 }, /* 若草色 */
  { 0.1647, 0.5137, 0.6352 }, /* 花浅葱 */
  { 0.0000, 0.9254, 0.2784 }, /* 菜の花色 */
  { 0.8039, 0.5490, 0.3607 }, /* 江戸茶 */
  { 0.6159, 0.3569, 0.5451 }, /* 京紫 */
};

int edge[][2] = {
  { 0, 1 },
  { 1, 2 },
  { 2, 3 },
  { 3, 0 },
  { 4, 5 },
  { 5, 6 },
  { 6, 7 },
  { 7, 4 },
  { 0, 4 },
  { 1, 5 },
  { 2, 6 },
  { 3, 7 }
};

GLfloat light0pos[] = { 0.0, 3.0, 5.0, 1.0 };
GLfloat light1pos[] = { 5.0, 3.0, 0.0, 1.0 };

GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };

void idle(void)
{
  glutPostRedisplay();
}

void display(void)
{
  int i;
  int j;

  static int r = 0; /* 回転角 */

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glLoadIdentity();

  /* 視点位置と視線方向 */
  gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  /* 光源の位置設定 */
  glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
  glLightfv(GL_LIGHT1, GL_POSITION, light1pos);


  /* 図形の回転 */
  glRotated((double)r, 0.0, 1.0, 0.0);

  /* 図形の描画 */
  glColor3d(0.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  for (j = 0; j < 6; ++j) {
    glNormal3dv(normal[j]);
    for(i = 0; i < 4; ++i){
      glVertex3dv(vertex[face[j][i]]);
    }
  }
  glEnd();

  glutSwapBuffers();

  /* 1週回ったら回転リセット */
  if (++r >= 360) r = 0;
}

void resize(int w, int h)
{
  glViewport(0, 0, w, h);

  /* 透視変換行列の設定 */
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
  
  /* モデルビュー変換行列の設定 */
  glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
  switch(button){
  case GLUT_LEFT_BUTTON:
    if (state == GLUT_DOWN){
      /* アニメーション開始 */
      glutIdleFunc(idle);
    }else{
      /* アニメーション停止 */
      glutIdleFunc(NULL);
    }
    break;
  case GLUT_RIGHT_BUTTON:
    if (state == GLUT_DOWN){
      /* コマ送り */
      glutPostRedisplay();
    }
    break;
    default:
    break;
  }
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
    case 'q':
    case 'Q':
    case '\033':
      exit(0);
    default:
      break;
  }
}


void init(void)
{
  glClearColor(0.75, 0.6328, 0.7773, 1.0); /* 薄葡萄 */

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, green);
  glLightfv(GL_LIGHT1, GL_SPECULAR, green);

}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow(argv[0]);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  init();
  glutMainLoop();
  return 0;
}
