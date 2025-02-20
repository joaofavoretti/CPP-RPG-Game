#pragma once

#include <memory>

#include "raylib.h"
#include "tmx.h"

#ifndef RAYLIB_TMX_LINE_THICKNESS
#define RAYLIB_TMX_LINE_THICKNESS 3.0f
#endif

struct TMX {
private:
  Color ColorFromTMX(uint32_t color) {
    tmx_col_bytes res = tmx_col_to_bytes(color);
    return *((Color *)&res);
  }

  void DrawLayers(tmx_layer *layers, int posX, int posY, Color tint) {
    while (layers) {
      if (layers->visible) {
        DrawLayer(layers, posX, posY, tint);
      }
      layers = layers->next;
    }
  }

  void DrawLayer(tmx_layer *layer, int posX, int posY, Color tint) {
    switch (layer->type) {
    case L_GROUP:
      DrawLayers(layer->content.group_head, posX + layer->offsetx,
                 posY + layer->offsety, tint);
      break;
    case L_OBJGR:
      DrawLayerObjects(layer->content.objgr, posX + layer->offsetx,
                       posY + layer->offsety, tint);
      break;
    case L_IMAGE:
      DrawLayerImage(layer->content.image, posX + layer->offsetx,
                     posY + layer->offsety, tint);
      break;
    case L_LAYER:
      DrawLayerTiles(layer, posX + layer->offsetx, posY + layer->offsety, tint);
      break;
    case L_NONE:
      // Nothing.
      break;
    }
  }

  void DrawLayerImage(tmx_image *image, int posX, int posY, Color tint) {
    if (image->resource_image) {
      Texture2D *texture = (Texture2D *)image->resource_image;
      DrawTexture(*texture, posX, posY, tint);
    }
  }

  void DrawLayerObjects(tmx_object_group *objgr, int posX, int posY,
                        Color tint) {
    tmx_object *head = objgr->head;
    Color color = ColorFromTMX(objgr->color);
    // TODO: Merge the tint

    while (head) {
      if (head->visible) {
        Rectangle dest = (Rectangle){(float)posX + (float)head->x,
                                     (float)posY + (float)head->y,
                                     (float)head->width, (float)head->height};
        switch (head->obj_type) {
        case OT_SQUARE:
          DrawRectangleLinesEx(dest, (int)RAYLIB_TMX_LINE_THICKNESS, color);
          break;
        case OT_POLYGON:
          DrawPolygon(dest.x, dest.y, head->content.shape->points,
                      head->content.shape->points_len, color);
          break;
        case OT_POLYLINE:
          DrawPolyline(dest.x, dest.y, head->content.shape->points,
                       head->content.shape->points_len, color);
          break;
        case OT_ELLIPSE:
          DrawEllipseLines(dest.x + head->width / 2.0,
                           dest.y + head->height / 2.0, head->width / 2.0f,
                           head->height / 2.0f, color);
          break;
        case OT_TILE: {
          int gid = head->content.gid;
          if (map->tiles[gid] != NULL) {
            DrawTile(map->tiles[gid], dest.x, dest.y - dest.height, tint);
          }
        } break;
        case OT_TEXT: {
          tmx_text *text = head->content.text;
          Color textColor = ColorFromTMX(text->color);
          // TODO: Fix application of the tint.
          textColor.a = tint.a;
          DrawText(text, dest, textColor);
        } break;
        case OT_POINT:
          DrawCircle(dest.x + head->width / 2.0, dest.y + head->height / 2.0, 5,
                     color);
          break;
        case OT_NONE:
          // Nothing.
          break;
        }
      }
      head = head->next;
    }
  }

  void DrawPolyline(double offset_x, double offset_y, double **points,
                    int points_count, Color color) {
    for (int i = 1; i < points_count; i++) {
      DrawLineEx((Vector2){(float)(offset_x + points[i - 1][0]),
                           (float)(offset_y + points[i - 1][1])},
                 (Vector2){(float)(offset_x + points[i][0]),
                           (float)(offset_y + points[i][1])},
                 RAYLIB_TMX_LINE_THICKNESS, color);
    }
  }

  void DrawPolygon(double offset_x, double offset_y, double **points,
                   int points_count, Color color) {
    DrawPolyline(offset_x, offset_y, points, points_count, color);
    if (points_count > 2) {
      DrawLineEx((Vector2){(float)(offset_x + points[0][0]),
                           (float)(offset_y + points[0][1])},
                 (Vector2){(float)(offset_x + points[points_count - 1][0]),
                           (float)(offset_y + points[points_count - 1][1])},
                 RAYLIB_TMX_LINE_THICKNESS, color);
    }
  }

  void DrawText(tmx_text *text, Rectangle dest, Color tint) {
    float fontSize = (float)text->pixelsize;
    const char *message = text->text;
    Font font = GetFontDefault();
    // TODO: Figure out the correct spacing.
    float spacing = (float)text->kerning * fontSize / 12.0f;
    Vector2 position = {dest.x, dest.y};

    if (text->wrap == 0) {
      Vector2 textSize = MeasureTextEx(font, message, fontSize, spacing);
      if (text->halign == HA_CENTER) {
        position.x = dest.x + dest.width / 2.0f - textSize.x / 2.0f;
      } else if (text->halign == HA_RIGHT) {
        position.x = dest.x + dest.width - textSize.x;
      }
      if (text->valign == VA_CENTER) {
        position.y = dest.y + dest.height / 2.0f - textSize.y / 2.0f;
      } else if (text->valign == VA_BOTTOM) {
        position.y = dest.y + dest.height - textSize.y;
      }
      DrawTextEx(font, message, position, fontSize, spacing, tint);
    } else {
      Vector2 origin = {0.0f, 0.0f};
      DrawTextPro(font, message, position, origin, 0.0f, fontSize, spacing,
                  tint);
    }
  }

  void DrawLayerTiles(tmx_layer *layer, int posX, int posY, Color tint) {
    unsigned int gid, baseGid; //, flags;
    tmx_tileset *ts;
    Color newTint = ColorAlpha(tint, (float)layer->opacity);

    switch (map->renderorder) {
    case R_NONE:
    case R_RIGHTDOWN:
      for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
          baseGid = layer->content.gids[(y * map->width) + x];
          gid = (baseGid)&TMX_FLIP_BITS_REMOVAL;
          // TODO: Add the flags of the tile to Draw.
          // flags = baseGid & ~TMX_FLIP_BITS_REMOVAL;
          if (map->tiles[gid] != NULL) {
            ts = map->tiles[gid]->tileset;
            DrawTile(map->tiles[gid], posX + x * ts->tile_width,
                     posY + y * ts->tile_height, newTint);
          }
        }
      }
      break;
    case R_RIGHTUP:
      for (int y = map->height - 1; y >= 0; y--) {
        for (int x = 0; x < map->width; x++) {
          baseGid = layer->content.gids[(y * map->width) + x];
          gid = (baseGid)&TMX_FLIP_BITS_REMOVAL;
          // TODO: Add the flags of the tile to Draw.
          // flags = baseGid & ~TMX_FLIP_BITS_REMOVAL;
          if (map->tiles[gid] != NULL) {
            ts = map->tiles[gid]->tileset;
            DrawTile(map->tiles[gid], posX + x * ts->tile_width,
                     posY + y * ts->tile_height, newTint);
          }
        }
      }
      break;
    case R_LEFTDOWN:
      for (int y = 0; y < map->height; y++) {
        for (int x = map->width - 1; x >= 0; x--) {
          baseGid = layer->content.gids[(y * map->width) + x];
          gid = (baseGid)&TMX_FLIP_BITS_REMOVAL;
          // TODO: Add the flags of the tile to Draw.
          // flags = baseGid & ~TMX_FLIP_BITS_REMOVAL;
          if (map->tiles[gid] != NULL) {
            ts = map->tiles[gid]->tileset;
            DrawTile(map->tiles[gid], posX + x * ts->tile_width,
                     posY + y * ts->tile_height, newTint);
          }
        }
      }
      break;
    case R_LEFTUP:
      for (int y = map->height - 1; y >= 0; y--) {
        for (int x = map->width - 1; x >= 0; x--) {
          baseGid = layer->content.gids[(y * map->width) + x];
          gid = (baseGid)&TMX_FLIP_BITS_REMOVAL;
          // TODO: Add the flags of the tile to Draw.
          // flags = baseGid & ~TMX_FLIP_BITS_REMOVAL;
          if (map->tiles[gid] != NULL) {
            ts = map->tiles[gid]->tileset;
            DrawTile(map->tiles[gid], posX + x * ts->tile_width,
                     posY + y * ts->tile_height, newTint);
          }
        }
      }
      break;
    }
  }

  void DrawTile(tmx_tile *tile, int posX, int posY, Color tint) {
    Texture *image;
    Rectangle srcRect;
    Rectangle destRect;

    srcRect.x = tile->ul_x;
    srcRect.y = tile->ul_y;
    srcRect.width = tile->tileset->tile_width;
    srcRect.height = tile->tileset->tile_height;

    destRect.x = posX * scale;
    destRect.y = posY * scale;
    destRect.width = srcRect.width * scale;
    destRect.height = srcRect.height * scale;

    // Find the image
    tmx_image *im = tile->image;

    if (im && im->resource_image) {
      image = (Texture *)im->resource_image;
    } else if (tile->tileset->image->resource_image) {
      image = (Texture *)tile->tileset->image->resource_image;
    }

    if (image) {
      DrawTexturePro(*image, srcRect, destRect, (Vector2){0, 0}, 0.0f, tint);
    }
  }

  static void *LoadTMXImage(const char *fileName) {
    Texture2D *returnValue = (Texture2D *)MemAlloc(sizeof(Texture2D));
    *returnValue = LoadTexture(fileName);
    return returnValue;
  }

  static void UnloadTMXImage(void *ptr) {
    if (ptr != NULL) {
      UnloadTexture(*((Texture2D *)ptr));
      MemFree(ptr);
    }
  }

  static void *MemReallocTMX(void *address, size_t len) {
    return MemRealloc(address, (int)len);
  }

public:
  std::unique_ptr<tmx_map> map;
  float scale = 1.5f;

  TMX(const char *filename) {
    tmx_alloc_func = MemReallocTMX;
    tmx_free_func = MemFree;
    tmx_img_load_func = LoadTMXImage;
    tmx_img_free_func = UnloadTMXImage;

    map = std::unique_ptr<tmx_map>(tmx_load(filename));
  }

  void Draw(Vector2 pos, Color tint) {
    Color background = ColorFromTMX(map->backgroundcolor);
    DrawRectangle(pos.x, pos.y, map->width, map->height, background);
    DrawLayers(map->ly_head, pos.x, pos.y, tint);
  }

  bool IsColliding(Rectangle rect) {
    tmx_layer *layer = map->ly_head;
    while (layer) {
      if (layer->type == L_LAYER) {
        for (int y = 0; y < map->height; y++) {
          for (int x = 0; x < map->width; x++) {
            unsigned int gid = layer->content.gids[(y * map->width) + x];
            if (gid != 0) {
              tmx_tile *tile = map->tiles[gid];
              if (tile != NULL) {
                tmx_object *collision = tile->collision;
                if (collision != NULL) {
                  Rectangle tileRect = {
                      (float)x * map->tile_width * scale, (float)y * map->tile_height * scale,
                      (float)map->tile_width * scale, (float)map->tile_height * scale};
                  if (CheckCollisionRecs(rect, tileRect)) {
                    return true;
                  }
                }
              }
            }
          }
        }
      }
      layer = layer->next;
    }
    return false;
  }
};
