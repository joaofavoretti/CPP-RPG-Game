#include <cfloat>
#include <memory>
#include <raylib.h>

#include "game_map.hpp"
#include "game_camera.hpp"
#include "player.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<GameMap> map;
std::unique_ptr<GameCamera> camera;

void Setup() {
  map = std::make_unique<GameMap>(GameMapOption::MAIN_HALL);
  player = std::make_unique<Player>(map->GetInitialPosition());
  player->AddCollisionCheck([&](Rectangle rect) { return map->IsColliding(rect); });
  camera = std::make_unique<GameCamera>();
}

void Update(double deltaTime) {
  player->Update(deltaTime);

  Rectangle playerBoundaries = player->GetBoundaries();
  Vector2 playerCenter = {playerBoundaries.x + playerBoundaries.width / 2.0f,
                          playerBoundaries.y + playerBoundaries.height / 2.0f};
  camera->FollowTarget(playerCenter);
  camera->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  BeginMode2D(camera->GetCamera());

  map->Draw();

  DrawRectangleLines(player->GetBoundaries().x, player->GetBoundaries().y,
                     player->GetBoundaries().width,
                     player->GetBoundaries().height, RED);
  player->Draw();
  EndMode2D();
}

int main() {
  const int screenWidth = 860;
  const int screenHeight = 500;

  InitWindow(screenWidth, screenHeight, "Shattered Unity");

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
