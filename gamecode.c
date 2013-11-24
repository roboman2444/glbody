#include "SDL.h"
#include "globaldefs.h"
#include "gamecode.h"
#include "sdlmanager.h"
#include "glmanager.h"
#include "matrixlib.h"
#include "math.h"

double campos[3];
double camangle[3];

float camzoom;

//extern int updateCameraViewMatrix(matrix4x4_t view);

unsigned char controllkeys = 0;
//	E, Q, SHIFT,SPACE, W,A,S,D
extern int updateCameraViewMatrix(double pos[3], double angle[3]);

int gamecodeTick(void){
	return TRUE;
}
int gamecodeHandleKeyPress(SDL_keysym * keysym, int type){
	switch(keysym ->sym){
		case SDLK_ESCAPE:
			exit(TRUE);
		break;
		case SDLK_w:
			if(type)controllkeys = controllkeys | 0x1;
			else controllkeys = controllkeys & (~0x1);
		break;
		case SDLK_a:
			if(type)controllkeys = controllkeys | 0x2;
			else controllkeys = controllkeys & (~0x2);
		break;
		case SDLK_s:
			if(type)controllkeys = controllkeys | 0x4;
			else controllkeys = controllkeys & (~0x4);
		break;
		case SDLK_d:
			if(type)controllkeys = controllkeys | 0x8;
			else controllkeys = controllkeys & (~0x8);
		break;
		case SDLK_SPACE:
			if(type)controllkeys = controllkeys | 0x16;
			else controllkeys = controllkeys & (~0x16);
		break;
		case SDLK_RSHIFT:
			if(type)controllkeys = controllkeys | 0x32;
			else controllkeys = controllkeys & (~0x32);
		break;
		case SDLK_q:
			if(type)controllkeys = controllkeys | 0x64;
			else controllkeys = controllkeys & (~0x64);
		break;
		case SDLK_e:
			if(type)controllkeys = controllkeys | 0x128;
			else controllkeys = controllkeys & (~0x128);
		break;
		default:
		break;

	}
	return TRUE;
}

int gamecodeHandleMouseMove(int xrel, int yrel){
	campos[0] = 1.0;
	campos[1] = 1.0;
	campos[2] = 1.0;
	camangle[2] += xrel;
	camangle[0] += yrel;
	if(camangle[0] > 90) camangle[0] = 90.0;
	if(camangle[0] < -90) camangle[0] = -90.0;
	camangle[2] = fmod(camangle[2], 360.0);
	updateCameraViewMatrix(campos, camangle);
	return TRUE;
}
int gamecodeHandleMousePress(int button, int type){
	return TRUE;
}

