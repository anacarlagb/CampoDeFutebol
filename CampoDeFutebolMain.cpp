#include <GL/gl.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
using namespace std;

/*
    Instituto de Computacao - UFAL
    Disciplina: Computacao Grafica - Campo de Futebol
    Alunas: Ana Carla Gomes Bibiano
            Laysa de Paula Silva
    Referencias: 
        * Menu (glMenu) - http://www.cprogramming.com/snippets/source-code/a-code-template-for-opengl-divide-glut
        * Algoritmo Simples de Rasterizacao -http://webserver2.tecgraf.puc-rio.br/~mgattass/cg/pdf/06A_RasterizacaoPPT.pdf

*/
        
GLint winWidth = 400, winHeight = 300;
int x1Arq = 0, y1Arq = 0, x2Arq = 0, y2Arq = 0;

void desenhaCampoBresenham(void);
void desenhaCampoSimples(void);

void desenhaLinhaHorizontalBresenham (int x1, int y1, int x2, int y2);
void desenhaLinhaVerticalBresenham (int x1, int x2, int y1, int y2);

void desenhaLinhaHorizontalSimples (int x1, int y1, int x2, int y2);
void desenhaLinhaVerticalSimples (int x1, int x2, int y1, int y2);

void desenhaCirculo(int r, int x1, int y1);
void desenhaCirculoCanto1(int r, int x1, int y1);
void desenhaCirculoCanto2(int r, int x1, int y1);
void desenhaCirculoCanto3(int r, int x1, int y1);
void desenhaCirculoCanto4(int r, int x1, int y1);

void desenhaPontosDoCirculo(int x1, int y1, int x, int y);
void desenhaPontosDoCirculoCanto1(int x1, int y1, int x, int y);
void desenhaPontosDoCirculoCanto2(int x1, int y1, int x, int y);
void desenhaPontosDoCirculoCanto3(int x1, int y1, int x, int y);
void desenhaPontosDoCirculoCanto4(int x1, int y1, int x, int y);

void menu(int op);
void menuArq(int op);

void init(void){
    glClearColor(0.0, 1.0, .0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0.0, 1050.0, 0.0, 650.0, -1.0, 1.0);
}

 
/* executed when a regular key is pressed */
void keyboardDown(unsigned char key, int x, int y) {
 
  switch(key) {
  case 'q':
  case  27:   // ESC
    exit(0);
  }
}
 
/* executed when a regular key is released */
void keyboardUp(unsigned char key, int x, int y) {
 
}
 
/* executed when a special key is pressed */
void keyboardSpecialDown(int k, int x, int y) {
 
}
 
/* executed when a special key is released */
void keyboardSpecialUp(int k, int x, int y) {
 
}
 
/* reshaped window */
void reshape(int width, int height) {
 
  GLfloat fieldOfView = 90.0f;
  glViewport (0, 0, (GLsizei) width, (GLsizei) height);
 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fieldOfView, (GLfloat) width/(GLfloat) height, 0.1, 500.0);
 
  glMatrixMode(GL_MODELVIEW);
  // glLoadIdentity();
}
 
/* executed when button 'button' is put into state 'state' at screen position ('x', 'y') */
void mouseClick(int button, int state, int x, int y) {
 
}
 
/* executed when the mouse moves to position ('x', 'y') */
void mouseMotion(int x, int y) {
 
}
 
/* render the scene */
void draw() {
 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
  /* render the scene here */
 
  glFlush();
  glutSwapBuffers();
}
 
/* executed when program is idle */
void idle() { 
 
}
 

void plotPoint(GLint x, GLint y){
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
}

void winReshapeFcn (GLint newWidth, GLint newHeight){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight), -1.0, 1.0);

    winWidth = newWidth;
    winHeight = newHeight;

}

void mousePtPlotSimples (GLint button, GLint action, GLint xMouse, GLint yMouse){

    if(x1Arq == 0 && y1Arq == 0){ //se for 1o clique - ponto inicial
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
            x1Arq = xMouse;
            y1Arq = winHeight - yMouse;
            plotPoint (x1Arq, y1Arq);
        }
    }
    else
        if(x2Arq == 0 && y2Arq == 0){ //se for 2o clique - ponto final
            if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
            x2Arq = xMouse;
            y2Arq = winHeight - yMouse;
            plotPoint (x2Arq, y2Arq);
            desenhaLinhaHorizontalSimples (x1Arq, y1Arq, x2Arq, y2Arq); 
            x1Arq =0, y1Arq = 0, x2Arq = 0, y2Arq = 0;
        }
    }

    glFlush();
}
void mousePtPlotBresenham (GLint button, GLint action, GLint xMouse, GLint yMouse){

    if(x1Arq == 0 && y1Arq == 0){ //se for 1o clique - ponto inicial
        if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
            x1Arq = xMouse;
            y1Arq = winHeight - yMouse;
            plotPoint (x1Arq, y1Arq);
        }
    }
    else
        if(x2Arq == 0 && y2Arq == 0){ //se for 2o clique - ponto final
            if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
            x2Arq = xMouse;
            y2Arq = winHeight - yMouse;
            plotPoint (x2Arq, y2Arq);
            
        }
    }

    glFlush();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1050,650);
	glutInitWindowPosition(25, 25);
	glutCreateWindow("Campo de Futebol - Para desenhar a Arquibancada clique nos pontos primeiro.");
	init();
   
    // register glut call backs
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(keyboardSpecialDown);
    glutSpecialUpFunc(keyboardSpecialUp);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    glutIgnoreKeyRepeat(true); // ignore keys held down

    // create a sub menu 
    int subMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Algoritmo Simples",'s');
    glutAddMenuEntry("Algoritmo Bresenham", 'b');

    int subMenuArq = glutCreateMenu(menuArq);
    glutAddMenuEntry("Algoritmo Simples", 's');
    glutAddMenuEntry("Algoritmo Bresenham", 'b');
   
    // create main "right click" menu
    glutCreateMenu(menu);
    glutCreateMenu(menuArq);
    glutAddSubMenu("Campo De Futebol", subMenu);
    glutAddSubMenu("Arquibancada", subMenuArq);
    glutAddMenuEntry("Quit", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutReshapeFunc(winReshapeFcn);
    glutMouseFunc(mousePtPlotBresenham);
   
    glutMainLoop();
	return 0;

}

void menu(int op) {
 
 if(op == 's'){
    desenhaCampoSimples();
 }
 if(op == 'b'){
    desenhaCampoBresenham();
 }
 if(op == 'q'){
    exit(0);
  }
}

void menuArq(int op) {
 
 if(op == 's'){
    desenhaLinhaHorizontalSimples (x1Arq, y1Arq, x2Arq, y2Arq);
    x1Arq =0, y1Arq = 0, x2Arq = 0, y2Arq = 0; 
 }
 if(op == 'b'){
    desenhaLinhaHorizontalBresenham (x1Arq, y1Arq, x2Arq, y2Arq); 
    x1Arq =0, y1Arq = 0, x2Arq = 0, y2Arq = 0;
 }
 if(op == 'q'){

    exit(0);
  }
}
void desenhaCampoSimples(void){
  glClear (GL_COLOR_BUFFER_BIT);
        desenhaLinhaHorizontalSimples(100, 100, 1000, 100);
        desenhaLinhaHorizontalSimples (100, 550, 1000, 550);
        desenhaLinhaVerticalSimples(100,100,100,550);
        desenhaLinhaVerticalSimples(1000,1000,100,550);
        desenhaLinhaVerticalSimples(550,550,100,550);
        desenhaLinhaHorizontalSimples(100, 250, 180, 250);
        desenhaLinhaHorizontalSimples(100, 400, 180, 400);
        desenhaLinhaHorizontalSimples(100, 250, 180, 250);
        desenhaLinhaHorizontalSimples(100, 250, 180, 250);
        desenhaLinhaHorizontalSimples(920, 250, 1000, 250);
        desenhaLinhaHorizontalSimples(920, 400, 1000, 400);
        desenhaLinhaVerticalSimples(180,180,250,400);
        desenhaLinhaVerticalSimples(920,920,250,400);
        desenhaLinhaHorizontalSimples(100, 175, 280, 175);
        desenhaLinhaHorizontalSimples(100, 475, 280, 475);
        desenhaLinhaHorizontalSimples(820, 175, 1000, 175);
        desenhaLinhaHorizontalSimples(820, 475, 1000, 475);
        desenhaLinhaVerticalSimples(280,280,175,475);
        desenhaLinhaVerticalSimples(820,820,175,475);
        desenhaLinhaHorizontalSimples(60, 287, 100, 287);
        desenhaLinhaHorizontalSimples(60, 363, 100, 363);
        desenhaLinhaHorizontalSimples(1000, 287, 1040, 287);
        desenhaLinhaHorizontalSimples(1000, 363, 1040, 363);
        desenhaLinhaVerticalSimples(60,60,287,363);
        desenhaLinhaVerticalSimples(1040,1040,287,363);

        desenhaCirculo(60, 550, 325);
        desenhaCirculoCanto1(25, 100, 550);
        desenhaCirculoCanto2(25, 1000, 550);
        desenhaCirculoCanto3(25, 100, 100);
        desenhaCirculoCanto4(25, 1000, 100);

    glFlush();
}
void desenhaCampoBresenham(){
      glClear (GL_COLOR_BUFFER_BIT);
    desenhaLinhaHorizontalBresenham(100, 100, 1000, 100);
    desenhaLinhaHorizontalBresenham (100, 550, 1000, 550);
    desenhaLinhaVerticalBresenham(100,100,100,550);
    desenhaLinhaVerticalBresenham(1000,1000,100,550);
    desenhaLinhaVerticalBresenham(550,550,100,550);
    desenhaLinhaHorizontalBresenham(100, 250, 180, 250);
    desenhaLinhaHorizontalBresenham(100, 400, 180, 400);
    desenhaLinhaHorizontalBresenham(100, 250, 180, 250);
    desenhaLinhaHorizontalBresenham(100, 250, 180, 250);
    desenhaLinhaHorizontalBresenham(920, 250, 1000, 250);
    desenhaLinhaHorizontalBresenham(920, 400, 1000, 400);
    desenhaLinhaVerticalBresenham(180,180,250,400);
    desenhaLinhaVerticalBresenham(920,920,250,400);
    desenhaLinhaHorizontalBresenham(100, 175, 280, 175);
    desenhaLinhaHorizontalBresenham(100, 475, 280, 475);
    desenhaLinhaHorizontalBresenham(820, 175, 1000, 175);
    desenhaLinhaHorizontalBresenham(820, 475, 1000, 475);
    desenhaLinhaVerticalBresenham(280,280,175,475);
    desenhaLinhaVerticalBresenham(820,820,175,475);
    desenhaLinhaHorizontalBresenham(60, 287, 100, 287);
    desenhaLinhaHorizontalBresenham(60, 363, 100, 363);
    desenhaLinhaHorizontalBresenham(1000, 287, 1040, 287);
    desenhaLinhaHorizontalBresenham(1000, 363, 1040, 363);
    desenhaLinhaVerticalBresenham(60,60,287,363);
    desenhaLinhaVerticalBresenham(1040,1040,287,363);

    desenhaCirculo(60, 550, 325);

    desenhaCirculoCanto1(25, 100, 550);
    desenhaCirculoCanto2(25, 1000, 550);
    desenhaCirculoCanto3(25, 100, 100);
    desenhaCirculoCanto4(25, 1000, 100);

    glFlush();
}



//Desenha linhas horizontais
void desenhaLinhaHorizontalBresenham (int x1, int y1, int x2, int y2){

    int dx, dy, incE, incNE, d, x, y, xFim, slope;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    d = 2*dy - dx; //Valor inicial do d

    incE = 2*dy; //Incremento do E
    incNE = 2 * (dy - dx);//Incremento do NE

    //Onde inverte a linha x1>x2
    if (x1>x2){
        //desenhaLinhaHorizontalBresenham (x2, y2, x1, y1);
        //return;
        x=x2;
        y=y2;
        xFim = x1;
    }
    else{
        x=x1;
        y=y1;
        xFim = x2;
    }

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
        glVertex2d(x, y);
    glEnd();

    while(x <xFim){

        x++;
        if (d<0){
            d+= incE;
        }
        else{
            y++;
            d+= incNE;
        }
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_POINTS);
            glVertex2d(x, y);
        glEnd();

    }
}

//Desenha linhas verticais
void desenhaLinhaVerticalBresenham (int x1, int x2, int y1, int y2){

    int dx, dy, incE, incNE, d, x, y;
    dx = x2 - x1;
    dy = y2 - y1;
    d = 2*dy - dx; //Valor inicial do d
    incE = 2*dy; //Incremento do E
    incNE = 2 * (dy - dx);//Incremento do NE
    x=x1;
    y=y1;

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
        glVertex2d(x, y);
    glEnd();

    while (y<=y2){

        if (d<=0){
            //Escolhe E
            d = d+ incE;
            x = x+1;
            y = y+1;
        }
        else{
            //Escolhe NE
            d = d + incNE;
            y = y+1;
        }
        glColor3f(0.0,0.0,0.0);
        glBegin(GL_POINTS);
            glVertex2d(x, y);
        glEnd();
    }


}


void desenhaLinhaHorizontalSimples (int x1, int y1, int x2, int y2){
        float m = (y2-y1)/(x2-x1); // enclinacao da reta igual a zero
        float b = y1 - m*x1;
        float y;
        glColor3f(0.0,0.0,0.0);
            glBegin(GL_POINTS);
               glVertex2d(x1, y);
            glEnd();
        while( x1 < x2 ){
                x1++; // x1 eh o proximo
                y = m*x1 + b;  // b=y1
                  glColor3f(0.0,0.0,0.0);
                  glBegin(GL_POINTS);
                    glVertex2d(x1, y); // y sempre ta sendo y1 e x1 vai pra o proximo
                  glEnd();
        }


}

void desenhaLinhaVerticalSimples (int x1, int x2, int y1, int y2){        
        
        float m = (x2-x1)/(y2-y1);  //inclinacao = 0
        float b = x1 - m*y1; //x1
        float x;
        glColor3f(0.0,0.0,0.0);
            glBegin(GL_POINTS);
               glVertex2d(x, y1);
            glEnd();
        while( y1 < y2 ){ 
                y1++; // y1 é o proximo
                x = x1 - m*y1;
                  glColor3f(0.0,0.0,0.0);
                  glBegin(GL_POINTS);
                    glVertex2d(x, y1);
                  glEnd();
        }

}

void desenhaCirculo(int r, int x1, int y1){

    int x=0;
    int y=r;
    int d= 1-r;

    void desenhaPontosDoCirculo(int, int, int, int);

    //Desenha o primeiro ponto do círculo
    desenhaPontosDoCirculo(x1, y1, x, y);

    while(x<y){
        x++;
        if(d<0){
            d+= 2*x+1;
        }
        else{
            y--;
            d+= 2*(x-y)+1;
        }
        desenhaPontosDoCirculo(x1, y1, x, y);
    }

}

void desenhaCirculoCanto1(int r, int x1, int y1){

    int x=0;
    int y=r;
    int d= 1-r;

    void desenhaPontosDoCirculoCanto1(int, int, int, int);

    //Desenha o primeiro ponto do círculo
    desenhaPontosDoCirculoCanto1(x1, y1, x, y);

    while(x<y){
        x++;
        if(d<0){
            d+= 2*x+1;
        }
        else{
            y--;
            d+= 2*(x-y)+1;
        }
        desenhaPontosDoCirculoCanto1(x1, y1, x, y);
    }

}


void desenhaCirculoCanto2(int r, int x1, int y1){

    int x=0;
    int y=r;
    int d= 1-r;

    void desenhaPontosDoCirculoCanto2(int, int, int, int);

    //Desenha o primeiro ponto do círculo
    desenhaPontosDoCirculoCanto2(x1, y1, x, y);

    while(x<y){
        x++;
        if(d<0){
            d+= 2*x+1;
        }
        else{
            y--;
            d+= 2*(x-y)+1;
        }
        desenhaPontosDoCirculoCanto2(x1, y1, x, y);
    }

}

void desenhaCirculoCanto3(int r, int x1, int y1){

    int x=0;
    int y=r;
    int d= 1-r;

    void desenhaPontosDoCirculoCanto3(int, int, int, int);

    //Desenha o primeiro ponto do círculo
    desenhaPontosDoCirculoCanto3(x1, y1, x, y);

    while(x<y){
        x++;
        if(d<0){
            d+= 2*x+1;
        }
        else{
            y--;
            d+= 2*(x-y)+1;
        }
        desenhaPontosDoCirculoCanto3(x1, y1, x, y);
    }

}

void desenhaCirculoCanto4(int r, int x1, int y1){

    int x=0;
    int y=r;
    int d= 1-r;

    void desenhaPontosDoCirculoCanto4(int, int, int, int);

    //Desenha o primeiro ponto do círculo
    desenhaPontosDoCirculoCanto4(x1, y1, x, y);

    while(x<y){
        x++;
        if(d<0){
            d+= 2*x+1;
        }
        else{
            y--;
            d+= 2*(x-y)+1;
        }
        desenhaPontosDoCirculoCanto4(x1, y1, x, y);
    }

}

void desenhaPontosDoCirculo(int x1, int y1, int x, int y){

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + x, y1 + y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - x, y1 + y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + x, y1 - y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - x, y1 - y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + y, y1 + x);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - y, y1 + x);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + y, y1 - x);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - y, y1 - x);
    glEnd();

}

void desenhaPontosDoCirculoCanto1(int x1, int y1, int x, int y){

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + x, y1 - y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + y, y1 - x);
    glEnd();

}

void desenhaPontosDoCirculoCanto2(int x1, int y1, int x, int y){

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - x, y1 - y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - y, y1 - x);
    glEnd();


}

void desenhaPontosDoCirculoCanto3(int x1, int y1, int x, int y){

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + x, y1 + y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 + y, y1 + x);
    glEnd();


}

void desenhaPontosDoCirculoCanto4(int x1, int y1, int x, int y){

    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - x, y1 + y);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POINTS);
    glVertex2d(x1 - y, y1 + x);
    glEnd();

}