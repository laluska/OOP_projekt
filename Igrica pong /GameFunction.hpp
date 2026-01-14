#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.hpp"
#include "Paddle.hpp"
#include "PowerUp.hpp"
using namespace sf;
using namespace std;

int showMenu(RenderWindow& window, Font& font);
void startGame(int mode);
