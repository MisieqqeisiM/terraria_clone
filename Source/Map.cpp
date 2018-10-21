#include "Map.h"
#include"Generator.h"

Map::Map(){
    Generator generator(50,10,30);
    for(int chunkX = -5; chunkX < 5; chunkX++)
    for(int chunkY = -2; chunkY < 5; chunkY++)
        activeChunks.push_back(generator.getChunkAt(chunkX, chunkY));

};
void Map::drawBack(BasicShader& shader, TextureManager& textureManager){
    textureManager.useTexture(0);
    for(Chunk* c:activeChunks){
        c->drawWalls(shader);
    }
};
void Map::drawFront(BasicShader& shader, TextureManager& textureManager){
    textureManager.useTexture(0);
    for(Chunk* c:activeChunks){
        c->drawFront(shader);
    }
};
bool Map::isAir(float x, float y){
    return getTileAt((int) x, (int) y).id == 0;
};
Tile Map::getTileAt(int x, int y){
    int chunkX = (int)std::floor((float)(x-(x<0))/CHUNK_SIZE);
    int chunkY = (int)std::floor((float)(y-(y<0))/CHUNK_SIZE);

    for(Chunk* chunk: activeChunks){
        if(chunk->getX() == chunkX && chunk->getY() == chunkY)
            return chunk->getTile(x-(x<0)-chunkX*CHUNK_SIZE, (y-(y<0))-chunkY*CHUNK_SIZE);
    }
    return Tile{0};
};
void Map::setTile(int x, int y, Tile tile){
    int chunkX = (int)std::floor((float)x/CHUNK_SIZE);
    int chunkY = (int)std::floor((float)(y-1)/CHUNK_SIZE);

    for(Chunk* chunk: activeChunks){
        if(chunk->getX() == chunkX && chunk->getY() == chunkY)
            chunk->setTile(x-chunkX*CHUNK_SIZE, (y-1)-chunkY*CHUNK_SIZE, tile);
    }

};

Map::~Map(){
    for(Chunk* c:activeChunks){
        delete c;
    }
};

