#include "Window.h"

Window::Window(int x, int y)
{
	w.create(sf::VideoMode(x * 8, y * 8), "PacMan");
	w.setFramerateLimit(60);

	font.loadFromFile("Res/emulogic.ttf");

	game = Game(font);
	game.load(level, ups);
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
				case sf::Keyboard::Up:
					keys[0] = true;
					break;
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					keys[1] = true;
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					keys[2] = true;
					break;
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					keys[3] = true;
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (e.key.code)
				{
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					keys[0] = false;
					break;
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					keys[1] = false;
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					keys[2] = false;
					break;
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					keys[3] = false;
					break;
				}
			}


		lag += clock.restart().asMilliseconds();
		while (lag >= 1000 / ups)
		{
			lag -= 1000 / ups;

			update();
		}
		render();
	}
}

void Window::update()
{
	int overState;
	int lives = game.getLives();
	int score = game.getScore();

	dir = -1;
	for (int i = 0; i < 4; i++)
		if (keys[i])
			dir = i;

	game.setPacDir(dir);
	game.movePac(ups);
	game.moveGhosts();
	game.update(ups);

	// reset game
	overState = game.isOver();
	if (overState)
	{
		game = Game(font);
		if (overState == 1)
		{
			// increase level if player won
			game.load(++level, ups);
			game.setLives(lives);
			game.setScore(score);
		}
		else
		{
			// go back to the beginning
			level = 0;
			game.load(level, ups);
		}
	}
}

void Window::render()
{
	w.clear();

	// reset scaling
	view.reset(sf::FloatRect(0, 0, w.getSize().x, w.getSize().y));
	w.setView(view);

	game.drawMap(w, ups);

	game.drawGhost(w);

	game.drawPac(w);

	w.display();
}