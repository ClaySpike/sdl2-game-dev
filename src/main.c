#include <stdio.h>
#include <SDL2/SDL.h>
#include <include/global.h>

int main(int argc, char *argv[]) {
	/* Initialize SDL2 Video and Audio Systems */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	/* Create the window and renderer
	 * The renderer is what is used to draw to the window
	 * SCREEN is used here to define what size the current window is
	 * window_flags is used to define what attributes the renderer will have
	 * 		SDL_RENDERER_ACCELERATED allows use of accelerated graphics (ex: graphics card)
	 * 		SDL_RENDERER_PRESENTVSYNC forces the window to only refresh at the refresh rate of the display
	 * 				This is important to start out with because the project is so easy to run that it would
	 * 				produce thousands of frames per second
	 */
	SDL_Window *window;
	SDL_Renderer *renderer;
	Uint32 window_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	if (SDL_CreateWindowAndRenderer(
			SCREEN.w, SCREEN.h,
			window_flags, &window,
			&renderer)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					"Couldn't create window and renderer: %s", SDL_GetError());
		return 2;
	}

	/* main loop
	 * responsible for obtaining input from devices
	 * 		and drawing to the window using the renderer
	 */
	int run = 1;
	while (run) {
		/* Obtain events that are what devices are doing
		 * Used to get user input
		 * Important to implement early to avoid Not Responding errors
		 */
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				run = 0;
				break;
			}
		}

		if (!run) {
			break;
		}

		/* Very basic drawing to the window
		 * Set color to a nice grey
		 * clear what was previously drawn to the renderer
		 * Draw a rectangle the size of the SCREEN
		 * present the renderer to the window (display what was just written)
		 */
		SDL_SetRenderDrawColor(renderer, 0x55, 0x55, 0x55, 0xFF);
		SDL_RenderClear(renderer);
		SDL_RenderFillRect(renderer, &SCREEN);
		SDL_RenderPresent(renderer);
	}

	/* Destroy/Quit all systems using from SDL */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
