#include "PowerUp.hpp"

PowerUp::PowerUp(string t, Vector2f pos) {
    type = t;
    shape.setRadius(12.f);
    shape.setOrigin(12.f, 12.f);
    shape.setPosition(pos);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(Color::White);

    if (type == "SpeedUp") shape.setFillColor(Color(0, 220, 120));
    if (type == "BigPaddle") shape.setFillColor(Color(220, 70, 70));
    if (type == "SmallPaddle") shape.setFillColor(Color(240, 200, 0));

    lifeTimer.restart();
}
void PowerUp::updateVisual() {
    pulse += 0.08f;
    float scale = 1.f + sin(pulse) * 0.1f;
    shape.setScale(scale, scale);
}
bool PowerUp::expired() const {
    return lifeTimer.getElapsedTime().asSeconds() > 30.f;
}
FloatRect PowerUp::getBounds() const { return shape.getGlobalBounds(); }
void PowerUp::draw(RenderWindow& window) { window.draw(shape); }
