#include "SFMLData.hpp"
#include "../core/GameObject.hpp"
#include "../core/Snake.hpp"

SFMLData::SFMLData(int width, int height, std::list<GameObject*> *objects) : Data(width, height, objects)
{

	x0 = (WIDTH - width * 20) / 2;
	y0 = (HEIGHT - height * 10) / 2;

	win = new sf::RenderWindow(sf::VideoMode(1920, 1600), "My window");
	font = new sf::Font();
	texture = new sf::Texture();
	background = new sf::RectangleShape(sf::Vector2f(width * 20, height * 20));
	//sprite = new sf::Sprite();
	// if (!font.loadFromFile("SPECIAL.TTF"))
	// {
 //    	std::cout << "WTF FONT CANT BE OPEN" << std::endl;
 //    	exit(-1);
	// }
	if (!font->loadFromFile("SPECIAL.TTF"))
	{
		std::cerr << "WTF FONT CANT BE OPEN" << std::endl;
		exit(-1);
	}
	if (!texture->loadFromFile("groundX.png"))
	{
		std::cerr << "WTF TExture CANT BE OPEN" << std::endl;
		exit(-1);
	}
	background->setPosition(x0, y0);
	texture->setRepeated(true);
	texture->setSmooth(true);
	background->setTexture(texture);
	background->setFillColor(sf::Color(80,80,80));

	inputs[sf::Keyboard::Up] = UP;
	inputs[sf::Keyboard::Down] = DOWN;
	inputs[sf::Keyboard::Left] = LEFT;
	inputs[sf::Keyboard::Right] = RIGHT;
	inputs[sf::Keyboard::Escape] = PAUSE;
	inputs[sf::Keyboard::W] = UP;
	inputs[sf::Keyboard::S] = DOWN;
	inputs[sf::Keyboard::A] = LEFT;
	inputs[sf::Keyboard::D] = RIGHT;
	inputs[sf::Keyboard::P] = PAUSE;
	inputs[sf::Keyboard::Num1] = F1;
	inputs[sf::Keyboard::Num3] = F3;
	inputs[sf::Keyboard::Return] = VALIDATE;
	chars[sf::Keyboard::Numpad0] = '0';
	chars[sf::Keyboard::Numpad1] = '1';
	chars[sf::Keyboard::Numpad2] = '2';
	chars[sf::Keyboard::Numpad3] = '3';
	chars[sf::Keyboard::Numpad4] = '4';
	chars[sf::Keyboard::Numpad5] = '5';
	chars[sf::Keyboard::Numpad6] = '6';
	chars[sf::Keyboard::Numpad7] = '7';
	chars[sf::Keyboard::Numpad8] = '8';
	chars[sf::Keyboard::Numpad9] = '9';
	chars[sf::Keyboard::Period ] = '.';
	chars[sf::Keyboard::BackSpace] = 127;

	shouldDraw = false;

	// if (!(font70 = TTF_OpenFont("COMICATE.TTF", 70)))
	// 	throw SFMLException(TTF_GetError());
	// if (!(font20 = TTF_OpenFont("COMICATE.TTF", 20)))
	// 	throw SFMLException(TTF_GetError());
}

void SFMLData::Draw()
{
	win->clear(sf::Color::Black);
	(this->*funcs[state])();
	win->display();
}

void SFMLData::DrawMainMenu()
{
	   sf::Text menuEntry;

	   menuEntry.setFont(*font);
	   menuEntry.setCharacterSize(35);


	   int i = 0;
	   while (i < SIZEMENUCHOICES)
	   {
			if (i == choice)
				menuEntry.setColor(sf::Color::Red);
			else
				menuEntry.setColor(sf::Color::White);
			menuEntry.setString(mainMenu[i] + (i == WALL ? (wall ? "ON" : "OFF") : ""));
			menuEntry.setPosition(950, 500 + i * 100);
			win->draw(menuEntry);
			i++;
	   }
}

void SFMLData::DrawHiScoreMenu()
{
	sf::Text menuEntry;

	menuEntry.setFont(*font);
	menuEntry.setCharacterSize(70);
	menuEntry.setColor(sf::Color::White);
	menuEntry.setString("Game Over");
	menuEntry.setPosition(850, 250);
	win->draw(menuEntry);

	menuEntry.setCharacterSize(35);
	menuEntry.setString("With wall :");
	menuEntry.setPosition(850, 350);
	win->draw(menuEntry);

	for (int i = 0; i < 5; ++i)
	{
		std::string s = std::to_string(hiScores->GetScore(i, true));
		s = std::string(" : " + s);
		std::string tmp( hiScores->GetPseudo(i, true) + s);
		menuEntry.setString(tmp.c_str());
		menuEntry.setPosition(850, 350 + 40 * (i + 1));
		win->draw(menuEntry);
	}

	menuEntry.setString("Without wall :");
	menuEntry.setPosition(850, 600);
	win->draw(menuEntry);

	for (int i = 0; i < 5; ++i)
	{
		std::string s = std::to_string(hiScores->GetScore(i, false));
		s = std::string(" : " + s);
		std::string tmp( hiScores->GetPseudo(i, false) + s);
		menuEntry.setString(tmp.c_str());
		menuEntry.setPosition(850, 600 + 40 * (i + 1));
		win->draw(menuEntry);
	}
}

void SFMLData::DrawNormalMode()
{
	win->draw(*background);

	if (wall)
	{
		sf::RectangleShape rect(sf::Vector2f(3, height * 20 + 6));
		rect.setFillColor(sf::Color(0x80, 0x80, 0x80));
		rect.setPosition(x0 - 3, y0- 3);
		win->draw(rect);

		sf::RectangleShape rect2(sf::Vector2f(width * 20 + 3, 3));
		rect2.setFillColor(sf::Color(0x80, 0x80, 0x80));
		rect2.setPosition(x0, y0- 3);
		win->draw(rect2);

		sf::RectangleShape rect3(sf::Vector2f(width * 20 + 3, 3));
		rect3.setFillColor(sf::Color(0x80, 0x80, 0x80));
		rect3.setPosition(x0, y0 + height * 20);
		win->draw(rect3);

		sf::RectangleShape rect4(sf::Vector2f(3, height * 20));
		rect4.setFillColor(sf::Color(0x80, 0x80, 0x80));
		rect4.setPosition(x0 + width * 20, y0);
		win->draw(rect4);
	}

	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	// SFML_Rect position;
	// SFML_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
	sf::Text scoreText;

	scoreText.setFont(*font);
	scoreText.setCharacterSize(45);
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	scoreText.setColor(sf::Color::White);
	scoreText.setString(tmp);
	scoreText.setPosition(1500, y0 - 60);
	win->draw(scoreText);
	// auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	// position.x = x0;
	// position.y = y0 - 40;
	// SFML_BlitSurface(texte, NULL, screenSurface, &position);
	// SFML_FreeSurface(texte);
	// SFML_UpdateWindowSurface(win);
}

void SFMLData::DrawMultiMode()
{
	win->draw(*background);
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	// SFML_Rect position;
	// SFML_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
	sf::Text scoreText;

	scoreText.setFont(*font);
	scoreText.setCharacterSize(45);
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	scoreText.setColor(sf::Color::White);
	scoreText.setString(tmp);
	scoreText.setPosition(1500, y0 - 60);
	win->draw(scoreText);
}

void SFMLData::DrawHostMenu()
{
	sf::Text title;

	title.setFont(*font);
	title.setCharacterSize(35);
	int i = 0;
	auto tmp = std::string(" Waitings Player ");


	title.setColor(sf::Color::White);
	title.setString(tmp);
	title.setPosition(950, 500 + i * 100);
	win->draw(title);
	i++;
	title.setString(myAccess);
	title.setPosition(950, 500 + i * 100);
	win->draw(title);
}

void SFMLData::DrawJoinMenu()
{
	sf::Text title;

	title.setFont(*font);
	title.setCharacterSize(35);
	auto tmp = std::string(" Enter IP : ");
	tmp += ip;


	title.setColor(sf::Color::White);
	title.setString(tmp);
	title.setPosition(950, 500);
	win->draw(title);

}

void SFMLData::DrawMulti()
{

}

void SFMLData::DrawMultiMenu()
{
	sf::Text menuEntry;

	menuEntry.setFont(*font);
	menuEntry.setCharacterSize(35);


	int i = 0;
	while (i < SIZEMULTIMENUCHOICES)
	{
		if (i == choice)
			menuEntry.setColor(sf::Color::Red);
		else
			menuEntry.setColor(sf::Color::White);
		menuEntry.setString(multiMenu[i]);
		menuEntry.setPosition(950, 500 + i * 100);
		win->draw(menuEntry);
		i++;
	}
}

void SFMLData::DrawPauseMenu()
{
	sf::Text menuEntry;

	   menuEntry.setFont(*font);
	   menuEntry.setCharacterSize(35);


	   int i = 0;
	   while (i < NBACTIONPAUSE)
	   {
			if (i == choice)
				menuEntry.setColor(sf::Color::Red);
			else
				menuEntry.setColor(sf::Color::White);
			menuEntry.setString(pauseMenu[i]);
			menuEntry.setPosition(950, 500 + i * 100);
			win->draw(menuEntry);
			i++;
	   }
}

void SFMLData::DrawEndMenu()
{
	sf::Text menuEntry;

	   menuEntry.setFont(*font);
	   menuEntry.setCharacterSize(35);


	   int i = 0;
	   while (i < NBACTIONEND)
	   {
			if (i == choice)
				menuEntry.setColor(sf::Color::Red);
			else
				menuEntry.setColor(sf::Color::White);
			menuEntry.setString(endMenu[i]);
			menuEntry.setPosition(950, 500 + i * 100);
			win->draw(menuEntry);
			i++;
	   }
}

void SFMLData::DrawBestEndMenu()
{
	sf::Text menuEntry;
	menuEntry.setFont(*font);
	menuEntry.setCharacterSize(70);
	menuEntry.setColor(sf::Color::White);
	menuEntry.setString("Game Over");
	menuEntry.setPosition(750, 300);
	win->draw(menuEntry);
	menuEntry.setCharacterSize(35);
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	menuEntry.setPosition(850, 400);
	menuEntry.setString(tmp.c_str());
	win->draw(menuEntry);
	for (int i = 0; i < 3; i++)
	{
		char tmp[2];
		tmp[0] = player[i];
		tmp[1] = 0;
		if (i == choice)
			menuEntry.setColor(sf::Color::Red);
		else
			menuEntry.setColor(sf::Color::White);
		menuEntry.setString(tmp);
		menuEntry.setPosition((WIDTH - 120) / 2 + i * 40, 470);
		win->draw(menuEntry);
	}
}

void SFMLData::SetInput(int keycode)
{
	value = inputs[keycode];
}

void SFMLData::DrawSnake(GameObject *it)
{
	auto snake = dynamic_cast<Snake *>(it)->GetSnake();

	for (auto i = snake.begin(); i != snake.end(); ++i)
	{
		sf::RectangleShape rect(sf::Vector2f(20, 20));
		if (i == snake.begin())
			rect.setFillColor(sf::Color(50, 50, 50));
		else
			rect.setFillColor(sf::Color(75, 75, 75));
		rect.setPosition(x0 + (int)(*i).getX() * 20, y0 + (int)(*i).getY() * 20);
		win->draw(rect);
	}
}

void SFMLData::DrawFood(GameObject *it)
{
	sf::CircleShape shape(8);
	shape.setFillColor(sf::Color(220, 0, 0));

// set a 10-pixel wide orange outline
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color(250, 10, 10));
	shape.setPosition(x0 + (int)it->GetPosition().getX() * 20, y0 + (int)it->GetPosition().getY() * 20);
	win->draw(shape);
}


void SFMLData::DrawPowerUp(GameObject *it)
{
	if (!it->IsActivate())
		return;
	sf::CircleShape shape(8);
	shape.setFillColor(sf::Color(0, 0, 255));
	shape.setOutlineThickness(3);
	shape.setOutlineColor(sf::Color(10, 10, 255));
	shape.setPosition(x0 + (int)it->GetPosition().getX() * 20, y0 + (int)it->GetPosition().getY() * 20);
	win->draw(shape);
}

void SFMLData::DrawObstacle(GameObject *it)
{
	if (!wall)
		return;
	sf::RectangleShape shape(sf::Vector2f(20, 20));
	shape.setFillColor(sf::Color(0x80, 0x80, 0x80));
	shape.setPosition(x0 + (int)it->GetPosition().getX() * 20, y0 + (int)it->GetPosition().getY() * 20);
	win->draw(shape);
}

eInput SFMLData::GetInput()
{
	sf::Event event;
	eInput ret = NONE;
	while (win->pollEvent(event))
	{
			if (event.type == sf::Event::Closed)
			{
				//emergency close
				win->close();
				exit(0);
			}
			else if (event.type == sf::Event::KeyPressed)
			{

		auto tmp = inputs[event.key.code];
		if (tmp != NONE)
			return tmp;
		else
		{
			ch = chars[event.key.code];
			return CHAR;
		}
			}

	}
	return ret;
}


SFMLData::~SFMLData()
{
	delete font;
	delete win;
}
