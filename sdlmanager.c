#include "SDL.h"

#include "globaldefs.h"
#include "sdlmanager.h"
#include "gamecode.h"
#include "glmanager.h"

//local vars
SDL_Surface *surface;
const SDL_VideoInfo *videoInfo;
int videoFlags;

extern  int gamecodeHandleKeyPress(SDL_keysym *keysym, int type);

//functions
int resizeWindow(int width, int height, int bpp, int debugmode){
	if(debugmode) printf("DEBUG -- SDL video resize to: %ix%i with %i bits per pixel \n", width, height, bpp);
	if(height<1) height = 1;
	if(width<1) width = 1;
	surface = SDL_SetVideoMode(width, height, bpp, videoFlags);
	if(!surface){
		fprintf(stderr, "ERROR -- SDL video resize failed: %s \n", SDL_GetError());
		return FALSE;
	}
	updateScreenSize(width, height);
	return TRUE;
}
void swapBuffers(void){
	SDL_GL_SwapBuffers();
}
int sdlInit(int width, int height, int bpp, int debugmode){
	if(debugmode) printf("DEBUG -- SDL window initializing \n");
	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr, "ERROR -- SDL video init failed: %s \n", SDL_GetError());
		return FALSE;
	}
	videoInfo = SDL_GetVideoInfo();
	videoFlags = SDL_OPENGL;
	videoFlags |= SDL_GL_DOUBLEBUFFER;
	videoFlags |= SDL_HWPALETTE;
	videoFlags |= SDL_RESIZABLE;
	if(videoInfo->hw_available) videoFlags |= SDL_HWSURFACE;
	else			    videoFlags |= SDL_SWSURFACE;
	if(videoInfo->blit_hw) 	    videoFlags |= SDL_HWACCEL;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
	return resizeWindow(width, height, bpp, debugmode);
}

//TODO get rid of this, its temporary so i can have some sort of textures
int sdlImportImage(const char * filename, int *height, int *width, void ** data){
	SDL_Surface *TextureImage;
	if(!(TextureImage = SDL_LoadBMP(filename))) return FALSE;
	*height = TextureImage->h;
	*width = TextureImage->w;
	int size = TextureImage->w * TextureImage->h * TextureImage->format->BytesPerPixel;
	*data = malloc(size);
	memcpy(*data, TextureImage->pixels, size);
	SDL_FreeSurface(TextureImage);
	return TRUE;
}
int sdlCheckEvent(void){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				SDL_Quit();
				exit(TRUE);
			break;
			case SDL_KEYDOWN:
				gamecodeHandleKeyPress(&event.key.keysym, 1);
			break;
			case SDL_KEYUP:
				gamecodeHandleKeyPress(&event.key.keysym, 0);
			break;
			case SDL_VIDEORESIZE:
				resizeWindow(event.resize.w, event.resize.h, 24, 0);
//				updateScreenSize(event.resize.w, event.resize.h);

			break;
			case SDL_MOUSEMOTION:
			//todo mouse position
				gamecodeHandleMouseMove(event.motion.xrel, event.motion.yrel);
			break;
			case SDL_MOUSEBUTTONDOWN:
				gamecodeHandleMousePress(event.button.button, 1);
			break;
			case SDL_MOUSEBUTTONUP:
				gamecodeHandleMousePress(event.button.button, 0);
			break;
		}
	}
	return TRUE;

}
//toggles and then returns true/false
int sdlToggleMouseGrab(void){
	if(SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_OFF){
		SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_ShowCursor(SDL_DISABLE);
		return TRUE;
	} else {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);
		return FALSE;
	}
}
void sdlSetMouseGrab(int grab){
	if(grab){
		SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_ShowCursor(SDL_DISABLE);

	} else {
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);

	}
}
