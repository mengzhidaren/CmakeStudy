#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float offsetV;
void main() {
    // FragColor = texture(texture1, texCoord)*vec4(ourColor,1.0f);
//     gl_FragColor = texture(texture1, texCoord)*vec4(ourColor,1.0f);
//    gl_FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), abs(sin(offsetV * 0.2)));
     FragColor=mix(texture(texture1,texCoord),texture(texture2,texCoord),offsetV);
    // FragColor = vec4(ourColor, 1.0f);
}