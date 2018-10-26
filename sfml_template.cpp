#include <SFML/Graphics.hpp>
sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

int main()
{

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        window.display();
    }

    return 0;
}
