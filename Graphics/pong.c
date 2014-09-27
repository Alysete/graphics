/*
 *  pong.c
 *  This program plays the classic game PONG
 */

#include <curses.h>
#include <math.h>
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>


float rad=0.05 ; /* ball size */
float xc=-.6, yc=.8, xv=0.5 , yv=-0.3; /* ball position */
float pl=0.15, pw=0.06 ; /* paddle length, width */
float lpx=-0.9, lpy=0.0, rpx = 0.9, rpy=0.0 ; /* paddle positions */
float dt = 0.001, damp = 1.0 ;
float degrees, angle ;
int n=360 ;
float lpv = 0.0, pv=0.4, rpv=0.0 ;

int sgn(float norp) {
 if (norp<0.0) return (-1) ;
  else return (1) ;
}

void init()
{

/* set clear color to black */

      glClearColor (0.0, 0.0, 0.0, 0.0); 
/* set fill  color to white */

      glColor3f(1.0, 1.0, 1.0); 

        glLoadIdentity ();
        glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  
}


void display() {

int k ;

glClear(GL_COLOR_BUFFER_BIT) ;
glColor3f(1.0, 1.0, 1.0);
glBegin(GL_POLYGON) ;
 for (k=0 ; k<n ; ++k) {
 angle = 3.14159*(degrees+(360/n)*k)/180.0 ;
 glVertex2f(rad*cos(angle)+xc, rad*sin(angle)+yc) ;
 }
glEnd() ;

glBegin(GL_POLYGON) ;
 glVertex2f(lpx-pw, lpy-pl) ;
 glVertex2f(lpx-pw, lpy+pl) ;
 glVertex2f(lpx+pw, lpy+pl) ;
 glVertex2f(lpx+pw, lpy-pl) ;
glEnd() ;

glBegin(GL_POLYGON) ;
 glVertex2f(rpx-pw, rpy-pl) ;
 glVertex2f(rpx-pw, rpy+pl) ;
 glVertex2f(rpx+pw, rpy+pl) ;
 glVertex2f(rpx+pw, rpy-pl) ;
glEnd() ;

glFlush() ;
glutSwapBuffers() ;
}

void idle() {
float dyl, dyr ;
float lpcx,lplcy,lpucy ; /* left paddle x corner, lower and upper y corners */
float rpcx,rplcy,rpucy ; /* right paddle x corner, lower and upper y corners */
  xc += xv*dt ;  yc += yv*dt ;
  dyl = lpy-yc ;
  dyr = rpy-yc ;

  lpcx=lpx+pw ; lplcy =lpy-pl ; lpucy=lpy+pl ; /* left paddle corners */
  rpcx=rpx-pw ; rplcy =rpy-pl ; rpucy=rpy+pl ; /* right paddle corners */

  if ( ( (xc-lpcx)*(xc-lpcx)+(yc-lplcy)*(yc-lplcy) <= rad*rad ) ||
  ( (xc-lpcx)*(xc-lpcx)+(yc-lpucy)*(yc-lpucy) <= rad*rad ) ||
  ( (xc-rpcx)*(xc-rpcx)+(yc-rplcy)*(yc-rplcy) <= rad*rad )  ||
  ( (xc-rpcx)*(xc-rpcx)+(yc-rpucy)*(yc-rpucy) <= rad*rad ) ) 
   { xv *= -1 ; yv *= -1 ; }
  
  if ((xc<rad+pw+lpx)&&(fabs(dyl)<pl))  xv=fabs(xv) ;
  if ((xc>rpx-rad-pw)&&(fabs(dyr)<pl)) {
   xv=-fabs(xv) ;
   rpv=0.0 ; }

  if ((xc<lpx+pw)&&(fabs(lpy-yc)<pl+rad)) yv *=-1 ;
  if ((xc>rpx-pw)&&(fabs(rpy-yc)<pl+rad)) yv *=-1 ;
  
  if(xc<=rad-1.0) xv*=-damp ;
  if(xc>=1.0-rad) xv*=-damp ;
  if(yc<=rad-1.0) yv*=-damp ;
  if(yc>=1.0-rad) yv*=-damp ;

  lpy += lpv*dt ;
  if (xv<0) rpv=0 ;
  if (xv>0) rpv = pv*sgn(yc-rpy) ;

  rpy += rpv*dt ;
  if (fabs(fabs(lpy)+pl)>0.95) lpv=0.0 ;


  glutPostRedisplay() ;
}

void keyb(unsigned char key, int xx, int yy) {

if (key=='q') lpv=pv ;
if (key=='a') lpv=0.0 ;
if (key=='z') lpv=-pv ;

}

int main(int argc, char** argv)
{

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);  
	glutInitWindowSize(900,800);
	glutInitWindowPosition(0,0); 
	glutCreateWindow("PONG!"); 
	glutKeyboardFunc(keyb);
        glutIdleFunc(idle) ;
	glutDisplayFunc(display);
        init() ;
	glutMainLoop();
     

}
