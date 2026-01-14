#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject {
public:
    virtual void update() = 0;
    virtual void draw(RenderWindow& window) = 0;
    virtual FloatRect getBounds() const = 0;
    virtual ~GameObject() {}
};
