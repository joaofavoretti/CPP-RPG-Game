#pragma once

#include <memory>

#include "raylib.h"
#include "tmx.h"

#define RAYLIB_TMX_IMPLEMENTATION
#include "raylib-tmx.h"

struct Map {

private:
  std::unique_ptr<tmx_map> map;
  Vector2 pos = {0, 0};
  float scale = 2.0f;

public:

  Map(const char *filename) {
    map = std::unique_ptr<tmx_map>(LoadTMX(filename));
  }

  ~Map() {
    UnloadTMX(map.get());
  }

  Vector2 GetPosition() {
    return pos;
  }

  void SetPosition(Vector2 position) {
    pos = position;
  }

  void Draw() {
    DrawTMX(map.get(), pos.x, pos.y, WHITE);
  }

};
