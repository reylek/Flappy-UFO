#include "UFO.h"
using namespace sf;

UFO::UFO(unsigned screenSizeY) {
    UFOTexture.loadFromFile("res/textures/UFO.png");
    UFOSprite.setTexture(UFOTexture);
    flameTexture.loadFromFile("res/textures/Flame.png");
    flameSprite.setTexture(flameTexture);
    y = static_cast<float>(screenSizeY) / 2.f;
    poofBuffer.loadFromFile("res/sounds/Poof.wav");
    poofSound.setBuffer(poofBuffer);
}

UFO::~UFO() {
}

void UFO::draw(RenderWindow& windowRef) {
    UFOSprite.setPosition(x, y);
    windowRef.draw(UFOSprite);
    if (verticalSpeed < 0) {
        flameSprite.setPosition(
            x + (UFOTexture.getSize().x - flameTexture.getSize().x) / 2,
            y + UFOTexture.getSize().y
        );
        windowRef.draw(flameSprite);
    }
}

void UFO::update(float deltaTime, status& statusGameRef, unsigned screenSizeY) {
    verticalSpeed += deltaTime * gravity;
    y += verticalSpeed * deltaTime;
    if ((y < 0) || ((y + UFOTexture.getSize().y) > screenSizeY)) {
        statusGameRef = status::GameOver;
    }
}

void UFO::flap() {
    verticalSpeed = -200;
    poofSound.play();
}

FloatRect UFO::getRect() {
    auto size = UFOTexture.getSize();
    return {
        x, y,
        static_cast<float>(size.x), static_cast<float>(size.y)
    };
}

void UFO::restart(unsigned screenSizeY) {
    y = static_cast<float>(screenSizeY)/2.f;
    verticalSpeed = 0.f;
}
