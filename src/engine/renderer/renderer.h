#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../graphics/mesh/mesh.h"
#include "../math/mat4.h"
#include "../graphics/shader/shader.h"
#include "../graphics/texture/texture.h"

typedef struct {
  GLuint shader;
  GLFWwindow *window;
  GLint locModel;
  GLint locView;
  GLint locProj;
  GLint locTextAtlas;
  GLint locTileSize;
  GLint locCutOut;
} Renderer;

void renderer_init(Renderer *renderer, GLFWwindow *window);
void renderer_begin(Renderer *renderer);
void renderer_draw_mesh(Renderer *renderer, Mesh *mesh, Mat4 model);
void renderer_draw_submesh(Renderer *renderer, Mesh *mesh, Mat4 model, size_t submeshIndex);
static void set_sub_mesh_render_config(Renderer *renderer, SubMesh *submesh);
void renderer_set_view(Renderer *renderer, Mat4 view);
void renderer_set_projection(Renderer *renderer, Mat4 projection);
void renderer_end(Renderer *renderer);
void renderer_draw_texture_from_atlas(Renderer *renderer, TextureAtlas *textureAtlas);