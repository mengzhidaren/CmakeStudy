#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 mTex;
out vec3 ourColor;
out vec2 texCoord;

uniform mat4 tansform;

void main() {
    gl_Position =tansform* vec4(aPos.x, aPos.y, aPos.z, 1.0f);
    ourColor = aColor;
    texCoord = mTex;
}