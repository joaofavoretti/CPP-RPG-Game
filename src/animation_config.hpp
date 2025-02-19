#pragma once

#include <raylib.h>
#include <string>

struct AnimationConfig {
  std::string texturePath;
  Vector2 textureTileSize;
  Vector2 texturePosition;
  int numberOfFrames;
  float frameSpeed;
  float scale;
  bool loop = false;
  bool flip = false;
};
