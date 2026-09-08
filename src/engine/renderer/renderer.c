#include "renderer.h"

void renderer_init(Renderer *renderer, GLFWwindow *window) {
  GLuint shader = shader_create(
    "assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl"
  );

  renderer->window = window;
  renderer->shader = shader;
  renderer->locModel = glGetUniformLocation(renderer->shader, "model"); 
  renderer->locView = glGetUniformLocation(renderer->shader, "view");
  renderer->locProj = glGetUniformLocation(renderer->shader, "projection");
  renderer->locTextAtlas = glGetUniformLocation(renderer->shader, "uTexture");
  renderer->locTileSize = glGetUniformLocation(renderer->shader, "tileSize");
  renderer->locCutOut = glGetUniformLocation(renderer->shader, "uCutout");
}

void renderer_begin(Renderer *renderer) {
  glBindVertexArray(0);
  glClearColor(1.f, 1.f, 1.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(renderer->shader); 
}

void renderer_draw_mesh(Renderer *renderer, Mesh *mesh, Mat4 model) {
  size_t numSubMeshes = vector_size(&mesh->subMeshes);

  for(size_t i = 0; i < numSubMeshes; ++i) {
    renderer_draw_submesh(renderer, mesh, model, i);
  }
}

void renderer_draw_submesh(Renderer *renderer, Mesh *mesh, Mat4 model, size_t submeshIndex) {
  if(submeshIndex >= vector_size(&mesh->subMeshes)) return;

  SubMesh *subMesh = vector_get_item(&mesh->subMeshes, submeshIndex);

  set_sub_mesh_render_config(renderer, subMesh);

  if(subMesh->indexesCount > 0) {
    glUniformMatrix4fv(renderer->locModel, 1, GL_FALSE, model.data);
    glBindVertexArray(mesh->VAO);
    glDrawArrays(GL_TRIANGLES, subMesh->startIndex, subMesh->indexesCount);
  }

  if(subMesh->renderMode == RENDER_MODE_BLEND) glDepthMask(GL_TRUE); 
}

static void set_sub_mesh_render_config(Renderer *renderer, SubMesh *submesh) {
  bool cutout = false;

  switch(submesh->renderMode) {
    case RENDER_MODE_OPAQUE:
      glDisable(GL_BLEND);
      break;

    case RENDER_MODE_CUTOUT:
      cutout = true;
      glDisable(GL_BLEND);
      break;
    
    case RENDER_MODE_BLEND:
      glEnable(GL_BLEND);
      glDepthMask(GL_FALSE);
      break;
    
    default:
      break;
  }

  glUniform1i(renderer->locCutOut, cutout);
}

void renderer_set_view(Renderer *renderer, Mat4 view) {
  glUniformMatrix4fv(renderer->locView, 1, GL_FALSE, view.data);
}

void renderer_set_projection(Renderer *renderer, Mat4 projection) {
  glUniformMatrix4fv(renderer->locProj, 1, GL_FALSE, projection.data);
}

void renderer_end(Renderer *renderer) {
  glfwSwapBuffers(renderer->window);
}

void renderer_draw_texture_from_atlas(Renderer *renderer, TextureAtlas *textureAtlas) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureAtlas->texture->id);
  glUniform1i(renderer->locTextAtlas, 0);
  
  glUniform2f(
    renderer->locTileSize, 
    ((float)textureAtlas->tileSize / (float)textureAtlas->texture->width),
    ((float)textureAtlas->tileSize / (float)textureAtlas->texture->height)
  );
}