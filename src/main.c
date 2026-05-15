#include "engine/core/game_app.h"

int main() {
  GameApp gameApp;

  gameApp_init(&gameApp);
  gameApp_run(&gameApp);
  gameApp_destroy(&gameApp);

  return 0;
}