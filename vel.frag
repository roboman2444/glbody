uniform sampler2D posTex;
//uniform sampler2D velTex;
varying vec2 texCoord;


void main(){
	
	gl_FragColor = vec4(0.0);
	vec3 testpos = vec3(texture2D(posTex, texCoord));

	int x =1; // for not sampling self
	for(int y = 0;y < 32; y++){
		for(;x < 32; x++){
			vec4 current = texture2D(posTex, texCoord + vec2(x,y)/32.0); // maybe change to textureoffset...
			//vec4 current = textureOffset(posTex, texCoord, ivec2(x,y)); // needs "constants"

			vec3 r = vec3(current) - testpos;
			
			float distSqr = r.x*r.x + r.y*r.y + r.z*r.z;
			//float distSqr = dot(r,r); //same performance
			float distSixth = distSqr * distSqr * distSqr;
			//float invDistCube = 1/length(r); //same performance... not actually the right math either

			float invDistCube = inversesqrt(distSixth);
			float s = current.w * invDistCube;
			
			//float DistCube = sqrt(distSixth); // no real performance gain
			//float s = current.w/DistCube;

			//gl_FragColor += vec4(r*s,1.0);
			gl_FragColor.rgb += r*s; //no real change in performance... but i like it better
		}
		x = 0;
	}
	//gl_FragColor/100000.0;

}
