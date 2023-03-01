#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::Sprite buttonSprite;
	sf::Color defaultColor = sf::Color(200, 200, 200, 255);
	sf::Color clickColor = sf::Color::White;
	sf::Color selectColor = sf::Color::Green;
public:
	Button();
	Button(float x, float y, sf::Texture& buttonTexture);
	~Button();
	bool isSelected = false;
	bool isClicked = false;
	void draw(sf::RenderWindow& windowRef);
	void update(float deltaTime, sf::RenderWindow& windowRef);
};

