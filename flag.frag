uniform sampler2D posTex;
//uniform sampler2D velTex;
varying vec2 texCoord;
void main(){
//	gl_FragColor = vec4(1.0);
//	gl_FragColor.g = 0.5;
//	gl_FragColor = texture2DLod(velTex, texCoord, 0.0);
//	gl_FragColor = vec4(normalize(abs(texture2D(posTex, texCoord))));
	gl_FragColor = vec4(normalize(abs(vec3(texture2D(posTex, texCoord))))*0.5, 1.0);
//	gl_FragColor = vec4(1.0, texture2D(posTex, texCoord).a*0.1, 1.0, 1.0);
}
