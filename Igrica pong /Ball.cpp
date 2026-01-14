#include "Ball.hpp"

Ball::Ball() {
    shape.setRadius(8.f);
    shape.setFillColor(Color::White);
    reset();
}
void Ball::reset() {
    shape.setPosition(400, 300);
    velocity.x = (rand() % 2 ? 1 : -1) * 5.f;
    velocity.y = (rand() % 2 ? 1 : -1) * 5.f;
}
void Ball::update() {
    shape.move(velocity);
    if (shape.getPosition().y <= 0 ||
        shape.getPosition().y >= 600 - shape.getRadius() * 2)
        velocity.y *= -1;
}
void Ball::draw(RenderWindow& window) { window.draw(shape); }
FloatRect Ball::getBounds() const { return shape.getGlobalBounds(); }
