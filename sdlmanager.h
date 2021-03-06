#ifndef SDLMANAGERHEADER
#define SDLMANAGERHEADER

int resizeWindow(int width, int height, int bpp, int debugmode);
int sdlInit(int width, int height, int bpp, int debugmode);
void swapBuffers(void);
int sdlCheckEvent(void);
void sdlSetMouseGrab(int grab);
int sdlToggleMouseGrab(void);

#endif
