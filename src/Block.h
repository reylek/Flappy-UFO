#pragma once
#include <SFML/Graphics.hpp>

class Block {
private:
    std::shared_ptr<sf::Texture> blockTexture;
    sf::Sprite upBlockSprite, downBlockSprite;
    float x;
    float y;
    float holeSize;
    bool isScored;
    const int minHeight = 20;

public:
    Block(std::shared_ptr<sf::Texture> blockTextureRef, unsigned screenSizeX, unsigned screenSizeY, float currentHoleSize);
    ~Block();
    float getX();
    bool getIsScored();
    void setIsScored(bool value);
    void draw(sf::RenderWindow& windowRef);
    void update(float deltaTime, float horizontalSpeed);
    sf::FloatRect getUpRect();
    sf::FloatRect getDownRect();
};

