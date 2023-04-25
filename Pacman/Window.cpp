#include "Window.h"

Window::Window(int x, int y)
{
	w.create(sf::VideoMode(x * 8, y * 8), "PacMan");
	w.setFramerateLimit(60);

	game = Game(font);
	game.load(level);
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
					keys[0] = true;
					break;
				case sf::Keyboard::D:
					keys[1] = true;
					break;
				case sf::Keyboard::S:
					keys[2] = true;
					break;
				case sf::Keyboard::A:
					keys[3] = true;
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (e.key.code)
				{
				case sf::Keyboard::W:
					keys[0] = false;
					break;
				case sf::Keyboard::D:
					keys[1] = false;
					break;
				case sf::Keyboard::S:
					keys[2] = false;
					break;
				case sf::Keyboard::A:
					keys[3] = false;
					break;
				}
			}


		lag += clock.restart().asMilliseconds();
		while (lag >= 1000 / 45)
		{
			lag -= 1000 / 45;

			update();
		}
		render();
	}
}

void Window::update()
{
	int overState;

	dir = -1;
	for (int i = 0; i < 4; i++)
		if (keys[i])
			dir = i;

	game.setPacDir(dir);
	game.movePac();
	game.moveGhosts();
	game.update();

	overState = game.isOver();
	if (overState)
	{
		game = Game(font);
		if (overState == 1)
		{
			printf("You Win!\n");
			game.load(++level);
		}
		else
		{
			printf("You Lose!\n");
			game.load(level);
		}
	}
}

void Window::render()
{
	w.clear();

	view.reset(sf::FloatRect(0, 0, w.getSize().x, w.getSize().y));
	w.setView(view);

	game.drawMap(w);

	game.drawGhost(w);

	game.drawPac(w);

	w.display();
}
