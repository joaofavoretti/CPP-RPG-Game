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

Vector2 pos = {0, 0};

void Setup() {
  /*player = std::make_unique<Player>((Vector2){10, 0});*/
  tmx = std::make_unique<TMX>("/archive/Tiled/first-map.tmx");
}

double t = 0.0f;

void Update(double deltaTime) {
  /*player->Update(deltaTime);*/

  // Move the map in a circle
  /*t += deltaTime;*/
  /*map->SetPosition(newPos);*/

  // Move the player
  if (IsKeyDown(KEY_RIGHT)) {
    pos.x += 1;
  } else if (IsKeyDown(KEY_LEFT)) {
    pos.x -= 1;
  } else if (IsKeyDown(KEY_UP)) {
    pos.y -= 1;
  } else if (IsKeyDown(KEY_DOWN)) {
    pos.y += 1;
  }
}

void Draw() {
  ClearBackground(RAYWHITE);

  Vector2 newPos = {static_cast<float>(100 + sin(t) * 100),
                    static_cast<float>(100 + cos(t) * 100)};
  tmx->Draw({0, 0}, WHITE);

  // Draw a small rectangle in the map, color RED if it collides with the map
  Rectangle playerRect = {pos.x, pos.y, 10, 10};
  Color color = tmx->IsColliding(playerRect) ? RED : GREEN;
  DrawRectangle(playerRect.x, playerRect.y, playerRect.width, playerRect.height,
                color);


  /*player->Draw();*/
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 480;

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
