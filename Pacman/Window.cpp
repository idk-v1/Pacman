#include "Window.h"

Window::Window(int x, int y)
{
	w.create(sf::VideoMode(x, y), "PacMan");
	w.setFramerateLimit(60);

	game.load("testmap");
}

void Window::start()
{
	clock.restart();

	while (w.isOpen())
	{
		sf::Event e;
		while (w.pollEvent(e))
			switch (e.type)
			{
			case sf::Event::Closed:
				w.close();
				break;
			case sf::Event::KeyPressed:
				switch (e.key.code)
				{
				case sf::Keyboard::W:
					game.setPacDir(0);
					break;
				case sf::Keyboard::D:
					game.setPacDir(1);
					break;
				case sf::Keyboard::S:
					game.setPacDir(2);
					break;
				case sf::Keyboard::A:
					game.setPacDir(3);
					break;
				}
			}

		lag += clock.restart().asMilliseconds();
		while (lag >= 1000 / 60)
		{
			lag -= 1000 / 60;
			update();
		}
		render();
	}
}

void Window::update()
{
	game.movePac();
}

void Window::render()
{
	w.clear();

	view.reset(sf::FloatRect(0, 0, w.getSize().x, w.getSize().y));
	w.setView(view);

	game.drawMap(w);

	game.drawPac(w);

	w.display();
}
