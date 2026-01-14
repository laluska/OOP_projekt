#pragma once
#include "GameObject.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
using namespace sf;

class Ball : public GameObject {
public:
    CircleShape shape;
    Vector2f velocity;

    Ball();
    void reset();
    void update() override;
    void draw(RenderWindow& window) override;
    FloatRect getBounds() const override;
};
