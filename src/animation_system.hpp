#pragma once

#include <map>
#include <memory>
#include <raylib.h>

#include "animation.hpp"

struct AnimationSystem {

private:
  std::map<int, std::unique_ptr<Animation>> animations;
  Animation *currentAnimation = nullptr;

public:
  int GetCurrentAnimationId();
  bool IsPerformingAnimation();
  Vector2 GetSize();
  void RegisterAnimation(int animationId, AnimationConfig animationConfig);
  void SetPosition(Vector2 position);
  void Update(int animationId, double deltaTime);
  void Update(double deltaTime);
  void Draw();
};
