//gloabl includes
#include <GL/glew.h>
#include <GL/gl.h>

//local includes
#include "globaldefs.h"
#include "framebuffermanager.h"

int fbnumber = 0; //the first is backbuffer
framebuffer_t *fblist;

extern int addFrameBufferToList(char *name, GLuint id, GLuint width, GLuint height, GLuint texid, char type);

int initFrameBufferSystem(void){
	if(fblist) free(fblist);
	fblist = malloc(fbnumber * sizeof(framebuffer_t));
	if(!fblist) memset(fblist, 0 , fbnumber * sizeof(framebuffer_t));
	addFrameBufferToList("default", 0,0,0,0, (char)0); //should put in the width/height
	return TRUE; // todo error check
}

int addFrameBufferToList(char *name, GLuint id, GLuint width, GLuint height, GLuint texid, char type){
	int current = fbnumber;
	fbnumber++;
	fblist = realloc(fblist, (fbnumber)*sizeof(framebuffer_t));
	fblist[current].name = name;
	fblist[current].id = id;
	fblist[current].width = width;
	fblist[current].height = height;
	fblist[current].aspect = (float)width/(float)height;
	fblist[current].texid = texid;
	fblist[current].type = type;
	//todo
	return current;
}
framebuffer_t returnFrameBuffer(int id){
	if(id >= fbnumber) return fblist[0];
	return fblist[id];
}

int findFrameBufferByName(char * name){
	int i;
	for(i = 0; i<fbnumber; i++){
		if(!strcmp(name, fblist[i].name)) return i;
	}
	return 0;
}
int resizeFrameBuffer(GLuint id, GLuint width, GLuint height){
	glBindTexture(GL_TEXTURE_2D, fblist[id].texid);
		glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	fblist[id].width = width;
	fblist[id].height = height;
	fblist[id].aspect = (float)width/(float)height;
	return id; //todo errorcheck
}
/*
int createFramebuffer(char * name){
	char * vertname = malloc(strlen(name) + 5);

	strcpy(vertname, name);strcat(vertname, ".vert");

	char * vertstring;
	int vertlength;

	loadFileString(vertname, &vertstring, &vertlength, 2);

	free(vertname);
	if(vertlength == 0){	//error
		free(vertstring);
		return FALSE;
	}
	char * fragname = malloc(strlen(name) + 5); //add on 5 extra characters for .frag
	strcpy(fragname,name); strcat(fragname, ".frag");
	char * fragstring;
	int fraglength;
	loadFileString(fragname, &fragstring, &fraglength, 2);
	free(fragname);
	if(fraglength == 0){	//error
		free(fragstring);
		return FALSE;
	}
	GLuint vertid = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertid, 1, (const GLchar**) &vertstring, &vertlength);
	glShaderSource(fragid, 1, (const GLchar**) &fragstring, &fraglength);
	free(vertstring); free(fragstring);
	//TODO errorcheck
	glCompileShader(vertid);
	glCompileShader(fragid);
	//TODO errorcheck
	//TODO errorcheck for compilation

	GLuint programid = glCreateProgram();
	//TODO errorcheck
	glAttachShader(programid, vertid);
	glAttachShader(programid, fragid);
	glLinkProgram(programid);
	//TODO errorcheck
	printProgramLogStatus(programid);
	int id = addProgramToList(name, programid, vertid, fragid);
	return id; //so far i am assuming that it works
}
*/
int createFrameBuffersAndTextures(int width, int height){
	GLuint velTexid, posTexid/*, massTexid*/;
	GLuint velFBOid, posFBOid;
	if (!width||!height){
		printf("Error, width and height have to be > 0");
		return 0;
	}
	glGenTextures(1, &velTexid);
	glGenTextures(1, &posTexid);
	if (!velTexid||!posTexid){
		printf("Error creating textures");
		return 0;
	}
#ifndef ONED
	glBindTexture(GL_TEXTURE_2D, posTexid);
		glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0 , GL_RGBA, GL_FLOAT, NULL); //todo set intiail pos
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, velTexid);
		glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0 , GL_RGBA, GL_FLOAT, NULL); // todo set initial vel
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

#else
	glBindTexture(GL_TEXTURE_2D, posTexid);
		glTexImage1D(GL_TEXTURE_1D, 0 , GL_RGBA, width*height, 0 , GL_RGBA, GL_FLOAT, NULL); //todo set intiail pos
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glBindTexture(GL_TEXTURE_2D, velTexid);
		glTexImage1D(GL_TEXTURE_1D, 0 , GL_RGBA, width*height, 0 , GL_RGBA, GL_FLOAT, NULL); // todo set initial vel
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_REPEAT);

#endif
	glBindTexture(GL_TEXTURE_2D, 0);
	glGenFramebuffers(1, &velFBOid);
	glGenFramebuffers(1, &posFBOid);
	if (!velFBOid||!posFBOid){
		printf("Error creating framebuffers");
		return 0;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, posFBOid);
		#ifndef ONED
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, posTexid, 0);
		#else
		glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_1D, posTexid, 0);
		#endif
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, velFBOid);
		#ifndef ONED
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, velTexid, 0);
		#else
		glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_1D, velTexid, 0);
		#endif
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

//	printf("%d\n",addFrameBufferToList("vel", velFBOid, width, height, velTexid, (char)1));
//	printf("%d\n",addFrameBufferToList("pos", posFBOid, width, height, posTexid, (char)1));
	addFrameBufferToList("vel", velFBOid, width, height, velTexid, (char)1);
	addFrameBufferToList("pos", posFBOid, width, height, posTexid, (char)1);

	return TRUE;
}
