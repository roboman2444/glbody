uniform sampler2D posTex;
//uniform sampler2D velTex;
varying vec2 texCoord;


void main(){
	
	gl_FragColor = vec4(0.0);
	vec3 testpos = texture2D(posTex, texCoord).rgb;
/*
	for(float x = 1.0; x < 32.0; x++){
		vec4 current = texture2D(posTex, vec2(texCoord.x + (x/32.0),texCoord.y));
		vec3 r = current.rgb - testpos;
		float distSqr = r.x*r.x + r.y*r.y + r.z*r.z;
		float distSixth = distSqr * distSqr * distSqr;
		float s = current.w * inversesqrt(distSixth);
		gl_FragColor.rgb += r*s;
	}
	for(float y = 1.0;y < 32.0; y++){
		for(float x = 0.0;x < 32.0; x++){
			vec4 current = texture2D(posTex, vec2(texCoord.x + (x/32.0), texCoord.y + (y/32.0))); // like 0.5% faster
			vec3 r = current.rgb - testpos;
			float distSqr = r.x*r.x + r.y*r.y + r.z*r.z;
			float distSixth = distSqr * distSqr * distSqr;
			float s = current.w * inversesqrt(distSixth);
			gl_FragColor.rgb += r*s;
		}
	}
*/

	float x = 1.0;
	for(float y = 0.0;y < 32.0; y++){
		for(;x < 32.0; x++){

			vec4 current = texture2D(posTex, vec2(texCoord.x + (x/32.0), texCoord.y + (y/32.0))); // like 0.3% faster
			//vec4 current = textureOffset(posTex, texCoord, ivec2(x,y)); // needs "constants"
			vec3 r = current.rgb - testpos;
			
			float distSqr = r.x*r.x + r.y*r.y + r.z*r.z;
//			float distSqr = dot(r,r); //same performance
			float distSixth = distSqr * distSqr * distSqr;


//			float invDistCube = inversesqrt(distSixth);
//			float s = current.w * invDistCube;

			float s = current.w * inversesqrt(distSixth);
			gl_FragColor.rgb += r*s;


		}
		x = 0.0;
	}


}
