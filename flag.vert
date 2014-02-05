uniform sampler2D posTex;
//uniform sampler2D velTex;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 viewprojection;
varying vec2 texCoord;
void main(){
	mat4 viewproj = view * proj;
    	texCoord = gl_MultiTexCoord0.xy;
	gl_Position.rgb = texture2D(posTex, texCoord).rgb / vec3(1.77777777778, 1.0, 1.0);
//	gl_Position = vec4(texture2D(posTex, texCoord).rgb / 100000.0, 1.0) * viewprojection;
//	gl_Position.rgb = texture2D(posTex, texCoord).rgb / 1000000.0;
	gl_Position.z = 1.0;
//	gl_Position *=0.1;

//	gl_PointSize = sqrt(sqrt(texture2D(posTex, texCoord).a/100000.0));
//	gl_PointSize = gl_Position.z* 100.0;	
	gl_PointSize = 1.0;
}
