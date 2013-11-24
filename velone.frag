uniform sampler1D posTex;
//uniform sampler2D velTex;
varying float texCoord;


void main(){
	
	gl_FragColor = vec4(0.0);
	vec3 testpos = vec3(texture1D(posTex, texCoord));

		for(int x = 1;x < 1024; x++){
			vec4 current = texture1D(posTex, texCoord + float(x)/1024.0); // maybe change to textureoffset...
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
}
