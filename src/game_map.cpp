
#include "game_map.hpp"

GameMap::GameMap(GameMapOption option) {
  this->option = option;
  tmx = std::make_unique<TMX>(GameMapFilename.at(option).c_str());
}

Vector2 GameMap::GetInitialPosition() {
  return GameMapInitialPosition.at(option);
}

bool GameMap::IsColliding(Rectangle rect) {
  return tmx->IsColliding(rect);
}

void GameMap::Draw() {
  tmx->Draw(pos, WHITE);
}
