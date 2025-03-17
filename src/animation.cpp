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
  floating = config.floating;
}

void Animation::UpdateScreenPosition(Vector2 screenPosition) {
  this->screenPosition = screenPosition;
}

void Animation::UpdateAngle(float angle) { this->angle = angle; }

void Animation::Reset() { currentFrame = 0; }

void Animation::Update(double deltaTime) {
  frameCounter += deltaTime;
  if (frameCounter >= frameSpeed) {
    frameCounter = 0.0f;
    currentFrame = loop ? (currentFrame + 1) % numberOfFrames
                        : std::min(currentFrame + 1, numberOfFrames - 1);
  }
}

void Animation::Draw() {
  Rectangle sourceRect = {(texturePosition.x + currentFrame) *
                              textureTileSize.x,
                          texturePosition.y * textureTileSize.y,
                          textureTileSize.x, textureTileSize.y};

  if (flip) {
    sourceRect.width *= -1;
  }

  Rectangle destRect = {screenPosition.x + offset.x,
                        screenPosition.y + offset.y, textureTileSize.x * scale,
                        textureTileSize.y * scale};
  Vector2 origin = {0.0f, 0.0f};

  float rotation = angle * RAD2DEG;

  if (floating) {
    DrawTexturePro(texture, sourceRect,
                   Rectangle{destRect.x + 2, destRect.y + 2, destRect.width,
                             destRect.height},
                   origin, rotation, Color{0, 0, 0, 150});
  } else {
    DrawTexturePro(texture, sourceRect,
                   Rectangle{destRect.x + 1, destRect.y + 1, destRect.width,
                             destRect.height},
                   origin, rotation, Color{0, 0, 0, 50});
  }

  DrawTexturePro(texture, sourceRect, destRect, origin, rotation, WHITE);
}

Vector2 Animation::GetSize() {
  return {textureTileSize.x * scale, textureTileSize.y * scale};
}

bool Animation::IsFinished() {
  return loop || currentFrame == numberOfFrames - 1;
}
