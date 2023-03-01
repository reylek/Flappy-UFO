#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Status.h"
#include "Button.h"

class Menu {
private:
	sf::Texture startTexture, quitTexture;
	Button startButton, quitButton;

public:
	Menu(unsigned screenSizeX, unsigned screenSizeY);
	~Menu();
	void draw(sf::RenderWindow& windowRef);
	void update(float deltaSeconds, status& gameStatusRef, sf::RenderWindow& windowRef);
	void eventClickOn();
	void eventClickDown(status& gameStatusRef, sf::RenderWindow& windowRef, sf::Sound& clickSoundRef);
};

