#include <stdexcept>

#include "animation_system.hpp"

void AnimationSystem::RegisterAnimation(int animationId, Animation *animation) {
	animations[animationId] = animation;
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

	if (currentAnimation != animations[animationId]) {
		currentAnimation = animations[animationId];
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
	for (auto const& [key, val] : animations) {
		if (val == currentAnimation) {
			return key;
		}
	}

	return -1;
}

bool AnimationSystem::IsPerformingAnimation() {
	return currentAnimation != nullptr && !currentAnimation->IsFinished();
}
