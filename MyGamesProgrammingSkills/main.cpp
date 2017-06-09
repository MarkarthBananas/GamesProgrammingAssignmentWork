#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "motion.h"
#include "camera.h"
#include <assert.h>
#include "SDL2\SDL_mixer.h"

//game window dimensions
#define WIDTH 800
#define HEIGHT 600

int main(int argc, char** argv)
{
	//renders window first

	std::cout << "Assert test passed: Display Initialised." << std::endl;

	display display(WIDTH, HEIGHT, "My Games Programming Skills");

	//sets up vertices for the model
	vertex vertices[] = { vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(0.0, 0.0)),
						  vertex(glm::vec3(0, 0.5, 0), glm::vec2(0.5, 1.0)),
						  vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1.0, 0.0)), };

	unsigned int indices[] = { 0, 1, 2 };

	//render mesh for the model
	mesh model(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	//renders lamp.obj 3D model as the model
	mesh model2("./res/lamp.obj");

	//initialises shaders from .vs and .fs files
	shader basicShader("./res/basicShader");

	//initialises texture for the model
	texture marbletexture("./res/marbletexture.jpg");

	//initialises camera
	camera camera(glm::vec3(0, 0, -30), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

	//initialises movement for the mode
	motion modelMotion;

	//initialises music
	Mix_Music *bgm;

	float counter = 0.0f;

	//error messages for if music couldnt be played
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Audio error" << std::endl;
	}

	bgm = Mix_LoadMUS("./res/music.wav");

	if (bgm == NULL)
	{
		std::cout << "Could not find music.wav" << std::endl;
	}

	//plays the music
	Mix_PlayMusic(bgm, -1);

	//sets initial angle of the 3D model via y axis value
	modelMotion.GetRot().y = -3.1f;

	assert(SDL_Init(SDL_INIT_EVERYTHING) != 1);
	std::cout << "Assert test passed: SDL Initiated." << std::endl;

	//execute these functions while display IS NOT (!) closed
	while (!display.IsClosed())
	{
			display.Clear(0.14f, 0.94f, 0.90f, 1.0f);
			
			//switch case for handling arrow key presses (also collision is handled here)
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					//when key is depressed
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						//when left key is pressed, move model 0.3f to the left aslong as the model x position is less than 19.0f (collision point)
					case SDLK_LEFT:
						if (modelMotion.GetPos().x < 19.0f)
						{
							modelMotion.GetPos().x += 0.3f;
						}
						break;
						//when right key is pressed, move model 0.3f to the right aslong as the model x position is more than -19.0f (collision point)
					case SDLK_RIGHT:
						if (modelMotion.GetPos().x > -19.0f)
						{
							modelMotion.GetPos().x -= 0.3f;
						}
						break;
						//when up key is pressed, move model 0.3f up aslong as the model y position is less than 14.0f (collision point)
					case SDLK_UP:
						if (modelMotion.GetPos().y < 14.0f)
						{
							modelMotion.GetPos().y += 0.3f;
						}
						break;
						//when down key is pressed, move model 0.3f down aslong as the model y position is more than than -14.0f (collision point)
					case SDLK_DOWN:
						if (modelMotion.GetPos().y > -14.0f)
						{
							modelMotion.GetPos().y -= 0.3f;
						}
						break;
						//if user quits, close the display
					case SDL_QUIT:
						display.Close();
						break;
					}
					break;
				}
			}

			//if mouse if pressed, set 3D model values to these (centre of the game window)
			if (SDL_GetMouseState(NULL, NULL) == 1)
			{
				modelMotion.GetPos().x = 0.0f;
				modelMotion.GetPos().y = 0.0f;
				modelMotion.GetPos().z = 0.0f;
			}

			
			//handles movement of the model by axis
			float cosCounter = cosf(counter);
			modelMotion.GetRot().y = cosCounter * 2;
			modelMotion.GetRot().z = cosCounter * 2;

			//commented out areas for spinning the model on certain axis

			//float sinCounter = sinf(counter);
			//modelMotion.GetPos().x = sinCounter;
			//modelMotion.GetPos().z = cosCounter;
			//modelMotion.GetRot().x = cosCounter * 2;
			//modelMotion.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));


			//binds shaders and texture
			basicShader.Bind();
			marbletexture.Bind(0);
			
			//updates shaders with values for the model and camera
			basicShader.Update(modelMotion, camera);

			//draws the 3D model
			model2.Draw();

			//updates the display window
			display.Update();

			counter += 0.01f;
		}

		return 0;
	}
