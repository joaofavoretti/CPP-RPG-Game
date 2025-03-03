#include <stdexcept>
#include <memory>

#include "animation_system.hpp"
#include "animation.hpp"

void AnimationSystem::RegisterAnimation(int animationId, AnimationConfig animationConfig) {
  std::unique_ptr<Animation> animation = std::make_unique<Animation>(animationConfig);
  animations[animationId] = std::move(animation);
}

void AnimationSystem::SetPosition(Vector2 position) {
  if (currentAnimation) {
    currentAnimation->UpdateScreenPosition(position);
  }
}

void AnimationSystem::Update(int animationId, double deltaTime) {
  if (animations.find(animationId) == animations.end()) {
    throw std::runtime_error("Animation not found");
  }

  if (currentAnimation != animations[animationId].get()) {
    currentAnimation = animations[animationId].get();
    currentAnimation->Reset();
  }

  currentAnimation->Update(deltaTime);
}

void AnimationSystem::Update(double deltaTime) {
  if (currentAnimation) {
    currentAnimation->Update(deltaTime);
  }
}

void AnimationSystem::Draw() {
  if (currentAnimation) {
    currentAnimation->Draw();
  }
}

int AnimationSystem::GetCurrentAnimationId() {
  for (auto const &[key, val] : animations) {
    if (val.get() == currentAnimation) {
      return key;
    }
  }

  return -1;
}

Vector2 AnimationSystem::GetSize() {
  if (currentAnimation) {
    return currentAnimation->GetSize();
  }

  return {0, 0};
}

bool AnimationSystem::IsPerformingAnimation() {
  return currentAnimation != nullptr && !currentAnimation->IsFinished();
}
