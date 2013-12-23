#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform float freq;
uniform float amp;

void main( void ) {
    
	vec2 position = ( gl_FragCoord.xy / resolution.xy ) + mouse / 4.0;
    
	float color = 0.0;
	color += sin( 10.0 + time * freq) + 1.0;
    color *= amp;
    
	gl_FragColor = vec4( vec3( color*0.5, color* 0.8, color ), 1.0 );
    
}