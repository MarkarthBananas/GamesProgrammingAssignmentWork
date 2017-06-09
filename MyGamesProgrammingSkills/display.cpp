#include "display.h"
#include <GL/glew.h>
#include <iostream>
#include <assert.h>

//initialises the game window
display::display(int width, int height, const std::string& title)
{
	//initialises SDL library
	SDL_Init(SDL_INIT_EVERYTHING);

	//sets up colour and alpha buffers
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//creates game window
	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	m_glContext = SDL_GL_CreateContext(m_window);

	//initialises GLEW library
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Glew failed to initialize!" << std::endl;
	}

	//window starts as NOT closed
	m_isClosed = false;

	glEnable(GL_DEPTH_TEST);

}

//window destructor
display::~display()
{
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

//clears colour data once window is closed so that processing power isnt being used
void display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//checks if the window is closed
bool display::IsClosed()
{
	return m_isClosed;
}

//sets m_isclosed to true is display is closed
void display::Close()
{
	m_isClosed = true;
}

//updates the game window
void display::Update()
{
	SDL_GL_SwapWindow(m_window);
}