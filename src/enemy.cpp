#include "enemy.hpp"

#define REGISTER_ANIMATION(animationSystem, animationId)                       \
  animationSystem->RegisterAnimation(animationId,                              \
                                     animations->at(animationId).get())

#define ENEMY_ANIMATION_BASE_PATH "../assets/pixel_art/3 Dungeon Enemies/1"

Enemy::Enemy(Vector2 position) : position(position) {
  SetupAnimations();

  velocity = {0.0f, 0.0f};

  animationSystem = std::make_unique<AnimationSystem>();

  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_MOVE_RIGHT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_MOVE_LEFT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_MOVE_UP);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_MOVE_DOWN);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_IDLE_RIGHT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_IDLE_LEFT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_IDLE_UP);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_IDLE_DOWN);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_ATTACK_RIGHT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_ATTACK_LEFT);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_ATTACK_UP);
  REGISTER_ANIMATION(animationSystem, EnemyAnimationEnum::ENEMY_ATTACK_DOWN);
}

void Enemy::UpdateAnimationSystem(double deltaTime) {
  if (Vector2Length(velocity) == 0) {
    animationSystem->Update(EnemyIdleAnimations[lastMoveAnimation], deltaTime);
  } else {
    animationSystem->Update(lastMoveAnimation, deltaTime);
  }

  if (IsKeyDown(KEY_SPACE)) {
    animationSystem->Update(EnemyAttackAnimations[lastMoveAnimation], deltaTime);
  }

  animationSystem->SetPosition(position);
}

bool Enemy::IsAvailableToMove(Rectangle newBoundary) {
  for (auto &collisionCheck : collisionChecks) {
    if (collisionCheck(newBoundary)) {
      return false;
    }
  }

  return true;
}

void Enemy::Update(double deltaTime) {
  if (animationSystem->IsPerformingAnimation()) {
    animationSystem->Update(deltaTime);
    return;
  }

  /*velocity.x = GetRandomValue(-1, 1) * speed;*/
  /*velocity.y = GetRandomValue(-1, 1) * speed;*/

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

Vector2 Enemy::GetPosition() { return position; }

Rectangle Enemy::GetBoundaries() { return GetBoundariesFromPosition(position); }

Rectangle Enemy::GetBoundariesFromPosition(Vector2 position) {
  Vector2 offset = {8, 3};

  return Rectangle{
      .x = position.x + offset.x,
      .y = position.y + offset.y,
      .width = animationSystem->GetSize().x - 2 * offset.x,
      .height = animationSystem->GetSize().y - 4 * offset.y,
  };
}

void Enemy::AddCollisionCheck(std::function<bool(Rectangle)> collisionCheck) {
  collisionChecks.push_back(collisionCheck);
}

EnemyAnimationEnum Enemy::GetLastMoveAnimation() { return lastMoveAnimation; }

void Enemy::Draw() {
  animationSystem->Draw();

#ifdef DEBUG
  DrawRectangleLines(GetBoundaries().x, GetBoundaries().y,
                     GetBoundaries().width, GetBoundaries().height, RED);
#endif
}

void Enemy::SetupAnimations() {
  animations = std::make_unique<std::map<int, std::unique_ptr<Animation>>>();

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_MOVE_RIGHT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = true,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_MOVE_LEFT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_MOVE_UP,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_MOVE_DOWN,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Walk.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 6,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_IDLE_RIGHT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = true,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_IDLE_LEFT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_IDLE_UP,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_IDLE_DOWN,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Idle.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = true,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_ATTACK_RIGHT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = false,
          .flip = true,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_ATTACK_LEFT,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/S_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = false,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_ATTACK_UP,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/U_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = false,
          .flip = false,
      })));

  animations->insert(std::make_pair(
      EnemyAnimationEnum::ENEMY_ATTACK_DOWN,
      std::make_unique<Animation>((AnimationConfig){
          .texturePath = ENEMY_ANIMATION_BASE_PATH "/D_Attack.png",
          .textureTileSize = {32, 32},
          .texturePosition = {0, 0},
          .numberOfFrames = 4,
          .frameSpeed = 0.1f,
          .scale = ENEMY_SCALE,
          .loop = false,
          .flip = false,
      })));
}
