#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
using namespace sf;
using namespace std;

class PowerUp {
public:
    CircleShape shape;
    string type;
    Clock lifeTimer;
    float pulse = 0.f;

    PowerUp(string t, Vector2f pos);
    void updateVisual();
    bool expired() const;
    FloatRect getBounds() const;
    void draw(RenderWindow& window);
};
