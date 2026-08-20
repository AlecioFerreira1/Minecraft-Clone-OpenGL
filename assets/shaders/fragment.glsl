#version 330 core

in vec2 vUv;
in vec4 vColor;
in vec2 vTileUv;

uniform sampler2D uTexture;
uniform vec2 tileSize; 
out vec4 FragColor;

void main()
{
  vec2 atlasUv = vTileUv + fract(vUv) * tileSize;
  FragColor = texture(uTexture, atlasUv);
}