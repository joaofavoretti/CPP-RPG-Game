#pragma once

#include <raylib.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <random>

#include "sprite.hpp"

struct Map {
	std::string TexturePath = "../assets/tiles.png";
	Texture2D texture;
	Rectangle textureTileRect;
	std::vector<std::unique_ptr<Sprite>> sprites;
	Vector2 size = { 32, 32 };
	

	enum class SandTileType {
		SAND_TILE_1,
		SAND_TILE_2,
		SAND_TILE_3,
		SAND_TILE_4,
		SAND_TILE_5,
		SAND_TILE_6,
		SAND_TILE_7,
		SAND_TILE_8,
	};

	std::map<SandTileType, Vector2> sandTilePosition = {
		{SandTileType::SAND_TILE_1, Vector2{42, 7}},
		{SandTileType::SAND_TILE_2, Vector2{43, 7}},
		{SandTileType::SAND_TILE_3, Vector2{44, 7}},
		{SandTileType::SAND_TILE_4, Vector2{45, 7}},
		{SandTileType::SAND_TILE_5, Vector2{46, 7}},
		{SandTileType::SAND_TILE_6, Vector2{47, 7}},
		{SandTileType::SAND_TILE_7, Vector2{48, 7}},
		{SandTileType::SAND_TILE_8, Vector2{49, 7}},
	};

	Map() {
		texture = LoadTexture(TexturePath.c_str());
		textureTileRect = { 0, 0, 32, 32 };

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, sandTilePosition.size() - 1);

		for (int x = 0; x < size.x; x++) {
			for (int y = 0; y < size.y; y++) {
				int randomIndex = dis(gen);
				auto it = sandTilePosition.begin();
				std::advance(it, randomIndex);
				SandTileType sandTileType = it->first;

				Vector2 screenPosition = { x * textureTileRect.width, y * textureTileRect.height };
				Vector2 tilePosition = sandTilePosition[sandTileType];
				sprites.push_back(std::make_unique<Sprite>(screenPosition, tilePosition, texture, textureTileRect));
			}
		}
	}

	~Map() {
		UnloadTexture(texture);
	}

	void draw() {
		for (auto& sprite : sprites) {
			sprite->Draw();
		}
	}
};
