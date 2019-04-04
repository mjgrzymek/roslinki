#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
typedef sf::Vector2f point;

const float w = 1000, h = 800;
sf::ContextSettings settings(0, 0, 8, 2, 0);
sf::RenderWindow window(sf::VideoMode(w, h), "drzewo works!",
						sf::Style::Default, settings);

float rf() { return ((float)rand()) / ((float)RAND_MAX); }
float rfr(float a, float b) { return a + (b - a) * rf(); }

ostream& operator<<(ostream& o, point p) {
		return o << '(' << p.x << ", " << p.y << ')';
}

void drawCircle(point p, float r, sf::Color color) {
		sf::CircleShape circ(r);
		circ.setOrigin(r, r);
		circ.setPosition(p);
		circ.setFillColor(color);
		window.draw(circ);
}

struct Line {
		sf::RectangleShape rect;
		Line(point p, float rot, float thicc, float len,
			 sf::Color color)
			: rect(point(thicc, len)) {
				rect.setOrigin(thicc / 2, len);
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

float chaos() {
		const float CHAOS = 0.1f;
		return rfr(1.f - CHAOS, 1.f + CHAOS);
}

float rsign() { return rand() % 2 ? -1.f : 1.f; }

float toZerofy(float x, float en) {
		en=0.5;
		x -= floor(x);
		float bad = min(sinf(x * M_PI) * en * 2.f, 0.2f);
		return x + rfr(-1.f, 1.f) * bad;
}

void drawTree(point p, float rot, float energy) {
		if (energy <= 0.f) return;
		const float MAX_THICK = 10;
		const float MAX_LEN = 20;
		const float MAX_ROT = 0.02f;
		sf::Color color(255.f * energy * rfr(0.8f, 1.f),
						50 + 150.f * (1 - energy) * rfr(0.8f, 1.f), 0);
		Line trunk(p, rot, MAX_THICK * chaos() * energy,
				   MAX_LEN * chaos() * energy * energy * 2, color);

		drawCircle(p, trunk.getThickness() / 2.f, color);

		int rs[] = {rand(), rand(), rand()};
		for (int i = 0; i < 1+(rf()<0.3); ++i) {
				drawTree(
					trunk.endPoint(),
					toZerofy(rot + rsign() * MAX_ROT * rfr(0.3, 0.7), energy),
					energy - rfr(0.025, 0.035));
				srand(rs[i]);
		}
}

int main() {
		window.setFramerateLimit(120);
		float en = 0.f;
		int seed = time(0);
		while (window.isOpen()) {
				en += 0.001;
				if (en > 1) {
						en = 0;
						++seed;
				}
				sf::Event event;
				while (window.pollEvent(event)) {
						if (event.type == sf::Event::Closed)
								window.close();
				}
				window.clear(sf::Color::Black);
				srand(seed);
				drawTree({w / 2, h * 3 / 4}, 0, en);
				// drawHalfCircle({w/2, h/2}, 100, en, {255,0,0});
				window.display();
		}

		return 0;
}
