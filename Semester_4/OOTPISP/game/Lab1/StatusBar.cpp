#include "StatusBar.h"

std::vector<std::string> StatusBar::strings = { "user", "0", "0", "easy", "5" };
std::vector<sf::Text> StatusBar::texts = {};
sf::Clock StatusBar::clock = sf::Clock{};
int StatusBar::time = 0;
int StatusBar::score = 0;
int StatusBar::additionalScore = 0;
GameField* StatusBar::field;
std::string StatusBar::difficulty{"easy"};
std::string StatusBar::playerName{ "user" };
int StatusBar::ballSpeed{CommonResource::getBallVelocityByDifficulty(difficulty)};
