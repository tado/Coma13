#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const int num = 20;
uniform float pulseFreq[num];


void main( void ) {
    vec3 col;
    for (int i = 0; i < num; i++) {
        float n = mod(float(i), 3.0);
        if (n == 0.0) {
            col.r = col.r + sin(time * pulseFreq[i]);
        }
        if (n == 1.0) {
            col.g = col.g + sin(time * pulseFreq[i]);
        }
        if (n == 2.0) {
            col.b = col.b + sin(time * pulseFreq[i]);
        }
        //col = col + sin(time * pulseFreq[i]) * 0.4;
    }
    gl_FragColor = vec4( col, 1.0 );
}