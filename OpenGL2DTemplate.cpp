//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <glut.h>
#include <array>
//-----------------

//  Methods Signatures
void drawSpaceShip(int x, int y);
void drawMoon(int x, int y, float r);
void drawChicken(int x, int y);
void drawPowerUp(int x, int y);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Display(void);
void Anim(int value);
void drawBulletP(int x, int y);
void drawBulletE(int x, int y);
void ShowEnemyHealth(void);
void ShowPlayerHealth(void);
void ShowControls(void);
void DisplayEndOfGame(void);
void showTextOnScreen(int x, int y, char* text);
//-----------------

//  Global Variables
int shiftX = 0;       // holds the X translation value of spaceship 
int shiftY = 0;       // holds the X translation value of spaceship
double xcord = -10;
int selectedFire = 0;
GLboolean flagRight = true;
GLboolean flagLeft = true;
GLboolean endOfGame = false;
GLboolean victory = false;
GLboolean defeat = false;
int playerHealth = 3;
int enemyHealth = 100;
int bulletArray[4000][2] = {};
int eggArray[4000][2] = {};
int i = 0;
int k = 0;
int c = 0;
int c2 = 0;
int t = -900;
int h = 0;
int powerupX = -10000;
int powerupY = -10000;
GLboolean immune = false;
//-----------------


void main(int argc, char** argr) {
    glutInit(&argc, argr);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("Space Invaders");
    glutDisplayFunc(Display);
    glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
    glutKeyboardUpFunc(KeyUp);  // sets the KeyboardUp handler function; called when a key is released
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glColor3f(0.0f, 0.0f, 0.0f);//Black
    gluOrtho2D(0, 800, 0, 800);
    glutTimerFunc(25, Anim, 0);
    glutMainLoop();
}

//to print text on screen
void showTextOnScreen(int x, int y, char* text) {
    glRasterPos2d(x, y);
    for (char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*c);
    }
}

// draw moon and sun
void drawMoon(int x, int y, float r) {
    glTranslatef(x, y, 0);
    GLUquadric* quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
}

//draw function for spaceship/player model
void drawSpaceShip(int x, int y) {
    glBegin(GL_POLYGON);
    if (immune) {
        glColor3f(0, 1, 0); //green
    }
    else {
        glColor3f(2.0f, 0.5f, 1.0f);//Lilac
    }
    glVertex2f(x,y);
    glVertex2f(x + 30,y);
    glVertex2f(x + 30,y + 30);
    glVertex2f(x,y + 30);
    glEnd();
    glBegin(GL_TRIANGLES);
    if (immune) {
        glColor3f(0, 1, 0); //green
    }
    else {
        glColor3f(2.0f, 0.5f, 1.0f);//Lilac
    }
    glVertex2f(x, y + 30);
    glVertex2f(x + 15, y + 45);
    glVertex2f(x + 30, y + 30);
    glEnd();
    glBegin(GL_POLYGON);
    if (immune) {
        glColor3f(0, 1, 0); //green
    }
    else {
        glColor3f(2.0f, 0.5f, 1.0f);//Lilac
    }
    glVertex2f(x, y);
    glVertex2f(x - 15, y - 15);
    glVertex2f(x + 45, y - 15);
    glVertex2f(x + 30, y);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//light blue
    glVertex2f(x + 5, y + 30);
    glVertex2f(x + 15, y + 40);
    glVertex2f(x + 25, y + 30);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.5f, 0.0f);//Orange
    glVertex2f(x - 15, y - 15);
    glVertex2f(x + 45, y - 15);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.0f);//Orange
    glVertex2f(x - 10, y - 15);
    glVertex2f(x, y - 15);
    glVertex2f(x, y - 20);
    glVertex2f(x - 10, y - 20);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 0.5f, 0.0f);//Orange
    glVertex2f(x + 40, y - 15);
    glVertex2f(x + 30, y - 15);
    glVertex2f(x + 30, y - 20);
    glVertex2f(x + 40, y - 20);
    glEnd();
   
}

//draw function for chicken/enemy model
void drawChicken(int x, int y) {
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glVertex2f(x, y);
    glVertex2f(x + 60, y);
    glVertex2f(x + 60, y + 60);
    glVertex2f(x, y + 60);
    glEnd();
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glVertex2f(x + 20, y + 60);
    glVertex2f(x + 20, y + 90);
    glVertex2f(x + 40, y + 90);
    glVertex2f(x + 40, y + 60);
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.5f, 0.0f);//Orange
    glVertex2f(x + 30, y + 60);
    glVertex2f(x + 25, y + 70);
    glVertex2f(x + 35, y + 70);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 23, y + 80);
    glVertex2f(x + 28, y + 80);
    glVertex2f(x + 28, y + 85);
    glVertex2f(x + 23, y + 85);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 32, y + 80);
    glVertex2f(x + 37, y + 80);
    glVertex2f(x + 37, y + 85);
    glVertex2f(x + 32, y + 85);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 20, y);
    glVertex2f(x + 20, y - 10);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 20, y);
    glVertex2f(x + 30, y - 10);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 20, y);
    glVertex2f(x + 10, y - 10);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 40, y);
    glVertex2f(x + 40, y - 10);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 40, y);
    glVertex2f(x + 30, y - 10);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.658824, 0.658824, 0.658824);//lightgrey
    glVertex2f(x + 40, y);
    glVertex2f(x + 50, y - 10);
    glEnd();
}


//draw function for powerup model
void drawPowerUp(int x, int y) {
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
    glVertex2f(x - 10, y - 75);
    glVertex2f(x - 10, y + 13);
    glVertex2f(x + 38, y + 13);
    glVertex2f(x + 38, y - 75);
    glEnd();
    
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x, y);//a
    glVertex2f(x + 20, y + 8);//b
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x + 20, y + 8);//b
    glVertex2f(x + 15, y - 30);//c
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x + 15, y - 30);//c
    glVertex2f(x + 33, y - 22);//d
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x + 33, y - 22);//d
    glVertex2f(x + 17, y - 70);//e
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x + 17, y - 70);//e
    glVertex2f(x + 18, y - 40);//f
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x + 18, y - 40);//f
    glVertex2f(x - 5, y - 50);//g
    glEnd();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    glVertex2f(x - 5, y - 50);//g
    glVertex2f(x, y);//a
    glEnd();  
}


// draw bullet for enemy (chicken)
void drawBulletE(int x, int y) {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 1.0f, 0.0f);//white
    glVertex2f(x + 10, y - 30);
    glVertex2f(x + 15, y - 25);
    glVertex2f(x + 20, y - 30);
    glEnd();
    glPopMatrix();
}


// draw bullet for player (spaceship)
void drawBulletP(int x, int y) {
    glPushMatrix();
    glBegin(GL_TRIANGLES);
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);//yellow
    glVertex2f(x + 30, y + 50);
    glVertex2f(x + 35, y + 55);
    glVertex2f(x + 40, y + 50);
    glEnd();
    glPopMatrix();
}






// Keyboard handler function
//   key: the key pressed on the keyboard
void Key(unsigned char key, int x, int y) {
    if ((key == 'a' || key == 'A') && (shiftX + 400 > 100))
        shiftX -= 30;
    if ((key == 'd' || key == 'D') && (shiftX + 400 < 700))
        shiftX += 30;
    if ((key == 'w' || key == 'W') && (shiftY + 400 < 450))
        shiftY += 30;
    if ((key == 's' || key == 'S') && (shiftY + 400 > 200))
        shiftY -= 30;
    if (key == 'f' || key == 'F') {
        selectedFire = 1;
    }
    if (key == 'r' || key == 'R') {
        playerHealth = 3;
        enemyHealth = 100;
        i = 0;
        k = 0;
        c = 0;
        c2 = 0;
        shiftX = 0;
        shiftY = 0;
        xcord = -10;
        selectedFire = 0;
        flagRight = true;
        flagLeft = true;
        endOfGame = false;
        victory = false;
        defeat = false;
        immune = false;
        powerupX = -10000;
        powerupY = -10000;
        t = -900;
        h = 0;
    }

    glutPostRedisplay();
}

// KeyboardUp handler function
//   similar to the Keyboard handler function except that it is called only when the key is released
void KeyUp(unsigned char key, int x, int y) {
    selectedFire = 0;
    glutPostRedisplay();
}

//player health display
void ShowEnemyHealth() {
    char text[40];
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    sprintf(text, "Chicken Health = %d", enemyHealth);
    showTextOnScreen(10, 10,text);
    glColor3f(1, 0, 0);
}

//controls display
void ShowControls() {
    char text1[150];
    char text2[150];
    char text3[150];
    char text4[150];
    char text5[250];
    char str1[] = "Controls:";
    char str2[] = "Up => W | Down => S";
    char str3[] = "Left => A | Right => D";
    char str4[] = "Fire Bullets => F | Restart Game => R";
    char str5[] = "Power Ups appear at random places and in random times.";
    glColor3f(0.6,0.8, 0.196078);//red
    sprintf(text1, " %s", str1);
    sprintf(text2, " %s", str2);
    sprintf(text3, " %s", str3);
    sprintf(text4, " %s", str4);
    sprintf(text5, " %s", str5);
    showTextOnScreen(10, 140, text1);
    showTextOnScreen(10, 115, text2);
    showTextOnScreen(10, 90, text3);
    showTextOnScreen(10, 65, text4);
    showTextOnScreen(10, 40, text5);
    glColor3f(1, 0, 0);
}


//player health display
void ShowPlayerHealth() {
    char text1[40];
    glColor3f(0.0f, 1.0f, 0.0f);//Green
    sprintf(text1, "Spaceship Lives = %d", playerHealth);
    showTextOnScreen(650, 10, text1);
    glColor3f(1, 0, 0);
}

//Display to player when immune
void DisplayImmune() {
    if (immune) {
        char text1[40];
        glColor3f(0, 1, 0);//green 
        sprintf(text1, "YOU ARE NOW IMMUNE TO BULLETS !!!");
        showTextOnScreen(350, 70, text1);
        glColor3f(1, 0, 0);
    }
}

//end of game display
void DisplayEndOfGame()
{
    char text1[100];
    char text2[100];
    if (playerHealth > 0 && enemyHealth <= 0) {
        endOfGame = true;
        victory = true;
        glColor3f(0.0f, 1.0f, 0.0f);//Green
        sprintf(text1, "V I C T O R Y,  YOU  WON ! ! ! :)");
        sprintf(text2, "Press R to Play Again.");
        showTextOnScreen(300, 400, text1);
        showTextOnScreen(335, 350, text2);
        glColor3f(1, 0, 0);
    }
    if(playerHealth <= 0 && enemyHealth > 0) {
        endOfGame = true;
        defeat = true;
        glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
        sprintf(text1, "D E F E A T,  YOU  LOST ! ! ! :( ");
        sprintf(text2, "Press R to Try Again.");
        showTextOnScreen(300, 400, text1);
        showTextOnScreen(335, 350, text2);
        glColor3f(1, 0, 0);
    }
    else {
        if (endOfGame && victory) {
            glColor3f(0.0f, 1.0f, 0.0f);//Green
            sprintf(text1, "V I C T O R Y,  YOU  WON ! ! ! :)");
            sprintf(text2, "Press R to Play Again.");
            showTextOnScreen(300, 400, text1);
            showTextOnScreen(335, 350, text2);
            glColor3f(1, 0, 0);
        }
        if (endOfGame && defeat) {
            glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
            sprintf(text1, "D E F E A T,  YOU  LOST ! ! ! :( ");
            sprintf(text2, "Press R to Try Again.");
            showTextOnScreen(300, 400, text1);
            showTextOnScreen(335, 350, text2);
            glColor3f(1, 0, 0);
        }
    }
}


void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    ShowEnemyHealth();
    ShowPlayerHealth();
    DisplayEndOfGame();
    DisplayImmune();
    ShowControls();
    //draw moon
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);//Grey
    drawMoon(100, 600, 100);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(110, 600, 30);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(50, 620, 20);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(70, 670, 15);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(80, 570, 10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(150, 540, 20);
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(150, 660, 17);
    glPopMatrix();


    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f);//Dark grey
    drawMoon(40, 550, 15);
    glPopMatrix();

    //draw sun
    glPushMatrix();
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);//red
    drawMoon(500, 200, 100);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(510, 200, 30);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(450, 220, 20);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(470, 270, 15);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(480, 170, 10);
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(550, 140, 20);
    glPopMatrix();


    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(550, 260, 17);
    glPopMatrix();


    glPushMatrix();
    glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
    drawMoon(440, 150, 15);
    glPopMatrix();
    
    //spaceship model & bullet model
    glPushMatrix();
    glTranslatef(shiftX, shiftY, 0);
    drawSpaceShip(400, 400);
    glPopMatrix();
    
    if (selectedFire && c2 % 6 == 0) {
        int xc = 380 + shiftX;
        int yc = 400 + shiftY;
        bulletArray[i][0] = xc;
        bulletArray[i][1] = yc;
        i++;
    }
    c2++;

    for (int j = 0; j < i; j++) {
        glPushMatrix();
        drawBulletP(bulletArray[j][0],bulletArray[j][1]);
        glPopMatrix();
    }   

    //powerup model
    glPushMatrix();
    glColor3f(0.1f, 0.0f, 0.1f);
    drawPowerUp(powerupX, powerupY);
    glPopMatrix();

    //chicken model
    glPushMatrix();
    glTranslatef(xcord, 0, 0);
    glColor3f(0.1f, 0.0f, 0.1f);
    drawChicken(50, 700);
    glPopMatrix();

    if (c % 33 == 0) {
        int xc = 50 + xcord;
        int yc = 700;
        eggArray[k][0] = xc;
        eggArray[k][1] = yc;
        k++;
    }
    c++;
    for (int l = 0; l < k; l++) {
        glPushMatrix();
        drawBulletE(eggArray[l][0], eggArray[l][1]);
        glPopMatrix();
    }
    if (xcord == 650) {
        flagRight = true;
        flagLeft = false;
    }
    if (xcord == -10) {
        flagLeft = true;
        flagRight = false;
    }

    if (flagRight && !(flagLeft)) {
        xcord -= 2;
    }
    else if(flagLeft && !(flagRight)){
    xcord += 2;
    }

    glFlush();
}



void Anim(int value)
{
    if (powerupX >= (shiftX + 370) &&  powerupX <= (shiftX + 430) && powerupY >= (400 + shiftY) && powerupY <= (470 + shiftY)) {
        powerupX = -10000;
        powerupY = -10000;
        immune = true;
    }

    if (h % 600 == 0) {
        immune = false;
    }
    h++;

    if ((!endOfGame) && (t % 930 == 0)) {
         powerupX = (rand() % (700 - 100 + 1)) + 100;
         powerupY = (rand() % (450 - 200 + 1)) + 200;
    }
    t++;

    for (int j = 0; j < i; j++) {
        bulletArray[j][1] += 8;

    }
    for (int u = 0; u < k; u++) {
        eggArray[u][1] -= 5;

    }
    for(int l = 0; l < k ; l++){
    if (eggArray[l][0] >= (shiftX + 370) && eggArray[l][0] <= (shiftX + 430) && eggArray[l][1] >= (400 + shiftY) && eggArray[l][1] <= (470 + shiftY)) {
        eggArray[l][1] = -100000;
        if (playerHealth > 0 && !(immune)) {
            playerHealth--;
        }
    }
    }

    for (int p = 0; p < i; p++) {
        if((bulletArray[p][0] > (xcord + 30) && bulletArray[p][0] < (xcord + 80) && bulletArray[p][1] > 650 && bulletArray[p][1] < 740)){
            bulletArray[p][1] = 100000;
            if (enemyHealth > 0) {
                enemyHealth--;
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(25, Anim,0);
}