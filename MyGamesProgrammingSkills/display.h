#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <string> 

class display
{
public:
	//initialises display with width, height and a window title
	display(int width, int height, const std::string& title);

	//clears colours and alpha when window closes
	void Clear(float r, float g, float b, float a);
	//updates display
	void Update();
	//closes display
	void Close();
	//checks if display is closed
	bool IsClosed();

	//destructor for the display
	virtual ~display();

protected:

private:
	//constructor
	display(const display& other) {}
	void operator=(const display& other) {}

	//variables for setting up the window in SDL and checking if window is closed
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;

};

#endif DISPLAY_H

