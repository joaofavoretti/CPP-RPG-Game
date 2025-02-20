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
  /*player = std::make_unique<Player>((Vector2){10, 0});*/
  tmx = std::make_unique<TMX>("/archive/Tiled/first-map.tmx");
}

double t = 0.0f;

void Update(double deltaTime) {
  /*player->Update(deltaTime);*/

  // Move the map in a circle
  t += deltaTime;
  /*map->SetPosition(newPos);*/
}

void Draw() {
  ClearBackground(RAYWHITE);

  /*player->Draw();*/
  Vector2 newPos = {static_cast<float>(100 + sin(t) * 100),
                    static_cast<float>(100 + cos(t) * 100)};
  tmx->Draw(newPos, RED);
}

int main() {
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Range");

  SetTargetFPS(60);

  Setup();

  while (!WindowShouldClose()) {
    double deltaTime = GetFrameTime();
    Update(deltaTime);

    BeginDrawing();
    Draw();
    DrawFPS(10, 10);
    EndDrawing();
  }

  CloseWindow();
}
