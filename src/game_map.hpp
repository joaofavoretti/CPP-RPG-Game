#pragma once

#include <memory>
#include <map>

#include "raylib.h"
#include "tmx.hpp"

enum GameMapOption {
  MAIN_HALL,
};

static const std::map<GameMapOption, std::string> GameMapFilename = {
  {MAIN_HALL, "/archive/Tiled/first-map.tmx"},
};

struct GameMap {
private:
  std::unique_ptr<TMX> tmx;
  Vector2 pos = {0, 0};

public:
  GameMap(GameMapOption option) {
    tmx = std::make_unique<TMX>(GameMapFilename.at(option).c_str());
  }

  void Draw() {
    tmx->Draw(pos, WHITE);
  }
};
