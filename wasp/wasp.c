#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

GLUquadricObj *p;
GLfloat theta[5] = { 0.0, 0.0, 0.0, 0.0 ,0.0};//
GLboolean bas = GL_FALSE;//Used to indicate whether to rotate
GLboolean win= GL_FALSE;//Used to turn on flight mode
GLboolean wing= GL_FALSE;//Used to indicate whether the wings are up or down
GLboolean jump = GL_FALSE;//Used to turn on jump mode
GLfloat position[3] = { 0.0, 0.0, 0.0 };//Randomly generated location
GLfloat range[3][2] = { {0.0,0.0},{0.0,0.0},{0.0,0.0} };//Range used for random
GLint bj = 0;
GLboolean new_jump= GL_FALSE;//Used to turn on jump mode which is CW required
GLint angle = 70;//Wings can reach the highest angle
GLint lowAngle = -5;//Wings can reach the lowest angle
GLint xt = 1;//Light Mode
GLint speed = 10;//Wings flapping speed
GLfloat a = 0.00004;//Bouncing acceleration
GLfloat jsp = 0.02;//Used to store the current jump speed
GLfloat setjsp = 0.02;//Set initial speed
//GLfloat res[3] = {0.0f,0.0f,0.0f};
GLfloat ambientLight_evening[] = { 0.2f,0.2f,0.2f,1.0f };// Late evening light
GLfloat diffuseLight_evening[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat specularLight_evening[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat lightpos_evening[] = { 1.0f,3.0f,1.0f,0.0f };// Late evening light position

GLfloat ambientLight_noon[] = { 0.4f,0.4f,0.4f,1.0f };//Noon light
GLfloat diffuseLight_noon[] = { 0.9f,0.9f,0.9f,1.0f };
GLfloat specularLight_noon[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightpos_noon[] = { 0.1f,1.0f,0.1f,0.0f };

GLfloat ambientLight_dusk[] = { 0.25f,0.2f,0.2f,1.0f };//Dusk light
GLfloat diffuseLight_dusk[] = { 0.9f,0.6f,0.4f,1.0f };
GLfloat specularLight_dusk[] = { 1.0f,0.70f,0.50f,1.0f };
GLfloat lightpos_dusk[] = { 0.0f,3.0f,-2.0f,0.0f };

GLfloat no_mat[] ={ 0.0f, 0.0f, 0.0f, 1.0f };        // No material color
GLfloat mat_ambient[3][4] = {{ 0.7f, 0.7f, 0.7f, 1.0f },{ 0.7f, 0.7f, 0.7f, 1.0f },{ 0.7f, 0.7f, 0.7f, 1.0f }};   // Ambient color
//GLfloat mat_ambient_color[] = { 0.6f, 0.6f, 0.6f, 1.0f };
GLfloat mat_diffuse[3][4] = {{ 0.5f, 0.5f, 0.5f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f }, { 0.5f, 0.5f, 0.5f, 1.0f }};   // Scattering color
GLfloat mat_specular[3][4] = {{ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f, 1.0f, 1.0f }};  // Mirror reflection color
GLfloat no_shininess[] = { 0.0f };                    // The specular reflection index is 0
GLfloat low_shininess[] = { 5.0f };                   // The specular reflection index is 5.0
GLfloat high_shininess[] = { 100.0f };                // The specular reflection index is 100.0
GLfloat mat_emission[3][4] = { { 0.3f, 0.3f, 0.3f, 0.0f } ,{ 0.3f, 0.3f, 0.3f, 0.0f } ,{ 0.3f, 0.3f, 0.3f, 0.0f } };  // The color of the emitted light
GLfloat foot_mat_ambient[3][4] = { { 0.05f,0.05f,0.05f,1.0f } ,{ 0.5f,0.5f,0.5f,1.0f }, { 0.05f,0.05f,0.05f,1.0f } };//foot Ambient
GLfloat foot_mat_diffuse[3][4] = { { 0.1f,0.1f,0.1f,1.0f } ,{  0.5f,0.5f,0.5f,1.0f } ,{ 0.05f,0.05f,0.05f,1.0f } };//foot diffuse color
GLfloat abdomen_mat_ambient[3][4] = { { 0.863f,0.66f,0.41f,1.0f } ,{ 0.7f,0.7f,0.7f,1.0f } ,{ 0.15f,0.15f,0.15f,1.0f } };//abdomen Ambient 
GLfloat abdomen_mat_diffuse[3][4] = { { 0.863f,0.66f,0.41f,1.0f } ,{ 0.7f,0.7f,0.7f,1.0f } ,{ 0.15f,0.15f,0.15f,1.0f } };//abdomen diffuse color
GLfloat stinger_mat_ambient[3][4] = { { 0.75f,0.75f,0.75f,1.0f } ,{ 0.8f,0.8f,0.8f,1.0f } ,{ 0.3f,0.3f,0.3f,1.0f } };//stinger Ambient 
GLfloat stinger_mat_diffuse[3][4] = { { 0.7f,0.7f,0.7f,1.0f } ,{ 0.8f,0.8f,0.8f,1.0f } ,{ 0.3f,0.3f,0.3f,1.0f } };//stinger diffuse color
GLfloat body_mat_ambient[3][4] = { { 0.65f,0.3f,0.0f,1.0f } ,{ 0.6f,0.6f,0.6f,1.0f } ,{ 0.13f,0.13f,0.13f,1.0f } };//body Ambient 
GLfloat body_mat_diffuse[3][4] = { { 0.65f,0.28f,0.0f,1.0f } ,{ 0.6f,0.6f,0.6f,1.0f } ,{ 0.13f,0.13f,0.13f,1.0f } };//body diffuse color
GLfloat head_mat_ambient[3][4] = { { 0.35f,0.18f,0.0f,1.0f } ,{ 0.55f,0.55f,0.55f,1.0f } ,{ 0.15f,0.15f,0.15f,1.0f } };//head Ambient 
GLfloat head_mat_diffuse[3][4] = { { 0.35f,0.17f,0.0f,1.0f } ,{ 0.55f,0.55f,0.55f,1.0f } ,{ 0.15f,0.15f,0.15f,1.0f } };//head diffuse color
GLfloat dark_red_mat_ambient[] = { 0.47f, 0.0f, 0.0f, 1.0f };//Special red color
GLfloat dark_red_mat_diffuse[] = { 0.47f, 0.0f, 0.0f, 1.0f };
//GLfloat sss[][2] = { {1.0,21.0},{12.0,3.2} };
GLint menur;
GLint menul;
GLint mat=0;

void reshape(int w, int h)//When changing the window size, keep the model scale
{
	if (h == 0) {//Avoid h to 0
		h = 1;
	}
	if (w == 0) {//Avoid w to 0
		w = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();//Reset matrix
	if (w <= h) {//Modify Ortho window, make a scale model unchanged
		glOrtho(-11.0, 11.0, -11.0* h / w, 11.0* h / w, -15.0, 15.0);
		range[0][0] = -33.0;
		range[0][1] = 33.0;
		range[1][0] = -33.0* h / w;
		range[1][1] = 33.0* h / w;
		range[2][0] = -45.0;
		range[2][1] = 45.0;
	}
	else {
		glOrtho(-11.0* w / h, 11.0* w / h, -11.0, 11.0, -15.0, 15.0);
		range[0][0] = -33.0* w / h;
		range[0][1] = 33.0* w / h;
		range[1][0] = -33.0;
		range[1][1] = 33.0;
		range[2][0] = -45.0;
		range[2][1] = 45.0;
	}
}

void mykey(unsigned char key, int x, int y)//Preset several keyboard listeners for testing rotation, flying, bouncing
{
	if (key == 'R' | key == 'r')
		bas = !bas;
	if (key == 'W' | key == 'w')
		win = !win;
	if (key == 'J' | key == 'j') {
		//jump = !jump;
		jump = GL_TRUE;
	}
	if (key == 'Z' | key == 'z')
		xt = 1;
	if (key == 'X' | key == 'x')
		xt = 2;
	if (key == 'C' | key == 'c')
		xt = 3;
}

void idle()
{
	if (bas) {//Rotate
		theta[0] += 0.01;
		if (theta[0] > 360) theta[0] -= 360;
	};
	if (win) {//Wings wings
		if (wing) {//Wings up wings
			theta[1] += 0.01*speed;
			theta[3] += 8 / (angle / (0.01*speed));
			theta[4] += 10 / (angle / (0.01*speed));
			if (theta[1] >= angle) {
				wing = !wing;
			}
		}
		else {//Wings down wings
			theta[1] -= 0.01*speed;
			theta[3] -= 8 / (angle / (0.01*speed));
			theta[4] -= 10 / (angle / (0.01*speed));
			if (theta[1] < lowAngle) {
				wing = !wing;
			}
		}
	};
	if (jump) {//Bounce with acceleration
		theta[2] += jsp;
		//printf("%.2f\n", jsp);
		jsp -= a;//a represents acceleration
		if (theta[2] <= 0) {
			jump = !jump;
			jsp = setjsp;
			//theta[2] = 0;
		}
	}
	else {
		theta[2] = 0;
	};
	/*
	GLboolean new_jump= GL_FALSE;//Used to turn on jump mode which is CW required
	GLfloat position[3] = { 0.0, 0.0, 0.0 };//Randomly generated location
	GLfloat range[3][2] = { {0.0,0.0},{0.0,0.0},{0.0,0.0} };//Range used for random
	*/
	if (new_jump) {//Random displacement
		position[0] = (rand() / (double)(RAND_MAX))*(range[0][1] - range[0][0]) + range[0][0];
		position[1] = (rand() / (double)(RAND_MAX))*(range[1][1] - range[1][0]) + range[1][0];
		position[2] = (rand() / (double)(RAND_MAX))*(range[2][1] - range[2][0]) + range[2][0];
		new_jump = !new_jump;
	};
	glutPostRedisplay();
}

void normalVector(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3) {
	GLfloat x= y1 * z2 + y2 * z3 + y3 * z1 - y1 * z3 - y2 * z1 - y3 * z2;
	GLfloat y= -(x1 * z2 + x2 * z3 + x3 * z1 - x3 * z2 - x2 * z1 - x1 * z3);
	GLfloat z= x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
	GLfloat e = sqrt(x * x + y * y + x * x);
	glNormal3f(x/e,y/e,z/e);
}

void material(int i) {
	switch (i) {
	case 1:
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[mat]);//Test material No reflection
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 2:
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[mat]);//Test material Low light reflection
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[mat]);
		glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission[mat]);
		break;
	case 3:
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient[mat]);//Test material High light reflection
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[mat]);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 4:
		glMaterialfv(GL_FRONT, GL_AMBIENT, foot_mat_ambient[mat]);//foot material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, foot_mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 5:
		glMaterialfv(GL_FRONT, GL_AMBIENT, abdomen_mat_ambient[mat]);//abdomen material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, abdomen_mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 6:
		glMaterialfv(GL_FRONT, GL_AMBIENT, stinger_mat_ambient[mat]);//stinger material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, stinger_mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular[mat]);
		glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 7:
		glMaterialfv(GL_FRONT, GL_AMBIENT, body_mat_ambient[mat]);//body material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, body_mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 8:
		glMaterialfv(GL_FRONT, GL_AMBIENT, head_mat_ambient[mat]);//head material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, head_mat_diffuse[mat]);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	case 9:
		glMaterialfv(GL_FRONT, GL_AMBIENT, dark_red_mat_ambient);//head material
		glMaterialfv(GL_FRONT, GL_DIFFUSE, dark_red_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_mat);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		break;
	}
}

void light(int i) {//Set the lights
	glEnable(GL_LIGHTING);
	switch (i) {
	case 1://Late evening
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight_evening);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_evening);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight_evening);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos_evening);
		break;
	case 2://Noon sunshine
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight_noon);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_noon);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight_noon);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos_noon);
		break;
	case 3://Early evening sunshine
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight_dusk);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_dusk);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight_dusk);
		glLightfv(GL_LIGHT0, GL_POSITION, lightpos_dusk);
		break;
	}
	glEnable(GL_LIGHT0);
}

void init()//Pretreatment
{
	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);//The environment is set to sky blue
	p = gluNewQuadric();
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);//Set counterclockwise positive
	glEnable(GL_NORMALIZE);//Enable normal vector
	//glEnable(GL_POLYGON_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	xt = 2;//Set the lighting mode
}

void antenna() {//Make the antenna model
	glPushMatrix();
	material(4);//Using a material similar to foot
	glColor3ub(110, 110, 110);
	glBegin(GL_TRIANGLES);
		normalVector(-0.4f, 0.8f, -3.0f, -0.6f, 1.6f, -3.5f, -0.6f, 1.3f, -3.5f);
		glVertex3f(-0.4f, 0.8f,-3.0f);
		glVertex3f(-0.6f, 1.6f, -3.5f);
		glVertex3f(-0.6f, 1.3f, -3.5f);

		normalVector(-0.4f, 0.8f, -3.0f, -0.6f, 1.3f, -3.5f, -0.6f, 1.6f, -3.5f);
		glVertex3f(-0.4f, 0.8f, -3.0f);
		glVertex3f(-0.6f, 1.3f, -3.5f);
		glVertex3f(-0.6f, 1.6f, -3.5f);

		normalVector(0.4f, 0.8f, -3.0f, 0.6f, 1.6f, -3.5f, 0.6f, 1.3f, -3.5f);
		glVertex3f(0.4f, 0.8f, -3.0f);
		glVertex3f(0.6f, 1.6f, -3.5f);
		glVertex3f(0.6f, 1.3f, -3.5f);

		normalVector(0.4f, 0.8f, -3.0f, 0.6f, 1.3f, -3.5f, 0.6f, 1.6f, -3.5f);
		glVertex3f(0.4f, 0.8f, -3.0f);
		glVertex3f(0.6f, 1.3f, -3.5f);
		glVertex3f(0.6f, 1.6f, -3.5f);
	glEnd();
	glBegin(GL_QUADS);
		normalVector(0.8f, 1.1f, -4.0f, 0.8f, 0.9f, -4.0f, 0.6f, 1.3f, -3.5f);
		glVertex3f(0.8f,1.1f,-4.0f);
		glVertex3f(0.8f, 0.9f, -4.0f);
		glVertex3f(0.6f, 1.3f, -3.5f);
		glVertex3f(0.6f, 1.6f, -3.5f);

		normalVector(0.8f, 1.1f, -4.0f, 0.6f, 1.6f, -3.5f, 0.6f, 1.3f, -3.5f);
		glVertex3f(0.8f, 1.1f, -4.0f);
		glVertex3f(0.6f, 1.6f, -3.5f);
		glVertex3f(0.6f, 1.3f, -3.5f);
		glVertex3f(0.8f, 0.9f, -4.0f);

		normalVector(-0.8f, 1.1f, -4.0f, -0.8f, 0.9f, -4.0f, -0.6f, 1.3f, -3.5f);
		glVertex3f(-0.8f, 1.1f, -4.0f);
		glVertex3f(-0.8f, 0.9f, -4.0f);
		glVertex3f(-0.6f, 1.3f, -3.5f);
		glVertex3f(-0.6f, 1.6f, -3.5f);

		normalVector(-0.8f, 1.1f, -4.0f, -0.6f, 1.6f, -3.5f, -0.6f, 1.3f, -3.5f);
		glVertex3f(-0.8f, 1.1f, -4.0f);
		glVertex3f(-0.6f, 1.6f, -3.5f);
		glVertex3f(-0.6f, 1.3f, -3.5f);
		glVertex3f(-0.8f, 0.9f, -4.0f);
	glEnd();
	glPopMatrix();
}

void Mouthparts() {//Make the antenna model
	glPushMatrix();//Material used in the buffer before
	//glRotatef(theta[4], 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, -2.8f);
	glColor3ub(105, 105, 105);
	glPushMatrix();
	glRotatef(-theta[4], 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		normalVector(0.3f, 0.0f, 0.0f, 0.3f, 0.2f, 0.0f, 0.8f, -0.3f, 0.0f);
		glVertex3f(0.3f,0.0f,0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);
		glVertex3f(0.8f,-0.3f,0.0f);
		glVertex3f(0.55f, -0.3f, 0.0f);
	glEnd();//glVertex3f(0.3f, -0.8f, 0.0f);

	glBegin(GL_POLYGON);
		normalVector(0.3f, 0.0f, 0.0f, 0.55f, -0.3f, 0.0f, 0.8f, -0.3f, 0.0f);
		glVertex3f(0.3f, 0.0f, 0.0f);
		glVertex3f(0.55f, -0.3f, 0.0f);
		glVertex3f(0.8f, -0.3f, 0.0f);
		glVertex3f(0.3f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		normalVector(0.8f, -0.3f, 0.0f, 0.55f, -0.3f, 0.0f, 0.3f, -0.8f, 0.0f);
		glVertex3f(0.8f, -0.3f, 0.0f);
		glVertex3f(0.55f, -0.3f, 0.0f);
		glVertex3f(0.3f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		normalVector(0.8f, -0.3f, 0.0f, 0.3f, -0.8f, 0.0f, 0.55f, -0.3f, 0.0f);
		glVertex3f(0.8f, -0.3f, 0.0f);
		glVertex3f(0.3f, -0.8f, 0.0f);
		glVertex3f(0.55f, -0.3f, 0.0f);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glRotatef(theta[4], 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		normalVector(-0.3f, 0.0f, 0.0f, -0.55f, -0.3f, 0.0f, -0.8f, -0.3f, 0.0f);
		glVertex3f(-0.3f, 0.0f, 0.0f);
		glVertex3f(-0.55f, -0.3f, 0.0f);
		glVertex3f(-0.8f, -0.3f, 0.0f);
		glVertex3f(-0.3f, 0.2f, 0.0f);
	glEnd();//glVertex3f(-0.3f, -0.8f, 0.0f);

	glBegin(GL_POLYGON);
		normalVector(-0.3f, 0.0f, 0.0f, -0.3f, 0.2f, 0.0f, -0.8f, -0.3f, 0.0f);
		glVertex3f(-0.3f, 0.0f, 0.0f);
		glVertex3f(-0.3f, 0.2f, 0.0f);
		glVertex3f(-0.8f, -0.3f, 0.0f);
		glVertex3f(-0.55f, -0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		normalVector(-0.8f, -0.3f, 0.0f, -0.55f, -0.3f, 0.0f, -0.3f, -0.8f, 0.0f);
		glVertex3f(-0.8f, -0.3f, 0.0f);
		glVertex3f(-0.55f, -0.3f, 0.0f);
		glVertex3f(-0.3f, -0.8f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		normalVector(-0.8f, -0.3f, 0.0f, -0.3f, -0.8f, 0.0f, -0.55f, -0.3f, 0.0f);
		glVertex3f(-0.8f, -0.3f, 0.0f);
		glVertex3f(-0.3f, -0.8f, 0.0f);
		glVertex3f(-0.55f, -0.3f, 0.0f);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void abdomen() {//Make abdomen model
	glPushMatrix();
	//material(5);//Use the material of abdomen
	if (mat == 2) {
		material(9);
	}
	else {
		material(5);
	}
	glColor3ub(120, 120, 120);
	glBegin(GL_TRIANGLES);
		normalVector(0.0f, 0.0f, 0.2f, 0.0f, 1.0f, 0.0f, 1.4f, 0.5f, 0.7f);
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.4f, 0.5f, 0.7f);

		normalVector(1.4f, 0.5f, 0.7f, 0.0f, 1.0f, 0.0f, 1.4f, 1.5f, 0.7f);
		glVertex3f(1.4f, 0.5f, 0.7f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(1.4f, 1.5f, 0.7f);

		normalVector(1.4f, 1.5f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 0.5f);
		glVertex3f(1.4f, 1.5f, 0.7f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, 0.5f);

		normalVector(-1.4f, 0.5f, 0.7f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.2f);
		glVertex3f(-1.4f, 0.5f, 0.7f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, 0.2f);

		normalVector(-1.4f, 1.5f, 0.7f, 0.0f, 1.0f, 0.0f, -1.4f, 0.5f, 0.7f);
		glVertex3f(-1.4f, 1.5f, 0.7f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.4f, 0.5f, 0.7f);

		normalVector(0.0f, 2.0f, 0.5f, 0.0f, 1.0f, 0.0f, -1.4f, 1.5f, 0.7f);
		glVertex3f(0.0f, 2.0f, 0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.4f, 1.5f, 0.7f);

	glEnd();
	material(5);
	glColor3ub(90, 90, 90);
	glBegin(GL_TRIANGLES);
		normalVector(0.0f, 2.0f, 0.5f, 0.0f, 1.0f, 2.5f, 1.4f, 1.5f, 0.7f);
		glVertex3f(0.0f, 2.0f, 0.5f);
		glVertex3f(0.0f, 1.0f, 2.5f);
		glVertex3f(1.4f, 1.5f, 0.7f);

		normalVector(0.0f, 2.0f, 0.5f, -1.4f, 1.5f, 0.7f, 0.0f, 1.0f, 2.5f);
		glVertex3f(0.0f, 2.0f, 0.5f);
		glVertex3f(-1.4f, 1.5f, 0.7f);
		glVertex3f(0.0f, 1.0f, 2.5f);
	glEnd();

	glColor3ub(70, 70, 70);
	glBegin(GL_QUADS);
		normalVector(0.0f, 1.0f, 2.5f, 0.0f, -1.5f, 2.5f, 1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, 1.0f, 2.5f);
		glVertex3f(0.0f, -1.5f, 2.5f);
		glVertex3f(1.4f, -2.0f, 0.7f);
		glVertex3f(1.4f, 1.5f, 0.7f);

		normalVector(0.0f, 1.0f, 2.5f, -1.4f, 1.5f, 0.7f, -1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, 1.0f, 2.5f);
		glVertex3f(-1.4f, 1.5f, 0.7f);
		glVertex3f(-1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, -1.5f, 2.5f);
	glEnd();

	glColor3ub(80, 80, 80);
	glBegin(GL_QUADS);
		normalVector(0.0f, 0.0f, 0.2f, 0.0f, -3.0f, 0.2f, -1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(0.0f, -3.0f, 0.2f);
		glVertex3f(-1.4f, -2.0f, 0.7f);
		glVertex3f(-1.4f, 0.5f, 0.7f);

		normalVector(0.0f, 0.0f, 0.2f, 1.4f, 0.5f, 0.7f, 1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, 0.0f, 0.2f);
		glVertex3f(1.4f, 0.5f, 0.7f);
		glVertex3f(1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, -3.0f, 0.2f);
	glEnd();

	glColor3ub(50, 50, 50);
	glBegin(GL_TRIANGLES);
		normalVector(0.0f, -3.0f, 0.2f, 1.4f, -2.0f, 0.7f, 0.0f, -1.5f, 2.5f);
		glVertex3f(0.0f, -3.0f, 0.2f);
		glVertex3f(1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, -1.5f, 2.5f);

		normalVector(0.0f, -3.0f, 0.2f, 0.0f, -1.5f, 2.5f, -1.4f, -2.0f, 0.7f);
		glVertex3f(0.0f, -3.0f, 0.2f);
		glVertex3f(0.0f, -1.5f, 2.5f);
		glVertex3f(-1.4f, -2.0f, 0.7f);
	glEnd();
	glPopMatrix();
}

void head() {//Make head model
	glPushMatrix();
	//Use the material of head
	if (mat == 2) {
		material(9);
	}
	else {
		material(8);
	}
	glColor3ub(70, 70, 70);
	glBegin(GL_POLYGON);
		normalVector(0.0f, 1.65f, -2.5f, -0.8f, 1.15f, -2.5f, -0.8f, 0.4f, -2.5f);
		glVertex3f(0.0f, 1.65f, -2.5f);
		glVertex3f(-0.8f, 1.15f, -2.5f);
		glVertex3f(-0.8f, 0.4f, -2.5f);
		glVertex3f(0.0f, -0.55f, -2.5f);
		glVertex3f(0.8f, 0.4f, -2.5f);
		glVertex3f(0.8f, 1.15f, -2.5f);
	glEnd();
	glColor3ub(30, 30, 30);
	glBegin(GL_POLYGON);
		normalVector(0.0f, 1.2375f, -3.0f, 0.6f, 0.8625f, -3.0f, 0.6f, 0.3f, -3.0f);
		glVertex3f(0.0f, 1.2375f, -3.0f);
		glVertex3f(0.6f, 0.8625f, -3.0f);
		glVertex3f(0.6f, 0.3f, -3.0f);
		glVertex3f(0.0f, -0.4125f, -3.0f);
		glVertex3f(-0.6f, 0.3f, -3.0f);
		glVertex3f(-0.6f, 0.8625f, -3.0f);
	glEnd();
	antenna();//Insert the antenna
	Mouthparts();//Insert the Mouthparts
	glColor3ub(50, 50, 50);
	material(8);
	glBegin(GL_QUADS);
		normalVector(0.0f, 1.65f, -2.5f, 0.0f, 1.2375f, -3.0f, -0.6f, 0.8625f, -3.0f);
		glVertex3f(0.0f, 1.65f, -2.5f);
		glVertex3f(0.0f, 1.2375f, -3.0f);
		glVertex3f(-0.6f, 0.8625f, -3.0f);
		glVertex3f(-0.8f, 1.15f, -2.5f);

		normalVector(-0.8f, 1.15f, -2.5f, -0.6f, 0.8625f, -3.0f, -0.6f, 0.3f, -3.0f);
		glVertex3f(-0.8f, 1.15f, -2.5f);
		glVertex3f(-0.6f, 0.8625f, -3.0f);
		glVertex3f(-0.6f, 0.3f, -3.0f);
		glVertex3f(-0.8f, 0.4f, -2.5f);

		normalVector(-0.8f, 0.4f, -2.5f, -0.6f, 0.3f, -3.0f, 0.0f, -0.4125f, -3.0f);
		glVertex3f(-0.8f, 0.4f, -2.5f);
		glVertex3f(-0.6f, 0.3f, -3.0f);
		glVertex3f(0.0f, -0.4125f, -3.0f);
		glVertex3f(0.0f, -0.55f, -2.5f);
		
		normalVector(0.0f, -0.55f, -2.5f, 0.0f, -0.4125f, -3.0f, 0.6f, 0.3f, -3.0f);
		glVertex3f(0.0f, -0.55f, -2.5f);
		glVertex3f(0.0f, -0.4125f, -3.0f);
		glVertex3f(0.6f, 0.3f, -3.0f);
		glVertex3f(0.8f, 0.4f, -2.5f);

		normalVector(0.8f, 0.4f, -2.5f, 0.6f, 0.3f, -3.0f, 0.6f, 0.8625f, -3.0f);
		glVertex3f(0.8f, 0.4f, -2.5f);
		glVertex3f(0.6f, 0.3f, -3.0f);
		glVertex3f(0.6f, 0.8625f, -3.0f);
		glVertex3f(0.8f, 1.15f, -2.5f);

		normalVector(0.8f, 1.15f, -2.5f, 0.6f, 0.8625f, -3.0f, 0.0f, 1.2375f, -3.0f);
		glVertex3f(0.8f, 1.15f, -2.5f);
		glVertex3f(0.6f, 0.8625f, -3.0f);
		glVertex3f(0.0f, 1.2375f, -3.0f);
		glVertex3f(0.0f, 1.65f, -2.5f);
	glEnd();
	glPopMatrix();
}

void foot() {//Make foot model
	glPushMatrix();
	glRotatef(-theta[3], 0.0, 0.0, 1.0);
	glTranslatef(-0.4, 0.0, 0.0);
	material(4);//Use the material of foot
	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(1.0f, 0.5f, -0.5f, 2.0f, 1.0f, -0.5f, 2.0f, 1.5f, -0.5f);
		glVertex3f(1.0f, 0.5f, -0.5f);
		glVertex3f(2.0f, 1.0f, -0.5f);
		glVertex3f(2.0f, 1.5f, -0.5f);

		normalVector(1.0f, 0.5f, -0.5f, 2.0f, 1.5f, -0.5f, 2.0f, 1.0f, -0.5f);
		glVertex3f(1.0f, 0.5f, -0.5f);
		glVertex3f(2.0f, 1.5f, -0.5f);
		glVertex3f(2.0f, 1.0f, -0.5f);

		normalVector(3.0f, 0.3f, -0.5f, 2.5f, 0.3f, -0.5f, 2.0f, -0.7f, -0.5f);
		glVertex3f(3.0f, 0.3f, -0.5f);
		glVertex3f(2.5f, 0.3f, -0.5f);
		glVertex3f(2.0f, -0.7f, -0.5f);

		normalVector(3.0f, 0.3f, -0.5f, 2.0f, -0.7f, -0.5f, 2.5f, 0.3f, -0.5f);
		glVertex3f(3.0f, 0.3f, -0.5f);
		glVertex3f(2.0f, -0.7f, -0.5f);
		glVertex3f(2.5f, 0.3f, -0.5f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(2.0f, 1.0f, -0.5f, 2.0f, 1.5f, -0.5f, 3.0f, 0.3f, -0.5f);
		glVertex3f(2.0f, 1.0f, -0.5f);
		glVertex3f(2.0f, 1.5f, -0.5f);
		glVertex3f(3.0f, 0.3f, -0.5f);
		glVertex3f(2.5f, 0.3f, -0.5f);

		normalVector(2.0f, 1.0f, -0.5f, 2.5f, 0.3f, -0.5f, 3.0f, 0.3f, -0.5f);
		glVertex3f(2.0f, 1.0f, -0.5f);
		glVertex3f(2.5f, 0.3f, -0.5f);
		glVertex3f(3.0f, 0.3f, -0.5f);
		glVertex3f(2.0f, 1.5f, -0.5f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(1.0f, 0.5f, -1.25f, 2.0f, 1.0f, -1.25f, 2.0f, 1.5f, -1.25f);
		glVertex3f(1.0f, 0.5f, -1.25f);
		glVertex3f(2.0f, 1.0f, -1.25f);
		glVertex3f(2.0f, 1.5f, -1.25f);

		normalVector(1.0f, 0.5f, -1.25f, 2.0f, 1.5f, -1.25f, 2.0f, 1.0f, -1.25f);
		glVertex3f(1.0f, 0.5f, -1.25f);
		glVertex3f(2.0f, 1.5f, -1.25f);
		glVertex3f(2.0f, 1.0f, -1.25f);

		normalVector(3.0f, 0.3f, -1.25f, 2.5f, 0.3f, -1.25f, 2.0f, -0.7f, -1.25f);
		glVertex3f(3.0f, 0.3f, -1.25f);
		glVertex3f(2.5f, 0.3f, -1.25f);
		glVertex3f(2.0f, -0.7f, -1.25f);

		normalVector(3.0f, 0.3f, -1.25f, 2.0f, -0.7f, -1.25f, 2.5f, 0.3f, -1.25f);
		glVertex3f(3.0f, 0.3f, -1.25f);
		glVertex3f(2.0f, -0.7f, -1.25f);
		glVertex3f(2.5f, 0.3f, -1.25f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(2.0f, 1.0f, -1.25f, 2.0f, 1.5f, -1.25f, 3.0f, 0.3f, -1.25f);
		glVertex3f(2.0f, 1.0f, -1.25f);
		glVertex3f(2.0f, 1.5f, -1.25f);
		glVertex3f(3.0f, 0.3f, -1.25f);
		glVertex3f(2.5f, 0.3f, -1.25f);

		normalVector(2.0f, 1.0f, -1.25f, 2.5f, 0.3f, -1.25f, 3.0f, 0.3f, -1.25f);
		glVertex3f(2.0f, 1.0f, -1.25f);
		glVertex3f(2.5f, 0.3f, -1.25f);
		glVertex3f(3.0f, 0.3f, -1.25f);
		glVertex3f(2.0f, 1.5f, -1.25f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(1.0f, 0.5f, -2.0f, 2.0f, 1.0f, -2.0f, 2.0f, 1.5f, -2.0f);
		glVertex3f(1.0f, 0.5f, -2.0f);
		glVertex3f(2.0f, 1.0f, -2.0f);
		glVertex3f(2.0f, 1.5f, -2.0f);

		normalVector(1.0f, 0.5f, -2.0f, 2.0f, 1.5f, -2.0f, 2.0f, 1.0f, -2.0f);
		glVertex3f(1.0f, 0.5f, -2.0f);
		glVertex3f(2.0f, 1.5f, -2.0f);
		glVertex3f(2.0f, 1.0f, -2.0f);

		normalVector(3.0f, 0.3f, -2.0f, 2.5f, 0.3f, -2.0f, 2.0f, -0.7f, -2.0f);
		glVertex3f(3.0f, 0.3f, -2.0f);
		glVertex3f(2.5f, 0.3f, -2.0f);
		glVertex3f(2.0f, -0.7f, -2.0f);

		normalVector(3.0f, 0.3f, -2.0f, 2.0f, -0.7f, -2.0f, 2.5f, 0.3f, -2.0f);
		glVertex3f(3.0f, 0.3f, -2.0f);
		glVertex3f(2.0f, -0.7f, -2.0f);
		glVertex3f(2.5f, 0.3f, -2.0f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(2.0f, 1.0f, -2.0f, 2.0f, 1.5f, -2.0f, 3.0f, 0.3f, -2.0f);
		glVertex3f(2.0f, 1.0f, -2.0f);
		glVertex3f(2.0f, 1.5f, -2.0f);
		glVertex3f(3.0f, 0.3f, -2.0f);
		glVertex3f(2.5f, 0.3f, -2.0f);

		normalVector(2.0f, 1.0f, -2.0f, 2.5f, 0.3f, -2.0f, 3.0f, 0.3f, -2.0f);
		glVertex3f(2.0f, 1.0f, -2.0f);
		glVertex3f(2.5f, 0.3f, -2.0f);
		glVertex3f(3.0f, 0.3f, -2.0f);
		glVertex3f(2.0f, 1.5f, -2.0f);
	glEnd();
	glPopMatrix();
}

void otherSideOfFoot() {//Make other foot model
	glPushMatrix();
	glRotatef(theta[3], 0.0, 0.0, 1.0);
	glTranslatef(0.4,0.0,0.0);
	material(4);//Use the material of foot
	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(-1.0f, 0.5f, -0.5f, -2.0f, 1.0f, -0.5f, -2.0f, 1.5f, -0.5f);
		glVertex3f(-1.0f, 0.5f, -0.5f);
		glVertex3f(-2.0f, 1.0f, -0.5f);
		glVertex3f(-2.0f, 1.5f, -0.5f);

		normalVector(-1.0f, 0.5f, -0.5f, -2.0f, 1.5f, -0.5f, -2.0f, 1.0f, -0.5f);
		glVertex3f(-1.0f, 0.5f, -0.5f);
		glVertex3f(-2.0f, 1.5f, -0.5f);
		glVertex3f(-2.0f, 1.0f, -0.5f);

		normalVector(-3.0f, 0.3f, -0.5f, -2.5f, 0.3f, -0.5f, -2.0f, -0.7f, -0.5f);
		glVertex3f(-3.0f, 0.3f, -0.5f);
		glVertex3f(-2.5f, 0.3f, -0.5f);
		glVertex3f(-2.0f, -0.7f, -0.5f);

		normalVector(-3.0f, 0.3f, -0.5f, -2.0f, -0.7f, -0.5f, -2.5f, 0.3f, -0.5f);
		glVertex3f(-3.0f, 0.3f, -0.5f);
		glVertex3f(-2.0f, -0.7f, -0.5f);
		glVertex3f(-2.5f, 0.3f, -0.5f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(-2.0f, 1.0f, -0.5f, -2.0f, 1.5f, -0.5f, -3.0f, 0.3f, -0.5f);
		glVertex3f(-2.0f, 1.0f, -0.5f);
		glVertex3f(-2.0f, 1.5f, -0.5f);
		glVertex3f(-3.0f, 0.3f, -0.5f);
		glVertex3f(-2.5f, 0.3f, -0.5f);

		normalVector(-2.0f, 1.0f, -0.5f, -2.5f, 0.3f, -0.5f, -3.0f, 0.3f, -0.5f);
		glVertex3f(-2.0f, 1.0f, -0.5f);
		glVertex3f(-2.5f, 0.3f, -0.5f);
		glVertex3f(-3.0f, 0.3f, -0.5f);
		glVertex3f(-2.0f, 1.5f, -0.5f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(-1.0f, 0.5f, -1.25f, -2.0f, 1.0f, -1.25f, -2.0f, 1.5f, -1.25f);
		glVertex3f(-1.0f, 0.5f, -1.25f);
		glVertex3f(-2.0f, 1.0f, -1.25f);
		glVertex3f(-2.0f, 1.5f, -1.25f);

		normalVector(-1.0f, 0.5f, -1.25f, -2.0f, 1.5f, -1.25f, -2.0f, 1.0f, -1.25f);
		glVertex3f(-1.0f, 0.5f, -1.25f);
		glVertex3f(-2.0f, 1.5f, -1.25f);
		glVertex3f(-2.0f, 1.0f, -1.25f);

		normalVector(-3.0f, 0.3f, -1.25f, -2.5f, 0.3f, -1.25f, -2.0f, -0.7f, -1.25f);
		glVertex3f(-3.0f, 0.3f, -1.25f);
		glVertex3f(-2.5f, 0.3f, -1.25f);
		glVertex3f(-2.0f, -0.7f, -1.25f);

		normalVector(-3.0f, 0.3f, -1.25f, -2.0f, -0.7f, -1.25f, -2.5f, 0.3f, -1.25f);
		glVertex3f(-3.0f, 0.3f, -1.25f);
		glVertex3f(-2.0f, -0.7f, -1.25f);
		glVertex3f(-2.5f, 0.3f, -1.25f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(-2.0f, 1.0f, -1.25f, -2.0f, 1.5f, -1.25f, -3.0f, 0.3f, -1.25f);
		glVertex3f(-2.0f, 1.0f, -1.25f);
		glVertex3f(-2.0f, 1.5f, -1.25f);
		glVertex3f(-3.0f, 0.3f, -1.25f);
		glVertex3f(-2.5f, 0.3f, -1.25f);

		normalVector(-2.0f, 1.0f, -1.25f, -2.5f, 0.3f, -1.25f, -3.0f, 0.3f, -1.25f);
		glVertex3f(-2.0f, 1.0f, -1.25f);
		glVertex3f(-2.5f, 0.3f, -1.25f);
		glVertex3f(-3.0f, 0.3f, -1.25f);
		glVertex3f(-2.0f, 1.5f, -1.25f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_TRIANGLES);
		normalVector(-1.0f, 0.5f, -2.0f, -2.0f, 1.0f, -2.0f, -2.0f, 1.5f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -2.0f);
		glVertex3f(-2.0f, 1.0f, -2.0f);
		glVertex3f(-2.0f, 1.5f, -2.0f);

		normalVector(-1.0f, 0.5f, -2.0f, -2.0f, 1.5f, -2.0f, -2.0f, 1.0f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -2.0f);
		glVertex3f(-2.0f, 1.5f, -2.0f);
		glVertex3f(-2.0f, 1.0f, -2.0f);

		normalVector(-3.0f, 0.3f, -2.0f, -2.5f, 0.3f, -2.0f, -2.0f, -0.7f, -2.0f);
		glVertex3f(-3.0f, 0.3f, -2.0f);
		glVertex3f(-2.5f, 0.3f, -2.0f);
		glVertex3f(-2.0f, -0.7f, -2.0f);

		normalVector(-3.0f, 0.3f, -2.0f, -2.0f, -0.7f, -2.0f, -2.5f, 0.3f, -2.0f);
		glVertex3f(-3.0f, 0.3f, -2.0f);
		glVertex3f(-2.0f, -0.7f, -2.0f);
		glVertex3f(-2.5f, 0.3f, -2.0f);
	glEnd();

	glColor3ub(20, 20, 20);
	glBegin(GL_QUADS);
		normalVector(-2.0f, 1.0f, -2.0f, -2.0f, 1.5f, -2.0f, -3.0f, 0.3f, -2.0f);
		glVertex3f(-2.0f, 1.0f, -2.0f);
		glVertex3f(-2.0f, 1.5f, -2.0f);
		glVertex3f(-3.0f, 0.3f, -2.0f);
		glVertex3f(-2.5f, 0.3f, -2.0f);

		normalVector(-2.0f, 1.0f, -2.0f, -2.5f, 0.3f, -2.0f, -3.0f, 0.3f, -2.0f);
		glVertex3f(-2.0f, 1.0f, -2.0f);
		glVertex3f(-2.5f, 0.3f, -2.0f);
		glVertex3f(-3.0f, 0.3f, -2.0f);
		glVertex3f(-2.0f, 1.5f, -2.0f);
	glEnd();
	glPopMatrix();
}

void body() {//Make body model
	glPushMatrix();
	//material(7);//Use the material of body
	if (mat == 2) {
		material(9);
	}
	else {
		material(7);
	}
	//glColor3ub(130, 130, 130);
	glBegin(GL_TRIANGLES);
		normalVector(0.0f, 0.0f, -0.5f, 1.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f,0.0f,-0.5f);
		glVertex3f(1.0f,0.5f,-0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		normalVector(1.0f, 0.5f, -0.5f, 1.0f, 1.5f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 0.5f, -0.5f);
		glVertex3f(1.0f, 1.5f, -0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		normalVector(1.0f, 1.5f, -0.5f, 0.0f, 2.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(1.0f, 1.5f, -0.5f);
		glVertex3f(0.0f, 2.0f, -0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		normalVector(-1.0f, 0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.5f, -0.5f);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		normalVector(-1.0f, 1.5f, -0.5f, -1.0f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.5f, -0.5f);
		glVertex3f(-1.0f, 0.5f, -0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

		normalVector(0.0f, 2.0f, -0.5f, -1.0f, 1.5f, -0.5f, 0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 2.0f, -0.5f);
		glVertex3f(-1.0f, 1.5f, -0.5f);
		glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();

	//glColor3ub(90, 90, 90);
	glBegin(GL_TRIANGLES);
		normalVector(0.0f, 0.0f, -2.0f, 0.0f, 1.0f, -2.5f, 1.0f, 0.5f, -2.0f);
		glVertex3f(0.0f, 0.0f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(1.0f, 0.5f, -2.0f);

		normalVector(1.0f, 0.5f, -2.0f, 0.0f, 1.0f, -2.5f, 1.0f, 1.5f, -2.0f);
		glVertex3f(1.0f, 0.5f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(1.0f, 1.5f, -2.0f);

		normalVector(1.0f, 1.5f, -2.0f, 0.0f, 1.0f, -2.5f, 0.0f, 2.0f, -2.0f);
		glVertex3f(1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(0.0f, 2.0f, -2.0f);

		normalVector(-1.0f, 0.5f, -2.0f, 0.0f, 1.0f, -2.5f, 0.0f, 0.0f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(0.0f, 0.0f, -2.0f);

		normalVector(-1.0f, 1.5f, -2.0f, 0.0f, 1.0f, -2.5f, -1.0f, 0.5f, -2.0f);
		glVertex3f(-1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(-1.0f, 0.5f, -2.0f);

		normalVector(0.0f, 2.0f, -2.0f, 0.0f, 1.0f, -2.5f, -1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 2.0f, -2.0f);
		glVertex3f(0.0f, 1.0f, -2.5f);
		glVertex3f(-1.0f, 1.5f, -2.0f);

	glEnd();
	material(7);
	//glColor3ub(110, 110, 110);
	glBegin(GL_QUADS);
		
		normalVector(1.0f, 0.5f, -0.5f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, -2.0f);
		glVertex3f(1.0f, 0.5f, -0.5f);
		glVertex3f(0.0f, 0.0f, -0.5f);
		glVertex3f(0.0f, 0.0f, -2.0f);
		glVertex3f(1.0f, 0.5f, -2.0f);

		normalVector(1.0f, 1.5f, -0.5f, 1.0f, 0.5f, -0.5f, 1.0f, 0.5f, -2.0f);
		glVertex3f(1.0f, 1.5f, -0.5f);
		glVertex3f(1.0f, 0.5f, -0.5f);
		glVertex3f(1.0f, 0.5f, -2.0f);
		glVertex3f(1.0f, 1.5f, -2.0f);

		normalVector(0.0f, 2.0f, -0.5f, 1.0f, 1.5f, -0.5f, 1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 2.0f, -0.5f);
		glVertex3f(1.0f, 1.5f, -0.5f);
		glVertex3f(1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 2.0f, -2.0f);

		normalVector(-1.0f, 0.5f, -0.5f, -1.0f, 0.5f, -2.0f, 0.0f, 0.0f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -0.5f);
		glVertex3f(-1.0f, 0.5f, -2.0f);
		glVertex3f(0.0f, 0.0f, -2.0f);
		glVertex3f(0.0f, 0.0f, -0.5f);

		normalVector(-1.0f, 1.5f, -0.5f, -1.0f, 1.5f, -2.0f, -1.0f, 0.5f, -2.0f);
		glVertex3f(-1.0f, 1.5f, -0.5f);
		glVertex3f(-1.0f, 1.5f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -2.0f);
		glVertex3f(-1.0f, 0.5f, -0.5f);

		normalVector(0.0f, 2.0f, -0.5f, 0.0f, 2.0f, -2.0f, -1.0f, 1.5f, -2.0f);
		glVertex3f(0.0f, 2.0f, -0.5f);
		glVertex3f(0.0f, 2.0f, -2.0f);
		glVertex3f(-1.0f, 1.5f, -2.0f);
		glVertex3f(-1.0f, 1.5f, -0.5f);
	glEnd();
	
	head();//Insert the head

	foot();//Insert the foot
	
	otherSideOfFoot();//other side of foot
	
	abdomen();//Insert the abdomen

	glPopMatrix();
}

void stinger() {//Make stinger model
	glPushMatrix();
	material(6);//Use the material of silver white
	glColor3ub(30, 30, 30);
	glTranslatef(0.0f, -1.8f, 0.6f);
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.5, 3.5, 20, 20);//Use a cone to represent stinger
	glPopMatrix();
}

void wings() {//Make wings model
	glPushMatrix();
	material(3);//Use the material of Test material High light reflection
	glColor4ub(180, 180, 180,50);
	glTranslatef(0.5f, 1.5f, -0.2f);
	glRotatef(theta[1], 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		normalVector(-0.1f, 0.0f, -0.5f, 4.5f, 0.0f, -2.0f, 5.8f, 0.0f, -4.0f);
		glVertex3f(-0.1f, 0.0f, -0.5f);
		glVertex3f(4.5f, 0.0f, -2.0f);
		glVertex3f(5.8f, 0.0f, -4.0f);
		glVertex3f(5.5f, 0.0f, -4.5f);
		glVertex3f(4.5f, 0.0f, -4.5f);
		glVertex3f(-0.1f, 0.0f, -1.0f);
	glEnd();
	glBegin(GL_POLYGON);
		normalVector(-0.1f, 0.0f, -0.5f, -0.1f, 0.0f, -1.0f, 4.5f, 0.0f, -4.5f);
		glVertex3f(-0.1f, 0.0f, -0.5f);
		glVertex3f(-0.1f, 0.0f, -1.0f);
		glVertex3f(4.5f, 0.0f, -4.5f);
		glVertex3f(5.5f, 0.0f, -4.5f);
		glVertex3f(5.8f, 0.0f, -4.0f);
		glVertex3f(4.5f, 0.0f, -2.0f);
	glEnd();
	glPopMatrix();
}

void otherWings() {//Make other side of wing
	glPushMatrix();
	material(3);//Use the material of Test material High light reflection
	glColor4ub(180, 180, 180, 50);
	glTranslatef(-0.5f, 1.5f, -0.2f);
	glRotatef(-theta[1], 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		normalVector(0.1f, 0.0f, -0.5f, -4.5f, 0.0f, -2.0f, -5.8f, 0.0f, -4.0f);
		glVertex3f(0.1f, 0.0f, -0.5f);
		glVertex3f(-4.5f, 0.0f, -2.0f);
		glVertex3f(-5.8f, 0.0f, -4.0f);
		glVertex3f(-5.5f, 0.0f, -4.5f);
		glVertex3f(-4.5f, 0.0f, -4.5f);
		glVertex3f(0.1f, 0.0f, -1.0f);
	glEnd();
	glBegin(GL_POLYGON);
		normalVector(0.1f, 0.0f, -0.5f, 0.1f, 0.0f, -1.0f, -4.5f, 0.0f, -4.5f);
		glVertex3f(0.1f, 0.0f, -0.5f);
		glVertex3f(0.1f, 0.0f, -1.0f);
		glVertex3f(-4.5f, 0.0f, -4.5f);
		glVertex3f(-5.5f, 0.0f, -4.5f);
		glVertex3f(-5.8f, 0.0f, -4.0f);
		glVertex3f(-4.5f, 0.0f, -2.0f);
	glEnd();
	glPopMatrix();
}

void display()
{
	light(xt);//Call the lighting mode
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	//gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//printf("%.2f\n", theta[2]);
	glTranslatef(0.0, theta[2], 0.0);//Start jumping here。。。。
	glTranslatef(position[0]/10,position[1]/10,position[2]/10);//random position
	//printf("%.2f,,%.2f,,%.2f\n", position[0], position[1], position[2]);
	glRotatef(theta[0], 0.0, 1.0, 0.0);//The glRotatef used when rotating
	//Build model
	body();

	stinger();

	wings();

	otherWings();
	//Exchange buffering
	glutSwapBuffers();
}

void specialkey(int key,int x,int y) {//Special keyboard events
	switch (key) {
	case GLUT_KEY_DOWN://Down arrow to decrease speed of waving wings
		speed -= 1;
		if (speed == 0) {
			speed = 1;
		}
		break;
	case GLUT_KEY_UP://Up arrow to increase speed of waving wings
		speed += 1;
		if (speed == 21) {
			speed = 15;
		}
		break;
	case GLUT_KEY_LEFT://The left arrow reduces the angle of waving wings
		angle -= 1;
		if (angle == 20) {
			angle = 21;
		}
		break;
	case GLUT_KEY_RIGHT://The right arrow increases the angle of waving wings
		angle += 1;
		if (angle == 96) {
			angle = 95;
		}
		break;
	}
}

void mymenur(int id) {//Callback of the right key menu
	if (id == 1) {
		jump = GL_TRUE;//"Jumping"
		new_jump = GL_TRUE;
	}
	if (id == 2) {
		bas = !bas;//"Rotating"
	}
	if (id == 3) {
		win = !win;//"Flying"
	}
	if (id == 4) {
		xt = 2;//get into noon light mode
	}
	if (id == 5) {
		xt = 3;//get into early evening light mode
	}
	if (id == 6) {
		xt = 1;//get into late evening light mode
	}
}

void mymenul(int id) {//Callback of the left key menu
	if (id == 1) {
		mat = 0;//"Normal wasp"
	}
	if (id == 2) {
		mat = 1;//"Silver wasp"
	}
	if (id == 3) {
		mat = 2;//"Dark wasp"
	}
}

void menus() {//Create a left and right key menu
	menur = glutCreateMenu(mymenur);//the menu of right key
	glutAddMenuEntry("Jumping", 1);
	glutAddMenuEntry("Rotating", 2);
	glutAddMenuEntry("Flying", 3);
	glutAddMenuEntry("Noon", 4);
	glutAddMenuEntry("Early evening", 5);
	glutAddMenuEntry("Late evening", 6);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	menul = glutCreateMenu(mymenul);//the menu of left key
	glutAddMenuEntry("Normal wasp", 1);
	glutAddMenuEntry("Silver wasp", 2);
	glutAddMenuEntry("Dark wasp", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

int main(int argc, char **argv)
{
	jsp = setjsp;//Initialize wingspan
	printf("%.2f\n", jsp);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("animated");
	glutKeyboardFunc(mykey);//Keyboard event
	glutSpecialFunc(specialkey);//Special keyboard events
	glutIdleFunc(idle);//Background function
	glutDisplayFunc(display);//Display function
	glutReshapeFunc(reshape);//Modify the window size of the callback function
	glEnable(GL_DEPTH_TEST); 
	init();//initialization
	menus();
	glutMainLoop();
}