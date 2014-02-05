uniform sampler2D posTex;
//uniform sampler2D velTex;
varying vec2 texCoord;


void main(){

	gl_FragColor = vec4(0.0);
	vec3 testpos = texture2D(posTex, texCoord).rgb;

	float x = 1.0;
	for(float y = 0.0;y < 32.0; y++){
		for(;x < 32.0; x++){

			vec4 current = texture2D(posTex, vec2(texCoord.x + (x/32.0), texCoord.y + (y/32.0))); // like 0.3% faster
//			vec4 current = texelFetch(posTex, ivec2(x,y), 0);
			vec3 r = current.rgb - testpos;
			float distSqr = r.x*r.x + r.y*r.y + r.z*r.z;
			float distSixth = distSqr * distSqr * distSqr;
			float s = current.w * inversesqrt(distSixth);
			gl_FragColor.rgb += r*s;


		}
		x = 0.0;
	}


}
