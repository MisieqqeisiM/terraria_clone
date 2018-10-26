#include<SFML/Graphics.hpp>
#include<GL/glew.h>
#include"Map.h"
#include<iostream>
#include"BasicShader.h"
#include"TextureManager.h"
#include"Player.h"
sf::RenderWindow * window;
BasicShader * shader;
TextureManager * textureManager;
Map * m;
Player * entity;
float deltaTime = 0;
float camX=0, camY = 0;

void setupGraphics(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.antialiasingLevel = 4;
    window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Template", sf::Style::Fullscreen, settings);


    glewExperimental = true;
    glewInit();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    shader = new BasicShader("Shaders/vertex_shader.vert", "Shaders/fragment_shader.frag");
    shader->loadAspectRatio((float)window->getSize().y/window->getSize().x);

    textureManager = new TextureManager();
    textureManager->loadTexture("Textures/tiles.bmp");
    textureManager->loadTexture("Textures/player.bmp");
}
void setupMechanics(){
    m = new Map(50, 6);
    entity = new Player(17,50);

}
void processInput(){
        sf::Event e;
        while(window->pollEvent(e)){
            switch(e.type){
                case sf::Event::Closed:
                    window->close();
                    break;
                default:
                    break;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window->close();
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        float mouseX = ((float)mousePosition.x-(float)window->getSize().x/2)/window->getSize().y*30+camX;
        float mouseY = -((float)mousePosition.y-(float)window->getSize().y/2)/window->getSize().y*30+camY;

        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            m->setTile((int)std::floor(mouseX), (int)std::floor(mouseY), Tile{ORE});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            m->setTile((int)std::floor(mouseX), (int)std::floor(mouseY), Tile{AIR});

}
void update(){
    entity->update(*m, deltaTime, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A), sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D), sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
    camX = entity->getX()+1.5f;
    camY = entity->getY()+5.0f;
}
void cleanup(){

    Entity::unload();
    delete window;
    delete shader;
    delete textureManager;
    delete m;
    delete entity;

}
void draw(){
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        shader->use();
        shader->loadCameraPosition(camX,camY);

        textureManager->useTexture(0);

        m->drawFront(*shader, *textureManager, camX, camY);
        entity->draw(*shader, *textureManager);
        m->drawBack(*shader, *textureManager, camX, camY);

        window->display();
}
int main(){
    setupGraphics();
    setupMechanics();
    sf::Clock clock;
    int counter = 0;

    while(window->isOpen()){
        processInput();
        update();
        draw();

        deltaTime = clock.restart().asSeconds();
        double fps = 1.0 / deltaTime;
        if(counter++>100){
            std::cout<<fps<<std::endl; //Display FPS
            counter = 0;
        }
    }
    cleanup();
    return 0;
}
