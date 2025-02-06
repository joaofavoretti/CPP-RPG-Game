#pragma once

#include <raylib.h>
#include <raymath.h>
#include <map>
#include <memory>

#include "animation.hpp"
#include "animation_system.hpp"

enum PlayerAnimationEnum {
	MOVE_RIGHT = 0,
	MOVE_LEFT,
	MOVE_UP,
	MOVE_DOWN,
	IDLE
};

#define REGISTER_ANIMATION(animationSystem, animationId) animationSystem->RegisterAnimation(animationId, animations->at(animationId).get())

struct Player {
private:
	Vector2 position;
	float speed = 2.0f;
	std::unique_ptr<std::map<int, std::unique_ptr<Animation>>> animations;
	std::unique_ptr<AnimationSystem> animationSystem;

	void SetupAnimations();
public:
	Player(Vector2 position);
	void Update(double deltaTime);
	void Draw();
};
