#pragma once

#include <raylib.h>

struct Sprite {
	Texture2D texture;
	Rectangle textureTileRect;
	Vector2 screenPosition;
	Vector2 tilePosition;
	float rotation = 0.0f;
	float scale = 1.0f;
	Vector2 offset = { 0, 0 };

	Sprite(Vector2 screenPosition, Vector2 tilePosition, Texture2D texture, Rectangle textureTileRect, float scale = 1.0f) :
		screenPosition(screenPosition), tilePosition(tilePosition), texture(texture), textureTileRect(textureTileRect), scale(scale) {}
	
	void Draw() {
	    Rectangle atlasTileRect = { tilePosition.x * textureTileRect.width, tilePosition.y * textureTileRect.height, textureTileRect.width, textureTileRect.height };
	    Vector2 origin = { textureTileRect.width / 2, textureTileRect.height / 2 };
	    Rectangle destRect = { screenPosition.x + offset.x, screenPosition.y + offset.y, textureTileRect.width * scale, textureTileRect.height * scale };
	    DrawTexturePro(texture, atlasTileRect, destRect, origin, rotation, WHITE);
	}

	void DrawMirrored() {
	    Rectangle atlasTileRect = { tilePosition.x * textureTileRect.width, tilePosition.y * textureTileRect.height, -textureTileRect.width, textureTileRect.height };
	    Vector2 origin = { textureTileRect.width / 2, textureTileRect.height / 2 };
	    Rectangle destRect = { screenPosition.x + offset.x, screenPosition.y + offset.y, textureTileRect.width * scale, textureTileRect.height * scale };
	    DrawTexturePro(texture, atlasTileRect, destRect, origin, rotation, WHITE);
	}
};
