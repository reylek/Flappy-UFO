#include "GameOverMenu.h"

using namespace sf;

GameOverMenu::GameOverMenu(unsigned screenSizeX, unsigned screenSizeY) {
	restartTexture.loadFromFile("res/textures/RestartButton.png");
	mainMenuTexture.loadFromFile("res/textures/MenuButton.png");
	restartButton = Button(static_cast<float>(screenSizeX - restartTexture.getSize().x) / 2.f, 140.f, restartTexture);
	mainMenuButton = Button(static_cast<float>(screenSizeX - mainMenuTexture.getSize().x) / 2.f, 260.f, mainMenuTexture);
	gameOverBuffer.loadFromFile("res/sounds/GameOver.wav");
	gameOverSound.setBuffer(gameOverBuffer);
	gameOverSound.play();
}

GameOverMenu::~GameOverMenu() {
}

void GameOverMenu::draw(sf::RenderWindow& windowRef) {
	restartButton.draw(windowRef);
	mainMenuButton.draw(windowRef);
}

void GameOverMenu::update(float deltaSeconds, status& gameStatusRef, sf::RenderWindow& windowRef) {
	restartButton.update(deltaSeconds, windowRef);
	mainMenuButton.update(deltaSeconds, windowRef);
}

void GameOverMenu::eventClickOn() {
	if (restartButton.isSelected) {
		restartButton.isClicked = true;
	}
	else if (mainMenuButton.isSelected) {
		mainMenuButton.isClicked = true;
	}
}

void GameOverMenu::eventClickDown(status& gameStatusRef, sf::RenderWindow& windowRef, Sound& clickSoundRef) {
	if (restartButton.isSelected) {
		gameStatusRef = status::Inisialization;
		clickSoundRef.play();
	}
	else if (mainMenuButton.isSelected) {
		gameStatusRef = status::InMenu;
		clickSoundRef.play();
	}
}
