# -*- coding: utf-8 -*-
"""
Created on May  4 22:57:31 2017

@author: PRITHVIRAJ NAIK
"""

#include<stdio.h>
#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#define PI 3.14
int flag=0;
GLfloat fall_x,basket_left_X=270,basket_right_X=330;
GLint k,xoff,posx=1275,posy=710,posz=0,space_char=10,i,next=0;
int balls_caught=0,missed_balls=0,level_count=1,points=0,base=0,in=1;
int p=0,bflag=0;
// for incrementing the points based on color
int d=0;
// for color selection
int ball_xc,ball_yc;
int lvl=1;
// for coordinates of ball
// for coordinates of basket
int a=1366,b=768; // for default size of the screen
int s=0;
// for menu option
int speed_1=1,speed_2=2,speed_3=3,speed_4=4,speed_5=5;
int orange_balls=0,white_balls=0,pink_balls=0,yellow_balls=0,gray_balls=0,green_balls=0;
int w=48,h=48,t=10,e=9,g=12;
void myinit();
void start_screen(int,int);
void ball();
void body();
void print_score();
void balls_start();
void color();
void score();
void display(void);
void myReshape(int,int);
void keys(unsigned char,int,int);
void menu(int);

void drawtext(float m,float n,float z,char str[])
{
	
    glRasterPos2f(m,n);
    for(i=0;i<=strlen(str);i++)
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}

void scoredisplay (int posx, int posy, int posz, int space_char, int balls_caught)
{
    int j=0,p,k;
    glColor3f(0.0,0.3,0.0);
    GLvoid *font_style1 = GLUT_BITMAP_TIMES_ROMAN_24;
    p = balls_caught;
    j= 0;
    k = 0; 
    while(p > 9)
    {
        k = p % 10;
        glRasterPos3f ((posx-(j*space_char)),posy, posz);    
        glutBitmapCharacter(font_style1,48+k);
        j++;
        p /= 10;
    }
    glRasterPos3f ((posx-(j*space_char)), posy, posz);    
    glutBitmapCharacter(font_style1,48+p);
           
}
        
void gameover()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
    drawtext(583,490,0,"GAME OVER");
    drawtext(543,410,0,"YOUR SCORE IS");
    scoredisplay(740,410,0,space_char,balls_caught);
    glColor3f(1.0,0.0,0.0);
    drawtext(513,350,0,"Loading Game...Please wait");
    glutSwapBuffers();
}

void restart()
{
    lvl=0;
    gray_balls=0;
    balls_caught=0;
    s=0;
}

void startscreen()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1);
    glColor3f(1.0,1.0,1.0);
    drawtext(450.0,650.0, 0,"CANARA ENGINEERING COLLEGE");
    drawtext(300.0,590.0, 0,"DEPARTMENT OF COMPUTER SCIENCE AND ENGINEERING");
    drawtext(530.0,520.0, 0,"A Mini Project On");
    drawtext(375.0,470.0, 0,"COMPUTER GRAPHICS AND VISUALIZATION");
    drawtext(495.0,420.0, 0,"CATCH THE FORTUITY");
    drawtext(605.0,380.0, 0,"BY");
    drawtext(605.0,378.0, 0,"___");
    drawtext(410.0,340.0, 0,"PRITHVIRAJ P NAIK     4CB14CS070");
    drawtext(420.0,300.0, 0,"PRIYANKA KINI          4CB14CS071");
    drawtext(495.0,229.0, 0,"Under the Guidance of");
    drawtext(495.0,230.0, 0,"__________________");
    drawtext(490.0,180.0, 0,"Prof.Shathanand Bhat");
    drawtext(460.0,140.0, 0, "Asst.Professor,Dept. of CSE");
    drawtext(915.0,120.0,0.0,"Press Enter Key To continue");
    glFlush();
}

void helpscreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,0.0,1);
    glColor3f(1.0,1.0,1.0);
    drawtext(100.0,650.0,0,"CONTROLS:");
    drawtext(120.0,600.0,0,"TO MOVE -");
    drawtext(280.0,600.0,0,"<-MOVE LEFT");
    drawtext(480.0,600.0,0,"MOVE RIGHT->");
    drawtext(454.0,600.0,0,"||");
    drawtext(120.0,560.0,0,"FOR NEW GAME PRESS -  'N/n' or RIGHT CLICK MENU");
    drawtext(120.0,520.0,0,"RESTART THE GAME PRESS -   'R/r'");
    drawtext(120.0,480.0,0,"TO QUIT THE GAME PRESS -  'Q/q'or RIGHT CLICK MENU");
    drawtext(120.0,440.0,0,"DAY MODE -  'D/d',NIGHT MODE -  'K/k'");
    drawtext(1050.0,270.0,0,"PLAYER");
    drawtext(100.0,390.0,0,"INSTRUCTIONS:");
    drawtext(120.0,350.0,0,"*CATCH THE BALL BY MOVING THE PLAYER LEFT OR RIGHT.");
    drawtext(120.0,310.0,0,"*IF THE GREY BALL IS CAUGHT THE SCORE IS DECREMENTED.");
    drawtext(120.0,270.0,0,"*MAXIMUM OF 3 GREY BALLS CAN BE CAUGHT.");
    drawtext(915.0,120.0,0.0,"Press Enter Key To continue");
    glFlush();
    glPushMatrix();
    glTranslated(800,300,0);
    body();
    glPopMatrix();
}

void myinit()
{
	glViewport(0,0,a,b);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,(GLdouble)1366,0.0,(GLdouble)768,865,-865);
	glMatrixMode(GL_MODELVIEW);
 	glutPostRedisplay();
}

void giant()
{
	int q,i;
	long double x,y,z;
	long double t;
   glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(990,560);
	glVertex2f(1040,560);
	glVertex2f(1040,530);
	glVertex2f(990,530);
	glEnd(); 
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(760,560);
	glVertex2f(810,560);
	glVertex2f(810,530);
	glVertex2f(760,530);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(875,630);
	glVertex2f(925,630);
	glVertex2f(925,660);
	glVertex2f(875,660);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(875,410);
	glVertex2f(925,410);
	glVertex2f(925,440);
	glVertex2f(875,440);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(965,450);
	glVertex2f(1015,450);
	glVertex2f(1015,480);
	glVertex2f(965,480);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(785,450);
	glVertex2f(835,450);
	glVertex2f(835,480);
	glVertex2f(785,480);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(965,600);
	glVertex2f(1015,600);
	glVertex2f(1015,630);
	glVertex2f(965,630);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0.0);
	glVertex2f(785,600);
	glVertex2f(835,600);
	glVertex2f(835,630);
	glVertex2f(785,630);
	glEnd();
	glBegin(GL_TRIANGLES);                                 
	glColor3f(1.0,.5,0.0);
	glVertex2f(900,550);
	glVertex2f(950,400);
	glVertex2f(980,400);
	glEnd();                                               
	glBegin(GL_TRIANGLES);
	glColor3f(1.0,0.5,0.0);
	glVertex2f(900,550);                                 
	glVertex2f(820,400);                          // GIANT WHEEL
	glVertex2f(850,400);
	glEnd();
	glLineWidth(30);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0,.8,0.0);
	for(t=0;t<360;t+=.2)
    {
        x = 900+120*(cos(t*3.14/180));
        y = 550+120*(sin(t*3.14/180));
        glVertex2f(x,y);                                              
    }
    glEnd(); 
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0,.8,0.0);
	for(t=0;t<360;t+=.2)
    {
        x = 900+110*(cos(t*3.14/180));
        y = 550+110*(sin(t*3.14/180));
        glVertex2f(x,y);                                              
    }
	glEnd(); 
}
    
void back()
{
    int q,i;
    long double x,y,z;
    long double t;
    glPointSize(2);                        //
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(300,600);
    glEnd();
    glPointSize(2);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(535,650);
    glEnd();
    glPointSize(2);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(100,620);
    glEnd();
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(700,760);
    glEnd();
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(555,450);
    glEnd();
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);                                 // STARS
    glVertex2f(735,600);
    glEnd();
    glPointSize(1);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(835,550);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);                                    //MOON
    glColor3f(1.0,1.0,1.0);
    for(t=0;t<360;t+=10)
    {
        x = 200+40*(cos(t*3.14/180));
        y = 700+40*(sin(t*3.14/180));
        glVertex2f(x,y);                                              
    }
    glEnd();
    glLineWidth(10);
    glBegin(GL_LINES);                                          //DIVIDER
    glColor3f(1.0,.0,0.2);
    glVertex2f(0,398);
    glVertex2f(1366,397);
    glEnd();
    if(bflag==1)
    {
        glClearColor(1.0,1.0,1.0,1.0);
        glBegin(GL_POLYGON);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(0,397);
        glVertex2f(1366,397);
        glColor3f(0.1,0.1,0.1);
        glVertex2f(1366,0);
        glVertex2f(0,0);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.0,0.0,1.0);
        glVertex2f(0,768);
        glVertex2f(1366,768);
        glColor3f(1.0,1.0,1.0);
        glVertex2f(1366,397);
        glVertex2f(0,397);
        glEnd();
        glBegin(GL_TRIANGLE_FAN);//SUN
        glColor3f(1.0,0.6,0.0);
        for(t=0;t<360;t+=10)
        {
             x = 200+40*(cos(t*3.14/180));
             y = 700+40*(sin(t*3.14/180));
             glVertex2f(x,y);                                              
        }
        glEnd();
        glBegin(GL_LINES);                                          //DIVIDER
        glColor3f(0.0,1.0,0.0);
        glVertex2f(0,398);
        glVertex2f(1366,397);
        glEnd();
        glFlush();
    }
    giant();
    glBegin(GL_TRIANGLES);                                       //
    glColor3f(1.0,0.5,0.0);
    glVertex2f(200,550);
    glVertex2f(100,520);
    glVertex2f(300,520);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,.8,0.0);
    glVertex2f(100,420);
    glVertex2f(300,420);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,.8,0.0);
    glVertex2f(105,405);
    glVertex2f(295,405);
    glEnd();
    glLineWidth(3);	
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(110,520);
    glVertex2f(110,422);
    glEnd();
    glLineWidth(3);	                                          //RIDE
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(160,520);
    glVertex2f(160,422);
    glEnd();
    glLineWidth(3);	
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(240,520);
    glVertex2f(240,422);
    glEnd();
    glLineWidth(3);	
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(290,520);
    glVertex2f(290,422);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(180,520);
    glVertex2f(220,520);
    glVertex2f(210,422);
    glVertex2f(190,422);
    glEnd();     
    glBegin(GL_POLYGON);               //
    glColor3f(1.0,0.0,0.0);
    glVertex2f(95,480);
    glVertex2f(130,480);
    glVertex2f(130,460);
    glVertex2f(95,460);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(130,480);
    glEnd();
    glBegin(GL_LINES); //TAIL
    glColor3f(1.0,0.0,0.0);                        // HORSE1
    glVertex2f(95,480);
    glVertex2f(90,483);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(130,460);
    glVertex2f(135,450);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(95,460);
    glVertex2f(85,450);
    glEnd();
    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(125,487);
    glEnd();                             //
    glBegin(GL_POLYGON);              //
    glColor3f(1.0,0.0,0.0);
    glVertex2f(275,480);
    glVertex2f(310,480);
    glVertex2f(310,460);
    glVertex2f(275,460);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(310,480);
    glEnd();
    glBegin(GL_LINES); //TAIL
    glColor3f(1.0,0.0,0.0);                        // HORSE2
    glVertex2f(275,480);
    glVertex2f(270,483);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(310,460);
    glVertex2f(315,450);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(275,460);
    glVertex2f(265,450);
    glEnd();
    glPointSize(5);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(305,487);
    glEnd();  //	
    glBegin(GL_POLYGON);           //
    glColor3f(1.0,0.0,0.0);
    glVertex2f(505,427);
    glVertex2f(535,427);		
    glVertex2f(535,410);
    glVertex2f(505,410);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(535,410);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(505,410);
    glEnd();
    glLineWidth(.2);	
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(520,427);
    glVertex2f(515,497);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.5,0.0);
    glVertex2f(515,497);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(520,427);
    glVertex2f(500,480);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);                 //BALLOON
    glBegin(GL_POINTS);
    glColor3f(0.0,0.0,0.5);
    glVertex2f(500,480);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(520,427);
    glVertex2f(535,490);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(0.0,1.0,1.0);
    glVertex2f(535,490);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(520,427);
    glVertex2f(540,465);
    glEnd();
    glPointSize(15);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0,0.8,0.0);
    glVertex2f(540,465);
    glEnd();                           //

}   
        
void screen()
{
    glBegin(GL_POLYGON); 
    glColor3f(1.0,0.5,0);
    glVertex3f(550.0, 530.0, 0.0); 
    glVertex3f(750.0, 530.0, 0.0); 
    glVertex3f(750.0, 480.0, 0.0); 
    glVertex3f(550.0, 480.0, 0.0); 
    glEnd();
    glBegin(GL_POLYGON); 
    glColor3f(1.0,0.5,0);
    glVertex3f(550.0, 460.0, 0.0); 
    glVertex3f(750.0, 460.0, 0.0); 
    glVertex3f(750.0, 410.0, 0.0); 
    glVertex3f(550.0, 410.0, 0.0); 
    glEnd();
    glBegin(GL_POLYGON); 
    glColor3f(1.0,0.5,0);
    glVertex3f(550.0, 390.0, 0.0); 
    glVertex3f(750.0, 390.0, 0.0); 
    glVertex3f(750.0, 340.0, 0.0); 
    glVertex3f(550.0, 340.0, 0.0); 
    glEnd();
}
void start_screen(int i,int j)
{
    screen();
    glColor3f(1.0,0.5,0);
    drawtext(490.0,650.0,0," CATCH ");
    glColor3f(1.0,0.5,0);
    drawtext(600.0,650.0,0,"THE ");
    glColor3f(1.0,0.5,0);
    drawtext(680.0,650.0,0,"FORTUITY");
    glColor3f(0.0,0.0,0.0);
    drawtext(580.0,500.0,0,"NEW GAME");
    glColor3f(0.0,0.0,0.0);
    drawtext(615.0,430.0,0,"HELP");
    glColor3f(0.0,0.0,0.0);
    drawtext(615.0,360,0," QUIT ");
    glColor3f(0.0,1.0,0);
    drawtext(915.0,180,0," PRESS N FOR NEW GAME ");
    drawtext(915.0,140,0," PRESS H FOR HELP ");
    drawtext(915.0,100,0," PRESS Q TO QUIT ");
}
void ball()
{
    long double x,y,z;
    long double t;
    glBegin(GL_POLYGON);
    for(t=0;t<=360;t+=1)
    {
        x = ball_xc+16*(cos(t));
        y = ball_yc+16*(sin(t));
        z = 0;
        glVertex3f(x,y,z);
    }
    glEnd();

}
void body()//for nose eyes and other parts of body
{  
    //HEAD
    glColor3d(1,0.5,0);
    glPushMatrix();
    ranslated(300,300,00);
    glutSolidSphere(40,50,50);
    glPopMatrix();
	//HAIR
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.8);
    glVertex2f(250.0, 314.0);
    glVertex2f(280.0, 345.0);
    glVertex2f(300.0, 345.0);
    glVertex2f(320.0, 345.0);
    glVertex2f(350.0, 314.0);
    glEnd();
	//EYES
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(280,310);
    glVertex2f(290,310);
    glVertex2f(290,300);
    glVertex2f(280,300);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(310,310);
    glVertex2f(310,300);
    glVertex2f(320,300);
    glVertex2f(320,310);
    glEnd();
	//NOSE
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(300,300);
    glVertex2f(300,290);
    glVertex2f(301,300);
    glVertex2f(301,290);
    glEnd();
	//MOUTH
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(285,280);
    glVertex2f(315,280);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(285,279);
    glVertex2f(315,279);
    glEnd();
    //neck
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(290.0, 261.5);
    glVertex2f(290.0, 240.0);
    glVertex2f(310.0, 240.0);
    glVertex2f(310.0, 261.5);
    glEnd();
	 //body
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(260.0, 240.0);
    glVertex2f(260.0, 140.0);
    glVertex2f(340.0, 140.0);
    glVertex2f(340.0, 240.0);
    glEnd();
    //right hand
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(340.0, 240.0);
    glVertex2f(360.0, 240.0);
    glVertex2f(360.0, 180.0);
    glVertex2f(340.0, 180.0);
    glEnd();
	//left hand
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(260.0, 240.0);
    glVertex2f(240.0, 240.0);
    glVertex2f(240.0, 180.0);
    glVertex2f(260.0, 180.0);
    glEnd();
	//leftwrist
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(240.0, 180.0);
    glVertex2f(250.0, 160.0);
    glVertex2f(280.0, 155.0);
    glVertex2f(290.0, 170.0);
    glVertex2f(260.0, 180.0);
    glEnd();
	//rightwrist
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.5, 0.0);
    glVertex2f(360.0, 180.0);
    glVertex2f(340.0, 180.0);
    glVertex2f(310.0, 170.0);
    glVertex2f(310.0, 155.0);
    glVertex2f(350.0, 160.0);
    glEnd();
	//left sleeves
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(260.0, 240.0);
    glVertex2f(240.0, 240.0);
    glVertex2f(240.0, 210.0);
    glVertex2f(260.0, 210.0);
    glEnd();
	//right sleeves
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(360.0, 240.0);
    glVertex2f(340.0, 240.0);
    glVertex2f(340.0, 210.0);
    glVertex2f(360.0, 210.0);
    glEnd();
	//quote on tee
    glColor3f(1.0,0,0);
    drawtext(260.0,210,0,"PLAYER");
	//pant left side
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(260.0, 140.0);
    glVertex2f(260.0, 20.0);
    glVertex2f(290.0, 20.0);
    glVertex2f(305.0, 140.0);
    glEnd();
    //pant right side
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(300.0, 140.0);
    glVertex2f(310.0, 20.0);
    glVertex2f(340.0, 20.0);
    glVertex2f(340.0, 140.0);
    glEnd();
	//leftshoe
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(290.0, 20.0);
    glVertex2f(260.0, 20.0);
    glVertex2f(260.0, 10.0);
    glVertex2f(240.0, 10.0);
    glVertex2f(240.0, 0.0);
    glVertex2f(290.0, 0.0);
    glEnd();
	//rightshoe
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 1.0);
    glVertex2f(310.0, 20.0);
    glVertex2f(310.0, 0.0);
    glVertex2f(360.0, 00.0);
    glVertex2f(360.0, 10.0);
    glVertex2f(340.0, 10.0);
    glVertex2f(340.0, 20.0);
    glEnd();
	//basket
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(270.0, 200.0);
    glVertex2f(288.0,150.0);
    glVertex2f(315.0, 150.0);
    glVertex2f(330.0, 200.0);
    glEnd();
	
}


void balls_start()
{
    ball_yc=768;
    switch(rand()%9)
    {
        case 0:ball_xc=305;d=rand()%6;
        	fall_x=ball_xc;
        	break;
        case 1:ball_xc=545;d=rand()%3;
        	fall_x=ball_xc;break;
        case 2:ball_xc=680;d=rand()%6; 
        	fall_x=ball_xc;break;
        case 5:ball_xc=705;d=rand()%9; 
        	fall_x=ball_xc;break;
        case 3:ball_xc=845;d=rand()%6;
        	fall_x=ball_xc;break;
        case 4:ball_xc=980;d=rand()%3;
        	fall_x=ball_xc;break;
        case 7:ball_xc=205;d=rand()%3; 
        	fall_x=ball_xc;break;
        case 6:ball_xc=545;d=rand()%6;
        	fall_x=ball_xc;break;
        case 8:ball_xc=380;d=rand()%9;
        	fall_x=ball_xc;break;
    }
}
    
void color()
{
    switch(d)
    {
        case 3:glColor3f(1,0.4,0);break; //orange
        case 2:glColor3f(0,1,0);break; //green
        case 4:glColor3f(0.2,0.2,0.2);break; //gray
        case 5:glColor3f(1,1,1);break; //white
        case 0:glColor3f(1,0,1);break; //pink
        case 1:glColor3f(1,1,0);break; //yellow
    }
}
    
void scoreboard()
{
    glBegin(GL_QUADS);
    glColor3f(1.0,0.5,0.0);
    glVertex2f(1200,768);
    glVertex2f(1366,768);
    glVertex2f(1366,698);
    glVertex2f(1200,698);
    glEnd();
    glFlush();
    glBegin(GL_POLYGON);
    glColor3f(1.0,0.5,0.0);
    glVertex2f(1200,697);
    glVertex2f(1366,697);
    glVertex2f(1366,628);
    glVertex2f(1200,628);
    glEnd();
    glFlush();
    glColor3f(0,0,0);
    drawtext(1245.0,740.0,0,"SCORE");
    glColor3f(0,0,0);
    drawtext(1210.0,672.0,0,"GREY BALLS");
    glColor3f(1,0,0);
    drawtext(653.0,745.0,0,"LEVEL");
}

void score()
{
    int i=20,o=0;
    if(ball_yc<217 && (fall_x<basket_right_X && fall_x>basket_left_X))
    {
    printf("\a");
    balls_caught++;
    switch(d)
    {
        case 0: pink_balls++;break;
        case 1: yellow_balls++;break;
        case 2: green_balls++;break;
        case 3: orange_balls++;break;
        case 4: gray_balls++;balls_caught-=2;
                if(gray_balls>=4)
                {
                    gameover();
                    Sleep(4000);
                    restart();
                }break;
        case 5: white_balls++;break;
    }
    ball_yc=-20;
    }
}
 
void display(void)
{ 	
	
	if(next==0)
	{
		startscreen();
	}
	else if(next==1)
	{
		helpscreen();
	}
    else
	{
    	 screen();
        int i;
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        back();
        glPushMatrix();
        glTranslatef(xoff, 0.0, 0.0);
        body( );
        glPopMatrix();
        glFlush();
        scoreboard();
    	//back();
        scoredisplay ( posx,posy, posz, space_char,balls_caught);
        scoredisplay ( 683,720,0, space_char,lvl);
        scoredisplay ( 1275,640,0, space_char,gray_balls);
        if(s>=1)
        {
             if(ball_yc<=100)
                 balls_start();
             color();
             ball();
             if(balls_caught>=10)
             {
                 lvl=2;
                 ball_yc-=speed_2;
             }
             if(balls_caught>=40)
             {
                  lvl=3;
                  ball_yc-=speed_3;
             }
             if(balls_caught>=70)
             {
                  lvl=4;
                  ball_yc-=speed_4;
             }
             if(balls_caught>=120)
             {
                  lvl=5;
                  ball_yc-=speed_5;
             }
             else
                 ball_yc-=speed_1;
             score();
        }
        else
            start_screen(500,500);
	}
    glutSwapBuffers();
}
             
//my reshape so that distortion doesnt occur 
void myReshape(int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,(GLdouble)1366,0.0,(GLdouble)768,865,-865);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
    a=w;
    b=h;
}

void keys(int key,int x,int y)
{
	if(key==GLUT_KEY_LEFT)
	{
        xoff -= 42;	   
        display();
        basket_left_X-=42;
        basket_right_X-=42;
        glFlush();
	}
	if (key == GLUT_KEY_RIGHT)
	{
        xoff += 42;
        display();
    	 basket_right_X+=42;
        basket_left_X+=42;
        glFlush();
	}
}
    
// these are the keys ,  to start press s
void key(unsigned char key,int x,int y)
{ 
    if(key=='d'||key=='D')
	{
        bflag=1;
        glutPostRedisplay();
	}
	if(key=='k'||key=='K')
	{
        glClearColor(0.0,0.0,0.0,1.0);
        bflag=0;
        glutPostRedisplay();
		//asket_right_X
	}
    if(key=='q'||key=='Q')
    {
        printf("\n\n\n\t\tQUIT BY PLAYER\n\n");
        exit(0);
    }

	if (key == 'h'||key=='H')
	{
    	 next=1;
        stRedisplay();
	}
	if(key=='r')
        restart();
	if(key=='n'||'N')
        s=s+1;
	if(key=='o')
    	 exit(0);
	if(key==13)
	{
		next+=1;
	}
}

//this is menu 
void menu(int id)
{
    switch(id)
    {
        case 1: s+=1;break;
    //case 2:print_score();
        case 3: printf("\n\n\n\t\tQUIT BY PLAYER\n");break;
        default:exit(0);
    }
    glutPostRedisplay();
}

int main(int argc,char **argv)
{// this will be displayed in back screen 
    printf("\n\t\t\t\t CATCH THE FORTUITY\n\n");
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(a,b);
    glutCreateWindow("GAME");
    myinit();
    glutCreateMenu(menu);
    glutAddMenuEntry("Start game",1);
    //glutAddMenuEntry("score",2);
    glutAddMenuEntry("Quit",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutSpecialFunc(keys);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(display);
    glutReshapeFunc(myReshape);
    glutMainLoop();
}
