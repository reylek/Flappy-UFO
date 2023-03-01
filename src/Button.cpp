#include "Button.h"
using namespace sf;

Button::Button() {
}

Button::Button(float x, float y, Texture& buttonTexture) {
	buttonSprite = Sprite(buttonTexture);
	buttonSprite.setPosition(x, y);
	buttonSprite.setColor(defaultColor);
}

Button::~Button() {
}

void Button::draw(RenderWindow& windowRef) {
	windowRef.draw(buttonSprite);
}

void Button::update(float deltaTime, RenderWindow& windowRef) {
	if (buttonSprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(windowRef)))) {
		isSelected = true;
	}
	else {
		isSelected = false;
		isClicked = false;
	}

	if (isClicked) {
		buttonSprite.setColor(clickColor);
	}
	else if (isSelected) {
		buttonSprite.setColor(selectColor);
	}
	else buttonSprite.setColor(defaultColor);
}
