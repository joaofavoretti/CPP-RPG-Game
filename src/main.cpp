#include <cfloat>
#include <memory>
#include <raylib.h>

#include "game_camera.hpp"
#include "game_map.hpp"
#include "player.hpp"
#include "fireball_entity.hpp"
#include "coin_entity.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<GameMap> map;
std::unique_ptr<GameCamera> camera;
std::unique_ptr<FireballEntity> fireball;
std::unique_ptr<CoinEntity> coin;

void Setup() {
  map = std::make_unique<GameMap>(GameMapOption::MAIN_HALL);
  player = std::make_unique<Player>(map->GetInitialPosition());
  player->AddCollisionCheck(
      [&](Rectangle rect) { return map->IsColliding(rect); });
  camera = std::make_unique<GameCamera>();
  fireball = std::make_unique<FireballEntity>(Vector2{100, 100}, Vector2{0, 0});
  coin = std::make_unique<CoinEntity>(Vector2{150, 150}, 4);

  // Approach 1
  coin->AddCollisionCallback(player.get(), [&](CoinEntity* coin) {
    player->AddScore(coin->GetScore());
    coin->SetPosition(Vector2{static_cast<float>(GetRandomValue(100, 200)), static_cast<float>(GetRandomValue(100, 200))});
  });
}

void Update(double deltaTime) {
  fireball->Update(deltaTime);
  coin->Update(deltaTime);
  player->Update(deltaTime);

  camera->FollowTarget(player->GetBoundaryCenter());
  camera->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  BeginMode2D(camera->GetCamera());
  map->Draw();
  fireball->Draw();
  coin->Draw();
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
