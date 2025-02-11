#include "animation.hpp"

Animation::Animation(AnimationConfig config) {
	texture = LoadTexture(config.texturePath.c_str());
	textureTileSize = config.textureTileSize;
	texturePosition = config.texturePosition;
	numberOfFrames = config.numberOfFrames;
	frameSpeed = config.frameSpeed;
	scale = config.scale;
	flip = config.flip;
	loop = config.loop;
}

void Animation::UpdateScreenPosition(Vector2 screenPosition) {
	this->screenPosition = screenPosition;
}

void Animation::UpdateAngle(float angle) {
	this->angle = angle;
}

void Animation::Reset() {
	currentFrame = 0;
}

void Animation::Update(double deltaTime) {
	frameCounter += deltaTime;
	if (frameCounter >= frameSpeed) {
		frameCounter = 0.0f;
		currentFrame = loop ? (currentFrame + 1) % numberOfFrames : std::min(currentFrame + 1, numberOfFrames - 1);
	}
}

void Animation::Draw() {
	Rectangle sourceRect = { (texturePosition.x + currentFrame) * textureTileSize.x, texturePosition.y * textureTileSize.y, textureTileSize.x, textureTileSize.y };

	if (flip) {
		sourceRect.width *= -1;
	}

	Rectangle destRect = { screenPosition.x + offset.x, screenPosition.y + offset.y, textureTileSize.x * scale, textureTileSize.y  * scale};
	Vector2 origin = { 0.0f, 0.0f };
	
	float rotation = angle * RAD2DEG;
	DrawTexturePro(texture, sourceRect, destRect, origin, rotation, WHITE);
}

bool Animation::IsFinished() {
	return loop || currentFrame == numberOfFrames - 1;
}
