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

static const std::map<GameMapOption, Vector2> GameMapInitialPosition = {
  {MAIN_HALL, {200, 200}},
};

struct GameMap {
private:
  GameMapOption option;
  std::unique_ptr<TMX> tmx;
  Vector2 pos = {0, 0};

public:
  GameMap(GameMapOption option) {
    this->option = option;
    tmx = std::make_unique<TMX>(GameMapFilename.at(option).c_str());
  }

  Vector2 GetInitialPosition() {
    return GameMapInitialPosition.at(option);
  }

  void Draw() {
    tmx->Draw(pos, WHITE);
  }
};
