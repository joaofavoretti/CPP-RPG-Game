#pragma once

#include <raylib.h>
#include <map>

#include "animation.hpp"

struct AnimationSystem {

private:
	std::map<int, Animation*> animations;
	Animation *currentAnimation = nullptr;


public:
	int GetCurrentAnimationId();
	void RegisterAnimation(int animationId, Animation *animation);
	void SetPosition(Vector2 position);
	void Update(int animationId, double deltaTime);
	void Draw();
};
