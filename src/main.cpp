#include <cfloat>
#include <memory>
#include <raylib.h>

#include "player.hpp"

#define RAYLIB_TMX_IMPLEMENTATION
#include "raylib-tmx.h"

std::unique_ptr<Player> player;

void Setup() {
  /*player = std::make_unique<Player>((Vector2){10, 0});*/
}

void Update(double deltaTime) {
  /*player->Update(deltaTime);*/
}

void Draw() {
  ClearBackground(RAYWHITE);

  /*player->Draw();*/
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Zone");

  SetTargetFPS(60);

  Setup();

  tmx_map *map = LoadTMX("/archive/Tiled/first-map.tmx");

  while (!WindowShouldClose()) {
    double deltaTime = GetFrameTime();
    Update(deltaTime);

    BeginDrawing();
    Draw();
    DrawTMX(map, 0, 0, WHITE);
    DrawFPS(10, 10);
    EndDrawing();
  }

  UnloadTMX(map);

  CloseWindow();
}
