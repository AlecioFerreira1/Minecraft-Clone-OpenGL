#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aUv;
layout (location = 3) in vec3 aNor;
layout (location = 4) in vec2 aTileUv;

out vec2 vUv;
out vec4 vColor;
out vec2 vTileUv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection; 

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  vUv = aUv;
  vColor = aColor;
  vTileUv = aTileUv;
}