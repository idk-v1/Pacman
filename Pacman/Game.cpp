#include "Game.h"

Game::Game()
{
	vertMap.setPrimitiveType(sf::Quads);
	tex.loadFromFile("Res/Textures.png");
}

void Game::load(std::string name)
{
	int xpos;

	if (!loadMap("Maps/" + name + ".bin"))
		loadFailedMap();

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
}

void Game::drawMap(sf::RenderWindow& w)
{
	float minScale = std::min(w.getSize().x / (float)size.x, w.getSize().y / (float)size.y);
	float xoff = (w.getSize().x - size.x * minScale) / 2.f;
	float yoff = (w.getSize().y - size.y * minScale) / 2.f;

	// position map to fill all of the window
	for (int col = 0; col < size.y; col++)
		for (int row = 0; row < size.x; row++)
		{
			vertMap[(row + col * size.x) * 4 + 0].position = sf::Vector2f((xoff + row + 0) * minScale, (yoff + col + 0) * minScale);
			vertMap[(row + col * size.x) * 4 + 1].position = sf::Vector2f((xoff + row + 1) * minScale, (yoff + col + 0) * minScale);
			vertMap[(row + col * size.x) * 4 + 2].position = sf::Vector2f((xoff + row + 1) * minScale, (yoff + col + 1) * minScale);
			vertMap[(row + col * size.x) * 4 + 3].position = sf::Vector2f((xoff + row + 0) * minScale, (yoff + col + 1) * minScale);

			if (map[col][row] == 0)
			{
				vertMap[(row + col * size.x) * 4 + 0].texCoords = sf::Vector2f(map[col][row] * 8,     0);
				vertMap[(row + col * size.x) * 4 + 1].texCoords = sf::Vector2f(map[col][row] * 8 + 8, 0);
				vertMap[(row + col * size.x) * 4 + 2].texCoords = sf::Vector2f(map[col][row] * 8 + 8, 8);
				vertMap[(row + col * size.x) * 4 + 3].texCoords = sf::Vector2f(map[col][row] * 8,     8);
			}
		}
	w.draw(vertMap, &tex);
}

void Game::drawPac(sf::RenderWindow &w)
{
	pac.draw(w, size);
}

void Game::movePac()
{
	pac.move(map, size, dots);

	// print map (DEBUG)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		system("cls");
		for (int y = 0; y < size.y; y++)
		{
			for (int x = 0; x < size.x; x++)
			{
				if (map[y][x] < 10)
					printf(" ");
				printf("%d ", int(map[y][x]));
			}
			printf("\n");
		}
	}
}

void Game::setPacDir(char dir)
{
	pac.setDir(dir);
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
				if (c == 0x20)
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
	for (int col = 0; col < size.y; col++)
		for (int row = 0; row < size.x; row++)
			map[col][row] = 0;
}