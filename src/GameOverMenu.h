#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Status.h"
#include "Button.h"

class GameOverMenu {
private:
	sf::Texture restartTexture, mainMenuTexture;
	Button restartButton, mainMenuButton;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;

public:
	GameOverMenu(unsigned screenSizeX, unsigned screenSizeY);
	~GameOverMenu();
	void draw(sf::RenderWindow& windowRef);
	void update(float deltaSeconds, status& gameStatusRef, sf::RenderWindow& windowRef);
	void eventClickOn();
	void eventClickDown(status& gameStatusRef, sf::RenderWindow& windowRef, sf::Sound& clickSoundRef);
};

