#include "Game.h"

Game::Game(sf::Font& f)
{
	file.open("Res/HighScore.txt", std::ios::in);
	if (file.is_open())
	{
		file >> highScore;
		file.close();
	}

	vertMap.setPrimitiveType(sf::Quads);
	tex.loadFromFile("Res/Textures.png");
	ghostTex.loadFromFile("Res/Ghost.png");
	pacTex.loadFromFile("Res/Pacman.png");

	text.setFont(f);

	ghosts[0] = new RedGhost(ghostTex);
	ghosts[1] = new PinkGhost(ghostTex);
	ghosts[2] = new OrangeGhost(ghostTex);
	ghosts[3] = new BlueGhost(ghostTex);

	pac = new Pacman(pacTex);

	lifeTex = new sf::Texture;
	lifeTex->loadFromFile("Res/Pacman.png");

	rect.setTexture(lifeTex);
	rect.setTextureRect(sf::IntRect(0, 14 * 3, 14, 14));

	fruitTex = new sf::Texture;
	fruitTex->loadFromFile("Res/Fruit.png");

	fruitRect.setTexture(fruitTex);
}

Game::Game()
{
	
}

void Game::load(int level)
{
	int xpos;

	this->level = level;

	if (!loadMap("Res/map.bin") || level > 255)
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

	if (level < 1)
	{
		phases[0] = 7 * 45;
		phases[1] = 20 * 45;
		phases[2] = 7 * 45;
		phases[3] = 20 * 45;
		phases[4] = 5 * 45;
		phases[5] = 20 * 45;
		phases[6] = 5 * 45;
		phases[7] = -1;
	}
	else if (level < 4)
	{
		phases[0] = 7 * 45;
		phases[1] = 20 * 45;
		phases[2] = 7 * 45;
		phases[3] = 20 * 45;
		phases[4] = 5 * 45;
		phases[5] = 1033 * 45;
		phases[6] = 1;
		phases[7] = -1;
	}
	else
	{
		phases[0] = 5 * 45;
		phases[1] = 20 * 45;
		phases[2] = 5 * 45;
		phases[3] = 20 * 45;
		phases[4] = 5 * 45;
		phases[5] = 1037 * 45;
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

	rect.setSize(sf::Vector2f(minScale, minScale));
	for (int i = 0; i < lives - 1; i++)
	{
		rect.setPosition(xoff + (i * 1.5f + 0.5f) * minScale, yoff + (size.y + 0.25f) * minScale);
		w.draw(rect);
	}

	debugTarget.setSize(sf::Vector2f(minScale, minScale));
	debugTarget.setFillColor(sf::Color(0x00000000));
	debugTarget.setOutlineThickness(4);
	for (int i = 0; i < 4; i++)
	{
		if (ghosts[i]->getMode() != 2)
		{
			debugTarget.setPosition(xoff + ghosts[i]->getTarget().x * minScale, yoff + ghosts[i]->getTarget().y * minScale);
			switch (i)
			{
			case 0:
				debugTarget.setOutlineColor(sf::Color(0xFF0000CF));
				break;
			case 1:
				debugTarget.setOutlineColor(sf::Color(0xFF88FFCF));
				break;
			case 2:
				debugTarget.setOutlineColor(sf::Color(0xFF8800CF));
				break;
			case 3:
				debugTarget.setOutlineColor(sf::Color(0x00FFFFCF));
			}
			w.draw(debugTarget);
		}
	}

	text.setCharacterSize(minScale);
	text.setString(std::to_string(score));
	text.setPosition(xoff + 9 * minScale - text.getLocalBounds().width / 2, yoff - 2 * minScale);
	w.draw(text);

	text.setCharacterSize(minScale);
	if (score > highScore)
		text.setString(std::to_string(score));
	else
		text.setString(std::to_string(highScore));
	text.setPosition(xoff + 18 * minScale - text.getLocalBounds().width / 2, yoff - 2 * minScale);
	w.draw(text);

	text.setCharacterSize(minScale);
	text.setString("HIGH SCORE");
	text.setPosition(xoff + 14 * minScale - text.getLocalBounds().width / 2, yoff - 3 * minScale);
	w.draw(text);

	if (fruit % 2)
	{
		fruitRect.setPosition(xoff + 13.5 * minScale, yoff + 17 * minScale);
		fruitRect.setSize(sf::Vector2f(minScale * 1.5, minScale * 1.5));
		w.draw(fruitRect);
	}
}

void Game::drawPac(sf::RenderWindow &w)
{
	pac->draw(w, size, ticks);
}

void Game::drawGhost(sf::RenderWindow &w)
{
	for (auto ghost : ghosts)
		ghost->draw(w, size, timer);
}

void Game::movePac()
{
	bool pacAtt = false;

	if (restart == 0)
	{
		pac->move(map, size, dots, pacAtt, level, score);
		if (pacAtt)
			pacAttack = true;

		if (pacAtt)
		{
			timer = 45 * 7;
			for (auto& ghost : ghosts)
				ghost->setMode(2, level);
		}
		if (pacAttack)
		{
			timer--;
			if (timer == 0)
			{
				ghostsEaten = 0;
				pacAttack = false;
				for (auto& ghost : ghosts)
					ghost->setMode(0, level);
			}
		}

		if (pac->getPos().x + 0.49 < 14.5 && pac->getPos().x + 0.49 > 12.5)
			if (pac->getPos().y + 0.49 < 18 && pac->getPos().y + 0.49 > 16.5)
				if (fruit % 2)
				{
					score += 100;
					fruitTimer = 0;
					fruit++;
				}
	}
}

void Game::moveGhosts()
{
	if (restart == 0)
	{
		if (!pacAttack)
		{
			if (phaseTimer == 0)
			{
				phase++;
				phaseTimer = phases[phase];
				for (auto& ghost : ghosts)
					ghost->setMode(phase % 2 == 0, level);
			}
			phaseTimer--;
		}

		for (auto& ghost : ghosts)
		{
			if (ghost->getDotReq() <= 244 - dots)
			{
				if (ghost->isInBox())
					ghost->enableMove(true);
				ghost->setTarget(ghosts[0], *pac);
				ghost->update(map, size, level);
			}
			if (ghost->needsRestart())
			{
				ghost->reset(ghostTex, true);
				ghost->setMode(phase % 2 == 0, level);
			}
		}
	}
}

void Game::update()
{
	int rx = rand() % size.x;
	int ry = rand() % size.y;

	if (restart == 0)
	{
		ticks++;

		if (failedMap && ticks % std::max(100 - ticks / 100, 1) == 0)
		{
			if (map[ry][rx] == 0x20 || map[ry][rx] == 0x21)
				dots--;
			map[ry][rx] = 0;
		}

		if (dots == 0)
		{
			over = 1;
		}
		if (lives == 0)
		{
			over = 2;
			if (score > highScore)
			{
				file.open("Res/HighScore.txt", std::ios::out);
				file << score;
				file.close();
			}
		}

		if (dots == 244 - 70 && fruit == 0)
		{
			fruitTimer = 45 * 10;
			fruit++;
		}
		else if (dots == 244 - 170 && fruit == 2)
		{
			fruitTimer = 45 * 10;
			fruit++;
		}
		if (fruitTimer != 0);
		{
			fruitTimer--;
			if (fruitTimer == 0)
				fruit++;
		}
	}
	else
		restart--;

	for (auto& ghost : ghosts)
	{
		if (!ghost->isDead())
			if (pac->getPos().x + 0.49 < ghost->getPos().x + 1 && pac->getPos().x + 0.49 > ghost->getPos().x)
				if (pac->getPos().y + 0.49 < ghost->getPos().y + 1 && pac->getPos().y + 0.49 > ghost->getPos().y)
				{
					if (ghost->getMode() == 2)
					{
						restart = 45 / 3 * 2;
						score += 200 * std::pow(2, ghostsEaten++);
						ghost->die();
					}
					else
					{
						fruit = 0;
						fruitTimer = 0;
						restart = 45;
						lives--;
						ghostsEaten = 0;
						for (auto& ghost : ghosts)
							ghost->reset(ghostTex, false);
						pac->reset(pacTex);
						phase = 0;
						phaseTimer = phases[phase];
					}
				}
	}
}

void Game::setPacDir(char dir)
{
	pac->setDir(dir);
}

int Game::getLives()
{
	return lives;
}

void Game::setLives(int newLives)
{
	lives = newLives;
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


int Game::getScore()
{
	return score;
}

void Game::setScore(int newScore)
{
	score = newScore;
}