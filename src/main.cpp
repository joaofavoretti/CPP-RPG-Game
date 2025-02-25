#include <cfloat>
#include <memory>
#include <raylib.h>

#include "game_map.hpp"
#include "player.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<GameMap> map;

void Setup() {
  player = std::make_unique<Player>((Vector2){10, 10});
  /*map = std::make_unique<GameMap>(GameMapOption::MAIN_HALL);*/
}

void Update(double deltaTime) {
  player->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  /*map->Draw();*/

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
