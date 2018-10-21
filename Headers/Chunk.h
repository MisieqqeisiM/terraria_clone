#ifndef CHUNK_H
#define CHUNK_H
#include"Tile.h"
#include"ChunkRenderer.h"
#include"Constants.h"

class Chunk{
    public:
        Chunk(Tile** tiles, int x, int y);
        ~Chunk();
        void drawFront(BasicShader& shader);
        void drawWalls(BasicShader& shader);
        void setTile(int x, int y, Tile tile);
        Tile getTile(int x, int y);
        int getX();
        int getY();
    private:
        Tile map[CHUNK_SIZE][CHUNK_SIZE];
        ChunkRenderer * renderer;
        int x, y;


};

#endif
