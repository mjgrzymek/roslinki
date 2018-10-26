#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
const float w=500, h=500;

sf::ContextSettings settings(0,0,0,2,0);
sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!", sf::Style::Default, settings);

void kolo(float x, float y, int r, int br){
    sf::CircleShape shape(r);
    shape.setOrigin(r,r);
    shape.setPosition(x,y);
    shape.setFillColor(sf::Color(br,br,br));
    window.draw(shape);
}

void obrazek(int a){
    for(float i=200.f; i<w*6/7; i+=1.f){
        kolo(i, (h/2+sin(10*i/w)*h/2)*0.5 + h/4, fabs(sin(a*0.2)*w/2 + w/2 - i )/10+3, fabs(cos(a*i/w))*255);
    }

}

int main()
{
    float a=1;
    while (window.isOpen())
    {
        a+=0.1f;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        obrazek(a);
        window.display();
    }
    return 0;
}
