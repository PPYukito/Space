#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

const int fps = 60;
const int frameDelay = 1000 / fps;

Uint32 frameStart;
int frameTime;

int main(int args, char *argv[])
{
	game = new Game();
	game->Init("Space Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while (game->isRunning)
	{
		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}

	game->Clean();

	return 0;
}