#ifdef GL_ES
precision mediump float;
#endif

varying vec4 position;
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

const int num = 6;
uniform int col[num];
uniform float freq[num];
uniform float phase[num];
uniform float amp[num];
uniform float lfo[num];

const vec3 ORANGE = vec3(1.4, 0.8, 0.4);
const vec3 BLUE = vec3(0.5, 0.9, 1.3);
const vec3 GREEN = vec3(0.9, 1.4, 0.4);
const vec3 RED = vec3(1.8, 0.4, 0.3);

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.545354678);
}

void main( void ) {
    //vec2 position = ( gl_FragCoord.xy / resolution.xy );
    vec3 color = vec3(0.0);
    
    for (int i = 0; i < num; i++) {
        float n = mod(float(i), 3.0);
        float l = sin(time * lfo[i]) * 0.4 + 0.4;
        //float l = 0.5;
        if (col[i] == 0) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            //color.b += p; color.g += p * 0.75; color.r += p * 0.33;
            color += ORANGE * p;
        }
        if (col[i] == 1) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            //color.b += p * 0.75; color.g += p; color.r += p * 0.33;
            color += GREEN * p;
        }
        if (col[i] == 2) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            //color.b += p * 0.75; color.g += p * 0.75; color.r += p;
            color += BLUE * p;
        }
        if (col[i] == 2) {
            float p = sin( position.x * freq[i] / 1000.0 + time * phase[i]) * amp[i] * l;
            //color.b += p * 0.75; color.g += p * 0.75; color.r += p;
            color += RED * p;
        }
    }
    
    gl_FragColor = vec4( color.r, color.g, color.b, 1.0 );
}