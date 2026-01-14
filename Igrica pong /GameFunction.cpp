#include "GameFunction.hpp"
#include <iostream>
#include <ctime>

int showMenu(RenderWindow& window, Font& font) {
    vector<string> options = { "Player vs Player", "Player vs Bot" };
    vector<Text> texts;

    Text title("PONG", font, 70);
    title.setFillColor(Color::Cyan);
    title.setPosition(300, 80);

    for (int i = 0; i < options.size(); i++) {
        Text t(options[i], font, 40);
        t.setPosition(250, 250 + i * 100);
        texts.push_back(t);
    }

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::MouseButtonPressed) {
                for (int i = 0; i < texts.size(); i++) {
                    if (texts[i].getGlobalBounds().contains(
                        (float)Mouse::getPosition(window).x,
                        (float)Mouse::getPosition(window).y))
                        return i + 1;
                }
            }
        }

        window.clear();
        window.draw(title);
        for (auto& t : texts) window.draw(t);
        window.display();
    }
    return -1;
}

// ================= GAME =================
void startGame(int mode) {
    RenderWindow window(VideoMode(800, 600), "Pong");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

    Ball ball;
    PlayerPaddle left(30, Keyboard::W, Keyboard::S);
    PlayerPaddle rightPlayer(760, Keyboard::Up, Keyboard::Down);
    BotPaddle bot(760, &ball.shape);

    Paddle* right = (mode == 1) ? (Paddle*)&rightPlayer : (Paddle*)&bot;

    vector<PowerUp> powerUps;
    vector<string> effects;
    Clock spawnClock;
    Clock effectTimer;

    int scoreL = 0, scoreR = 0;
    Text score("", font, 40);
    score.setPosition(360, 20);

    bool gameOver = false;
    Text winnerText("", font, 30);
    winnerText.setFillColor(Color::Yellow);
    winnerText.setOutlineColor(Color::Black);
    winnerText.setOutlineThickness(3.f);

    Clock gameOverClock;

    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e))
            if (e.type == Event::Closed)
                window.close();

        if (!gameOver) {
            // Spawn power-ups
            if (spawnClock.getElapsedTime().asSeconds() > 3.f) {
                vector<string> types = { "SpeedUp", "BigPaddle", "SmallPaddle" };
                string t = types[rand() % types.size()];
                powerUps.emplace_back(
                    t,
                    Vector2f(rand() % 600 + 100, rand() % 400 + 100)
                );
                spawnClock.restart();
            }

            // Update objects
            left.update();
            right->update();
            ball.update();

            // Ball collision with paddles
            if (ball.getBounds().intersects(left.getBounds()))
                ball.velocity.x *= -1;
            if (ball.getBounds().intersects(right->getBounds()))
                ball.velocity.x *= -1;

            // Power-ups
            for (int i = 0; i < powerUps.size(); i++) {
                powerUps[i].updateVisual();

                if (powerUps[i].expired()) {
                    powerUps.erase(powerUps.begin() + i);
                    i--;
                    continue;
                }

                if (powerUps[i].getBounds().intersects(ball.getBounds())) {
                    string t = powerUps[i].type;
                    effects.push_back(t);
                    effectTimer.restart();

                    if (t == "SpeedUp")
                        ball.velocity *= 1.3f;

                    if (t == "BigPaddle") {
                        left.shape.setSize({ 10, 150 });
                        right->shape.setSize({ 10, 150 });
                    }

                    if (t == "SmallPaddle") {
                        left.shape.setSize({ 10, 60 });
                        right->shape.setSize({ 10, 60 });
                    }

                    powerUps.erase(powerUps.begin() + i);
                    i--;
                }
            }

            // Reset effects after 5 sec
            if (!effects.empty() && effectTimer.getElapsedTime().asSeconds() > 5.f) {
                ball.velocity.x = (ball.velocity.x > 0) ? 5.f : -5.f;
                ball.velocity.y = (ball.velocity.y > 0) ? 5.f : -5.f;
                left.shape.setSize({ 10, 100 });
                right->shape.setSize({ 10, 100 });
                effects.clear();
            }

            // Score update
            if (ball.shape.getPosition().x < 0) {
                scoreR++;
                ball.reset();
            }
            if (ball.shape.getPosition().x > 800) {
                scoreL++;
                ball.reset();
            }

            score.setString(to_string(scoreL) + " : " + to_string(scoreR));

            // Check for game over
            if (scoreL == 3 || scoreR == 3) {
                gameOver = true;
                if (scoreL == 3)
                    winnerText.setString("Player 1 je pobijedio!");
                else
                    winnerText.setString((mode == 1) ? "Player 2 je pobijedio!" : "    Bot je pobijedio!");
            }
        }

        // Render
        window.clear(Color::Black);
        window.draw(score);

        left.draw(window);
        right->draw(window);
        ball.draw(window);
        for (auto& p : powerUps) p.draw(window);

        if (gameOver) {
            // Panel pozadine iza teksta i opcija
            RectangleShape panel;
            panel.setSize({ 400.f, 200.f });
            panel.setFillColor(Color(50, 50, 50, 220)); // tamno siva poluprozirna
            panel.setOutlineColor(Color::White);
            panel.setOutlineThickness(3.f);
            panel.setPosition(200.f, 180.f); // centrirano
            window.draw(panel);

            // Winner text
            winnerText.setPosition(270.f, 200.f); // pomaknuto unutar panela
            window.draw(winnerText);

            // Opcije
            vector<string> options = { "Play Again", "Exit" };
            vector<Text> texts;
            for (int i = 0; i < options.size(); i++) {
                Text t(options[i], font, 40);
                t.setPosition(200.f + 120.f, 260.f + i * 50.f); // centrirano unutar panela
                t.setFillColor(Color::White);
                t.setOutlineColor(Color::Black);
                t.setOutlineThickness(2.f);
                texts.push_back(t);
                window.draw(t);
            }
        }

        window.display();

        // Ako je gameOver, čekaj klik na opcije
        if (gameOver) {
            bool chosen = false;
            while (!chosen && window.isOpen()) {
                Event e2;
                while (window.pollEvent(e2)) {
                    if (e2.type == Event::Closed) {
                        window.close();
                        return;
                    }
                    if (e2.type == Event::MouseButtonPressed) {
                        Vector2f mp((float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y);
                        // Play Again
                        if (mp.x >= 320 && mp.x <= 480 && mp.y >= 260 && mp.y <= 300) {
                            chosen = true;
                            window.close();
                            startGame(mode);
                            return;
                        }
                        // Exit
                        if (mp.x >= 320 && mp.x <= 480 && mp.y >= 310 && mp.y <= 350) {
                            chosen = true;
                            window.close();
                            return;
                        }
                    }
                }
            }
        }
    }
}
