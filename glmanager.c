#include <GL/glew.h>
#include <GL/gl.h>

#include <time.h> // yes i know..
#include <math.h> // yes i know..


#include "globaldefs.h"
#include "glmanager.h"
#include "shadermanager.h"
#include "framebuffermanager.h"
#include "sdlmanager.h"
#include "matrixlib.h"
#include "gamecode.h"

#define SIZE 32

int screenx;
int screeny;

GLuint velTexid, posTexid, velFBid, posFBid;
GLuint vel2Texid, vel2FBid;
GLuint velShader, posShader, starShader;
GLuint vaoID, vboID, indicesID;
GLuint starID, vaostarID;
GLuint starprojpos, starviewpos, starviewprojpos;
GLuint forceunipos;
matrix4x4_t projectionmatrix, viewmatrix;

//		   2d vert   |texcoords
#ifndef ONED

GLfloat fsverts[] ={-1.0, -1.0, 0.0, 0.0,
		   1.0, -1.0, 1.0, 0.0,
		   1.0,  1.0, 1.0, 1.0,
		  -1.0,  1.0, 0.0, 1.0};
#else
GLfloat fsverts[] ={-1.0, -1.0, 0.0,
		   1.0, -1.0, 1.0,
		   1.0,  1.0, 1.0,
		  -1.0,  1.0, 0.0};

#endif

GLuint fsindices[] = {0,1,2, 2,3,0};

extern int initUniforms(void);
//extern int updateCameraViewMatrix(void);
extern int updateCameraProjMatrix(void);
extern int updateCameraViewMatrix(double pos[3], double angle[3]);
extern int updateMatrix(void);


int glVBO(void){
	glGenVertexArrays(1, &vaoID);
	glGenVertexArrays(1, &vaostarID);
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &indicesID);
	glGenBuffers(1, &starID);

	glBindVertexArray(vaostarID);

	GLfloat *starverts;
	starverts = malloc(5*SIZE*SIZE*sizeof(GLfloat));
	memset(starverts, 0, 5*SIZE*SIZE*sizeof(GLfloat));
#ifndef ONED
	int x, y, i;
	for(x = 0; x< SIZE; x++){
		for(y = 0; y< SIZE; y++){
			i = (x*SIZE + y)*5;
//			starverts[i]   = (float)x;
//			starverts[i+1] = (float)y/(float)SIZE;
			starverts[i]   = 0.0;
			starverts[i+1] = 0.0;
			starverts[i+2] = 0.0;
			starverts[i+3] = (float)x/(float)SIZE;
			starverts[i+4] = (float)y/(float)SIZE;
		}
	}
#else
	int x;
	for(x = 0; x< SIZE * SIZE; x++){
			int i = x*5;
			starverts[i]   = (float)x/100.0;
			starverts[i+1] = 0.0;
			starverts[i+2] = 0.0;
			starverts[i+3] = (float)x/(float)SIZE*SIZE;
			starverts[i+3] = (float)x/(float)SIZE*SIZE;
	}
#endif
#ifndef ONED
	glBindBuffer(GL_ARRAY_BUFFER, starID);
	glBufferData(GL_ARRAY_BUFFER, 5*SIZE*SIZE*sizeof(GLfloat), starverts, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY); //todo maybe remove
	glVertexPointer(3, GL_FLOAT, 5*sizeof(GLfloat), NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 5*sizeof(GLfloat), ((char*)NULL) + 3*sizeof(GLfloat));


	free(starverts);



	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fsverts), fsverts, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 4*sizeof(GLfloat), NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 4*sizeof(GLfloat), ((char*)NULL) + 2*sizeof(GLfloat));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fsindices), fsindices, GL_STATIC_DRAW);
#else
	glBindBuffer(GL_ARRAY_BUFFER, starID);
	glBufferData(GL_ARRAY_BUFFER, 5*SIZE*SIZE*sizeof(GLfloat), starverts, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY); //todo maybe remove
	glVertexPointer(3, GL_FLOAT, 5*sizeof(GLfloat), NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 5*sizeof(GLfloat), ((char*)NULL) + 3*sizeof(GLfloat));


	free(starverts);



	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fsverts), fsverts, GL_STATIC_DRAW);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 3*sizeof(GLfloat), NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(1, GL_FLOAT, 3*sizeof(GLfloat), ((char*)NULL) + 2*sizeof(GLfloat));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(fsindices), fsindices, GL_STATIC_DRAW);

#endif






	return TRUE;
}
int fillRandom(void){
	srand(time(NULL));
	GLfloat * posarray = malloc(4*SIZE*SIZE*sizeof(GLfloat));
	GLfloat * velarray = malloc(4*SIZE*SIZE*sizeof(GLfloat));
#ifndef FLAG
	int i;
	int top = 4*SIZE*SIZE;
	for(i = 0; i< top; i+=4){
		posarray[i]   = (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5);
		posarray[i+1] = (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5);
//		posarray[i+2] = (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5);
		posarray[i+2] = 0.0;
		float length = sqrt(posarray[i]*posarray[i]+posarray[i+1]*posarray[i+1]+posarray[i+2]*posarray[i+2]);
		length += (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5)/5.0;
//		length /= 1000000000.0;
//		length /= 1000000000.0;
		length /= 700000.0;
		posarray[i]/=length;
		posarray[i+1]/=length;
		posarray[i+2]/=length;
		posarray[i+3] = ((GLfloat)rand() / (GLfloat)RAND_MAX)*500.0; // "mass"
		posarray[i+3] *= posarray[i+3] * posarray[i+3];

//		velarray[i]   = (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5)*1000.0;
		velarray[i]   = (-posarray[i+1]/length)/1000000000.0;
		velarray[i+1] =  (posarray[i]/length)  /1000000000.0;
//		velarray[i]   = 0.0;
//		velarray[i+1] = 0.0;
//		velarray[i+2] = 0.0;
//		velarray[i+3] = 0.0;

	}
	velarray[0] = 0.0;
	velarray[1] = 0.0;
	velarray[2] = 0.0;
	posarray[0] = 0.0;
	posarray[1] = 0.0;
	posarray[2] = 0.0;
	posarray[3] = 1000000000000.0;
#else
	int x, y;
	for(x = 0; x< SIZE; x++){
		for(y = 0; y < SIZE; y++){
			int i = (x*SIZE+y)*4;
//			posarray[i]   = ((float)x*2.0/(float)SIZE) -1.0;
//			posarray[i+1] = ((float)y*2.0/(float)SIZE) -1.0;
			posarray[i]   = (float)x/(float)SIZE;
			posarray[i+1] = (float)y/(float)SIZE;
			posarray[i+2] = 0.0;
			posarray[i+2] = (((GLfloat)rand() / (GLfloat)RAND_MAX)-0.5)*0.1;
			posarray[i+3] = 1.0; // movement multiplier
			velarray[i]   = 0.0;
			velarray[i+1] = 0.0;
			velarray[i+2] = 0.0;
			velarray[i+3] = 0.0;
		}
	}
	x = 0;
	for(y = 0; y < SIZE; y++){
		int i = (x*SIZE+y)*4;
		posarray[i+3] = 0.0; //they dont move, period
	}
/*
	y = 0;
	for(x = 0; x < SIZE; x++){
		int i = (x*SIZE+y)*4;
		posarray[i+3] = 0.0; //they dont move, period
	}

	x = SIZE-1;
	for(y = 0; y < SIZE; y++){
		int i = (x*SIZE+y)*4;
		posarray[i+3] = 0.0; //they dont move, period
	}
	y = SIZE-1;
	for(x = 0; x < SIZE; x++){
		int i = (x*SIZE+y)*4;
		posarray[i+3] = 0.0; //they dont move, period
	}
*/
#endif
	glBindTexture(GL_TEXTURE_2D, posTexid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SIZE, SIZE, 0 , GL_RGBA, GL_FLOAT, posarray);
	glBindTexture(GL_TEXTURE_2D, velTexid);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SIZE, SIZE, 0 , GL_RGBA, GL_FLOAT, velarray);

	if(posarray)free(posarray);
	if(velarray)free(velarray);

	return TRUE;

}
int glSetupUniforms(void){

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, posTexid);
	glUniform1i(glGetUniformLocation(velShader, "posTex"), 1);
	glUniform1i(glGetUniformLocation(posShader, "posTex"), 1);
	glUniform1i(glGetUniformLocation(starShader, "posTex"), 1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, velTexid);
	glUniform1i(glGetUniformLocation(posShader, "velTex"), 2);
	glUniform1i(glGetUniformLocation(velShader, "velTex"), 2);
	glUniform1i(glGetUniformLocation(starShader, "velTex"), 2);


	glActiveTexture(GL_TEXTURE0);

	return TRUE;
}
int glInit(void){
	GLenum glewError = glewInit();
	if(glewError != GLEW_OK){
		printf("ERROR with the glew: %s\n", glewGetErrorString(glewError));
		return FALSE;
	}
	initShaderSystem();
	initFrameBufferSystem();
	#ifndef ONED
	#ifdef FLAG
		velShader = returnShader(createAndLoadShader("flagvel")).id;
		starShader = returnShader(createAndLoadShader("flag")).id;
	#else
		velShader = returnShader(createAndLoadShader("vel")).id;
		starShader = returnShader(createAndLoadShader("star")).id;
	#endif
	posShader = returnShader(createAndLoadShader("pos")).id;
	#else
	velShader = returnShader(createAndLoadShader("velone")).id;
	posShader = returnShader(createAndLoadShader("posone")).id;
	starShader = returnShader(createAndLoadShader("starone")).id;
	#endif
	createFrameBuffersAndTextures(SIZE, SIZE);
	framebuffer_t tf;
	tf = returnFrameBuffer(findFrameBufferByName("pos"));
	posTexid = tf.texid;
	posFBid = tf.id;
	tf = returnFrameBuffer(findFrameBufferByName("vel"));
	velTexid = tf.texid;
	velFBid = tf.id;

	printf("velTexid: %d velFBid: %d velShader: %d  posTexid: %d posFBid: %d posShader: %d \n", velTexid, velFBid, velShader, posTexid, posFBid, posShader);
	printf("star: %d\n", starShader);
	glVBO();

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_ONE, GL_ONE); // for adding the current with the changes
	glColor3f(1.0f, 1.0f, 1.0f);

	fillRandom();
//	glSetupUniforms();
	initUniforms();
	updateCameraProjMatrix();
//	updateCameraViewMatrix({0.0,0.0,0.0},{0.0,0.0,0.0});

	return TRUE; // so far so good
}

int updateCameraViewMatrix(double campos[3], double camangle[3]){
	float out[16];

/*
	Matrix4x4_CreateTranslate(&viewmatrix, campos[0], campos[1], campos[2]);
	Matrix4x4_ConcatRotate(&viewmatrix, 90, 1.0, 0.0, 0.0 );
	Matrix4x4_ConcatRotate(&viewmatrix, camangle[2], 0.0, 1.0, 0.0);
	Matrix4x4_ConcatRotate(&viewmatrix, camangle[0], 1.0, 0.0, 0.0);
*/
/*
	matrix4x4_t tempmatrix;
	matrix4x4_t basematrix;
	Matrix4x4_CreateTranslate(&viewmatrix, campos[0], campos[1], campos[2]);
//	Matrix4x4_ConcatRotate(&viewmatrix, 90, 1.0, 0.0, 0.0 );
	Matrix4x4_ConcatRotate(&viewmatrix, camangle[2], 0.0, 1.0, 0.0);
	Matrix4x4_ConcatRotate(&viewmatrix, camangle[0], 1.0, 0.0, 0.0);


        Matrix4x4_Invert_Full(&tempmatrix, &viewmatrix);
        Matrix4x4_CreateRotate(&basematrix, -90, 1, 0, 0);
        Matrix4x4_ConcatRotate(&basematrix, 90, 0, 0, 1);
        Matrix4x4_Concat(&viewmatrix, &basematrix, &tempmatrix);
*/

	matrix4x4_t tempmatrix;
	matrix4x4_t basematrix;
	Matrix4x4_CreateFromQuakeEntity(&viewmatrix, campos[0], campos[1], campos[2], camangle[0], camangle[2], camangle[1], 1.0);
//	Matrix4x4_ConcatRotate(&viewmatrix, 90, 1.0, 0.0, 0.0 );
//	Matrix4x4_ConcatRotate(&viewmatrix, camangle[2], 0.0, 1.0, 0.0);
//	Matrix4x4_ConcatRotate(&viewmatrix, camangle[0], 1.0, 0.0, 0.0);


        Matrix4x4_Invert_Full(&tempmatrix, &viewmatrix);
        Matrix4x4_CreateRotate(&basematrix, -90, 1, 0, 0);
        Matrix4x4_ConcatRotate(&basematrix, 90, 0, 0, 1);
        Matrix4x4_Concat(&viewmatrix, &basematrix, &tempmatrix);


	glUseProgram(starShader);
	Matrix4x4_ToArrayFloatGL(&viewmatrix, out);
	glUniformMatrix4fv(starviewpos,1, GL_FALSE, out);
	updateMatrix();
	return TRUE;
}
int updateMatrix(){
	matrix4x4_t viewprojectionmatrix;
	float out[16];
	glUseProgram(starShader);
	Matrix4x4_Concat(&viewprojectionmatrix, &viewmatrix, &projectionmatrix);
//	matrix4x4_t temp;
//	Matrix4x4_Invert_Simple(&temp, &viewmatrix);
//	Matrix4x4_Concat(&viewprojectionmatrix, &temp, &projectionmatrix);
	Matrix4x4_ToArrayFloatGL(&viewprojectionmatrix, out);
	glUniformMatrix4fv(starviewprojpos,1, GL_FALSE, out);
	return TRUE;
}
int updateCameraProjMatrix(/*matrix4x4_t proj*/){
	glUseProgram(starShader);

	float out[16];
	float nearclip = 0.1;
	float fov = 360/130*3.1415926; // degrees to radians / 2
	float aspect = screenx/screeny;
	const float nudge = 1.0 - 1.0 / (1<<23);
//	float frustumy = tan((fov));
//	float frustumx = frustumy/aspect;
	float frustumy = 0.75;
	float frustumx = 0.75 * aspect;
	memset(out, 0, sizeof(out));
        out[ 0] = 1.0 / frustumx;
        out[ 5] = 1.0 / frustumy;
        out[10] = -nudge;
        out[11] = -1.0;
        out[14] = -2.0 * nearclip * nudge;
	Matrix4x4_FromArrayFloatGL(&projectionmatrix, out);
	glUniformMatrix4fv(starprojpos,1, GL_FALSE, out);
	updateMatrix();
	return TRUE;
}
int updateScreenSize(int x, int y){
	if(x < 1) x = 1;
	if(y < 1) y = 1;
	screenx = x;
	screeny = y;
	//if needed, resize framebuffers, redo matricies for stuff, etc
	return TRUE;
}
int initUniforms(void){
	starprojpos = glGetUniformLocation(starShader, "proj");
	starviewprojpos = glGetUniformLocation(starShader, "viewprojection");
	starviewpos = glGetUniformLocation(starShader, "view");
	forceunipos = glGetUniformLocation(velShader, "force");

	return TRUE;
}

int glRender(void){
	glBindVertexArray(vaoID);

	glViewport(0,0, SIZE, SIZE);
	glUseProgram(velShader);
#ifdef FLAG
	glUniform2f(forceunipos, ((GLfloat)rand() / (GLfloat)RAND_MAX)*0.1, -0.01);

#endif
	glBindFramebuffer(GL_FRAMEBUFFER, velFBid);
	glBindTexture(GL_TEXTURE_2D, posTexid);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

#ifdef FLAG
	glBlendFunc(GL_DST_COLOR, GL_ZERO); // for adding the current with the changes
	glColor3f(0.8, 0.8, 0.8);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBlendFunc(GL_ONE, GL_ONE); // for adding the current with the changes
	glColor3f(1.0, 1.0, 1.0);
#endif

	glUseProgram(posShader);
	glBindFramebuffer(GL_FRAMEBUFFER, posFBid);
	glBindTexture(GL_TEXTURE_2D, velTexid);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(vaostarID);
	glViewport(0,0,screenx,screeny);
	glUseProgram(starShader);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, posTexid);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, SIZE*SIZE);






//sleep(1);

	swapBuffers();


	return TRUE;
}
