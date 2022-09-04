#version 330 core
// out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform float offsetV;
void main() {
    // FragColor = texture(ourTexture, texCoord);
    // gl_FragColor = texture(texture1, texCoord);

    if(texCoord.y > 0.5) {
        gl_FragColor =vec4(1.0f,0.0f,0.0f,1.0f);
        //  texture(vec4(1.0f,1.0f,1.0f,1.0f), texCoord * 2.0f);
    } else {
        gl_FragColor = texture(texture1, texCoord * 1.0f);
    }

    // if(texCoord.x > 0.5) {
    //     gl_FragColor =vec4(1.0f,0.0f,0.0f,1.0f);
    //     //  texture(vec4(1.0f,1.0f,1.0f,1.0f), texCoord * 2.0f);
    // } else {
    //     gl_FragColor = texture(texture1, texCoord * 1.0f);
    // }

    // gl_FragColor = texture(texture1, texCoord * 2.0f);
    // gl_FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), abs(sin(offsetV * 0.2)));
    // FragColor=mix(texture(texture1,texCoord),texture(texture2,texCoord),offsetV);
    // FragColor = vec4(ourColor, 1.0f);
}