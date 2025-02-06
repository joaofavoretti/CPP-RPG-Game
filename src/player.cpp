#include "player.hpp"

Player::Player(Vector2 position): position(position) {
	SetupAnimations();

	animationSystem = std::make_unique<AnimationSystem>();

	REGISTER_ANIMATION(animationSystem, PlayerAnimationEnum::MOVE_RIGHT);
	REGISTER_ANIMATION(animationSystem, PlayerAnimationEnum::MOVE_LEFT);
	REGISTER_ANIMATION(animationSystem, PlayerAnimationEnum::MOVE_UP);
	REGISTER_ANIMATION(animationSystem, PlayerAnimationEnum::MOVE_DOWN);
	REGISTER_ANIMATION(animationSystem, PlayerAnimationEnum::IDLE);
}

void Player::Update(double deltaTime) {
	if (IsKeyDown(KEY_RIGHT)) {
		position.x += speed;
		
		animationSystem->Update(PlayerAnimationEnum::MOVE_RIGHT, deltaTime);
	} else if (IsKeyDown(KEY_LEFT)) {
		position.x -= speed;
		animationSystem->Update(PlayerAnimationEnum::MOVE_LEFT, deltaTime);
	} else if (IsKeyDown(KEY_UP)) {
		position.y -= speed;
		animationSystem->Update(PlayerAnimationEnum::MOVE_UP, deltaTime);
	} else if (IsKeyDown(KEY_DOWN)) {
		position.y += speed;
		animationSystem->Update(PlayerAnimationEnum::MOVE_DOWN, deltaTime);
	}
	else {
		animationSystem->Update(PlayerAnimationEnum::IDLE, deltaTime);
	}
	animationSystem->SetPosition(position);
}

void Player::Draw() {
	animationSystem->Draw();
}

void Player::SetupAnimations() {
	animations = std::make_unique<std::map<int, std::unique_ptr<Animation>>>();

	animations->insert(std::make_pair(PlayerAnimationEnum::MOVE_RIGHT, std::make_unique<Animation>((AnimationConfig){
		.texturePath = "../assets/pixel_art/1 Characters/1/D_Walk.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 6,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true,
		.flip = false,
	}, position)));

	animations->insert(std::make_pair(PlayerAnimationEnum::MOVE_LEFT, std::make_unique<Animation>((AnimationConfig){
		.texturePath = "../assets/pixel_art/1 Characters/1/D_Walk.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 6,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true,
		.flip = true,
	}, position)));

	animations->insert(std::make_pair(PlayerAnimationEnum::MOVE_UP, std::make_unique<Animation>((AnimationConfig){
		.texturePath = "../assets/pixel_art/1 Characters/1/U_Walk.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 6,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true,
		.flip = false,
	}, position)));

	animations->insert(std::make_pair(PlayerAnimationEnum::MOVE_DOWN, std::make_unique<Animation>((AnimationConfig){
		.texturePath = "../assets/pixel_art/1 Characters/1/S_Walk.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 6,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true,
		.flip = false,
	}, position)));

	animations->insert(std::make_pair(PlayerAnimationEnum::IDLE, std::make_unique<Animation>((AnimationConfig){
		.texturePath = "../assets/pixel_art/1 Characters/1/D_Idle.png",
		.textureTileSize = { 32, 32 },
		.texturePosition = { 0, 0 },
		.numberOfFrames = 4,
		.frameSpeed = 0.1f,
		.scale = 2.0f,
		.loop = true,
		.flip = false,
	}, position)));	

}
