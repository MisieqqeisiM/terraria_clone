#include "Map.h"
#include"Generator.h"

Map::Map(int width, int height){
    Generator generator(50,10,30);
    this->width = width;
    this->height = height;
    chunks = new Chunk**[width];
    for(int i = 0; i<width; i++){
        chunks[i] = new Chunk*[height];
        for(int j = 0; j<height; j++){
            chunks[i][j] = generator.getChunkAt(i-width/2, j-height/2);
        }
    }

};
void Map::drawBack(BasicShader& shader, TextureManager& textureManager, float camX, float camY){
    int chunkX = (int)std::floor((float)(camX)/CHUNK_SIZE)+width/2;
    int chunkY = (int)std::floor((float)(camY)/CHUNK_SIZE)+height/2;
    textureManager.useTexture(0);
    for(int i = chunkX-2; i<=chunkX+2; i++){
        for(int j = chunkY-1; j<=chunkY+1; j++){
            if(i>=0&&i<width&&j>=0&&j<height)
                chunks[i][j]->drawWalls(shader);
        }
    }
};
void Map::drawFront(BasicShader& shader, TextureManager& textureManager, float camX, float camY){
    int chunkX = (int)std::floor((float)(camX)/CHUNK_SIZE)+width/2;
    int chunkY = (int)std::floor((float)(camY)/CHUNK_SIZE)+height/2;
    textureManager.useTexture(0);
    for(int i = chunkX-2; i<=chunkX+2; i++){
        for(int j = chunkY-1; j<=chunkY+1; j++){
            if(i>=0&&i<width&&j>=0&&j<height)
                chunks[i][j]->drawFront(shader);
        }
    }
};
bool Map::isAir(float x, float y){
    return getTileAt((int) std::floor(x), (int) std::floor(y)).id == 0;
};
Tile Map::getTileAt(int x, int y){
    int chunkX = (int)std::floor((float)(x)/CHUNK_SIZE)+width/2;
    int chunkY = (int)std::floor((float)(y)/CHUNK_SIZE)+height/2;

    if(chunkX>=0&&chunkX<width&&chunkY>=0&&chunkY<height)
          return chunks[chunkX][chunkY]->getTile(x-(chunkX-width/2)*CHUNK_SIZE, (y)-(chunkY-height/2)*CHUNK_SIZE);
    return Tile{0};
};
void Map::setTile(int x, int y, Tile tile){
    int chunkX = (int)std::floor((float)(x)/CHUNK_SIZE)+width/2;
    int chunkY = (int)std::floor((float)(y)/CHUNK_SIZE)+height/2;

    if(chunkX>=0&&chunkX<width&&chunkY>=0&&chunkY<height)
         chunks[chunkX][chunkY]->setTile(x-(chunkX-width/2)*CHUNK_SIZE, (y)-(chunkY-height/2)*CHUNK_SIZE, tile);
};

Map::~Map(){
    for(int i = 0; i<width; i++){
        for(int j = 0; j<height; j++){
            delete chunks[i][j];
        }
        delete [] chunks[i];
    }
    delete [] chunks;
};

