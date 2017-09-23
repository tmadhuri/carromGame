#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <sys/time.h>
#include <string.h>

#define PI 3.1417

using namespace std;

void drawUnfilledCircle(float x, float y, float z, float radius)
{
	float i;

	glLineWidth(1.4f);
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < (2 * PI); i += PI/36)
	{
		glVertex3f(x + radius * cos(i), y + radius * sin(i), z);
	}
	glEnd();
}

void drawFilledCircle(float x, float y, float z, float radius)
{
	int i;
	int triangleamount = 60;

	float twopi = 2 * PI;

	glBegin(GL_TRIANGLE_FAN);

	glVertex3f(x, y, z);

	for(i = 0; i <= triangleamount; i++)
	{
		glVertex3f(x + radius * cos(i * twopi / triangleamount), y + radius * sin(i * twopi / triangleamount), z);
	}

	glEnd();
}

void displayString(float x, float y, float z, float r, float g, float b, void* font, char *string)
{
  glColor3f( r, g, b );
  glRasterPos3f(x, y, z);
  int i;
  for (i = 0; string[i] != '\0'; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}

class Board
{
	float s;          //size of the board
	int points;		//score
	long long int t;	//time of the game

	public:
		Board()
		{
			s = 1.5f;
			points = 30;

			struct timeval tv;
			struct timezone tz;

			gettimeofday(&tv, &tz);

			t = tv.tv_sec;
		}

		//getters and setters
		float side()
		{
			return s;
		}

		void setPoints(int pts)
		{
			points = pts;
		}

		int getPoints()
		{
			return points;
		}

		long long int getTime()
		{
			return t;
		}

		void setTime(long long int tm)
		{
			t = tm;
		}

		//drawBoard
		void drawBoard();
};

void Board::drawBoard()
{
	float sz = s + 0.2f; //size of outer board

	//draw base of the board
	glBegin(GL_QUADS);

	glColor3f(0.2f, 0.0f, 0.0f);

	glVertex3f(-1 * sz, sz, 0.0f);
	glVertex3f(sz, sz, 0.0f);
	glVertex3f(sz, -1 * sz, 0.0f);
	glVertex3f(-1 * sz, -1 * sz, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	//draw inner board; main area of game play
	glColor3f(1.0f, 1.0f, 0.63f);
	
	glVertex3f(-1 * s, s, 0.01f);
	glVertex3f(s, s, 0.01f);
	glVertex3f(s, -1 * s, 0.01f);
	glVertex3f(-1 * s, -1 * s, 0.01f);

	glEnd();

	//draw pockets
	glColor3f(0.38f, 0.38f, 0.25f);
	drawFilledCircle(-1 * s + 0.08, s - 0.08, 0.02, 0.08);
	drawFilledCircle(s - 0.08, s - 0.08, 0.02, 0.08);
	drawFilledCircle(s - 0.08, -1 * s + 0.08, 0.02, 0.08);
	drawFilledCircle(-1 * s + 0.08, -1 * s + 0.08, 0.02, 0.08);

	//render lines on board

	glLineWidth(3.32f);
	glBegin(GL_LINE_LOOP);

	sz = s - 0.55f;

	glColor3f(0.0f, 0.0f, 0.0f);
	
	glVertex3f(-1 * sz, sz, 0.02f);
	glVertex3f(sz, sz, 0.02f);
	glVertex3f(sz, -1 * sz, 0.02f);
	glVertex3f(-1 * sz, -1 * sz, 0.02f);

	glEnd();

	glColor3f(0.63f, 0.0f, 0.0f);
	drawFilledCircle(-1 * sz + 0.06f, sz - 0.06f, 0.02f, 0.06f);
	drawFilledCircle(sz - 0.06f, sz - 0.06f, 0.02f, 0.06f);
	drawFilledCircle(sz - 0.06f, -1 * sz + 0.06f, 0.02f, 0.06f);
	drawFilledCircle(-1 * sz + 0.06f, -1 * sz + 0.06f, 0.02f, 0.06f);
	drawFilledCircle(0.0f, 0.0f, 0.02f, 0.05f);

	glColor3f(0.0f, 0.0f, 0.0f);

	drawFilledCircle(-1 * sz + 0.06f, sz - 0.06f, 0.02f, 0.08f);
	drawFilledCircle(sz - 0.06f, sz - 0.06f, 0.02f, 0.08f);
	drawFilledCircle(sz - 0.06f, -1 * sz + 0.06f, 0.02f, 0.08f);
	drawFilledCircle(-1 * sz + 0.06f, -1 * sz + 0.06f, 0.02f, 0.08f);
	drawFilledCircle(0.0f, 0.0f, 0.02f, 0.06f);

	drawUnfilledCircle(0.0f, 0.0f, 0.02f, 0.3f);
	drawUnfilledCircle(0.0f, 0.0f, 0.02f, 0.34f);
}

class Coin
{
	int color; 
	float vel_x;
	float vel_y;
	float cen_x;
	float cen_y;
	float cen_z;
	float radius;

	public:
		int tm;
		int status;

		Coin()
		{
			color = -1;
			vel_x = vel_y = 0.0f;
			cen_x = cen_y = 0.0f;
			cen_z = 0.08f;
			radius = 0.06f;
			tm = 0;
			status = 1;
		}

		void drawCoin();

		//getters and setters
		void setColor(int c)
		{
			color = c;
		}

		void set_xCoord(float x)
		{
			cen_x = x;
		}

		void set_yCoord(float y)
		{
			cen_y = y;
		}

		void set_zCoord(float z)
		{
			cen_z = z;
		}

		float get_xCoord()
		{
			return cen_x;
		}

		float get_yCoord()
		{
			return cen_y;
		}

		float getRadius()
		{
			return radius;
		}

		void set_xVel(float vel)
		{
			vel_x = vel;
		}

		void set_yVel(float vel)
		{
			vel_y = vel;
		}

		float get_xVel()
		{
			return vel_x;
		}

		float get_yVel()
		{
			return vel_y;
		}

		int getColor()
		{
			return color;
		}
};

void Coin::drawCoin()
{
	glColor3f(0.0f, 0.0f, 0.0f);
	drawUnfilledCircle(cen_x, cen_y, cen_z, radius);

	if(color == 0)
		glColor3f(0.0f, 0.0f, 0.0f);
	else if(color == 1)
		glColor3f(1.0f, 1.0f, 1.0f);
	else if(color == 2)
		glColor3f(1.0f, 0.0f, 0.0f);

	drawFilledCircle(cen_x, cen_y, cen_z, radius);
}

class Striker
{
	float vel_x;
	float vel_y;
	float cen_x;
	float cen_y;
	float cen_z;
	float radius;
	float angle;

	public:
		int move;
		int tm;

		Striker()
		{
			vel_x = vel_y = 0.0f;
			
			cen_x = 0.0f;
			cen_y = -0.875f;
			cen_z = 0.05f;
			
			radius = 0.075f;

			angle = 0.00f;

			move = 0;
			tm = 0;
		}

		void drawStriker();

		float get_xCoord()
		{
			return cen_x;
		}

		void set_xCoord(float x)
		{
			cen_x = x;
		}

		float get_yCoord()
		{
			return cen_y;
		}

		void set_yCoord(float y)
		{
			cen_y = y;
		}

		void set_zCoord(float z)
		{
			cen_z = z;
		}

		float getAngle()
		{
			return angle;
		}

		void setAngle(float a)
		{
			angle = a;
		}

		float get_xVel()
		{
			return vel_x;
		}

		float get_yVel()
		{
			return vel_y;
		}

		void set_xVel(float vel)
		{
			vel_x = vel;
		}

		void set_yVel(float vel)
		{
			vel_y = vel;
		}

		float getRadius()
		{
			return radius;
		}
};

void Striker::drawStriker()
{
	glColor3f(0.0f, 0.0f, 1.0f);

	drawFilledCircle(cen_x, cen_y, cen_z, radius);

	if(move == 0)
	{
		glPushMatrix();
		glTranslatef(cen_x, cen_y, cen_z);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);

		glBegin(GL_TRIANGLES);

		glColor3f(0.0f, 0.0f, 0.0f);

		glVertex3f(-1 * 0.025f, radius + 0.01f, 0.0f);
		glVertex3f(0.025f, radius + 0.01f, 0.0f);
		glVertex3f(0.0f, radius + 0.05, 0.0f);

		glPopMatrix();

		glEnd();
	}
}


Board b;
Coin coins[11];
Striker striker;
int move = 0, power = 0;


void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void handleKeypress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);

		case 97:
			striker.setAngle(striker.getAngle() + 10);
			break;

		case 99:
			striker.setAngle(striker.getAngle() - 10);
			break;

		case 32:
			striker.move = 1;
	}
}

void handleSpecialKeypress(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			if((striker.get_xCoord() - 0.09f) > -0.95f)
			{
				striker.set_xCoord(striker.get_xCoord() - 0.02f);
			}
			break;

		case GLUT_KEY_RIGHT:
			if((striker.get_xCoord() + 0.09f) < 0.95f)
			{
				striker.set_xCoord(striker.get_xCoord() + 0.02f);
			}
			break;

		case GLUT_KEY_UP:
			if(striker.move == 0 && power < 10)
			{
				striker.set_xVel(striker.get_xVel() + sin(striker.getAngle() * PI / 180) * -0.3f);
				striker.set_yVel(striker.get_yVel() + cos(striker.getAngle() * PI / 180) * 0.3f);
				power++;
			}
			break;

		case GLUT_KEY_DOWN:
			if(striker.move == 0 && power < 10)
			{
				striker.set_xVel(striker.get_xVel() - sin(striker.getAngle() * PI / 180) * -0.3f);
				striker.set_yVel(striker.get_yVel() - cos(striker.getAngle() * PI / 180) * 0.3f);
				power--;
			}
			break;
	}
}

void handleMouseclick(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		move = 1;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		float pt_x = ((float)x - 600.0f) / 100.0f;
		float pt_y = ((float)y - 600.0f) / 100.0f;

		power = sqrt(pow(pt_x - striker.get_xCoord(), 2) + pow(pt_y - striker.get_yCoord(), 2)) / 0.34121;

		if(striker.move == 0)
		{
			striker.set_xVel(striker.get_xVel() + power * sin(atan2(pt_x - striker.get_xCoord(), pt_y - striker.get_yCoord())) * 0.05f);
			striker.set_yVel(striker.get_yVel() + power * cos(atan2(pt_x - striker.get_xCoord(), pt_y - striker.get_yCoord())) * -0.05f);
		}
	}
	else if(state == GLUT_UP)
	{
		if(move == 1)
			move = 0;
		else
			striker.move = 1;
	}
}

void handleMousedrag(int x, int y)
{
	if(move == 1 && (((float)x - 600.0f) / 180.0f) > -0.87 && (((float)x - 600.0f) / 180.0f) < 0.87)
	{
		striker.set_xCoord(((float)x - 600.0f) / 180.0f);
	}
	else if(move == 1 && (((float)x - 600.0f) / 180.0f) < -0.87)
	{
		striker.set_xCoord(-0.87);
	}
	else if(move == 1 && (((float)x - 600.0f) / 180.0f) > 0.87)
	{
		striker.set_xCoord(0.87);
	}
}

void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	//counting number red, white and black coins scored
	int num_red = 0, num_white = 0, num_black = 0;

	int i;
	for(i = 0; i < 11; i++)
	{
		if(coins[i].status == 0)
		{
			if(coins[i].getColor() == 0)
				num_black++;
			else if(coins[i].getColor() == 1)
				num_white++;
			else if(coins[i].getColor() == 2)
				num_red++;
		}
	}

	//if score > 0, play game else show result
	if(b.getPoints() > 0 && (num_white < 5 || num_red == 0))
	{
		//draw board
		glPushMatrix();

		b.drawBoard();

		glPopMatrix();

		//draw coins
		int i, j;
		for(i = 0; i < 11; i++)
		{
			glPushMatrix();

			if(coins[i].getColor() == -1)
			{
				if(i == 10)
					coins[i].setColor(2);
				else if((i % 2) == 0)
					coins[i].setColor(1);
				else
					coins[i].setColor(0);

				if(i != 10)
				{
					coins[i].set_xCoord(0.24f * cos(PI * i * 2 / 10));
					coins[i].set_yCoord(0.24f * sin(PI * i * 2 / 10));
				}
			}

			if(coins[i].status == 1)
				coins[i].drawCoin();

			glPopMatrix();
		}

		//draw striker
		glPushMatrix();

		striker.drawStriker();

		glPopMatrix();

		//display score
		glPushMatrix();

		displayString(-2.5f, 1.0f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Score");

		int score = b.getPoints();

		char str[5];
		i = 0, j = 100;

		if(score < 0)
		{
			str[0] = '-';
			i++;
		}

		while(j)
		{
			str[i++] = abs(score / j) % 10 + '0';
			j = j / 10;
		}

		str[i] = '\0';

		displayString(-2.5f, 0.75f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, str);	

		glPopMatrix();

		//display power
		glPushMatrix();

		displayString(-2.5f, -0.75f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Power");

		i = 0, j = 100;

		while(j)
		{
			str[i++] = abs(power / j) % 10 + '0';
			j = j / 10;
		}

		str[i] = '\0';

		displayString(-2.5f, -1.00f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, str);	

		glPopMatrix();
	}
	else
	{
		//display result
		if(num_white == 5 && num_red == 1)
		{
			displayString(-0.5f, 1.00f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"You Won!!");
		}
		else
		{
			displayString(-0.5f, 1.00f, 0.9f, 0.0f, 0.0f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, (char *)"Game Over!!");
		}
	}

	glutSwapBuffers();
}

void update(int value)
{
	//collision : striker- board
	if((striker.get_xCoord() + striker.getRadius()) >= b.side() || (striker.get_xCoord() - striker.getRadius()) <= -1 * b.side())
	{
		if(striker.get_xCoord() + striker.getRadius() >= b.side())
			striker.set_xCoord(striker.get_xCoord() - 0.035f);
		else
			striker.set_xCoord(striker.get_xCoord() + 0.035);

		striker.set_xVel(-0.6 * striker.get_xVel() * striker.move);
		striker.tm = 0;
	}

	if(striker.get_yCoord() + striker.getRadius() >= b.side() || striker.get_yCoord() - striker.getRadius() <= -1 * b.side())
	{
		if(striker.get_yCoord() + striker.getRadius() >= 1.5f)
			striker.set_yCoord(striker.get_yCoord() - 0.035f);
		else
			striker.set_yCoord(striker.get_yCoord() + 0.035);

		striker.set_yVel(-0.6 * striker.get_yVel() * striker.move);
		striker.tm = 0;
	}

	int i, j;

	for(i = 0; i < 11; i++)
	{	
		//collision : striker - coin
		float dist = pow((coins[i].get_xCoord() - striker.get_xCoord()), 2) + pow((coins[i].get_yCoord() - striker.get_yCoord()), 2);
		float sum_radii = pow((coins[i].getRadius() + striker.getRadius()), 2);

		if(dist <= sum_radii)
		{
			float striker_x = striker.get_xVel() * striker.move;
			float striker_y = striker.get_yVel() * striker.move;

			striker.set_xVel(0.666f * 0.5 * striker.get_xVel() * striker.move + 0.333f * 0.5 * coins[i].get_xVel());
			striker.set_yVel(0.666f * 0.5 * striker.get_yVel() * striker.move + 0.333f * 0.5 * coins[i].get_yVel());

			coins[i].set_xVel(0.668f * 0.5 * striker_x + 0.334f * 0.5 * coins[i].get_xVel());
			coins[i].set_yVel(0.668f * 0.5 * striker_y + 0.334f * 0.5 * coins[i].get_yVel());

			striker.tm = 0;
			coins[i].tm = 0;
		}

		//collision : coin - board
		if((coins[i].get_xCoord() + coins[i].getRadius()) >= b.side() || (coins[i].get_xCoord() - coins[i].getRadius()) <= -1 * b.side())
		{
			if(coins[i].get_xCoord() + coins[i].getRadius() >= b.side())
				coins[i].set_xCoord(coins[i].get_xCoord() - 0.035);
			else
				coins[i].set_xCoord(coins[i].get_xCoord() + 0.035);

			coins[i].set_xVel(-0.6 * coins[i].get_xVel() * striker.move);
			coins[i].tm = 0;
		}

		if(coins[i].get_yCoord() + coins[i].getRadius() >= b.side() || coins[i].get_yCoord() - coins[i].getRadius() <= -1 * b.side())
		{
			if(coins[i].get_yCoord() + coins[i].getRadius() >= b.side())
				coins[i].set_yCoord(coins[i].get_yCoord() - 0.035);
			else
				coins[i].set_yCoord(coins[i].get_yCoord() + 0.035);

			coins[i].set_yVel(-0.6 * coins[i].get_yVel() * striker.move);
			coins[i].tm = 0;
		}

		//collision : coin - coin
		for(j = i + 1; j < 11; j++)
		{
			dist = pow((coins[i].get_xCoord() - coins[j].get_xCoord()), 2) + pow((coins[i].get_yCoord() - coins[j].get_yCoord()), 2);
			sum_radii = pow((coins[i].getRadius() + coins[j].getRadius()), 2);

			if(dist <= sum_radii)
			{
				float temp_x = coins[j].get_xVel();
				float temp_y = coins[j].get_yVel();

				coins[j].set_xVel(0.505f * coins[i].get_xVel() + 0.495f * coins[j].get_xVel());
				coins[j].set_yVel(0.505f * coins[i].get_yVel() + 0.495f * coins[j].get_yVel());

				coins[i].set_xVel(0.495f * coins[i].get_xVel() + 0.505f * temp_x);
				coins[i].set_yVel(0.495f * coins[i].get_yVel() + 0.505f * temp_y);

				coins[i].tm = 0;
			}
		}

		//friction : coin - board
		if(coins[i].get_xVel() != 0 || coins[i].get_yVel() != 0)
		{
			coins[i].tm++;

			if(coins[i].get_xVel() > 0.001)
			{
				coins[i].set_xVel(coins[i].get_xVel() - 0.00784f * coins[i].tm * 0.001f * cos(atan2(coins[i].get_yVel(), coins[i].get_xVel())));
			}
			else if(coins[i].get_xVel() < -0.001)
			{
				coins[i].set_xVel(coins[i].get_xVel() + 0.00784f * coins[i].tm * 0.001f * cos(atan2(coins[i].get_yVel(), coins[i].get_xVel())));
			}
			else
			{
				coins[i].set_xVel(0.0f);
			}

			if(coins[i].get_yVel() > 0.001)
			{
				coins[i].set_yVel(coins[i].get_yVel() - 0.00784f * coins[i].tm * 0.001f * sin(atan2(coins[i].get_yVel(), coins[i].get_xVel())));
			}
			else if(coins[i].get_yVel() < -0.001)
			{
				coins[i].set_yVel(coins[i].get_yVel() + 0.00784f * coins[i].tm * 0.001f * sin(atan2(coins[i].get_yVel(), coins[i].get_xVel())));
			}
			else
			{
				coins[i].set_yVel(0.0f);
			}

			if(sqrt(pow(coins[i].get_xVel(), 2) + pow(coins[i].get_yVel(), 2)) < 0.005f)
			{
				coins[i].set_xVel(0.0f);
				coins[i].set_yVel(0.0f);
			}
		}
	}

	//friction : striker - board
	if(striker.get_xVel() != 0 || striker.get_yVel() != 0)
	{
		striker.tm++;

		if(striker.get_xVel() > 0)
		{
			striker.set_xVel(striker.get_xVel() - 0.00784f * striker.tm * 0.001f * cos(atan2(striker.get_yVel(), striker.get_xVel())));
		}
		else
		{
			striker.set_xVel(striker.get_xVel() + 0.00784f * striker.tm * 0.001f * cos(atan2(striker.get_yVel(), striker.get_xVel())));
		}

		if(striker.get_yVel() > 0)
		{
			striker.set_yVel(striker.get_yVel() - 0.00784f * striker.tm * 0.001f * sin(atan2(striker.get_yVel(), striker.get_xVel())));	
		}
		else
		{
			striker.set_yVel(striker.get_yVel() + 0.00784f * striker.tm * 0.001f * sin(atan2(striker.get_yVel(), striker.get_xVel())));
		}
	}

	//reset striker
	int set_striker = 1;

	if((abs(striker.get_xVel()) > 0.001f || abs(striker.get_yVel()) > 0.001f) || striker.move == 0)
	{
		set_striker = 0;
	}

	for(i = 0; i < 11; i++)
	{
		if(abs(coins[i].get_xVel()) > 0.001f || abs(coins[i].get_yVel()) > 0.001f)
		{
			set_striker = 0;
		}
	}

	if(set_striker == 1)
	{
		striker.move = 0;
		striker.tm = 0;

		striker.set_xCoord(0.0f);
		striker.set_yCoord(-0.875f);
		striker.set_zCoord(0.05f);

		striker.setAngle(0.00f);

		for(i = 0; i < 50000000; i++);

		glPushMatrix();
		striker.drawStriker();
		glPopMatrix();

		//striker.set_xVel(0.0f);
		//striker.set_yVel(0.0f);
		power = 0;

		for(i = 0; i < 11; i++)
		{
			coins[i].set_xVel(0.0f);
			coins[i].set_yVel(0.0f);
		}
	}

	//update striker position
	striker.set_xCoord(striker.get_xCoord() + (striker.get_xVel() * striker.move));
	striker.set_yCoord(striker.get_yCoord() + (striker.get_yVel() * striker.move));

	//update coin position
	for(i = 0; i < 11; i++)
	{
		if(coins[i].get_xCoord() < b.side() && coins[i].get_xCoord() > -1 * b.side())
			coins[i].set_xCoord(coins[i].get_xCoord() + coins[i].get_xVel());
		if(coins[i].get_yCoord() < b.side() && coins[i].get_yCoord() > -1 * b.side())
			coins[i].set_yCoord(coins[i].get_yCoord() + coins[i].get_yVel());
	}

	//pocketin : striker
	float x = striker.get_xCoord();
	float y = striker.get_yCoord();

	if(pow(x + b.side() - 0.08f, 2) + pow(y + b.side() - 0.08f, 2) <= 0.0064f 
		|| pow(x + b.side() - 0.08f, 2) + pow(y - b.side() + 0.08f, 2) <= 0.0064f 
		|| pow(x - b.side() + 0.08f, 2) + pow(y - b.side() + 0.08f, 2) <= 0.0064f 
		|| pow(x - b.side() + 0.08f, 2) + pow(y + b.side() - 0.08f, 2) <= 0.0064f)
	{
		striker.set_xVel(0.0f);
		striker.set_yVel(0.0f);

		striker.set_zCoord(0.03f);

		b.setPoints(b.getPoints() - 5);
		
		glPushMatrix();
		striker.drawStriker();
		glPopMatrix();

		for(i = 0; i < 10000000; i++);
	}
	
	//pocketing : coins
	for(i = 0; i < 11; i++)
	{
		x = coins[i].get_xCoord();
		y = coins[i].get_yCoord();

		if(pow(x + b.side() - 0.08f, 2) + pow(y + b.side() - 0.08f, 2) <= 0.0064 
			|| pow(x + b.side() - 0.08f, 2) + pow(y - b.side() + 0.08f, 2) <= 0.0064 
			|| pow(x - b.side() + 0.08f, 2) + pow(y - b.side() + 0.08f, 2) <= 0.0064 
			|| pow(x - b.side() + 0.08f, 2) + pow(y + b.side() - 0.08f, 2) <= 0.0064)
		{
			coins[i].set_xVel(0.0f);
			coins[i].set_yVel(0.0f);

			coins[i].set_zCoord(0.03f);

			if(coins[i].getColor() == 0 && coins[i].status == 1)
			{
				b.setPoints(b.getPoints() - 5);
			}
			else if(coins[i].getColor() == 1 && coins[i].status == 1)
			{	
				b.setPoints(b.getPoints() + 10);
			}
			else if(coins[i].getColor() == 2 && coins[i].status == 1)
			{	
				b.setPoints(b.getPoints() + 50);
			}

			for(j = 0; j < 10000000; j++);

			coins[i].set_xCoord(2.0f);
			coins[i].set_yCoord(2.0f);
			coins[i].set_zCoord(0.0f);

			coins[i].status = 0;
		}
	}

	//timer for score
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);

	if(tv.tv_sec > b.getTime())
	{
		b.setPoints(b.getPoints() - (tv.tv_sec - b.getTime()));
		b.setTime(tv.tv_sec);
	}

	glutPostRedisplay();
	glutTimerFunc(10, update, 0);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 800);

	glutCreateWindow("Carrom");
	initRendering();

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutSpecialFunc(handleSpecialKeypress);
	glutMotionFunc(handleMousedrag);
	glutMouseFunc(handleMouseclick);

	glutTimerFunc(10, update, 0);

	glutMainLoop();

	return 0;
}