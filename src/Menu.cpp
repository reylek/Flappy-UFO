#include "Menu.h"

using namespace sf;

Menu::Menu(unsigned screenSizeX, unsigned screenSizeY) {
	startTexture.loadFromFile("res/textures/StartButton.png");
	quitTexture.loadFromFile("res/textures/QuitButton.png");
	startButton = Button(static_cast<float>(screenSizeX - startTexture.getSize().x) / 2.f, 140.f, startTexture);
	quitButton = Button(static_cast<float>(screenSizeX - quitTexture.getSize().x) / 2.f, 260.f, quitTexture);
}

Menu::~Menu() {
}

void Menu::draw(RenderWindow& windowRef) {
	startButton.draw(windowRef);
	quitButton.draw(windowRef);
}

void Menu::update(float deltaSeconds, status& gameStatusRef, RenderWindow& windowRef) {
	startButton.update(deltaSeconds, windowRef);
	quitButton.update(deltaSeconds, windowRef);
}

void Menu::eventClickOn() {
	if (startButton.isSelected) {
		startButton.isClicked = true;
	}
	else if (quitButton.isSelected) {
		quitButton.isClicked = true;
	}
}

void Menu::eventClickDown(status& gameStatusRef, RenderWindow& windowRef, Sound& clickSoundRef) {
	if (startButton.isSelected) {
		gameStatusRef = status::Inisialization;
		clickSoundRef.play();
	}
	else if (quitButton.isSelected) {
		windowRef.close();
		clickSoundRef.play();
	}
}
