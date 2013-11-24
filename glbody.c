//System includes

//local includes
#include "globaldefs.h"
#include "glbody.h"
#include "glmanager.h"
#include "sdlmanager.h"
//main
extern int SDL_GetTicks();

int main(int argc, char *argv[]){
unsigned int to, t;
unsigned int framecount = 0;

	if(!sdlInit(1366, 768, 24, TRUE) || !glInit()) return FALSE;
//	sdlSetMouseGrab(1);
	to = SDL_GetTicks();
	while(TRUE){
		sdlCheckEvent();
		glRender();
		framecount++;
		if(framecount == 1000){
			t = SDL_GetTicks();
			printf("%f fps \n", 1000000.0f/(t-to));
			to = t;
			framecount = 0;
		}
	}
//	glRender();
//	sleep (2000);
	return TRUE;
}
