#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "global.h"
#include "image.h"

int main(int argc, char *argv[]) {
	/* Initialize SDL2 Video and Audio Systems */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	/* Initialize IMG system
	 * Used for importing image assets
	 * Initialization depends on what type of files using as assets
	 * These flags can be OR'd together
	 * .jpg files: IMG_INIT_JPG
	 * .png files: IMG_INIT_PNG
	 * .tif files: IMG_INIT_TIF
	 * ex: IMG_INIT_JPG | IMG_INIT_PNG
	 */
	int img_flags = IMG_INIT_JPG|IMG_INIT_PNG;
	int img_init = IMG_Init(img_flags);
	if((img_init&img_flags) != img_flags) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
					"Unable to initialize IMG: %s", IMG_GetError());
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
		return 1;
	}

	/* Import Image as a texture
	 * The texture will be used to draw the image to the renderer
	 */
	SDL_Texture *img = importToTexture(renderer, "src/assets/lizard.png");
	SDL_Rect img_size = {0, 0, 0, 0};
	SDL_QueryTexture(img, NULL, NULL, &img_size.w, &img_size.h);

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

		/* After drawing the background draw the image to the renderer
		 * When drawing to the renderer make sure to draw in the correct order
		 * location is used to show where the img will be copied to
		 * in this case we are copying it to the center of the screen
		 */
		SDL_Rect location = {SCREEN.w/2-img_size.w/2, SCREEN.h/2-img_size.h/2, img_size.w, img_size.h};
		SDL_RenderCopy(renderer, img, &img_size, &location);

		SDL_RenderPresent(renderer);
	}

	/* Destroy/Quit all systems using from SDL */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
	return 0;
}
