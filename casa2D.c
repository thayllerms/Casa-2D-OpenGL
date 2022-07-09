#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float posX=0.0,posY=0.0,posZ=0.0;
float transX=0.0,transY=0.0,transZ=0.0;
GLsizei rsize = 50;

void movimento(int key,int x,int y){
    //Movimento
    switch (key){
        //movimento para direita
        case GLUT_KEY_RIGHT:
          posY += 0.5;
        break;
        //movimento para esquerda.
        case GLUT_KEY_LEFT:
          posY -= 0.5;
        break;
        //identifica o movimento para cima
        case GLUT_KEY_UP:
          posX += 0.5;
        break;
        //identifica o movimento para baixo.
        case GLUT_KEY_DOWN:
          posX -= 0.5;
        break;

        case GLUT_KEY_F1:
          transZ += 0.5;
        break;

        case GLUT_KEY_F2:
          transZ -= 0.5;
        break;

        case GLUT_KEY_F3:
          transY += 0.5;
        break;

        case GLUT_KEY_F4:
          transY -= 0.5;
        break;

        case GLUT_KEY_F5:
          transX += 0.5;
        break;

        case GLUT_KEY_F6:
          transX -= 0.5;
        break;

        case GLUT_KEY_F7:
          transX = 0.0;
          transY = 0.0;
          transZ = 0.0;
        break;

        default:
         break;
    }
    glutPostRedisplay();
}

void desenha () {

  if (posX==360)
    posX=0;

  if (posY==360)
      posY=0;

   /* clear window */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* future matrix manipulations should affect the modelview matrix */
//    glMatrixMode(GL_MODELVIEW);
  float t;
  
//Quadrado em baixo do telhado Triangular
	glBegin(GL_QUADS);
  	glColor3f(1.0f, 1.0f, 0.7f); 
		glVertex2f(0.5f,-1.0f);
		glVertex2f(0.5f,  0.0f);       
		glVertex2f( 0.0f,  0.0f);       
		glVertex2f( 0.0f, -2.0f);
	glEnd();

glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // vermelho
        glVertex2f(-0.2f,0.37f);
        glVertex2f( 0.2f,0.36f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(-0.45, 0.0);
    glEnd();

//Retangulo maior
  glBegin(GL_QUADS);
  	glColor3f(0.0f, 0.0f, 1.0f); 
		glVertex2f(-0.45f,-1.5f);
		glVertex2f(-0.45f,  0.0f);       
		glVertex2f( 0.0f,  0.0f);       
		glVertex2f( 0.0f,-1.5f);       
	glEnd();

  
	glBegin(GL_LINES);
  	glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(-0.445,0.0);
    glVertex2f(0.4,2.0);
  glEnd();

	glBegin(GL_LINES);
  	glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,-5.0);
  glEnd();

// Porta
    glBegin(GL_QUAD_STRIP);
    	glColor3f(0.7f, 0.8f, 0.5f); 
      glVertex2f(0.4, -6); //y direita baixo x inclinação direita da porta
      glVertex2f(10, -0.4); // y altura meio x lateral
      glVertex2f(0.4, -0.5); //x esquerda y profundidade do meio
      glVertex2f(0.1, -4);
      glVertex2f(0, -0.5); //linha diferente em cima
      glVertex2f(0.1, -0.5); //altura certa da porta em y
    glEnd();

    glPushMatrix();
        //movimentos de rotacao e translacao
        glRotatef(posX,1.0,0.0,0.0);
        glRotatef(posY,0.0,1.0,0.0);
        glTranslatef(transX, transY, transZ);
		
        //desenha a base da casa.
        glPushMatrix();
            glScalef(1.0, 1.0, 2.0);
            glutSolidCube(2);
        glPopMatrix(); 

    glPopMatrix();
    

    glBegin(GL_POLYGON); // Primitiva para desenhar um polígono
      	glColor3f(1.0f, 1.0f, 0.0f); 
        glVertex2f( 0.0f, 0.0f);  // define o primeiro vértice do polígono
        glVertex2f( 0.2f, 0.37f); // define o segundo vértice do polígono
        glVertex2f( 0.50f, 0.0f); // define o terceiro vértice do polígono
    glEnd();  

  glColor3f(0.0f, 0.0f, 1.0f);  
    //Janela Redonda
    glBegin(GL_POLYGON);
      glColor3f(0.0f, 1.0f, 0.0f);  
      for(int i = 0; i < 360; i++){
        t = i*3.142/180;
        glVertex2f(0.23+(0.08*cos(t)), (0.12+(-0.1*(sin(t))))); 
      }
    glEnd();
    //janela da frente
    glBegin(GL_QUADS);
      glColor3f(0.0f, 1.0f, 1.0f); // verde
      glVertex2f(0.15,-0.1);
      glVertex2f(0.35, -0.1); //X vai pras laterais y é a altura 
      glVertex2f(0.35, -0.3); //x é a borda de baixo direita y parece ser altura
      glVertex2f(0.15, -0.3);
    glEnd();

    /* flush drawing routines to the window */
    glFlush();
}

void inicializar(){

    // set up depth-buffering 
    glEnable(GL_DEPTH_TEST);

    // define the projection transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //FovY, Aspect, zNear, ZFar
    gluPerspective(45,1,4,20);

    // define the viewing transformation 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	// eyeX, eyeY, eyeZ
	// Especifica a posicao do olho. Câmera
	//
	// centerX, centerY, centerZ
	// Especifica a posicao do ponto de referencia. Para onde a câmera aponta.
	//
	// upX, upY, upZ
	// Especifica a direção do vetor "Cima". Geralmente, Y.
    gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
} 

int main ( int argc, char * argv[] ) {

    /* initialize GLUT, using any commandline parameters passed to the
       program */
    glutInit(&argc,argv);

    /* setup the size, position, and display mode for new windows */
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH);
    /* create and set up a window */
    glutCreateWindow("Casinha 2D");
    glutDisplayFunc(desenha);
//    inicializar();
    glutSpecialFunc(movimento);
    glutMainLoop();
}
