#include <bits/stdc++.h>
#include<GL/glut.h>
#define MAX_CARS 3

void drawCar();
void drawFootPath();
void drawDivider();
void drawSurroundings();
void stopGame();
void drawOtherCars(int);
void drawOther();
void setCars();
void moveOtherCars();
int detectCollision();
void drawString(std::string);
void drawMainMenu();
void drawExitMenu();
void drawTime();
void stopGame();
void resumeGame();
void drawScore(int);
void drawDistanceBar();
void drawEnd();
void moveEnd();
void drawFuelBar();
void fuelMessage();
void drawFuel();

int foot_y = 200;
int div_y = 220;
int end_y = 160;

int a = 0;
int speed = 1;
int steerSpeed = 1;
int temp = 0;
int seconds = 0;
int distance = 178;
int fuel = 178;

int game_state = 0;

void moveDivider();
void moveRoad();
void moveCar();
void periodicFunction(int);
void moveFuel();

int lane[MAX_CARS];
int pos[MAX_CARS];
int speeds[MAX_CARS];
int speedsTemp[MAX_CARS];

GLdouble width=1200, height=800;
//some boolean to handle the game
bool carMoveLeft = false, carMoveRight = false, carMoveFast = false, carStopped = false, gameStopped = false, horn = false;
bool highlightStart = false, highlightExit = false,breakk =false;
bool reachedEnd = false, gameCompleted = false, fuelOver = false;
//Car variables
int car_x = 0;
int car_y = -100;

int fuel_x = 0;
int fuel_y = -80;
//ali
void maindisp(){

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

   switch(game_state)
	{
        case 1 : glClearColor(0.5, 0.5, 0.5, 0.0);
                 drawFootPath();
                 drawSurroundings();
                 drawDivider();
                 //drawEnd();
                 drawCar();
                 drawOther();
                 drawTime();
                 drawDistanceBar();
                 drawFuelBar();
                 drawFuel();
                 break;

        case 0 : drawMainMenu();

                 break;

        case 2 : glClearColor(0.5, 0.5, 0.5, 0.0);
                 drawFootPath();
                 drawSurroundings();
                 drawDivider();
                 if(gameCompleted)
                    drawEnd();

                 if(fuelOver)
                    fuelMessage();

                 drawCar();
                 drawOther();
                 drawDistanceBar();
                 drawFuelBar();
                 drawExitMenu();
                 drawTime();
                 break;
	}

	glFlush();
	glutSwapBuffers();
}
//kareem
void keyBoardFunc(int key, int x, int y){
	switch(key)
	{
		case GLUT_KEY_LEFT : carMoveLeft = true; carMoveRight = false; break;
		case GLUT_KEY_RIGHT : carMoveRight = true; carMoveLeft = false; break;
		case GLUT_KEY_UP 	: carMoveFast = true; break;
	}
}
//kareem
void keyboard_up_func(int k, int x, int y){
    switch(k)
    {
        case GLUT_KEY_LEFT: carMoveLeft=false;
                            break;
        case GLUT_KEY_RIGHT:carMoveRight=false;
                            break;

		case GLUT_KEY_UP : carMoveFast = false; break;
		case GLUT_KEY_DOWN : carStopped = false; break;
    }
}
//kareem
void normalKeyBoardFunc(unsigned char key, int x, int y){
    if(game_state == 1)
    {
        switch(key)
        {
            //Horn
            case 'H':
            case 'h': horn = true; break;

        }
    }

    else if(game_state == 0)
    {
        if(key == 13)
        {
            setCars();
            game_state = 1;
        }
    }
}
//ali
void mouse_func(int button, int state, int x, int y){
    switch(game_state)
    {
        case 0 : if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                 {
                    if(x >=  630 && x <= 810 && y >= 320 && y <= 405)
                    {
                        //gameStopped = false;
                        setCars();
                        game_state = 1;
                    }

                    else if(x >=  630 && x <= 810 && y >= 490 && y <= 575)
                        exit(0);
                 }
                 break;

        case 2 : if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
                 {
                    if(x >=  630 && x <= 810 && y >= 320 && y <= 405)
                    {
                        gameStopped = false;
                        gameCompleted = false;
                        reachedEnd = false;
                        seconds = 0;
                        distance = 178;
                        fuel = 178;
                        fuelOver = false;
                        end_y = 160;
                        setCars();
                        game_state = 1;
                        car_x = 0;
                    }

                    else if(x >=  630 && x <= 810 && y >= 490 && y <= 575)
                        exit(0);
                 }
                 break;



    }
}
//fady
void mouse_hover(int x, int y){
        if(x >=  630 && x <= 810 && y >= 320 && y <= 405)
        {
            highlightStart = true;
            highlightExit = false;
        }

        else if(x >=  630 && x <= 810 && y >= 490 && y <= 575)
        {
            highlightStart = false;
            highlightExit = true;
        }

        else
        {
            highlightExit = false;
            highlightStart = false;
        }
}
//nada
void drawCar(void){
    glPushMatrix();

    glTranslated(car_x, car_y, 0.0);

    glColor3f(0.88, 0.88, 0.88);

    glRectd(2, 10, -2, -10);
    glRectf(-8, 12, 8, 13);
    glRectf(-10.0, 9.0, -8.0, 15.0);
    glRectf(8.0, 9.0, 10.0, 15.0);

    glBegin(GL_LINES);
        glVertex2f(8.0,11.0);
        glVertex2f(6.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(6.0,-7.0);
        glVertex2f(6.0,-7.0);
        glVertex2f(10.0,-12.0);
        glVertex2f(-8.0,11.0);
        glVertex2f(-6.0,7.0);
        glVertex2f(-6.0,7.0);
        glVertex2f(-6.0,-7.0);
        glVertex2f(-6.0,-7.0);
        glVertex2f(-10.0,-12.0);
        glVertex2f(10.0,-12.0);
        glVertex2f(-10.0,-12.0);
    glEnd();

    glRectf(-11.0, -16.0, -9.0, -8.0);
    glRectf(9.0, -16.0, 11.0, -8.0);
    glRectf(-7.0, -14.0, -5.0, -12.0);
    glRectf(5.0, -14.0, 7.0, -12.0);

    glBegin(GL_POINTS);
        glVertex2f(-7,-15);
        glVertex2f(-5,-15);
        glVertex2f(-8,-16);
        glVertex2f(-4,-16);
        glVertex2f(-6,-16);
        glVertex2f(-6,-17);
    glEnd();

	glPopMatrix();
}
//nada
void drawOtherCars(int i){
    glPushMatrix();

    glTranslated((lane[i] - 1)*37, pos[i], 0.0);

    switch(speeds[i])
    {
        case 2 : glColor3f(0.0, 1.0, 0.0); break;
        case 3 : glColor3f(0.0, 0.0, 1.0); break;
        case 4 :
        case 5 :
        case 6:
        case 7 : glColor3f(1.0, 0.0, 0.0); break;
        case 0 : glColor3f(0.0, 0.0, 0.0); break;
    }

    glRectd(2, 10, -2, -10);
    glRectf(-8, 12, 8, 13);
    glRectf(-10.0, 9.0, -8.0, 15.0);
    glRectf(8.0, 9.0, 10.0, 15.0);

    glBegin(GL_LINES);
        glVertex2f(8.0,11.0);
        glVertex2f(6.0,7.0);
        glVertex2f(6.0,7.0);
        glVertex2f(6.0,-7.0);
        glVertex2f(6.0,-7.0);
        glVertex2f(10.0,-12.0);
        glVertex2f(-8.0,11.0);
        glVertex2f(-6.0,7.0);
        glVertex2f(-6.0,7.0);
        glVertex2f(-6.0,-7.0);
        glVertex2f(-6.0,-7.0);
        glVertex2f(-10.0,-12.0);
        glVertex2f(10.0,-12.0);
        glVertex2f(-10.0,-12.0);
    glEnd();

    glRectf(-11.0, -16.0, -9.0, -8.0);
    glRectf(9.0, -16.0, 11.0, -8.0);
    glRectf(-7.0, -14.0, -5.0, -12.0);
    glRectf(5.0, -14.0, 7.0, -12.0);

    glBegin(GL_POINTS);
        glVertex2f(-7,-15);
        glVertex2f(-5,-15);
        glVertex2f(-8,-16);
        glVertex2f(-4,-16);
        glVertex2f(-6,-16);
        glVertex2f(-6,-17);
    glEnd();

	glPopMatrix();
}
//omar
void drawFootPath(){
	int i, y;
	glPushMatrix();

	//Draw right side foot path
	glTranslated(60, 0, 0);
	y = foot_y + 20;

	for(i = 0; i < 20; i++)
	{
		if(a == 0)
		{
			if(i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		else
		{
			if(i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}


		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

	//Draw left side foot path
	glPushMatrix();
	glTranslated(-60, 0, 0);

	y = foot_y + 20;
	for(i = 0; i < 20; i++)
	{

		if(a == 0)
		{
			if(i % 2 == 0)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		else
		{
			if(i % 2 == 1)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(1.0, 1.0, 0.0);
		}

		y -= 20;
		glRectd(5, y, -5, y - 20);
	}
	glPopMatrix();

}
//omar
void drawDivider(){
	int i;
	int y = div_y + 80;
	glColor3f(1.0, 1.0, 1.0);

	for(i = 0 ; i < 8; i++)
	{
		y-=80;
		glRectd(22, y, 18, y-40);
		glRectd(-18, y, -22, y-40);
	}

}
//noran
void drawSurroundings(){
	glColor3f(0.4f, 0.4f, 0.4f);
	glRectd(240, 160, 65, -160);
	glRectd(-240, 160, -65, -160);
}
//noran
void stopGame(){
	speed = 0;
	steerSpeed = 0;
}
//noran
void resumeGame(){
    speed = 2;
    steerSpeed = 1;
}
//noran
void drawOther(){
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		drawOtherCars(i);
	}
}
//omar
void setCars(){
	int i;
	for(i = 0; i < MAX_CARS; i++)
	{
		lane[i] = i;
		pos[i] = 110 + rand()%100;
        speeds[i] = 1 + i + rand()%4;
	}
}
//ahmed
void moveDivider(){
	div_y -= speed;
	if(div_y < 120 && distance > 0)
    {
        div_y = 200;

        if(carMoveFast)
        {
            distance -= 1.5;
            fuel -=4;
        }
        else
        {

            distance -= 0.5;
            fuel -= 2;
        }

        if(fuel < 0)
            fuelOver = true;

        if(distance < 5)
            reachedEnd = true;

    }
}
//ali
void moveCar(){
	if(carMoveLeft)
		car_x -= steerSpeed;


	else if(carMoveRight)
		car_x += steerSpeed;

	if(car_x > 45 || car_x < -45)
    {
        game_state = 2;
        gameStopped = true;
    }
}
//nada
void moveRoad(){
	foot_y -= speed;
	if(foot_y < 160)
	{
		foot_y = 180;
		if(a == 0)
			a = 1;
		else
			a = 0;
	}
}
//fady
void periodicFunction(int v){
    if(gameStopped)
        stopGame();

    else
        resumeGame();

	if(speed != 0)
	{
		if(carMoveFast)
            speed = 6;

		else
            speed = 2;

	}

	if(fuelOver)
	{
        gameStopped = true;
        game_state = 2;

	}

	moveRoad();
	moveDivider();
	moveCar();
    moveOtherCars();
    moveEnd();
    moveFuel();

    if(!detectCollision() && !gameStopped && game_state == 1)
        temp += 15;

	if(temp > 1000)
    {
        temp  = 0;
        seconds++;
    }

	glutPostRedisplay();
	glutTimerFunc(10, periodicFunction, v);
}
//sama
void moveOtherCars(){
    int i;
    for(i = 0; i < MAX_CARS; i++)
    {
        pos[i] += -speed + speeds[i];

        if(pos[i] < -200 || pos[i] > 200)
        {
            pos[i] = 200 + rand()%100;
            speeds[i] = 2 + rand()%4;
        }
    }

    if(horn)
    {
        speeds[(car_x + 60)/40]++;
        if(speeds[(car_x + 60)/40] > 7)
            speeds[(car_x + 60)/40] = 7;
        horn = false;
    }

}

int detectCollision(){
    if(game_state != 1)
        return 0;

    int i, limit;
    for(i = 0; i < MAX_CARS; i++)
    {
        if(pos[i] < -70 && pos[i] > -130)
        {
            limit = (i - 1)*40;
            if(car_x < limit + 22 && car_x > limit - 22)
            {
                speeds[i] = 0;
                gameStopped = true;
                game_state = 2;
                return 1;
            }
        }
    }

    if((fuel_x > car_x && fuel_x - car_x < 20) || (fuel_x < car_x && car_x - fuel_x < 20))
    {
        if(fuel_y < -80 && fuel_y > -120)
        {
            fuel+=40;
            if(fuel > 178)
                fuel = 178;
            fuel_y = 600 + rand()%150;
            fuel_x = (rand()%3 - 1)*37;
        }
    }

    return 0;

}
//ahmed
void draw_string(std::string str){
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i)); //32 -> 127 //maximum top 119.05 units //the bottom descends 33.33 units
    }
}
//ahmed
void drawMainMenu(){
    //Draw start button
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    drawFootPath();
    drawSurroundings();
    drawDivider();
    drawCar();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-20, 30, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("START");

    glPopMatrix();

    //Draw exit button
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-15, -30, 0);
    glScalef(0.1, 0.1, 0.1);
    draw_string("EXIT");

    glPopMatrix();

    if(highlightStart)
    {
        glColor3f(0.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslated(0, 30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }

    if(highlightExit)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, -30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }
}
//sara
void drawExitMenu(){
    //Draw start button
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(0, 30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-25, 30, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("RESTART");

    glPopMatrix();

    //Draw exit button
    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();
    glTranslated(0, -30, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(30, 15);
        glVertex2f(30, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-15, -30, 0);
    glScalef(0.1, 0.1, 0.1);
    draw_string("EXIT");

    glPopMatrix();

    if(highlightStart)
    {
        glColor3f(0.0f, 1.0f, 0.0f);

        glPushMatrix();
        glTranslated(0, 30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }

    if(highlightExit)
    {
        glColor3f(1.0, 0.0, 0.0);

        glPushMatrix();
        glTranslated(0, -30, 0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(35, 20);
            glVertex2f(35, -20);
            glVertex2f(-35, -20);
            glVertex2d(-35, 20);
        glEnd();
        glPopMatrix();

    }
}
//sara
void drawTime(){
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslated(-200, 90, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(50, 15);
        glVertex2f(50, -15);
        glVertex2f(-30, -15);
        glVertex2d(-30, 15);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-220, 85, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 1.0, 1.0);
    draw_string("Time: ");
    glPopMatrix();

    glPushMatrix();
    glTranslated(-180, 85, 0);
    glScalef(0.1, 0.1, 0.1);
    glColor3f(1.0, 0.0, 0.0);
    //glutStrokeCharacter(GLUT_STROKE_ROMAN, '4');
    drawScore(seconds);
    glPopMatrix();
}
//sara
void drawScore(int score){
    int temp = score;
    int str[20],i=0;

    while(temp>0)
    {
        str[i++] = (temp%10);
        temp /= 10;
    }
    i--;
    while(i>=0)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i--]+'0');
    }
    if(score == 0) glutStrokeCharacter(GLUT_STROKE_ROMAN, '0');
}
//mazen
void drawDistanceBar(){
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);

    glTranslated(-75, 40, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5, 90);
        glVertex2f(5, -90);
        glVertex2f(-5, -90);
        glVertex2d(-5, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-75, -49, 0);
    glColor3f(0.9, 0.2, 0.2);
    glRectd(4, 0, -4, distance);
    glPopMatrix();

}
//mazen
void drawFuelBar(){
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);

    glTranslated(75, 40, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5, 90);
        glVertex2f(5, -90);
        glVertex2f(-5, -90);
        glVertex2d(-5, 90);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(75, -49, 0);
    glColor3f(0 , 1 , 0);
    glRectd(4, 0, -4, fuel);
    glPopMatrix();

}
//noran
void drawEnd(){
    int i, j;
    for(i = 0; i < 5; i++)
    {
        if(i % 2 == 0)
            glColor3f(0.0, 0.0, 0.0);
        else
            glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();

        glTranslated(-55 , end_y + 10*i, 0);

        for(j = 0; j < 11; j++)
        {
            if(i%2)
            {
                if(j % 2 == 0)
                    glColor3f(0.0, 0.0, 0.0);
                else
                    glColor3f(1.0, 1.0, 1.0);

            }

            else
            {
                if(j % 2)
                    glColor3f(0.0, 0.0, 0.0);
                else
                    glColor3f(1.0, 1.0, 1.0);
            }

            glRectd(10 * j,0,10*(j+1),10);
        }

        glPopMatrix();
    }
}
//fady
void fuelMessage(){
    glPushMatrix();
    glTranslated(75, -70, 0);
    glScalef(0.1,0.1,0.1);
    glColor3f(0, 1.0,0);
    draw_string("Fuel Exhausted\n");
    glPopMatrix();
}
//sara
void moveEnd(){
    if(reachedEnd)
        end_y-= speed;

    if(end_y < -125)
    {
        gameStopped = true;
        gameCompleted = true;
        game_state = 2;
    }
}
//sama
void drawFuel(){
    glPushMatrix();
    glTranslated(fuel_x, fuel_y, 0);
    glColor3f(0.0, 1.0, 0.0);
    glRectf(5, 5, -5, -5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(fuel_x, fuel_y+5, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(5, 0);
        glVertex2f(5, 5);
        glVertex2f(-3, 5);
        glVertex2d(-5, 0);
    glEnd();
    glPopMatrix();

}
//sama
void moveFuel(){
    fuel_y-=speed;

    if(fuel_y < -200)
    {
        fuel_y = 600 + rand()%150;
        fuel_x = (rand()%3 - 1)*37;
    }
}
//ali
int main(int argc, char *argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH );
	glutInitWindowSize((int) width, (int) height);
	glutCreateWindow("Graphic Project");
	glutFullScreen();


	gluOrtho2D(-240.0, 240.0, -160.0, 160.0);

	glutDisplayFunc(maindisp);
	glutTimerFunc(100, periodicFunction, 0);

    glutSpecialFunc(keyBoardFunc);
    glutSpecialUpFunc(keyboard_up_func);
    glutKeyboardFunc(normalKeyBoardFunc);
    glutMouseFunc(mouse_func);
    glutPassiveMotionFunc(mouse_hover);

	glutMainLoop();
	return 0;
}
