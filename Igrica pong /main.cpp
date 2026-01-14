#include <SFML/Graphics.hpp>
#include <ctime>
#include "GameFunction.hpp"

using namespace sf;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    RenderWindow menu(VideoMode(800, 600), "Menu");
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    int mode = showMenu(menu, font);
    menu.close();

    startGame(mode);
    return 0;
}
