#include <cfloat>
#include <memory>
#include <raylib.h>

#include "player.hpp"
#include "map.hpp"

#define RAYLIB_TMX_IMPLEMENTATION
#include "raylib-tmx.h"

std::unique_ptr<Player> player;
std::unique_ptr<Map> map;

void Setup() {
  /*player = std::make_unique<Player>((Vector2){10, 0});*/
  map = std::make_unique<Map>("/archive/Tiled/first-map.tmx");
}

double t = 0.0f;

void Update(double deltaTime) {
  /*player->Update(deltaTime);*/

  // Move the map in a circle
  t += deltaTime;
  Vector2 newPos = {static_cast<float>(100 + sin(t) * 100), static_cast<float>(100 + cos(t) * 100)};
  map->SetPosition(newPos);


}

void Draw() {
  ClearBackground(RAYWHITE);

  /*player->Draw();*/
  map->Draw();
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Range");

  SetTargetFPS(144);

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
