#include "game_camera.hpp"

GameCamera::GameCamera() {
  camera.target = {0, 0};
  camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 3.0f;
}

void GameCamera::FollowTarget(Vector2 target) { this->target = target; }

void GameCamera::Update(double deltaTime) {
  camera.target.x += (target.x - camera.target.x) * lerpFactor;
  camera.target.y += (target.y - camera.target.y) * lerpFactor;
}

Camera2D GameCamera::GetCamera() { return camera; }
