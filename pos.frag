uniform sampler2D velTex;
//uniform sampler2D posTex;
varying vec2 texCoord;

void main(){
//	gl_FragColor = vec4(0.0);
	gl_FragColor.rgb = texture2D(velTex, texCoord).rgb;///10000.0;
}
