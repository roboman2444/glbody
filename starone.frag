uniform sampler1D posTex;
//uniform sampler2D velTex;
varying float texCoord;
void main(){
//	gl_FragColor = vec4(1.0);
//	gl_FragColor.g = 0.5;
//	gl_FragColor = texture1DLod(velTex, texCoord, 0.0);
	gl_FragColor = vec4(normalize(abs(texture1D(posTex, texCoord))));
	gl_FragColor = vec4(normalize(abs(vec3(texture1D(posTex, texCoord)))), 1.0);
//	gl_FragColor = vec4(1.0, texture2D(posTex, texCoord).a*0.1, 1.0, 1.0);
}
