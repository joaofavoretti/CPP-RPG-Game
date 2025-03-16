#pragma once

#include <iostream>
#include <map>
#include <raylib.h>
#include <raymath.h>
#include <stdexcept>
#include <string>

#include "animation_config.hpp"
#include "entity.hpp"
#include "player.hpp"

struct CoinEntity : Entity {
private:
  int amount;
  float targetFollowRange = 60.0f;
  Player *target = nullptr;
  Vector2 attractionSpeed = {0.0f, 0.0f};
  float attractionSpeedFactor = 0.8f;
  float maxAttractionSpeed = 1.0f;

protected:
  void RegisterAnimations() override {

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

    RegisterAnimation(EntityAnimationId::IDLE,
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

    SetAnimation(EntityAnimationId::IDLE);
  }

public:
  CoinEntity(Vector2 position, int amount)
      : Entity(position, {0, 0}, 1.0), amount(amount) {

    SetupAnimationSystem();

    if (amount < 1) {
      throw std::invalid_argument("Coin amount must be greater than 0");
    }
  }

  int GetScore() { return amount; }

  void AddTarget(Player *target) { this->target = target; }

  double t = 0;
  void Update(double deltaTime) override {
    animationSystem->Update(deltaTime);
    animationSystem->SetPosition(position);

    // Be attracted to the nearest player
    if (target != nullptr &&
        Vector2Distance(target->GetBoundaryCenter(), GetBoundaryCenter()) <
            targetFollowRange) {

      Vector2 direction = Vector2Normalize(
          Vector2Subtract(target->GetBoundaryCenter(), GetBoundaryCenter()));

      attractionSpeed =
          Vector2Add(Vector2Scale(direction, attractionSpeedFactor * deltaTime),
                     Vector2Scale(attractionSpeed, 0.99f));

      if (Vector2Length(attractionSpeed) > maxAttractionSpeed) {
        attractionSpeed =
            Vector2Scale(Vector2Normalize(attractionSpeed), maxAttractionSpeed);
      }

      /*std::cout << "Attraction speed: " << attractionSpeed.x << ", "*/
      /*          << attractionSpeed.y << std::endl;*/
      std::cout << "Size: " << Vector2Length(attractionSpeed) << std::endl;

      position = Vector2Add(position, attractionSpeed);

      CheckCollisionCallbacks();
      return;
    } else {
      attractionSpeed = Vector2Scale(attractionSpeed, 0.99f);
      position = Vector2Add(position, attractionSpeed);
    }

    // Make the coin float motion
    t += deltaTime;
    t = fmod(t, 3600.0);
    float floatAmplitude = 0.1f;
    float floatSpeed = 5.0f;
    SetPosition(Vector2{
        position.x,
        position.y + static_cast<float>(floatAmplitude * sin(floatSpeed * t))});
  }

  void Draw() override {
    Entity::Draw();

#ifdef DEBUG
    Vector2 center = GetBoundaryCenter();
    DrawCircleLines(static_cast<int>(center.x), static_cast<int>(center.y),
                    targetFollowRange, BLUE);
#endif
  }
};
