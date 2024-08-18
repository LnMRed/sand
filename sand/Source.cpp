#include <SDL.h>
#include "Handler.h"

Handler *handler = nullptr;

// the pain engine aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	const int windowWidth = 500;
	const int windowHeight = 500;

	Uint32 FrameStart = SDL_GetTicks64();
	Uint32 FrameTime = 0;
	
	handler = new Handler();
	handler->init("game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, false);
	while (handler->running()) 
	{
		FrameStart = SDL_GetTicks64();

		handler->handleEvents();

		handler->update();
		
		SDL_Rect rect = {0,0,5,5};
		SDL_RenderFillRects(handler->getRenderer(), &rect, 1);
		handler->render();
		FrameTime = SDL_GetTicks64() - FrameStart;
		if (frameDelay > FrameTime) {
			Uint32 waitTime = frameDelay - FrameTime;
			SDL_Delay(waitTime);
		}
	}
	handler->clean();

	return 0;
}