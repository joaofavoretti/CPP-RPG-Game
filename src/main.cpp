#include <cfloat>
#include <memory>
#include <raylib.h>

#include "map.hpp"
#include "player.hpp"

#define RAYLIB_TMX_IMPLEMENTATION
#include "raylib-tmx.h"

#include "tmx.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<TMX> tmx;

void Setup() {
  player = std::make_unique<Player>((Vector2){10, 0});
  tmx = std::make_unique<TMX>("/archive/Tiled/first-map.tmx");
}

void Update(double deltaTime) {
  player->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  tmx->Draw({0, 0}, WHITE);

  player->Draw();
}

int main() {
  const int screenWidth = 860;
  const int screenHeight = 500;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Range");

  SetTargetFPS(60);

  Setup();

  while (!WindowShouldClose()) {
    double deltaTime = GetFrameTime();
    Update(deltaTime);

    BeginDrawing();
    Draw();
    EndDrawing();
  }

  CloseWindow();
}
