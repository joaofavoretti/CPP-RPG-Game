#pragma once

#include <memory>
#include <map>

#include "raylib.h"
#include "tmx.hpp"

enum GameMapOption {
  MAIN_HALL,
  STAR_HALL,
};

static const std::map<GameMapOption, std::string> GameMapFilename = {
  {MAIN_HALL, "../assets/map/first-map.tmx"},
  {STAR_HALL, "../assets/map/second-map.tmx"},
};

static const std::map<GameMapOption, Vector2> GameMapInitialPosition = {
  {MAIN_HALL, {200, 200}},
  {STAR_HALL, {150, 150}},
};

struct GameMap {
private:
  GameMapOption option;
  std::unique_ptr<TMX> tmx;
  Vector2 pos = {0, 0};
 
public:
  GameMap(GameMapOption option);
  Vector2 GetInitialPosition();
  bool IsColliding(Rectangle rect);
  void Draw();
};
