#version 330 core

in vec2 vUv;
in vec4 vColor;
in vec2 vTileUv;

uniform sampler2D uTexture;
uniform vec2 tileSize;
uniform bool uCutout; 
out vec4 FragColor;

void main()
{
  vec2 atlasUv = vTileUv + fract(vUv) * tileSize;
  vec4 finalColor = texture(uTexture, atlasUv) * vColor;

  if(finalColor.a < 0.5 && uCutout) {
    discard;
  }

  FragColor = finalColor;
}