uniform sampler1D velTex;
//uniform sampler2D posTex;
varying float texCoord;

void main(){
//	gl_FragColor = vec4(0.0);
	gl_FragColor.rgb = texture1D(velTex, texCoord).rgb;///10000.0;
}
