#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.545354678);
}

void main( void ) {
    vec2 position = ( gl_FragCoord.xy / resolution.xy );
    vec3 color = vec3(0.0);
    float mod;
    float rdm;
    
    for (int i = 0; i < 4; i++) {
        rdm = rand(vec2(1.0, float(i)));
        mod = cos(time * rdm * 10.0);
        color.r += sin( position.y * 5.0 * rdm + time * 100.0 * rdm) * 0.5;
        
        rdm = rand(vec2(float(i), float(i+1)));
        mod = cos(time * rdm * 10.0);
        color.g += sin( position.y * 5.0 * rdm - time * 100.0 * rdm) * 0.5;
        
        rdm = rand(vec2(float(i+1), float(i+2)));
        mod = cos(time * rdm * 10.0);
        color.b += sin( position.y * 5.0 * rdm + time * 100.0 * rdm) * 0.5;
    }
    gl_FragColor = vec4(color.r, color.g, color.b, 1.0 );
    
}