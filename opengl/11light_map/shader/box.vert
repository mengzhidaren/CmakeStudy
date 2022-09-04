#version 330 core
//位置X Y Z
layout(location = 0) in vec3 Position;
//法向量
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoords;

out vec2 outTexCoord;
out vec3 outNormal;
// 片段的位置
out vec3 outFragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {

  gl_Position = projection * view * model * vec4(Position, 1.0f);
  outFragPos = vec3(model * vec4(Position, 1.0));
  outTexCoord = TexCoords;
  //（注意：等比缩放不会破坏法线，因为法线的方向没被改变，仅仅改变了法线的长度，而这很容易通过标准化来修复）
  //每当我们应用一个不等比缩放时，法向量就不会再垂直于对应的表面了，这样光照就会被破坏
  //修复这个行为的诀窍是使用一个为法向量专门定制的模型矩阵。
  // 这个矩阵称之为法线矩阵(Normal Matrix)，它使用了一些线性代数的操作来移除对法向量错误缩放的影响
  // 法线矩阵被定义为「模型矩阵左上角的[逆矩阵]的[转置矩阵]」
  outNormal = mat3(transpose(inverse(model))) * Normal;

}