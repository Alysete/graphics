//
//  main.c
//  MineSweeper
//
//  Created by Alyssa Silver on October/9/2013.
//  Copyright (c) 2013 Alyssa Silver. All rights reserved.
//

#include <stdio.h>
#include <GLUT/glut.h>
#include <string.h>


int flags[20][20];
int mines[20][20];
int minerow;
int minecol;
int nummines;



void display(void)
{
	int i;
	int j;
    
	while(nummines < 20)
	{
		minerow = rand() % 20;
		minecol = rand() % 20;
		
		if(mines[minerow][minecol] == 0)
		{
			mines[minerow][minecol] = 1;
			nummines++;
            
		}
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	for(i = 0; i < 20; i++)
	{
		
		for(j = 0; j < 20; j++)
		{
			if(flags[i][j] == 1)
			{
				
				if(mines[i][j] == 1)
				{
					glColor3f(1.0, 0.0, 0.0);
				}
				else
				{
					glColor3f(0.5, 0.8, 0.2);
				}
				
			}
			else
			{
				glColor3f(0.1, 0.1, 0.1);
			}
            glTranslatef((float)j * .1, (float)i * .1, 0.0);
            glBegin(GL_POLYGON);
            glVertex2f(-1.0, -1.0);
            glVertex2f(-1.0, -0.9);
            glVertex2f(-0.9, -0.9);
            glVertex2f(-0.9, -1.0);
            glEnd();
            glColor3f(0.5, 0.5, 0.5);
            glBegin(GL_LINE_LOOP);
            glVertex2f(-1.0, -1.0);
            glVertex2f(-1.0, -0.9);
            glVertex2f(-0.9, -0.9);
            glVertex2f(-0.9, -1.0);
            glEnd();
            glLoadIdentity();
            glFlush();
            
		}
        
	}
}


void init() {
    
    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */
    
    /* glMatrixMode (GL_PROJECTION);
     glLoadIdentity ();
     glOrtho(0.0, 500.0, 0.0, 500.0, -10.0, 10.0);
     glViewport(0,0,500,500) ;*/
    
    
}

void maus(int btn, int state, int x, int y) {
    int matx, maty, ny, i, j ;
    char nc[1];
    ny = 500-y;
    
    glColor3f(1.0, 0.0, 0.0);
    
    if (btn==GLUT_LEFT_BUTTON  && state == GLUT_DOWN) {
		printf("X:%d Y:%d\n", x, ny) ;
        matx = x / 25;
		maty = ny / 25;
		printf("Row:%d Column:%d\n", maty, matx);
		flags[maty][matx] = 1;
		display();
		
        
    /*if (clicked[i][j]) {
        glColor3f(0.0,0.0,0.0);
        sprintf(nc,"%d", neighbor[i][j]) ;
        glRasterPos2i(i*(minerow)+sz/2,j*(minecol)+sz/2);
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, nc[0]); }*/

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
        glutCreateWindow("MineSweeper");
        init();
        glutMouseFunc(maus) ;
        glutDisplayFunc(display);
        glutMainLoop();
        
    }

    
    

