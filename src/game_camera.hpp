#pragma once

#include <raylib.h>

struct GameCamera {
  Camera2D camera = {0};
  Vector2 target = {0.0f, 0.0f};
  float lerpFactor = 0.1f;

  GameCamera();
  void FollowTarget(Vector2 target);
  void Update(double deltaTime);
  Camera2D GetCamera();
};
