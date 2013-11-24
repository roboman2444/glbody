#ifndef GAMECODEHEADER
#define GAMECODEHEADER

//	int gamecodeHandleKeyPress(SDL_keysym *keysym, int type);
	int gamecodeTick(void);
	int gamecodeHandleMouseMove(int xrel, int yrel);
	int gamecodeHandleMousePress(int button, int type);

#endif
