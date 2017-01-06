uniform sampler2D flagImage;
varying float height;
const float SHADOW = 1.5;

void main()
{
	gl_FragColor = texture2D(flagImage, gl_TexCoord[0].st);
	gl_FragColor =  gl_FragColor * vec4(height+SHADOW,
										height+SHADOW,
										height+SHADOW,
										1.0);
}