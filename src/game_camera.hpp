#pragma once

#include <raylib.h>

struct GameCamera {
  Camera2D camera = {0};
  Vector2 target = {0.0f, 0.0f};
  float lerpFactor = 0.1f; // Lerp factor for smooth interpolation

  GameCamera() {
    camera.target = {0, 0};
    camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 3.0f;
  }

  void FollowTarget(Vector2 target) { this->target = target; }

  void Update(double deltaTime) {
    // Linear Interpolation (Lerp)
    camera.target.x += (target.x - camera.target.x) * lerpFactor;
    camera.target.y += (target.y - camera.target.y) * lerpFactor;
  }

  Camera2D GetCamera() { return camera; }
};
