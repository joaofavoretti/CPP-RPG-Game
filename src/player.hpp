#pragma once

#include <raylib.h>
#include <raymath.h>
#include <map>
#include <memory>

#include "animation.hpp"
#include "animation_system.hpp"

// Has to start with 0
enum PlayerAnimationEnum {
	MOVE_RIGHT = 0,
	MOVE_LEFT,
	MOVE_UP,
	MOVE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_DOWN
};

#define REGISTER_ANIMATION(animationSystem, animationId) animationSystem->RegisterAnimation(animationId, animations->at(animationId).get())

struct Player {
private:
	Vector2 position;
	float speed = 2.0f;

	std::unique_ptr<std::map<int, std::unique_ptr<Animation>>> animations;
	std::unique_ptr<AnimationSystem> animationSystem;
	PlayerAnimationEnum lastMoveAnimation = PlayerAnimationEnum::MOVE_RIGHT;
	std::map<PlayerAnimationEnum, PlayerAnimationEnum> idleAnimations = {
		{ PlayerAnimationEnum::MOVE_RIGHT, PlayerAnimationEnum::IDLE_RIGHT },
		{ PlayerAnimationEnum::MOVE_LEFT, PlayerAnimationEnum::IDLE_LEFT },
		{ PlayerAnimationEnum::MOVE_UP, PlayerAnimationEnum::IDLE_UP },
		{ PlayerAnimationEnum::MOVE_DOWN, PlayerAnimationEnum::IDLE_DOWN }
	};


	void SetupAnimations();
public:
	Player(Vector2 position);
	void Update(double deltaTime);
	void Draw();
};
