/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef APPLE
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <iostream>

#include <stdlib.h>

#define PI 3.14159265


static int slices = 16;
static int stacks = 16;

int skyLength[5000];
int start[5000];
GLfloat radius[5000];

float starWidth[5000];
GLfloat dua_pi = 2.0 * PI;
int x_pos =300, y_pos;
int starPath[5000];
/* GLUT callback Handlers */

void init(){
    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0.0, 1000, 0.0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

void square_window(int x_left, int x_right, int y_bottom, int y_top, int distance_x){

//    glColor3ub(130,165,159);
    glBegin(GL_POLYGON);
    glVertex2i(x_left, y_bottom);
    glVertex2i(x_right, y_bottom);
    glVertex2i(x_right, y_top);
    glVertex2i(x_left, y_top);
    glEnd();

    int distance_y = distance_x * 3/2;

//    glColor3ub(237,229,187);
    glColor3ub(123,119,97);
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_top - distance_y);
    glVertex2i(x_left + distance_x, y_top - distance_y);
    glEnd();

    x_left = x_left + distance_x;
    x_right = x_right - distance_x;
    y_bottom  = y_bottom + distance_y;
    y_top = y_top - distance_y;

    int x_right_glass_bottom = x_left + (x_right-x_left - 2* distance_x)/2 + distance_x/2;
    int x_left_glass_bottom = x_right_glass_bottom + distance_x;

    int y_top_glass_bottom = y_bottom + (y_top - y_bottom - 2*distance_y)*3/5 + distance_y/2;
    int y_bottom_glass_top = y_top_glass_bottom + distance_y;

    //LEFT BOTTOM
//    glColor3ub(211,219,180);
    glColor3ub(109,113,93);
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x, y_bottom + distance_y);
    glVertex2i(x_right_glass_bottom, y_bottom + distance_y);
    glVertex2i(x_right_glass_bottom, y_top_glass_bottom);
    glVertex2i(x_left + distance_x, y_top_glass_bottom);
    glEnd();

    //RIGHT BOTTOM
    glBegin(GL_POLYGON);
    glVertex2i(x_left_glass_bottom, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_top_glass_bottom);
    glVertex2i(x_left_glass_bottom, y_top_glass_bottom);
    glEnd();

    //RIGHT TOP
    glBegin(GL_POLYGON);
    glVertex2i(x_left_glass_bottom, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_top - distance_y);
    glVertex2i(x_left_glass_bottom, y_top - distance_y);
    glEnd();

    //LEFT TOP
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x, y_bottom_glass_top);
    glVertex2i(x_right_glass_bottom, y_bottom_glass_top);
    glVertex2i(x_right_glass_bottom, y_top - distance_y);
    glVertex2i(x_left + distance_x, y_top - distance_y);
    glEnd();

    //LEFT BOTTOM
//    glColor3ub(218,229,200);
    glColor3ub(113,119,104);
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x + (x_right-x_left-2*distance_x)/20, y_bottom + distance_y);
    glVertex2i(x_right_glass_bottom, y_bottom + distance_y);
    glVertex2i(x_right_glass_bottom, y_top_glass_bottom - (y_top - y_bottom - 2*distance_y)*3/40);
    glVertex2i(x_left + distance_x + (x_right-x_left-2*distance_x)/20, y_top_glass_bottom - (y_top - y_bottom - 2*distance_y)*3/40);
    glEnd();

    //RIGHT BOTTOM
    glBegin(GL_POLYGON);
    glVertex2i(x_left_glass_bottom + (x_right-x_left-2*distance_x)/20, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_top_glass_bottom - (y_top - y_bottom - 2*distance_y)*3/40);
    glVertex2i(x_left_glass_bottom + (x_right-x_left-2*distance_x)/20, y_top_glass_bottom - (y_top - y_bottom - 2*distance_y)*3/40);
    glEnd();

    //RIGHT TOP
    glBegin(GL_POLYGON);
    glVertex2i(x_left_glass_bottom + (x_right-x_left-2*distance_x)/20, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_top - distance_y - (y_top - y_bottom - 2*distance_y)*3/40);
    glVertex2i(x_left_glass_bottom + (x_right-x_left-2*distance_x)/20, y_top - distance_y - (y_top - y_bottom - 2*distance_y)*3/40);
    glEnd();

    //LEFT TOP
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x + (x_right-x_left-2*distance_x)/20, y_bottom_glass_top);
    glVertex2i(x_right_glass_bottom, y_bottom_glass_top);
    glVertex2i(x_right_glass_bottom, y_top - distance_y - (y_top - y_bottom - 2*distance_y)*3/40);
    glVertex2i(x_left + distance_x + (x_right-x_left-2*distance_x)/20, y_top - distance_y - (y_top - y_bottom - 2*distance_y)*3/40);
    glEnd();

}


void window(int x_left, int x_right, int y_bottom, int y_top, int distance_x){
//    glColor3ub(237,229,187);
    glColor3ub(123,119,97);
    glBegin(GL_POLYGON);
    glVertex2i(x_left, y_bottom);
    glVertex2i(x_right, y_bottom);
    glVertex2i(x_right, y_top);
    glVertex2i(x_left, y_top);
    glEnd();

    int distance_y = distance_x * 3/2;

    int y_top_glass_bottom = y_bottom + (y_top- y_bottom - 2*distance_y) * 2/5 + distance_y/2;
    int y_bottom_glass_top = y_top_glass_bottom + distance_y;

//    glColor3ub(218,229,200);
    glColor3ub(113,119,104);
    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_bottom + distance_y);
    glVertex2i(x_right - distance_x, y_top_glass_bottom);
    glVertex2i(x_left + distance_x, y_top_glass_bottom);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(x_left + distance_x, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_bottom_glass_top);
    glVertex2i(x_right - distance_x, y_top - distance_y);
    glVertex2i(x_left + distance_x, y_top - distance_y);
    glEnd();


}

void rectangle_window(int x_left, int x_right, int y_bottom, int y_top, int distance_x){
//    glColor3ub(145,176,170);
    glColor3ub(75,91,88);
    glBegin(GL_POLYGON);
    glVertex2i(x_left, y_bottom);
    glVertex2i(x_right, y_bottom);
    glVertex2i(x_right, y_top);
    glVertex2i(x_left, y_top);
    glEnd();

    int distance_y = distance_x * 3/2;
    int x_right_glass_left = x_left - distance_x/2 + (x_right-x_left -2*distance_x)/2;
    int x_left_glass_right = x_right_glass_left + 3*distance_x;
    window(x_left + distance_x, x_right_glass_left, y_bottom + distance_y, y_top - distance_y, distance_x);
    window(x_left_glass_right, x_right - distance_x, y_bottom + distance_y, y_top - distance_y, distance_x);
}

void rumah(){

    //tanah
    glColor3ub(79,107,149);
    glBegin(GL_POLYGON);
    glVertex2i(0, 0);
    glVertex2i(1000, 0);
    glVertex2i(1000, 50);
    glVertex2i(0, 50);
    glEnd();


//    glColor3ub(222,209,185);
//    glBegin(GL_POLYGON);
//    glVertex2i(200, 200);
//    glEnd();



    //2 POT DI TENGAH
    glColor3ub(121,108,139);
    glBegin(GL_POLYGON);
    glVertex2i(200,50);
    glVertex2i(300, 50);
    glVertex2i(300, 100);
    glVertex2i(200, 100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(800,50);
    glVertex2i(700, 50);
    glVertex2i(700, 100);
    glVertex2i(800, 100);
    glEnd();

    //TANGGA RUMAH
//    glColor3ub(221,205,184);
    glColor3ub(114,106,95);
    glBegin(GL_POLYGON);
    glVertex2i(445, 50);
    glVertex2i(550, 50);
    glVertex2i(550, 115);
    glVertex2i(445, 115);
    glEnd();

//    glColor3ub(188,171,143);
    glColor3ub(97,89,74);

    glBegin(GL_POLYGON);
    glVertex2i(465, 100);
    glVertex2i(540, 100);
    glVertex2i(540, 110);
    glVertex2i(465, 110);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(465, 80);
    glVertex2i(540, 80);
    glVertex2i(540, 90);
    glVertex2i(465, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(465, 60);
    glVertex2i(540, 60);
    glVertex2i(540, 70);
    glVertex2i(465, 70);
    glEnd();


    //RUMAH
//    glColor3ub(217,117,38);
    glColor3ub(112,61,20);
    glBegin(GL_POLYGON);
    glVertex2i(300, 50);
    glVertex2i(445, 50);
    glVertex2i(445, 70);
    glVertex2i(450, 70);
    glVertex2i(450, 110);
    glVertex2i(300, 110);
    glEnd();

    //DAPUR
//    glColor3ub(242,235,219);
    glColor3ub(125,122,133);
    glBegin(GL_POLYGON);
    glVertex2i(310, 110);
    glVertex2i(465, 110);
    glVertex2i(465, 200);
    glVertex2i(310, 200);
    glEnd();

    //JENDELA DAPUR
    rectangle_window(350, 425, 125, 190, 3);

    //RIGHT PART
//    glColor3ub(227,199,144);
    glColor3ub(118,103,75);


    //RIGHT UPPER PART
    glBegin(GL_TRIANGLES);
    glVertex2i(500, 150);
    glVertex2i(740, 605);
    glVertex2i(415, 730);
    glEnd();

//    glColor3ub(236,215,152);
    glColor3ub(122,111,79);
    glBegin(GL_POLYGON);
    glVertex2i(740, 605);
    glVertex2i(415, 730);
    glVertex2i(415, 750);
    glVertex2i(740, 625);
    glEnd();

//    glColor3ub(217,117,38);
    glColor3ub(112,61,20);
    glBegin(GL_POLYGON);
    glVertex2i(465, 400);
    glVertex2i(700, 400);
    glVertex2i(700, 550);
    glVertex2i(465, 650);
    glEnd();
    square_window(465, 540, 522, 615, 5);
    window(535, 580, 405, 520, 5);
    window(585, 630, 405, 520, 5);
    window(635, 680, 405, 520, 5);

    //RIGHT LOWER PART
//    glColor3ub(242,235,219);
    glColor3ub(125,122,113);
    glBegin(GL_POLYGON);
    glVertex2i(550, 50);
    glVertex2i(700, 50);
    glVertex2i(700, 400);
    glVertex2i(550, 400);
    glEnd();
    rectangle_window(600, 670, 300, 350, 2);

//    glColor3ub(75,125,126);
    glColor3ub(39,65,65);
    glBegin(GL_POLYGON);
    glVertex2i(570, 50);
    glVertex2i(680, 50);
    glVertex2i(680, 200);
    glVertex2i(570, 200);
    glEnd();

//    glColor3ub(66,116,117);
    glColor3ub(34,60,61);
    glBegin(GL_POLYGON);
    glVertex2i(575, 180);
    glVertex2i(675, 180);
    glVertex2i(675, 190);
    glVertex2i(575, 190);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 160);
    glVertex2i(675, 160);
    glVertex2i(675, 170);
    glVertex2i(575, 170);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 140);
    glVertex2i(675, 140);
    glVertex2i(675, 150);
    glVertex2i(575, 150);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 120);
    glVertex2i(675, 120);
    glVertex2i(675, 130);
    glVertex2i(575, 130);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 100);
    glVertex2i(675, 100);
    glVertex2i(675, 110);
    glVertex2i(575, 110);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 80);
    glVertex2i(675, 80);
    glVertex2i(675, 90);
    glVertex2i(575, 90);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(575, 60);
    glVertex2i(675, 60);
    glVertex2i(675, 70);
    glVertex2i(575, 70);
    glEnd();



    //DINDING KIRI
//    glColor3ub(145,176,170);
    glColor3ub(75,91,88);
    glBegin(GL_POLYGON);
    glVertex2i(290, 200);
    glVertex2i(465, 200);
    glVertex2i(465, 500);
    glVertex2i(290, 500);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(285, 500);
    glVertex2i(555, 500);
    glVertex2i(555, 520);
    glVertex2i(285, 520);
    glEnd();

    //JENDELA
//    glColor3ub(130,165,159);
    glColor3ub(67,85,82);
    square_window(310, 445, 235, 465, 5);

    //DINDING TENGAH
//    glColor3ub(145,176,170);
    glColor3ub(75,91,88);
    glBegin(GL_POLYGON);
    glVertex2i(465, 115);
    glVertex2i(550, 115);
    glVertex2i(550, 500);
    glVertex2i(465, 500);
    glEnd();

    //SHADOW DI ATAS
//    glColor3ub(130,165,159);
    glColor3ub(67,85,82);
    glBegin(GL_POLYGON);
    glVertex2i(290, 490);
    glVertex2i(550, 490);
    glVertex2i(550, 500);
    glVertex2i(290, 500);
    glEnd();

    //JENDELA TENGAH
//    glColor3ub(130,165,159);
    glColor3ub(67,85,82);
    square_window(465, 545, 360, 465, 5);

    //ATAP PINTU MASUK
//    glColor3ub(155,189,180);
    glColor3ub(80,98,93);
    glBegin(GL_POLYGON);
    glVertex2i(465, 250);
    glVertex2i(590, 250);
    glVertex2i(590, 265);
    glVertex2i(465, 265);
    glEnd();

    //DOOR SHADOW
//    glColor3ub(130,165,159);
    glColor3ub(67,85,82);
    glBegin(GL_POLYGON);
    glVertex2i(465, 115);
    glVertex2i(472, 115);
    glVertex2i(472, 250);
    glVertex2i(465, 250);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(465, 235);
    glVertex2i(550, 235);
    glVertex2i(550, 250);
    glVertex2i(465, 250);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(550, 210);
    glVertex2i(560, 210);
    glVertex2i(590, 250);
    glVertex2i(550, 250);
    glEnd();

    //PINTU
//    glColor3ub(242,240,235);
    glColor3ub(125,124,122);
    glBegin(GL_POLYGON);
    glVertex2i(472, 115);
    glVertex2i(530, 115);
    glVertex2i(530, 235);
    glVertex2i(472, 235);
    glEnd();

//    glColor3ub(192,233,209);
    glColor3ub(99,121,108);
    glBegin(GL_POLYGON);
    glVertex2i(477, 125);
    glVertex2i(492, 125);
    glVertex2i(492, 225);
    glVertex2i(477, 225);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2i(500, 125);
    glVertex2i(525, 125);
    glVertex2i(525, 225);
    glVertex2i(500, 225);
    glEnd();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLoadIdentity();

    //langit
    glBegin(GL_POLYGON);
    glColor3ub(4,4,9);
    glVertex2i(0, 1000);
    glVertex2i(1000, 1000);
    glColor3ub(14,38,125);
    glVertex2i(1000, 0);
    glVertex2i(0, 0);
    glEnd();

    glPointSize(2.0);
    glColor3ub(255,255,255);
    glLineWidth(1.5);
    //INGAT KEMBALIKAN JADI 400
    for(int i=0; i<3000; i++){
        if(i>250 && i<500){
            glLineWidth(starWidth[i]);
            glBegin(GL_LINE_STRIP);
            for(int j = start[i]; j < start[i] + skyLength[i]; j++){
                int k = j%starPath[i];
                glVertex2f(
                    500 + (radius[i] * cos(k * dua_pi/starPath[i])),
                    200 + (radius[i] * sin(k * dua_pi/starPath[i])) *3/2
                );
            }
            glEnd();


        }
        else if(i>=500){
            glPointSize(starWidth[i]);
            glBegin(GL_POINTS);
            glVertex2f(
                    500 + (radius[i] * cos(start[i] * dua_pi/starPath[i])),
                    200 + (radius[i] * sin(start[i] * dua_pi/starPath[i])) * 3/2
                );
            glEnd();
        }
    }
    glLineWidth(1);
    rumah();




    glFlush();

    glutSwapBuffers();

}

void reshape(int w, int h){
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
    glMatrixMode(GL_MODELVIEW);
}

int state = 1;
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    for(int i=0; i<5000; i++){
        start[i] = (start[i] + 1) % starPath[i];
    }

}


int main(int argc, char *argv[])
{
    double theta ;
    for(int i=0; i<5000; i++){
        starPath[i] = (300 + rand()%700) + (rand() % 300*20);
        if(i<500){
            float decay = (1000 - (radius[i] * 4 / 5))/1000;
            radius[i] = static_cast<float>(rand() %  200 * 5);
            skyLength[i] = (rand() % starPath[i]) /4;
            skyLength[i] = skyLength[i] * decay;
        }else{
            radius[i] = static_cast<float>(rand() % 32000) / static_cast<float>(32000.0f/900.0f)+(static_cast<float>(rand()%100));
            skyLength[i] = 1;
        }
        start[i] = rand() % starPath[i];
        starWidth[i] = 0.5 + (static_cast<float>(rand()%10000) / static_cast<float>(10000.0f/2.5f));
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glEnable(GL_MULT);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("Polaris Sky");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return EXIT_SUCCESS;
}
