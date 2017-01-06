const float PI = 3.14159265;
const float TIMEDIV = 500;


uniform float time;
uniform float wind;
varying float texS;
varying float height;

void main()
{
	vec4 a = gl_Vertex;
	vec4 b = gl_MultiTexCoord0;
	
	a.y = a.y + sin(mod(b.s * wind + (time/TIMEDIV) * wind/5.0 ,2.0*PI));
	
	height = a.y;
	
    gl_Position = gl_ModelViewProjectionMatrix * a;  
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}