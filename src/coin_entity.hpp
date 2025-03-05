#pragma once

#include <map>
#include <raylib.h>
#include <raymath.h>
#include <stdexcept>
#include <string>

#include "animation_config.hpp"
#include "entity.hpp"

struct CoinEntity : Entity {
private:
  int amount;

protected:
  void SetupAnimationSystem() {
    Entity::SetupAnimationSystem();

    const std::map<int, std::string> CoinEntityTexturePaths = {
        {1, "../assets/pixel_art/2 Dungeon Tileset/2 Objects/Other/16.png"},
        {2, "../assets/pixel_art/2 Dungeon Tileset/2 Objects/Other/18.png"},
        {3, "../assets/pixel_art/2 Dungeon Tileset/2 Objects/Other/19.png"},
        {-1, "../assets/pixel_art/2 Dungeon Tileset/2 Objects/Other/20.png"},
    };

    const std::map<int, Vector2> CoinEntityTileSize = {
        {1, {4, 4}},
        {2, {5, 7}},
        {3, {7, 7}},
        {-1, {9, 10}},
    };

    std::string texturePath = amount < 4 ? CoinEntityTexturePaths.at(amount)
                                         : CoinEntityTexturePaths.at(-1);

    Vector2 textureTileSize =
        amount < 4 ? CoinEntityTileSize.at(amount) : CoinEntityTileSize.at(-1);

    animationSystem->RegisterAnimation(EntityAnimationId::IDLE,
                                       AnimationConfig{
                                           .texturePath = texturePath,
                                           .textureTileSize = textureTileSize,
                                           .texturePosition = {0, 0},
                                           .numberOfFrames = 1,
                                           .frameSpeed = 0.1f,
                                           .scale = scale,
                                           .loop = false,
                                           .flip = false,
                                       });

    animationSystem->Update(EntityAnimationId::IDLE, 0);
  }

public:
  CoinEntity(Vector2 position, int amount)
      : Entity(position, {0, 0}, 1.0), amount(amount) {

    if (amount < 1) {
      throw std::invalid_argument("Coin amount must be greater than 0");
    }

    SetupAnimationSystem();
  }

  void Update(double deltaTime) override { Entity::Update(deltaTime); }

  void Draw() override { Entity::Draw(); }
};
