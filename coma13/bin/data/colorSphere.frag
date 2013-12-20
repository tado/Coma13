#ifdef GL_ES
precision mediump float;
#endif

varying vec4 position;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const int num = 5;
uniform int col[num];
uniform float freq[num];
uniform float phase[num];
uniform float amp[num];
uniform float lfo[num];

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.545354678);
}

void main( void ) {
    //vec2 position = ( gl_FragCoord.xy / resolution.xy );
    vec3 color = vec3(0.0);
    
    for (int i = 0; i < num; i++) {
        float n = mod(float(i), 3.0);
        //float l = sin(time * lfo[i]) * 0.5 + 0.5;
        float l = 0.5;
        if (col[i] == 0) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            color.b += p; color.g += p * 0.75; color.r += p * 0.33;
        }
        if (col[i] == 1) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            color.b += p * 0.75; color.g += p; color.r += p * 0.33;
        }
        if (col[i] == 2) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            color.b += p * 0.75; color.g += p * 0.75; color.r += p;
        }
    }
    
    gl_FragColor = vec4( color.r, color.g, color.b, 1.0 );
}