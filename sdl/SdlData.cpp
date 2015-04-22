#include "SdlData.hpp"
#include "../core/GameObject.hpp"
#include "../core/Snake.hpp"
#include "SdlException.hpp"

SdlData::SdlData(int width, int height, std::list<GameObject*> *objects) : Data(width, height, objects)
{
	x0 = (WIDTH - width * 10) / 2;
	y0 = (HEIGHT - height * 10) / 2;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw SdlException(SDL_GetError());
	if(TTF_Init() == -1)
		throw SdlException(TTF_GetError());
	if(!(win = SDL_CreateWindow("snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS)))
		throw SdlException(SDL_GetError());

	if (!(screenSurface = SDL_GetWindowSurface(win)))
		throw SdlException(SDL_GetError());

	inputs[SDLK_UP] = UP;
	inputs[SDLK_DOWN] = DOWN;
	inputs[SDLK_LEFT] = LEFT;
	inputs[SDLK_RIGHT] = RIGHT;
	inputs[SDLK_ESCAPE] = PAUSE;
	inputs[SDLK_w] = UP;
	inputs[SDLK_s] = DOWN;
	inputs[SDLK_a] = LEFT;
	inputs[SDLK_d] = RIGHT;
	inputs[SDLK_p] = PAUSE;
	inputs[SDLK_1] = F1;
	inputs[SDLK_2] = F2;
	inputs[SDLK_RETURN] = VALIDATE;
	chars[SDLK_KP_0] = '0';
	chars[SDLK_KP_1] = '1';
	chars[SDLK_KP_2] = '2';
	chars[SDLK_KP_3] = '3';
	chars[SDLK_KP_4] = '4';
	chars[SDLK_KP_5] = '5';
	chars[SDLK_KP_6] = '6';
	chars[SDLK_KP_7] = '7';
	chars[SDLK_KP_8] = '8';
	chars[SDLK_KP_9] = '9';
	chars[SDLK_KP_PERIOD] = '.';
	chars[SDLK_BACKSPACE] = 127;
	shouldDraw = false;

	if (!(font70 = TTF_OpenFont("COMICATE.TTF", 70)))
		throw SdlException(TTF_GetError());
	if (!(font20 = TTF_OpenFont("COMICATE.TTF", 20)))
		throw SdlException(TTF_GetError());
}

void SdlData::Draw()
{
	(this->*funcs[state])();
	SDL_UpdateWindowSurface(win);
}

void SdlData::DrawMainMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	auto title = TTF_RenderText_Solid(font70, "snake", text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 350;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	for (int i = 0; i < SIZEMENUCHOICES; ++i)
	{
		if (i == choice)
			text_color = {0xFF, 0x0, 0x0, 0xFF};
		else
			text_color = {0x0, 0x0, 0x0, 0xFF};
		std::string tmp(mainMenu[i] + (i == WALL ? (wall ? "ON" : "OFF") : ""));
		auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
		position.x = (WIDTH - texte->w) / 2;
		position.y = 450 + i * 30;
		SDL_BlitSurface(texte, NULL, screenSurface, &position);
		SDL_FreeSurface(texte);
	}
}

void SdlData::DrawHiScoreMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	auto title = TTF_RenderText_Solid(font70, "hi-score", text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 350;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	title = TTF_RenderText_Solid(font20, "With wall :", text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 420;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	for (int i = 0; i < 5; ++i)
	{
		std::string s = std::to_string(hiScores->GetScore(i, true));
		s = std::string(" : " + s);
		std::string tmp( hiScores->GetPseudo(i, true) + s);
		auto score = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
		if (!score)
			throw SdlException(TTF_GetError());
		position.x = (WIDTH - score->w) / 2;
		position.y = 430 + 20 * (i + 1);
		SDL_BlitSurface(score, NULL, screenSurface, &position);
		SDL_FreeSurface(score);
	}
	title = TTF_RenderText_Solid(font20, "Without wall :", text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 560;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	for (int i = 0; i < 5; ++i)
	{
		std::string s = std::to_string(hiScores->GetScore(i, false));
		s = std::string(" : " + s);
		std::string tmp( hiScores->GetPseudo(i, false) + s);
		auto score = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
		if (!score)
			throw SdlException(TTF_GetError());
		position.x = (WIDTH - score->w) / 2;
		position.y = 570 + 20 * (i + 1);
		SDL_BlitSurface(score, NULL, screenSurface, &position);
		SDL_FreeSurface(score);
	}
}

void SdlData::DrawNormalMode()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x0));
	SDL_Rect bg = {x0, y0, width * 10, height * 10};
	SDL_FillRect(screenSurface, &bg, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	if (wall)
	{
		auto noir = SDL_MapRGB(screenSurface->format, 178, 34, 34);
		SDL_Rect wall1 = {x0 - 3, y0 - 3, 3, height * 10 + 6};
		SDL_Rect wall2 = {x0, y0 - 3, width * 10 + 3, 3};
		SDL_Rect wall3 = {x0, y0 + height * 10, width * 10 + 3, 3};
		SDL_Rect wall4 = {x0 + width * 10, y0, 3, height * 10};
		SDL_FillRect(screenSurface, &wall1, noir);
		SDL_FillRect(screenSurface, &wall2, noir);
		SDL_FillRect(screenSurface, &wall3, noir);
		SDL_FillRect(screenSurface, &wall4, noir);
	}
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	SDL_Rect position;
	SDL_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	position.x = x0;
	position.y = y0 - 40;
	SDL_BlitSurface(texte, NULL, screenSurface, &position);
	SDL_FreeSurface(texte);
}

void SdlData::DrawMultiMode()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x0));
	SDL_Rect bg = {x0, y0, width * 10, height * 10};
	SDL_FillRect(screenSurface, &bg, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	if (wall)
	{
		auto noir = SDL_MapRGB(screenSurface->format, 178, 34, 34);
		SDL_Rect wall1 = {x0 - 3, y0 - 3, 3, height * 10 + 6};
		SDL_Rect wall2 = {x0, y0 - 3, width * 10 + 3, 3};
		SDL_Rect wall3 = {x0, y0 + height * 10, width * 10 + 3, 3};
		SDL_Rect wall4 = {x0 + width * 10, y0, 3, height * 10};
		SDL_FillRect(screenSurface, &wall1, noir);
		SDL_FillRect(screenSurface, &wall2, noir);
		SDL_FillRect(screenSurface, &wall3, noir);
		SDL_FillRect(screenSurface, &wall4, noir);
	}
	for (auto i = objects->begin(); i != objects->end(); ++i)
	{
		(this->*funcs2[(*i)->GetType()])(*i);
	}
	SDL_Rect position;
	SDL_Color text_color = {0xFF, 0xFF, 0xFF, 0xFF};
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	position.x = x0;
	position.y = y0 - 40;
	SDL_BlitSurface(texte, NULL, screenSurface, &position);
	SDL_FreeSurface(texte);
}

void SdlData::DrawMultiMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color;
	for (int i = 0; i < SIZEMULTIMENUCHOICES; ++i)
	{
		if (i == choice)
			text_color = {0xFF, 0x0, 0x0, 0xFF};
		else
			text_color = {0x0, 0x0, 0x0, 0xFF};
		auto texte = TTF_RenderText_Solid(font20, multiMenu[i].c_str(), text_color);
		position.x = (WIDTH - texte->w) / 2;
		position.y = 450 + i * 30;
		SDL_BlitSurface(texte, NULL, screenSurface, &position);
		SDL_FreeSurface(texte);
	}
}

void SdlData::DrawHostMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	auto title = TTF_RenderText_Solid(font70, "waiting players", text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 350;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
}

void SdlData::DrawJoinMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	auto tmp = std::string("enter ip : ");
	tmp += ip;
	auto title = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	if (!title)
		throw SdlException(TTF_GetError());
	position.x = (WIDTH - title->w) / 2;
	position.y = 350;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
}

void SdlData::DrawMulti()
{

}

void SdlData::DrawPauseMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	SDL_Surface *title = TTF_RenderText_Solid(font70, "pause", text_color);
	position.x = (WIDTH - title->w) / 2;
	position.y = 350;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	for (int i = 0; i < NBACTIONPAUSE; ++i)
	{
		if (i == choice)
			text_color = {0xFF, 0x0, 0x0, 0xFF};
		else
			text_color = {0x0, 0x0, 0x0, 0xFF};
		std::string tmp(pauseMenu[i]);
		auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
		position.x = (WIDTH - texte->w) / 2;
		position.y = 450 + i * 30;
		SDL_BlitSurface(texte, NULL, screenSurface, &position);
		SDL_FreeSurface(texte);
	}
}

void SdlData::DrawEndMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	SDL_Surface *title = TTF_RenderText_Solid(font70, "game over", text_color);
	position.x = (WIDTH - title->w) / 2;
	position.y = 300;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	SDL_Surface *score = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	position.x = (WIDTH - score->w) / 2;
	position.y = 400;
	SDL_BlitSurface(score, NULL, screenSurface, &position);
	SDL_FreeSurface(score);
	SDL_FreeSurface(title);
	for (int i = 0; i < NBACTIONEND; ++i)
	{
		if (i == choice)
			text_color = {0xFF, 0x0, 0x0, 0xFF};
		else
			text_color = {0x0, 0x0, 0x0, 0xFF};
		std::string tmp(endMenu[i]);
		auto texte = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
		position.x = (WIDTH - texte->w) / 2;
		position.y = 450 + i * 30;
		SDL_BlitSurface(texte, NULL, screenSurface, &position);
		SDL_FreeSurface(texte);
	}
}

void SdlData::DrawBestEndMenu()
{
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_Rect position;
	SDL_Color text_color = {0x0, 0x0, 0x0, 0xFF};
	SDL_Color text_color_selected = {0xFF, 0x0, 0x0, 0xFF};
	SDL_Surface *title = TTF_RenderText_Solid(font70, "game over", text_color);
	position.x = (WIDTH - title->w) / 2;
	position.y = 300;
	SDL_BlitSurface(title, NULL, screenSurface, &position);
	std::string s = std::to_string(score);
	std::string tmp("score : " + s);
	SDL_Surface *score = TTF_RenderText_Solid(font20, tmp.c_str(), text_color);
	position.x = (WIDTH - score->w) / 2;
	position.y = 400;
	SDL_BlitSurface(score, NULL, screenSurface, &position);
	SDL_FreeSurface(title);
	SDL_FreeSurface(score);
	for (int i = 0; i < 3; i++)
	{
		char tmp[2];
		tmp[0] = player[i];
		tmp[1] = 0;
		SDL_Surface *pseudo;
		if (i == choice)
			pseudo = TTF_RenderText_Solid(font20, tmp, text_color_selected);
		else
			pseudo = TTF_RenderText_Solid(font20, tmp, text_color);
		position.x = (WIDTH - 60) / 2 + i * 20;
		position.y = 430;
		SDL_BlitSurface(pseudo, NULL, screenSurface, &position);
		SDL_FreeSurface(pseudo);
	}
}

void SdlData::SetInput(int keycode)
{
	value = inputs[keycode];
}

void SdlData::DrawSnake(GameObject *it)
{
	auto snake = dynamic_cast<Snake *>(it)->GetSnake();
	int color;
	for (auto i = snake.begin(); i != snake.end(); ++i)
	{
		if (i == snake.begin())
			color = SDL_MapRGB(screenSurface->format, 0xFF, 0, 0);
		else
			color = SDL_MapRGB(screenSurface->format, 0, 0xFF, 0);
		SDL_Rect rect = {x0 + (int)(*i).getX() * 10, y0 + (int)(*i).getY() * 10, 10, 10};
		SDL_FillRect(screenSurface, &rect,color);
	}
}

void SdlData::DrawFood(GameObject *it)
{
	auto color = SDL_MapRGB(screenSurface->format, 0x0, 0, 0xFF);
	SDL_Rect rect = {x0 + (int)it->GetPosition().getX() * 10, y0 + (int)it->GetPosition().getY() * 10, 10, 10};
	SDL_FillRect(screenSurface, &rect,color);
}

eInput SdlData::GetInput()
{
	SDL_Event event;
	if (!SDL_PollEvent(&event))
		return NONE;
	if (event.type == SDL_KEYDOWN)
	{
		auto tmp = inputs[event.key.keysym.sym];
		if (tmp != NONE)
			return tmp;
		else
		{
			ch = chars[event.key.keysym.sym];
			return CHAR;
		}
	}
	else if (event.type == SDL_QUIT)
	{
		TTF_CloseFont(font20);
		TTF_CloseFont(font70);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(0);
	}
	return NONE;
}

SdlData::~SdlData()
{
	TTF_CloseFont(font20);
	TTF_CloseFont(font70);
	TTF_Quit();
	SDL_DestroyWindow(win);
	SDL_Quit();
}
