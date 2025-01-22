#pragma once

#include <raylib.h>

struct Sprite {
	Vector2 screenPosition;
	Vector2 tilePosition;
	Texture2D texture;
	Rectangle textureTileRect;

	Sprite(Vector2 screenPosition, Vector2 tilePosition, Texture2D texture, Rectangle textureTileRect) :
		screenPosition(screenPosition), tilePosition(tilePosition), texture(texture), textureTileRect(textureTileRect) {}

	void Draw() {
		Rectangle atlasTileRect = { tilePosition.x * textureTileRect.width, tilePosition.y * textureTileRect.height, textureTileRect.width, textureTileRect.height };
		DrawTextureRec(texture, atlasTileRect, screenPosition, WHITE);
	}

	void DrawMirrored() {
		Rectangle atlasTileRect = { tilePosition.x * textureTileRect.width, tilePosition.y * textureTileRect.height, -textureTileRect.width, textureTileRect.height };
		DrawTextureRec(texture, atlasTileRect, screenPosition, WHITE);	
	}
};
