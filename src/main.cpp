#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <fstream>
#include "UFO.h"
#include "Block.h"
#include "Menu.h"
#include "GameOverMenu.h"
#include "Status.h"

using namespace sf;

unsigned score, maxScore;
Text scoreText;
Font font;
float horizontalSpeed = 100.f;
float holeSize = 200.f;
const float startHoleSize = 200.f;
const float minHoleSize = 110.f;
const float decreaseHoleSize = 5.f;
status statusGame = status::InMenu;
const Vector2u screenSize = Vector2u(640u, 480u);
RenderWindow window(VideoMode(screenSize.x, screenSize.y), "Flappy UFO");
std::unique_ptr<Menu>menu;
std::unique_ptr<GameOverMenu>gameOverMenu;
std::unique_ptr<UFO>ufo;
std::vector<std::unique_ptr<Block>>blocks;
std::shared_ptr<Texture> blockTexture;
std::unique_ptr<Clock> blockSpawnClock;
SoundBuffer clickBuffer;
Sound clickSound;
Music music;
Texture backgroundTexture;
Sprite backgroundSprite;

void addMusic() {
    music.openFromFile("res/sounds/MainTheme.wav");
    music.play();
    music.setLoop(true);
}

void startSettings() {
    addMusic();
    backgroundTexture.loadFromFile("res/textures/Background.png");
    backgroundSprite.setTexture(backgroundTexture);
    clickBuffer.loadFromFile("res/sounds/Click.wav");
    clickSound.setBuffer(clickBuffer);
    srand(static_cast<unsigned>(time(NULL)));
    font.loadFromFile("res/fonts/Swiss721BlackExtendedBT.ttf");
    scoreText = Text("", font, 30);
    scoreText.setFillColor(Color::Green);
    std::ifstream ifs{ "save_maxscore.sav" };
    if (ifs) {
        ifs >> maxScore;
    }
    else {
        maxScore = 0;
    }
}

void update(float deltaTime) {
    window.draw(backgroundSprite);
    switch (statusGame) {
        case status::InMenu: {
            if (!menu) {
                menu = std::unique_ptr<Menu>(new Menu(screenSize.x, screenSize.y));
                scoreText.setString("Max score: " + std::to_string(maxScore));
                blocks.clear();
                ufo = nullptr;
                blockSpawnClock = nullptr;
                blockTexture = nullptr;
                gameOverMenu = nullptr;
            }
            menu->update(deltaTime, statusGame, window);
            menu->draw(window);
            break;
        }
        case status::Inisialization: {
            blocks.clear();
            menu = nullptr;
            gameOverMenu = nullptr;
            score = 0u;
            scoreText.setString("Score: " + std::to_string(score));
            holeSize = startHoleSize;
            if (!ufo) {
                ufo = std::unique_ptr<UFO>(new UFO(screenSize.y));
                blockSpawnClock = std::unique_ptr<Clock>(new Clock());
                blockTexture = std::shared_ptr<Texture>(new Texture());
                blockTexture->loadFromFile("res/textures/Block.png");
            }
            else {
                ufo->restart(screenSize.y);
                blockSpawnClock->restart();
            }

            blocks.push_back(std::unique_ptr<Block>(new Block(blockTexture, screenSize.x, screenSize.y, holeSize)));
            statusGame = status::Play;
            break;
        }
        case status::Play: {
            ufo->update(deltaTime, statusGame, screenSize.y);
            ufo->draw(window);
            auto it = blocks.begin();
            while (it != blocks.end()) {
                (*it)->update(deltaTime, horizontalSpeed);
                (*it)->draw(window);
                // Проверяем на столкновение игрока с препятствием
                auto ufoRect = ufo->getRect();
                if (ufoRect.intersects((*it)->getUpRect()) || ufoRect.intersects((*it)->getDownRect())) {
                    statusGame = status::GameOver;
                }

                // Проверяем прохождение препятствия
                if ((ufoRect.left > ((*it)->getX() + blockTexture->getSize().x)) && !(*it)->getIsScored()) {
                    (*it)->setIsScored(true);
                    score++;
                    scoreText.setString("Score: " + std::to_string(score));
                    if (holeSize > minHoleSize) {
                        holeSize -= decreaseHoleSize;
                    }
                }

                // Удаление препятствий, вышедших за границу экрана
                if ((*it)->getX() < -static_cast<float>(blockTexture->getSize().x)) {
                    it = blocks.erase(it);
                }
                else {
                    ++it;
                }
            }

            // Генерация новых препятствий
            if (blockSpawnClock->getElapsedTime().asSeconds() > 3.f) {
                blockSpawnClock->restart();
                blocks.push_back(std::unique_ptr<Block>(new Block(blockTexture, screenSize.x, screenSize.y, holeSize)));
            }

            break;
        }
        case status::GameOver: {
            if (!gameOverMenu) {
                gameOverMenu = std::unique_ptr<GameOverMenu>(new GameOverMenu(screenSize.x, screenSize.y));
                if (score > maxScore) {
                    maxScore = score;
                    std::ofstream ofs{ "save_maxscore.sav" };
                    ofs << maxScore;
                }
            }

            ufo->draw(window);
            for (const auto& block : blocks) {
                block->draw(window);
            }

            gameOverMenu->update(deltaTime, statusGame, window);
            gameOverMenu->draw(window);
            break;
        }
    }
    scoreText.setPosition((static_cast<float>(screenSize.x) - scoreText.getGlobalBounds().width) / 2.f, 10.f);
    window.draw(scoreText);
}

int main() {
    Clock clock;
    startSettings();
    while (window.isOpen()) {
        auto deltaTime = static_cast<float>(clock.getElapsedTime().asMicroseconds()) / 1000.f / 1000.f;
        clock.restart();
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
                
            if (event.type == Event::MouseButtonPressed) {
                switch (statusGame) {
                    case status::Play:
                        ufo->flap();
                        break;
                    case status::InMenu:
                        menu->eventClickOn();
                        break;
                    case status::GameOver:
                        gameOverMenu->eventClickOn();
                        break;
                }
            }

            if (event.type == Event::MouseButtonReleased) {
                switch (statusGame) {
                    case status::InMenu:
                        menu->eventClickDown(statusGame, window, clickSound);
                        break;
                    case status::GameOver:
                        gameOverMenu->eventClickDown(statusGame, window, clickSound);
                        break;
                }
            }
        }

        window.clear();
        update(deltaTime);
        window.display();
    }

    return 0;
}