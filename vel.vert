varying vec2 texCoord;
//uniform float offsetVec;
void main(){
	gl_Position = gl_Vertex; // faster... dont need the viewprojection anyway
    	texCoord = gl_MultiTexCoord0.xy;
}
