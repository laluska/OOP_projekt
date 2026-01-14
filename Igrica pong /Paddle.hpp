#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

class Paddle : public GameObject {
public:
    RectangleShape shape;
    float speed = 7.f;

    Paddle(float x);
    void move(float dy);
    void draw(RenderWindow& window) override;
    FloatRect getBounds() const override;
};

class PlayerPaddle : public Paddle {
    Keyboard::Key up, down;
public:
    PlayerPaddle(float x, Keyboard::Key u, Keyboard::Key d);
    void update() override;
};

class BotPaddle : public Paddle {
    const CircleShape* ball;
public:
    BotPaddle(float x, const CircleShape* b);
    void update() override;
};
