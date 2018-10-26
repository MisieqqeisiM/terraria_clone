#ifndef MAP_H
#define MAP_H
#include<vector>
#include"Chunk.h"
#include"TextureManager.h"

class Map{
    public:
        Map(int width, int height);
        ~Map();
        void drawBack(BasicShader& shader, TextureManager& textureManager, float camX, float camY);
        void drawFront(BasicShader& shader, TextureManager& textureManager,float camX, float camY);
        bool isAir(float x, float y);
        Tile getTileAt(int x, int y);
        void setTile(int x, int y, Tile tile);
    private:
        int width, height;
        Chunk*** chunks;
        
};
#endif
