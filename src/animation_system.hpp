#pragma once

#include <map>
#include <raylib.h>

#include "animation.hpp"

#define REGISTER_ANIMATION(animationSystem, animationId)                       \
  animationSystem->RegisterAnimation(animationId,                              \
                                     animations->at(animationId).get())

struct AnimationSystem {

private:
  std::map<int, Animation *> animations;
  Animation *currentAnimation = nullptr;

public:
  int GetCurrentAnimationId();
  bool IsPerformingAnimation();
  Vector2 GetSize();
  void RegisterAnimation(int animationId, Animation *animation);
  void SetPosition(Vector2 position);
  void Update(int animationId, double deltaTime);
  void Update(double deltaTime);
  void Draw();
};
