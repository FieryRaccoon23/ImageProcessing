#include "stdafx.h"
#include "Display.h"

using namespace std;

void changeViewPort(int w, int h)
{
	//glViewport(0, 0, w, h);
}

void render()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glutSwapBuffers();
}

Display::Display()
{
}


Display::~Display()
{
}

uint16_t Display::DrawWindow(int argc, char* argv[], char* title)
{/*
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Hello,GL"
	glutCreateWindow(title);
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}

	glutMainLoop();
	*/
	return 0;
}



