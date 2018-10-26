#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
typedef sf::Vector2f point;

const float w=1000, h=800;
sf::ContextSettings settings(0,0,8,2,0);
sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!", sf::Style::Default, settings);

float rf(){
    return ((float)rand()) / ((float)RAND_MAX);
}
float rfr(float a, float b){
    return a+(b-a)*rf();
}

ostream&operator<<(ostream&o, point p){
	return o<<'('<<p.x<<", "<<p.y<<')';
}

void drawCircle(point p, float r, sf::Color color){
    sf::CircleShape circ(r);
    circ.setOrigin(r,r);
    circ.setPosition(p);
    circ.setFillColor(color);
    window.draw(circ);
}

struct Line{
    sf::RectangleShape rect;
	Line(point p, float rot, float thicc, float len, sf::Color color)
		:rect(point(thicc, len)){
		rect.setOrigin(thicc/2, len);
		rect.setFillColor(color);
		rect.rotate(-360*rot);
		rect.setPosition(p);
		window.draw(rect);
	}
    float getThickness(){
        return rect.getPoint(1).x;
    }
	point endPoint(){
        return rect.getTransform().transformPoint(
            (rect.getPoint(0)+rect.getPoint(1))/2.f);
	}
};

float chaos(){
    const float CHAOS=0.1f;
    return rfr(1.f-CHAOS, 1.f+CHAOS);
}

float rsign(){
    return rand()%2?-1.f:1.f;
}

float toZerofy(float x, float en){
    x-=floor(x);
    float bad=min(sinf(x*M_PI)*en*2.f, 1.f);
    return x+rfr(-0.4f, 0.4f)*bad;
}

point onAngle(float f){
    return {cos(M_PI*2*f), sin(M_PI*2*f)};
}

void drawHalfCircle(point p, float rad, float rot, sf::Color color){
    sf::ConvexShape circ;
    circ.setFillColor(color);
    circ.setPointCount(rad+1);
    for(float i=0; i<rad; ++i)
        circ.setPoint(i, rad*onAngle((i/2.f)/rad));
    circ.setPoint(rad, {-rad, 0});
    circ.rotate(-360.f*rot);
    circ.setPosition(p);
    window.draw(circ);
}

void drawTree(point p, float rot, float energy){
    if(energy<=0.f)
        return;
    const float MAX_THICC=10;
    const float MAX_LEN=20;
    const float MAX_ROT=0.05f;
    sf::Color color(255.f*energy*rfr(0.8f, 1.f),
            50+150.f*(1-energy)*rfr(0.8f, 1.f),
            0);
    Line trunk(p, rot,
        MAX_THICC*chaos()*energy, MAX_LEN*chaos()*energy, color);
    
    drawCircle(p, trunk.getThickness()/2.f,  color);
    
    int rs[]={rand(), rand(), rand()};
    for(int i=0; i<3; ++i){
        drawTree(trunk.endPoint(),
            toZerofy(rot+rsign()*MAX_ROT*rf(), energy),
            energy-rfr(0.03, 0.04));
        srand(rs[i]);
        if(rf()>0.2f) break;
    }
}

int main()
{
	//window.setFramerateLimit(120);
    float en=0.0f;
    int seed=2137;
    while (window.isOpen())
    {
        en+=0.001;
        if(en>1){
            en=0;
            ++seed;
        }
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
        srand(seed);
        drawTree({w/2, h*3/4}, 0, en);
        //drawHalfCircle({w/2, h/2}, 100, en, {255,0,0});
		window.display();
    }

    return 0;
}
