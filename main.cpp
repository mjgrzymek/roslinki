#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
typedef sf::Vector2f point;

const float WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 800;
sf::ContextSettings settings(0, 0, 8, 2, 0);
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                        "roslinki works!", sf::Style::Default,
                        settings);

float RandFloat() { return ((float)rand()) / ((float)RAND_MAX); }
float RandFloatRange(float a, float b) {
    return a + (b - a) * RandFloat();
}

ostream& operator<<(ostream& o, point p) {
    return o << '(' << p.x << ", " << p.y << ')';
}

void DrawCircle(point center, float radius, sf::Color color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    circle.setFillColor(color);
    window.draw(circle);
}

struct Line {
    sf::RectangleShape rect;
    Line(point p, float rot, float thickness, float len,
         sf::Color color)
        : rect(point(thickness, len)) {
        rect.setOrigin(thickness / 2, len);
        rect.setFillColor(color);
        rect.rotate(-360 * rot);
        rect.setPosition(p);
        window.draw(rect);
    }
    float getThickness() { return rect.getPoint(1).x; }
    point endPoint() {
        return rect.getTransform().transformPoint(
            (rect.getPoint(0) + rect.getPoint(1)) / 2.f);
    }
};

float ToZero(float x) {
    while (x < -0.5) ++x;
    while (x > 0.5) --x;
    return x * 0.7;
}

void DrawTree(point p, float rot, float energy) {
    if (energy <= 0.f) return;
    const float MAX_THICK = 10;
    const float MAX_LEN = 40;
    const float MAX_ROT = 0.2;
    sf::Color color(255.f * energy, 50 + 150.f * (1 - energy), 0);
    Line trunk(p, rot, MAX_THICK * energy, MAX_LEN * energy * energy,
               color);

    DrawCircle(p, trunk.getThickness() / 2.f, color);

    int branch_seeds[] = {rand(), rand(), rand()};
    for (int i = 0; i < 1 + (RandFloat() < 0.3) && i < 3; ++i) {
        DrawTree(trunk.endPoint(),
                 ToZero(rot + RandFloatRange(-MAX_ROT, MAX_ROT)),
                 energy - RandFloatRange(0.025, 0.05));
        srand(branch_seeds[i]);
    }
}

int main() {
    window.setFramerateLimit(60);
    float trunk_energy = 0.f;
    int seed = 0;//time(0);
    while (window.isOpen()) {
        trunk_energy += 0.002;
        if (trunk_energy > 1) {
            trunk_energy = 0;
            //++seed;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(sf::Color::Black);
        srand(seed);
        DrawTree({WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 4}, 0, trunk_energy);
        window.display();
    }

    return 0;
}
