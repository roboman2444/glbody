uniform sampler1D posTex;
//uniform sampler2D velTex;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 viewprojection;
varying float texCoord;
void main(){
//	mat4 viewproj = view * proj;
    	texCoord = gl_MultiTexCoord0.x;
//	gl_Position.rgb = texture1D(posTex, texCoord).rgb / 1000000.0 / vec3(1.77777777778, 1.0, 1.0);
	gl_Position = gl_Vertex;
	gl_Position.y = texCoord;
	gl_Position.z = 1.0;

//	gl_PointSize = sqrt(texture2D(posTex, texCoord).a/100000.0);
//	gl_PointSize = gl_Position.z* 100.0;	
	gl_PointSize = 1.0;
}
