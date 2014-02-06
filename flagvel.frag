uniform sampler2D posTex;
//uniform sampler2D velTex;
varying vec2 texCoord;
uniform vec3 force;


void main(){
	vec3 output;

	gl_FragColor = vec4(force, 0.0);
	vec4 mypos = texture2D(posTex, texCoord);
	if(mypos.a == 0.0) discard;

//	ivec2 pos;
	vec2 pos;
/*
	for(pos.x = -1.0; pos.x <= 1.0; pos.x++){
		for(pos.y = -1.0; pos.y <= 1.0; pos.y++){
//			if(pos.x == 0.0 && pos.y == 0.0) continue; // dont try itself
			vec2 samplevec = texCoord + pos/32.0;
//			if(samplevec.x > 1.0 || samplevec.x < 0.0 || samplevec.y > 1.0 || samplevec.y < 0.0) continue;
	//		vec3 testpos = textureOffset(posTex, texCoord, pos).rgb;
//			vec3 testpos = texture2D(posTex, texCoord + pos/32.0).rgb;
			vec3 testpos = texture2D(posTex, samplevec).rgb;
			vec3 delta = testpos - mypos.rgb;
			if(delta == vec3(0.0)) continue;
			float mylength = length(delta);
			vec3 forcedir = delta / mylength;
			gl_FragColor.rgb += (mylength - 0.03125) * forcedir;
		}
	}

*/
	for(pos.x = -10.0; pos.x <= 10.0; pos.x+=1.0){
		for(pos.y = -10.0; pos.y <= 10.0; pos.y+=1.0){
			if(pos.x == 0.0 && pos.y == 0.0) continue; // dont try itself
			vec2 samplevec = texCoord + pos/256.0;
//			if(samplevec.x > 1.0 || samplevec.x < 0.0 || samplevec.y > 1.0 || samplevec.y < 0.0) continue;
	//		vec3 testpos = textureOffset(posTex, texCoord, pos).rgb;
			vec3 testpos = texture2D(posTex, samplevec).rgb;
			vec3 delta = testpos - mypos.rgb;
			if(delta == vec3(0.0)) continue;
			float mylength = length(delta);
			vec3 forcedir = delta / mylength;
//			gl_FragColor.rgb += (mylength - 0.0625) * forcedir;
//			float stretch = (mylength - (0.03125 * length(pos)));
			float stretch = (mylength - (0.00390625 * length(pos)));
			gl_FragColor.rgb += stretch * forcedir;

		}
	}

	gl_FragColor *= 0.02;
	gl_FragColor *= mypos.a;

}
