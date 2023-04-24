#include "Game.h"

Game::Game(sf::Font &f)
{
	vertMap.setPrimitiveType(sf::Quads);
	tex.loadFromFile("Res/Textures.png");

	text.setFont(f);

	ghosts.push_back(new RedGhost());
	ghosts.push_back(new PinkGhost());
	ghosts.push_back(new OrangeGhost());
}

Game::Game()
{
}

void Game::load(int level)
{
	int xpos;

	if (!loadMap("Maps/map0.bin"))
		loadFailedMap();
	printf("dots: %d\n", 244 - dots);

	// all pacman mazes are symmetrical
	vertMap.resize(size.x * size.y * 4);
	for (int col = 0; col < size.y; col++)
		for (int row = 0; row < size.x / 2; row++)
		{
			xpos = map[col][row];
			vertMap[(row + col * size.x) * 4 + 0].texCoords = sf::Vector2f(xpos * 8 + 0, 0);
			vertMap[(row + col * size.x) * 4 + 1].texCoords = sf::Vector2f(xpos * 8 + 8, 0);
			vertMap[(row + col * size.x) * 4 + 2].texCoords = sf::Vector2f(xpos * 8 + 8, 8);
			vertMap[(row + col * size.x) * 4 + 3].texCoords = sf::Vector2f(xpos * 8 + 0, 8);

			vertMap[(size.x - 1 - row + col * size.x) * 4 + 0].texCoords = sf::Vector2f(xpos * 8 + 8, 0);
			vertMap[(size.x - 1 - row + col * size.x) * 4 + 1].texCoords = sf::Vector2f(xpos * 8 + 0, 0);
			vertMap[(size.x - 1 - row + col * size.x) * 4 + 2].texCoords = sf::Vector2f(xpos * 8 + 0, 8);
			vertMap[(size.x - 1 - row + col * size.x) * 4 + 3].texCoords = sf::Vector2f(xpos * 8 + 8, 8);
		}

	if (level < 1)
	{
		phases[0] = 7 * 60;
		phases[1] = 20 * 60;
		phases[2] = 7 * 60;
		phases[3] = 20 * 60;
		phases[4] = 5 * 60;
		phases[5] = 20 * 60;
		phases[6] = 5 * 60;
		phases[7] = -1;
	}
	else if (level < 4)
	{
		phases[0] = 7 * 60;
		phases[1] = 20 * 60;
		phases[2] = 7 * 60;
		phases[3] = 20 * 60;
		phases[4] = 5 * 60;
		phases[5] = 1033 * 60;
		phases[6] = 1;
		phases[7] = -1;
	}
	else
	{
		phases[0] = 5 * 60;
		phases[1] = 20 * 60;
		phases[2] = 5 * 60;
		phases[3] = 20 * 60;
		phases[4] = 5 * 60;
		phases[5] = 1037 * 60;
		phases[6] = 1;
		phases[7] = -1;
	}

	phaseTimer = phases[phase];
}

void Game::drawMap(sf::RenderWindow& w)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)(size.y + 2 + 3));
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - (size.y - 2) * minScale) / 2.f;

	// position map to fill all of the window
	for (int col = 0; col < size.y; col++)
		for (int row = 0; row < size.x; row++)
		{
			vertMap[(row + col * size.x) * 4 + 0].position = sf::Vector2f(xoff + (row + 0) * minScale, yoff + (col + 0) * minScale);
			vertMap[(row + col * size.x) * 4 + 1].position = sf::Vector2f(xoff + (row + 1) * minScale, yoff + (col + 0) * minScale);
			vertMap[(row + col * size.x) * 4 + 2].position = sf::Vector2f(xoff + (row + 1) * minScale, yoff + (col + 1) * minScale);
			vertMap[(row + col * size.x) * 4 + 3].position = sf::Vector2f(xoff + (row + 0) * minScale, yoff + (col + 1) * minScale);

			if (map[col][row] == 0)
			{
				vertMap[(row + col * size.x) * 4 + 0].texCoords = sf::Vector2f((map[col][row] + 0) * 8, 0);
				vertMap[(row + col * size.x) * 4 + 1].texCoords = sf::Vector2f((map[col][row] + 1) * 8, 0);
				vertMap[(row + col * size.x) * 4 + 2].texCoords = sf::Vector2f((map[col][row] + 1) * 8, 8);
				vertMap[(row + col * size.x) * 4 + 3].texCoords = sf::Vector2f((map[col][row] + 0) * 8, 8);
			}
		}
	w.draw(vertMap, &tex);
}

void Game::drawPac(sf::RenderWindow &w)
{
	pac.draw(w, size);
}

void Game::drawGhost(sf::RenderWindow &w)
{
	for (auto ghost : ghosts)
		ghost->draw(w, size);
}

void Game::movePac()
{
	bool pacAtt = false;
	int rx = rand() % size.x;
	int ry = rand() % size.y;

	printf("dots: %d\n", 244 - dots);

	pac.move(map, size, dots, pacAtt);
	if (pacAtt)
		pacAttack = true;
	for (auto& ghost : ghosts)
	{
		if (int(pac.getPos().x + 0.49) == int(ghost->getPos().x + 0.49) && int(pac.getPos().y + 0.49) == int(ghost->getPos().y + 0.49))
		{
			if (ghost->getMode() == 2)
			{
				ghost->reset(true);
				ghost->setMode(phase % 2 == 0);
			}
			else
			{
				lives--;
				for (auto& ghost : ghosts)
					ghost->reset(false);
				pac.reset();
				phase = 0;
				phaseTimer = phases[phase];
			}
		}
	}

	if (pacAtt)
	{
		timer = 300;
		for (auto& ghost : ghosts)
			ghost->setMode(2);
	}
	if (pacAttack)
	{
		timer--;
		if (timer == 0)
		{
			pacAttack = false;
			for (auto& ghost : ghosts)
				ghost->setMode(0);
		}
	}

	ticks++;

	if (failedMap && ticks % std::max(100 - ticks / 100, 1) == 0)
	{
		if (map[ry][rx] == 0x20)
			dots--;
		map[ry][rx] = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) // set ghosts to chase
		for (auto& ghost : ghosts)
			ghost->setMode(0);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) // set ghosts to scatter
		for (auto& ghost : ghosts)
			ghost->setMode(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) // set ghosts to frightened
		for (auto& ghost : ghosts)
			ghost->setMode(2);

	if (dots == 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // reset map
		over = 1;
	if (lives == 0)
		over = 2;
}

void Game::moveGhosts()
{
	if (!pacAttack)
	{
		if (phaseTimer == 0)
		{
			phase++;
			phaseTimer = phases[phase];
			for (auto& ghost : ghosts)
				ghost->setMode(phase % 2 == 0);
		}
		phaseTimer--;
	}

	for (auto& ghost : ghosts)
	{
		if (ghost->getDotReq() <= 244 - dots)
		{
			if (ghost->isInBox())
				ghost->enableMove(true);
			ghost->setTarget(ghosts, pac);
			ghost->update(map, size);
		}
	}
}

void Game::setPacDir(char dir)
{
	pac.setDir(dir);
}

char Game::isOver() 
{
	return over;
}

bool Game::loadMap(std::string name)
{
	std::ifstream file(name);
	char c;

	if (file.is_open())
	{		
		for (int col = 0; col < size.y; col++)
		{
			for (int row = 0; row < size.x / 2; row++)
			{
				file.get(c);
				map[col][row] = c;
				map[col][size.x - 1 - row] = c;
				if (c == 0x20 || c == 0x21)
					dots += 2;
			}
		}
		return true;
	}
	else
		return false;
}

void Game::loadFailedMap()
{
	char c;
	dots = 0;
	srand(time(NULL));
	for (int col = 0; col < size.y; col++)
		for (int row = 0; row < size.x / 2; row++)
		{
			switch (rand() % 7)
			{
			case 0:
			case 1:
			case 2:
				c = (rand() % 0x22); // random. mostly walls
				break;
			case 3:
			case 4:
				c = 0x20; // dots
				break;
			case 5:
				c = 0; // empty space
				break;
			case 6:
				c = (rand() % 5 == 0 ? 0x21 : 0x20); // power dots / dots
			}
			map[col][row] = c;
			map[col][size.x - 1 - row] = c;
			if (c == 0x20 || c == 0x21)
				dots += 2;
		}
	map[23][13] = 0;
	map[23][14] = 0;

	failedMap = true;
}