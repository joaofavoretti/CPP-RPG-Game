#pragma once

#include <raylib.h>

#include "animation_config.hpp"

struct Animation {
  Texture2D texture;
  Vector2 textureTileSize;
  Vector2 texturePosition;
  float frameCounter = 0.0f;
  int numberOfFrames;
  int currentFrame = 0;
  float frameSpeed;
  bool loop;
  bool flip;
  float scale;
  bool floating;
  Vector2 screenPosition = {0, 0};
  Vector2 offset = {0, 0};
  float angle = 0.0f;

  void SetOffset(Vector2 offset);
  Vector2 GetSize();
  Animation(AnimationConfig config);
  void UpdateScreenPosition(Vector2 screenPosition);
  void UpdateAngle(float angle);
  void Reset();
  void Update(double deltaTime);
  void Draw();
  bool IsFinished();
};
