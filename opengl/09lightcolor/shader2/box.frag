#version 330 core
//绘制到屏幕的像素点
out vec4 FragColor;
// 纹理坐标
in vec2 outTexCoord;
//法向量是一个垂直于顶点表面的（单位）向量。
// 由于顶点本身并没有表面（它只是空间中一个独立的点），我们利用它周围的顶点来计算出这个顶点的表面
in vec3 outNormal;
// 片段的位置
in vec3 outFragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
//观察者位置
uniform vec3 viewPos;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main() {
  vec4 objectColor = mix(texture(texture1, outTexCoord), texture(texture2, outTexCoord), 0.1) * vec4(lightColor, 1.0); 

  // vec3 objectColor=vec3(0.0,1.0,0.0);

  //-----------环境光------------
  //环境光常量 0.1
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

//------------漫反射光照----------------
//diffuse
  //法线标准化
  vec3 norm = normalize(outNormal);
  //光的方向向量是光源位置向量与片段位置向量之间的向量差
  //最终的方向向量标准化
  vec3 lightDir = normalize(lightPos - outFragPos);
  //点乘，计算光源对当前片段实际的漫发射影响。两个向量之间的角度大于90度，点乘的结果就会变成负数，负数颜色没有意义
  float diff = max(dot(norm, lightDir), 0.0);
  //乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小
  vec3 diffuse = diff * lightColor;

  //环境光分量和漫反射分量，我们把它们相加，然后把结果乘以物体的颜色，来获得片段最后的输出颜色
  // vec3 result = (ambient + diffuse) * vec3(objectColor);

// ----------------镜面光照--------------------
  float specularStrength = 0.5;
  vec3 viewDir = normalize(viewPos - outFragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  //计算镜面分量
  //32是高光的反光度(Shininess)。一个物体的反光度越高，反射光的能力越强，散射得越少，高光点就会越小
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
  vec3 specular = specularStrength * spec * lightColor;
//
  vec3 result = (ambient + diffuse + specular) * vec3(objectColor);
  FragColor = vec4(result, 1.0);
}