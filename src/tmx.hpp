#pragma once

#include <memory>

#include "raylib.h"
#include "tmx.h"

#ifndef RAYLIB_TMX_LINE_THICKNESS
#define RAYLIB_TMX_LINE_THICKNESS 3.0f
#endif

struct TMX {
private:
  std::unique_ptr<tmx_map> map;
  float scale = 1.0f;

  Color ColorFromTMX(uint32_t color);

  void DrawLayers(tmx_layer *layers, int posX, int posY, Color tint);

  void DrawLayer(tmx_layer *layer, int posX, int posY, Color tint);

  void DrawLayerImage(tmx_image *image, int posX, int posY, Color tint);

  void DrawLayerObjects(tmx_object_group *objgr, int posX, int posY,
                        Color tint);

  void DrawPolyline(double offset_x, double offset_y, double **points,
                    int points_count, Color color);

  void DrawPolygon(double offset_x, double offset_y, double **points,
                   int points_count, Color color);

  void DrawText(tmx_text *text, Rectangle dest, Color tint);

  void DrawLayerTiles(tmx_layer *layer, int posX, int posY, Color tint);

  void DrawTile(tmx_tile *tile, int posX, int posY, Color tint);

  static void *LoadTMXImage(const char *fileName);

  static void UnloadTMXImage(void *ptr);

  static void *MemReallocTMX(void *address, size_t len);

public:
  TMX(const char *filename);

  void Draw(Vector2 pos, Color tint);

  bool IsColliding(Rectangle rect);
};
