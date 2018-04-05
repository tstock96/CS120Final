//
// Created by Thomas Stockham on 4/5/18.
//

#include "graphics.h"
#include <string>
#include <vector>
#include "shapes.h"

using namespace std;

enum mode{start, game, endgame};

GLdouble width, height;
int wd;
mode screen;
Rect myRectangle;
Circle myCircle, c1, c2, c3, p1;
vector <Circle> stars;
vector <Circle> stars2;
vector <Circle> coins;

void init() {
    screen = start;

    width = 500;
    height = 720;

    //initialize rectangle
    myRectangle.setDimensions(20, 40);
    myRectangle.setColor(1.0, 1.0, 1.0);
    myRectangle.setPoint((width/2)-(int)myRectangle.getWidth(), (height-10)-(int)myRectangle.getHeight());


    //Initialize Circle
    myCircle.setRadius(50.0);
    myCircle.setColor(1.0, 0.0, 0.0);
    myCircle.setPoint(350, 200);

    c1.setRadius(10.0);
    c1.setColor(1.0,1.0,0.0);
    c1.setPoint(350, 200);

    p1.setRadius(700);
    p1.setColor(0.329412,0.329412,0.329412);
    p1.setPoint(250, 1390);


    //Initialize stars
    srand(time(NULL));
    for (int i = 0; i<100; i++){
        stars.push_back(Circle(rand()%5+1, rand() % (int)width,rand()%int(height),1.0,1.0,1.0));
    }
    srand(time(NULL));
    for (int i = 0; i<100; i++){
        stars2.push_back(Circle(rand()%5+1, rand() % (int)width,rand()%int(height),1.0,1.0,1.0));
    }
    srand(time(NULL));
    for (int i = 0; i<5; i++){
        coins.push_back(Circle(rand()%5+1, rand() % (int)width,rand()%int(height),1.0,1.0,1.0));
    }

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.15f, 1.0f); // Black and opaque
}

void displayStart(){
    for (int i = 0; i<stars.size(); i++){
        stars[i].draw();
    }
    string message2 = "Deep Blue";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(200, 300);
    for (char c: message2) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    string message1 = "Click anywhere to begin";
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(180, 350);
    for (char c: message1) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }

}

void displayGame(){

    for (int i = 0; i<stars2.size(); i++){
        stars2[i].draw();
    }
    myRectangle.draw();

    // Draw words
    string message = "$: ";
    glColor3f(1.0, 1.0, 0.0);
    glRasterPos2i(400,20);
    for (char c: message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
    }
//draw objects
    myCircle.draw();
    p1.draw();
}
void displayEnd(){}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */


//    glBegin(GL_QUADS);
//    glVertex2i(10, 10);
//    glVertex2i(890, 10);
//    glVertex2i(890, 490);
//    glVertex2i(10, 490);
//    glEnd();

    switch(screen){
        case start: displayStart();
            break;
        case game: displayGame();
            break;
        case endgame: displayEnd();
            break;

    }

    glFlush();  // Render now
}



// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape ascii code

    if (key == 27){
        glutDestroyWindow(wd);
        exit(0);
    }
    if (screen ==game) {
        switch (key) {
            case 'r':
                myRectangle.setColor(1.0, 0.0, 0.0); // this won't work yet without global variables
                break;
            case 'p':
                myRectangle.setColor(0.4, 0.0, 0.8);
                break;
            case 'w':
                myRectangle.setColor(1.0, 1.0, 1.0);
        }
    }
    glutPostRedisplay();

    return;
}

void kbdS(int key, int x, int y) {
    if (screen == game) {
        switch (key) {
            case GLUT_KEY_DOWN:
                myRectangle.move(0, 30);
                break;
            case GLUT_KEY_LEFT:
                myRectangle.move(-30, 0);
                break;
            case GLUT_KEY_RIGHT:
                myRectangle.move(30, 0);
                break;
            case GLUT_KEY_UP:
                myRectangle.move(0, -30);
                break;
        }
    }

    glutPostRedisplay();

    return;
}

void cursor(int x, int y) {
    //move circle with mouse
   /* if (screen == game) {
        myCircle.setPoint(x, y);
    }
    */
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && screen == start){
        screen = game;
    }

    glutPostRedisplay();
}

void timer(int extra) {
//make the stars fall
    for (int i = 0;i<stars.size();i++){
        stars[i].move(0, stars[i].getRadius());
        if (stars[i].getCenter().y > height){
            //stars is moving off the bottom of the screen, which is bad
            stars[i].setPoint(stars[i].getCenter().x, 0);
        }
    }
    glutPostRedisplay();
    //glutTimerFunc waits for 30 milliseconds before it calls itself.
    glutTimerFunc(40, timer, 0);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(200, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fun with Drawing!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
