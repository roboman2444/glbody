varying vec2 texCoord;
//uniform vec2 offsetVec;
void main(){
	gl_Position = gl_Vertex; // faster... dont need the viewprojection anyway
    	texCoord = gl_MultiTexCoord0.xy;
}
