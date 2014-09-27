/*
 *  picker.c
 */


#include <GLUT/glut.h>

#define MAXCEL 9
int sz=10 ;
int llflag=1, urflag=1 ;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    
    int j, i;
    

    for(j=0; j<5; ++j)
    {
        
        for(i=0;i<5; ++i)
        {
            glTranslatef((float)i*.3,(float)j*.3, 0.0);
            
            glBegin(GL_POLYGON);
            glVertex2f(-0.7, -0.7);
            glVertex2f(-0.7, -0.5);
            glVertex2f(-0.5, -0.5);
            glVertex2f(-0.5, -0.7);
            
            glEnd();
            glLoadIdentity();
            glFlush();
        }
        
        
    }

    
	glFlush();
}


void init() {
    int ii, jj ;
    
    /* set clear color to black */
    
    glClearColor (0.0, 0.0, 0.0, 0.0);
    /* set fill  color to red */
    
    glColor3f(0.0, 0.0, 1.0);
    
    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
    
}

void maus(int btn, int state, int x, int y) {
    int ix, iy, ny ;
    int ii, jj ;
    
    ny = 500-y ;
    
    glColor3f(1.0, 0.0, 0.0);
    
    if (btn==GLUT_LEFT_BUTTON  && state == GLUT_DOWN) {
        printf("%d %d\n", x, y) ;
        if (x<200 && ny<200) llflag = !llflag ;
        if (llflag) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2i(0,0);
        glVertex2i(0,200);
        glVertex2i(200,200);
        glVertex2i(200,0);
        glEnd();
        
        
        if (x>300 && ny>300) urflag = !urflag ;
        if (urflag) glColor3f(0.0, 0.0, 1.0);
        else glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2i(300,300);
        glVertex2i(300,500);
        glVertex2i(500,500);
        glVertex2i(500,300);
        glEnd();
    }
    glFlush();
}

int main(int argc, char** argv)
{
    
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
    
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("mouse test");
    init();
    glutMouseFunc(maus) ;
	glutDisplayFunc(display);
	glutMainLoop();
    
}
