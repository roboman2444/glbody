#ifndef FRAMEBUFFERMANAGERHEADER
#define FRAMEBUFFERMANAGERHEADER

typedef struct framebuffer_s
{
	GLuint id;
	char * name;
	GLuint width;
	GLuint height;
	float aspect; // maybe
	GLuint fov; // maybe
	GLuint texid;
	char type;
} framebuffer_t;
int initFrameBufferSystem(void);
//int createAndLoadShader(char * name);
int addFrameBufferToList(char * name, GLuint id, GLuint width, GLuint height, GLuint texid, char type);
int resizeFrameBuffer(GLuint id, GLuint width, GLuint height);

int findFrameBufferByName(char * name);
int createFrameBuffersAndTextures(int width, int height);
framebuffer_t returnFrameBuffer(int id);
#endif
