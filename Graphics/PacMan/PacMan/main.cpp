//
//  pacman2.cpp
//  PacMan
//
//  Created by Alyssa Silver on November/12/2013.
//  Copyright (c) 2013 Alyssa Silver. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <GLUT/glut.h>
#include <string>
#include "Header.h"

//each direction is given a number to be referred to
#define LEFT 2
#define RIGHT 0
#define UP 3
#define DOWN 1
//speed is the boxsize / the set percentage of speed
#define SPEED bxsz/percentagespeed


//each wall is given a number like the directions, they correspond
#define RWALL 0
#define BWALL 1
#define LWALL 2
#define TWALL 3

//pacman stuff
float percentagespeed = 4; // how many times the pacman can move until it's in a new center.
float pi = 3.14159265359; // the equivalent of the first 18 digits of pi
float rpac = .07; //rpac=pacman's radius
float angle; //used to draw pacman and his mouth
int dd = LEFT; // desired direction
float dt = 0.002; //pacman speed
int dirpm = LEFT;//initial direction of pacman movement
int ctr; //count frames in idle >> for mouth movement
float limit = 25000; //limit number frames
float bxsz = .24; //box size .286
int mouthpm = 1; //pacman mouth starts open
int numboxx = 7; //num boxes x
int numboxy = 7; //num boxes y
float pospm[2] = {0, -(float)numboxy/2 *bxsz+bxsz/2}; //initial position of pacman
float vx = 0; //x velocity pacman
float vy = 0; //y velocity pacman
int pmctr =0; //to see if pm is in the center of a box
int score = 0; //initalized score
float rando;

//maze stuff

float psz = .01; //pellet size

float allowpmx; //where pacman is allowed to go (set up walls)
float allowpmy;
float yc; //y center of box
float xc; //x center of box


//defined walls of the maze
int drawmaze[7][7][4]=
{{{0,0,1,1},{0,1,0,1},{1,0,0,1},{1,1,1,1},{0,0,1,1},{0,1,0,1}, {1,0,0,1}},
    {{0,1,1,0},{0,0,0,1},{0,1,0,0},{0,0,0,1},{0,1,0,0},{0,0,0,1},{1,1,0,0}},
    {{0,0,1,1},{1,0,0,0},{0,0,1,1},{0,0,0,0},{1,0,0,1},{0,0,1,0},{1,0,0,1}},
    {{1,0,1,0},{0,0,1,0},{1,0,0,0},{1,1,1,0},{0,0,1,0},{1,0,0,0},{1,0,1,0}},
    {{0,1,1,0},{1,0,0,0},{0,0,1,0},{0,1,0,1},{1,0,0,0},{0,0,1,0},{1,1,0,0}},
    {{0,0,1,1},{1,1,0,0},{0,1,1,0},{0,0,0,1},{1,1,0,0},{0,1,1,0},{1,0,0,1}},
    {{0,1,1,0},{0,1,0,1},{0,1,0,1},{0,1,0,0},{0,1,0,1},{0,1,0,1},{1,1,0,0}}};


//defined where pellets are in the maze
int drawpellets [7][7]=
{{1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}};

//if i were to do the ghosts..
/*ghost stuff
 int gd; //current ghost dir
 float posg [2] = {0,0}; //starting ghost position
 int dirg = UP; //starting ghost direction
 float gspeed = .003; // ghost speed during game*/


void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
    drawman(dirpm, mouthpm);
    //to draw the maze and place the pellets
	for(int i = 0; i < numboxy; i++) //rows
	{
		for(int j = 0; j < numboxx; j++) //columns
		{
            glLoadIdentity();
            //glTranslatef((float)(j+1) * bxsz, (-(float)i * bxsz), 0.0);
            //glTranslatef(-(float)bxsz/2,(float)bxsz/2, 0.0);
            glTranslatef((((float)j) * bxsz)-numboxx/2*bxsz, -(float)i * bxsz+numboxy/2*bxsz, 0.0);
            glColor3f(0.5, 0.5, 0.5);
            if(drawpellets[j][i] == 1){
                glColor3f(1.0,0.0, 0.0);
                glBegin(GL_POLYGON);
                glVertex2f(-psz, psz);
                glVertex2f(-psz, -psz);
                glVertex2f(psz, -psz);
                glVertex2f(psz, psz);
                
                glEnd();
            }
            
            
            glLoadIdentity();
            // glTranslatef(((float)j * bxsz) +.25, -(float)i * bxsz, 0.0);
            glTranslatef((((float)j+1) * bxsz), -(float)i * bxsz, 0.0);
            
            float amt = 0;//bxsz*.1;
            
            glColor3f(0, 0, 1);
            //glFlush();
            if(drawmaze[i][j][RWALL]){
                glBegin(GL_LINES);
                glVertex2f(-((float)numboxx/2)*bxsz-amt, ((float)numboxy/2)*bxsz);//top right corner
                glVertex2f(-((float)numboxx/2)*bxsz-amt, (((float)numboxy/2)*bxsz)-bxsz); //bottom right corner
                glEnd();
            }
            if(drawmaze[i][j][BWALL]){
                glBegin(GL_LINES);
                glVertex2f(-((float)numboxx/2)*bxsz, (((float)numboxy/2)*bxsz)-bxsz+amt); //bottom right corner
                glVertex2f(-(((float)numboxx/2)*bxsz)-bxsz, (((float)numboxy/2)*bxsz)-bxsz+amt); //bottom leftcorner
                
                glEnd();
            }
            if(drawmaze[i][j][LWALL]){
                glBegin(GL_LINES);
                glVertex2f(-(((float)numboxx/2)*bxsz)-bxsz+amt, (((float)numboxy/2)*bxsz)-bxsz); //bottom leftcorner
                glVertex2f(-(((float)numboxx/2)*bxsz)-bxsz+amt, ((float)numboxy/2)*bxsz);//top left corner
                
                glEnd();
            }
            if(drawmaze[i][j][TWALL]){
                glBegin(GL_LINES);
                glVertex2f(-((float)numboxx/2)*bxsz, ((float)numboxy/2)*bxsz-amt);//top right corner
                glVertex2f(-(((float)numboxx/2)*bxsz)-bxsz, ((float)numboxy/2)*bxsz-amt);//top left corner
                
                glEnd();
            }
            
            glLoadIdentity();
            
		}
        
	}
    
    //Write Score
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(.5, .90);
    char txt[6];
    for(int i=0; i<6; i++){
        txt[i]=NULL;
    }
    
    std::string printscore = "Score: ";
    sprintf(txt, "%d",score);
    for(int s = 0; s<7; s++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, printscore[s]);
    }
    for(int i = 0; i<5; i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, txt[i]);
        
    }
    
    glFlush();
    glutSwapBuffers();

    
    
    glColor3f(0.4, 0.8, 0.4);
    glRasterPos2f(-.2,0);
    char winn [8];
    for(int j =0; j<8; j++){
        winn[j]=NULL;
    }
    std::string winner = "You Win!";
    if(score == 470){
        for(int win=0; win <9; win++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,winner[win]);
        }
    }
    glFlush();
    glutSwapBuffers();

}

void drawman(int dir, int mouth) //drawing pacman
{
    //for mouth
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for(int i=0; i<300; ++i){
        angle= 2*pi*(float(i)/300);
        glVertex2f(rpac*cos(angle)+pospm[0], rpac*sin(angle)+pospm[1]);
        
    }
    glEnd();
    
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(pospm[0], pospm[1]);
    for(int i=-20; i<20;++i){
        angle=-dir*pi/2 +mouth *i*pi/80;
        glVertex2f(rpac*cos(angle)+pospm[0], rpac*sin(angle)+pospm[1]);
    }
    glEnd();
    
    
    
}


void arrows(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            //dirpm = UP;
            dd = UP;
            break;
        case GLUT_KEY_DOWN:
            //dirpm = DOWN;
            dd = DOWN;
            break;
        case GLUT_KEY_LEFT:
            //dirpm = LEFT;
            dd = LEFT;
            break;
        case GLUT_KEY_RIGHT:
            //dirpm = RIGHT;
            dd = RIGHT;
            break;
    }
    
}
float modulus(float a, float b){
    int c = a/b;
    float d = c*b;
   float e= a - d;
    return e;

}

void idle(void){
    ctr ++;
    
    
    if (ctr == limit){
        int xcel = (pospm[0]-(-numboxx/2.0 * bxsz))/bxsz; //make pacman not go through walls X
        int ycel = -(pospm[1]-(numboxx/2.0*bxsz))/bxsz; //make pacman not go through walls y
        float xoff = modulus((pospm[0]-(-numboxx/2.0 * bxsz)),bxsz);
        float yoff = modulus((-(pospm[1]-(numboxx/2.0*bxsz))),bxsz);
        printf("%d %d %f %f\n", xcel, ycel, xoff, yoff);
        mouthpm = !mouthpm;
        
        ctr = 0;
        printf("%f %d\n", bxsz/2, xoff == bxsz/2);//reset counter each time
        if(drawmaze[ycel][xcel][dd] != 1 && pmctr ==0){
            dirpm=dd;//moves in dd dir
            //printf("We're in the center\n");
        }
        if(drawpellets[xcel][ycel]==1){
            
            drawpellets[xcel][ycel] =0;
            
            score +=10;
        }
        printf("wall: %d counter: %d\n", drawmaze[ycel][xcel][dirpm], pmctr);
        if(drawmaze[ycel][xcel][dirpm] != 1 or pmctr!=0){
            pmctr++;
            if(pmctr >= percentagespeed){
                pmctr =0;
            }
            switch(dirpm){
                case UP:
                    pospm[1]+=SPEED;
                    break;
                case DOWN:
                    pospm[1] += -SPEED;
                    
                    break;
                case LEFT:
                    pospm[0] += -SPEED;
                    
                    break;
                case RIGHT:
                    pospm[0] += SPEED;
                    
                    break;
            }
        }
        
        glutPostRedisplay();
    }
    /* if player hits key early, prevents pacman from going through wall. Pacman turnes at next available spot
     int dirs [5][2] = {{1, 0},{0,1},{-1,0}, {0,-1}, {0,0}};
     vx = dirs[ad][0];
     vy = dirs[ad][1];
     rpac += dt * vx;
     rpac += dt *vy;*/
    
    
}



int main(int argc, char** argv)
{
    
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */
    
    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Pac Man");
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    /*init();
     glutMouseFunc(maus) ;*/
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutSpecialFunc(arrows);
     gluOrtho2D(-1,1,-1,1);
    glutMainLoop();
   
    
}

