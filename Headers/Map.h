#ifndef MAP_H
#define MAP_H
#include<vector>
#include"Chunk.h"
#include"TextureManager.h"

class Map{
    public:
        Map();
        ~Map();
        void drawBack(BasicShader& shader, TextureManager& textureManager);
        void drawFront(BasicShader& shader, TextureManager& textureManager);
        bool isAir(float x, float y);
        Tile getTileAt(int x, int y);
        void setTile(int x, int y, Tile tile);
    private:
        std::vector<Chunk *> activeChunks;
        
};
#endif
