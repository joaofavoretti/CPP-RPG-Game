#include <cfloat>
#include <memory>
#include <raylib.h>

#include "coin_entity.hpp"
#include "enemy.hpp"
#include "fireball_entity.hpp"
#include "game_camera.hpp"
#include "game_map.hpp"
#include "player.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<GameMap> map;
std::unique_ptr<GameCamera> camera;
std::unique_ptr<FireballEntity> fireball;
std::unique_ptr<CoinEntity> coin;
std::unique_ptr<Enemy> enemy;

void CreateCoin() {
  coin = std::make_unique<CoinEntity>(
      Vector2{static_cast<float>(GetRandomValue(100, 200)),
              static_cast<float>(GetRandomValue(100, 200))},
      GetRandomValue(1, 4));

  coin->AddTarget(player.get());

  coin->AddCollisionCallback(player.get(), [&](Entity *coinEntity) {
    CoinEntity *currentCoin = dynamic_cast<CoinEntity *>(coinEntity);
    player->AddScore(currentCoin->GetScore());
    CreateCoin();
  });
}

void Setup() {
  map = std::make_unique<GameMap>(GameMapOption::MAIN_HALL);
  player = std::make_unique<Player>(map->GetInitialPosition());
  player->AddCollisionCheck(
      [&](Rectangle rect) { return map->IsColliding(rect); });
  enemy = std::make_unique<Enemy>(Vector2{150, 100});
  enemy->AddPossibleTarget(player.get());
  enemy->AddCollisionCheck(
      [&](Rectangle rect) { return map->IsColliding(rect); });
  player->AddPossibleTarget(enemy.get());
  camera = std::make_unique<GameCamera>();
  fireball = std::make_unique<FireballEntity>(Vector2{100, 100}, Vector2{0, 0});
  CreateCoin();
}

void Update(double deltaTime) {
  fireball->Update(deltaTime);
  coin->Update(deltaTime);

  if (player->IsAlive()) {
    player->Update(deltaTime);
  }

  if (enemy->IsAlive()) {
    enemy->Update(deltaTime);
  }

  camera->FollowTarget(player->GetBoundaryCenter());
  camera->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  BeginMode2D(camera->GetCamera());
  map->Draw();
  fireball->Draw();
  coin->Draw();

  if (player->IsAlive()) {
    player->Draw();
  }

  if (enemy->IsAlive()) {
    enemy->Draw();
  }

  EndMode2D();

  DrawText(TextFormat("Score: %i", player->GetScore()), 10, 10, 20, GREEN);
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
    /*DrawFPS(10, 10);*/
    EndDrawing();
  }

  CloseWindow();
}
