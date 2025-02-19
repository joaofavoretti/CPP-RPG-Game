#include <cfloat>
#include <memory>
#include <raylib.h>

#include "player.hpp"
#include "projectile.hpp"
#include "projectile_system.hpp"

std::unique_ptr<Player> player;
std::unique_ptr<ProjectileSystem> projectileSystem;

void Setup() {
  player = std::make_unique<Player>((Vector2){10, 0});

  projectileSystem = std::make_unique<ProjectileSystem>(
      std::move(std::make_unique<Animation>(AnimationConfig{
          .texturePath = "../assets/pixel_art/1 Characters/Other/Arrow.png",
          .textureTileSize = {11, 3},
          .texturePosition = {0, 0},
          .numberOfFrames = 1,
          .frameSpeed = 0.1f,
          .scale = 2.0f,
          .loop = false,
          .flip = false,
      })));
}

void Update(double deltaTime) {
  player->Update(deltaTime);

  std::map<PlayerAnimationEnum, float> angleMap = {
      {PlayerAnimationEnum::MOVE_RIGHT, 0},
      {PlayerAnimationEnum::MOVE_LEFT, PI},
      {PlayerAnimationEnum::MOVE_UP, 3 * PI / 2},
      {PlayerAnimationEnum::MOVE_DOWN, PI / 2}};

  std::map<PlayerAnimationEnum, Vector2> offsetMap = {
      {PlayerAnimationEnum::MOVE_RIGHT, {17, 18}},
      {PlayerAnimationEnum::MOVE_LEFT, {32, 24}},
      {PlayerAnimationEnum::MOVE_UP, {18, 42}},
      {PlayerAnimationEnum::MOVE_DOWN, {36, 16}}};

  projectileSystem->SetOffset(offsetMap[player->GetLastMoveAnimation()]);

  if (IsKeyPressed(KEY_SPACE)) {
    projectileSystem->Add(ProjectileConfig{
        .position = player->GetPosition(),
        .angle = angleMap[player->GetLastMoveAnimation()],
        .speed = 500,
    });
  }
  projectileSystem->Update(deltaTime);
}

void Draw() {
  ClearBackground(RAYWHITE);

  player->Draw();
  projectileSystem->Draw();
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "Sprite Testing Zone");

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
