#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Status.h"

class UFO {
private:
    sf::Texture UFOTexture, flameTexture;
    sf::Sprite UFOSprite, flameSprite;
    const float x = 200.f;
    float y;
    float verticalSpeed = 0.f;
    const float gravity = 400.f;
    sf::SoundBuffer poofBuffer;
    sf::Sound poofSound;

public:
    UFO(unsigned screenSizeY);
    ~UFO();
    void draw(sf::RenderWindow& windowRef);
    void update(float deltaTime, status& statusGameRef, unsigned screenSizeY);
    void flap();
    void restart(unsigned screenSizeY);
    sf::FloatRect getRect();
};