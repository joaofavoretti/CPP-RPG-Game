#include <memory>

#include "player.hpp"

#define PLAYER_ANIMATION_BASE_PATH "../assets/pixel_art/1 Characters/1"

Player::Player(Vector2 position) : position(position) {
  SetupAnimationSystem();
  SetupProjectileSystem();

  velocity = {0.0f, 0.0f};
}

void Player::UpdateProjectileSystem(double deltaTime) {
  std::map<PlayerAnimationEnum, float> angleMap = {
      {PlayerAnimationEnum::MOVE_RIGHT, 0},
      {PlayerAnimationEnum::MOVE_LEFT, PI},
      {PlayerAnimationEnum::MOVE_UP, 3 * PI / 2},
      {PlayerAnimationEnum::MOVE_DOWN, PI / 2}};

  std::map<PlayerAnimationEnum, Vector2> offsetMap = {
      {PlayerAnimationEnum::MOVE_RIGHT, {8 * PLAYER_SCALE, 9 * PLAYER_SCALE}},
      {PlayerAnimationEnum::MOVE_LEFT, {16 * PLAYER_SCALE, 12 * PLAYER_SCALE}},
      {PlayerAnimationEnum::MOVE_UP, {12 * PLAYER_SCALE, 21 * PLAYER_SCALE}},
      {PlayerAnimationEnum::MOVE_DOWN, {18 * PLAYER_SCALE, 8 * PLAYER_SCALE}}};

  projectileSystem->SetOffset(offsetMap[GetLastMoveAnimation()]);

  if (IsKeyPressed(KEY_SPACE)) {
    projectileSystem->Add(ProjectileConfig{
        .position = GetPosition(),
        .angle = angleMap[GetLastMoveAnimation()],
        .speed = 200,
    });
  }
  projectileSystem->Update(deltaTime);
}

void Player::UpdateAnimationSystem(double deltaTime) {
  // If the magnitude of velocity is 0. Show Idle animation
  if (Vector2Length(velocity) == 0) {
    animationSystem->Update(idleAnimations[lastMoveAnimation], deltaTime);
  } else {
    animationSystem->Update(lastMoveAnimation, deltaTime);
  }

  if (IsKeyDown(KEY_SPACE)) {
    animationSystem->Update(attackAnimations[lastMoveAnimation], deltaTime);
  }

  animationSystem->SetPosition(position);
}

bool Player::IsAvailableToMove(Rectangle newBoundary) {
  for (auto &collisionCheck : collisionChecks) {
    if (collisionCheck(newBoundary)) {
      return false;
    }
  }

  return true;
}

void Player::Update(double deltaTime) {
  UpdateProjectileSystem(deltaTime);

  if (animationSystem->IsPerformingAnimation()) {
    animationSystem->Update(deltaTime);
    return;
  }

  if (IsKeyDown(KEY_UP)) {
    velocity.y -= speed;
    lastMoveAnimation = PlayerAnimationEnum::MOVE_UP;
  }
  if (IsKeyDown(KEY_DOWN)) {
    velocity.y += speed;
    lastMoveAnimation = PlayerAnimationEnum::MOVE_DOWN;
  }
  if (IsKeyDown(KEY_RIGHT)) {
    velocity.x += speed;
    lastMoveAnimation = PlayerAnimationEnum::MOVE_RIGHT;
  }
  if (IsKeyDown(KEY_LEFT)) {
    velocity.x -= speed;
    lastMoveAnimation = PlayerAnimationEnum::MOVE_LEFT;
  }

  velocity =
      Vector2Scale(Vector2Scale(Vector2Normalize(velocity), speed), deltaTime);
  Vector2 newPosition = Vector2Add(position, velocity);

  Rectangle newBoundary = GetBoundariesFromPosition(newPosition);

  if (IsAvailableToMove(newBoundary)) {
    position = newPosition;
  }

  UpdateAnimationSystem(deltaTime);

  velocity = {0.0f, 0.0f};
}

Vector2 Player::GetPosition() { return position; }

Vector2 Player::GetBoundaryCenter() {
  Rectangle boundaries = GetBoundaries();
  return {boundaries.x + boundaries.width / 2.0f,
          boundaries.y + boundaries.height / 2.0f};
}

Rectangle Player::GetBoundaries() {
  return GetBoundariesFromPosition(position);
}

Rectangle Player::GetBoundariesFromPosition(Vector2 position) {
  Vector2 offset = {8, 3};

  return Rectangle{
      .x = position.x + offset.x,
      .y = position.y + offset.y,
      .width = animationSystem->GetSize().x - 2 * offset.x,
      .height = animationSystem->GetSize().y - 4 * offset.y,
  };
}

void Player::AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck) {
  collisionChecks.push_back(collisionCheck);
  projectileSystem->AddCollisionCheck(collisionCheck);
}

PlayerAnimationEnum Player::GetLastMoveAnimation() { return lastMoveAnimation; }

void Player::Draw() {
  projectileSystem->Draw();
  animationSystem->Draw();

#ifdef DEBUG
  DrawRectangleLines(GetBoundaries().x, GetBoundaries().y,
                     GetBoundaries().width, GetBoundaries().height, RED);
#endif
}

void Player::SetupProjectileSystem() {
  projectileSystem = std::make_unique<ProjectileSystem>(
      std::move(std::make_unique<Animation>(AnimationConfig{
          .texturePath = "../assets/pixel_art/1 Characters/Other/Arrow.png",
          .textureTileSize = {11, 3},
          .texturePosition = {0, 0},
          .numberOfFrames = 1,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = false,
          .flip = false,
      })),
      Rectangle{
          .x = 0,
          .y = 0,
          .width = 11,
          .height = 3,
      });
}

void Player::SetupAnimationSystem() {
  animationSystem = std::make_unique<AnimationSystem>();

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::MOVE_RIGHT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = true,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::MOVE_LEFT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::MOVE_UP,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/U_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::MOVE_DOWN,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/D_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::IDLE_RIGHT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = true,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::IDLE_LEFT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::IDLE_UP,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/U_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::IDLE_DOWN,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/D_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = true,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::ATTACK_RIGHT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = false,
          .flip = true,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::ATTACK_LEFT,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/S_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = false,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::ATTACK_UP,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/U_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = false,
          .flip = false,
      });

  animationSystem->RegisterAnimation(
      PlayerAnimationEnum::ATTACK_DOWN,
      AnimationConfig{
          .texturePath = PLAYER_ANIMATION_BASE_PATH "/D_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = PLAYER_SCALE,
          .loop = false,
          .flip = false,
      });
}
