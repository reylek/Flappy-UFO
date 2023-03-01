#include "Block.h"
using namespace sf;

Block::Block(std::shared_ptr<Texture> blockTextureRef, unsigned screenSizeX, unsigned screenSizeY, float currentHoleSize) {
    blockTexture = blockTextureRef;
    upBlockSprite.setTexture(*blockTexture.get());
    upBlockSprite.setTextureRect(IntRect(0, static_cast<int>(blockTexture->getSize().y), blockTexture->getSize().x, -static_cast<int>(blockTexture->getSize().y)));
    downBlockSprite.setTexture(*blockTexture.get());
    holeSize = currentHoleSize;
    x = static_cast<float>(screenSizeX);
    y = static_cast<float>(minHeight + rand() % (screenSizeY - minHeight * 2 - static_cast<int>(holeSize) + 1));
    isScored = false;
}

Block::~Block() {
}

float Block::getX() {
    return x;
}

bool Block::getIsScored() {
    return isScored;
}

void Block::setIsScored(bool value) {
    isScored = value;
}

void Block::draw(RenderWindow& windowRef) {
    upBlockSprite.setPosition(x, y - static_cast<float>(blockTexture->getSize().y));
    windowRef.draw(upBlockSprite);
    downBlockSprite.setPosition(x, y + holeSize);
    windowRef.draw(downBlockSprite);
}

FloatRect Block::getUpRect() {
    auto size = blockTexture->getSize();
    return {
        x, y - static_cast<float>(size.y),
        static_cast<float>(size.x), static_cast<float>(size.y)
    };
}

FloatRect Block::getDownRect() {
    auto size = blockTexture->getSize();
    return {
        x, y + holeSize,
        static_cast<float>(size.x), static_cast<float>(size.y)
    };
}

void Block::update(float deltaTime, float horizontalSpeed) {
    x -= horizontalSpeed * deltaTime;
}