#pragma once

#include <raylib.h>
#include <raymath.h>

#include "animation_config.hpp"
#include "entity.hpp"

struct FireballEntity : Entity {

protected:
  void RegisterAnimations() override {
    RegisterAnimation(
      EntityAnimationId::IDLE,
      AnimationConfig {
          .texturePath = "../assets/pixel_art/2 Dungeon Tileset/3 Animated objects/Fire1.png",
          .textureTileSize = {16, 16},
          .texturePosition = {0, 0},
          .numberOfFrames = 8,
          .frameSpeed = 0.1f,
          .scale = scale,
          .floating = true,
          .loop = true,
          .flip = false,
      });

    SetAnimation(EntityAnimationId::IDLE);
  }

public:
  FireballEntity(Vector2 position, Vector2 velocity)
      : Entity(position, velocity, 1.0) {
    SetupAnimationSystem();
  }

  Rectangle GetBoundaries() override {
    Vector2 offset = {
      animationSystem->GetSize().x / 2,
      animationSystem->GetSize().y / 2,
    };
    
    return Rectangle{
        .x = position.x + offset.x / 2,
        .y = position.y + offset.y,
        .width = animationSystem->GetSize().x - offset.x,
        .height = animationSystem->GetSize().y - offset.x,
    };
  }
};
