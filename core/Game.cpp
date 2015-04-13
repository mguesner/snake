#include "Game.hpp"
#include <ctime>
#include <sys/time.h>

Game::Game()
{
}

Game::Game(Game const & src)
{
	(void)src;
}

Game& Game::operator=(Game const & src)
{
	(void)src;
	return *this;
}

Game::Game(Data* data, loader* lib, std::string cur, int width, int height, std::list<GameObject*> *obj)
{
	player[0] = 'A';
	player[1] = 'A';
	player[2] = 'A';
	player[3] = 0;
	hiScores = new Score();
	this->width = width;
	this->height = height;
	object = obj;
	gameData = data;
	this->lib = lib;
	first = new Player(object, width, height, 1);
	food = new Food(width, height);
	object->push_back(food);
	shouldLeave = false;
	progress = 100000;
	entry = 0;
	(void)second;
	(void)cur;

}

Game::~Game()
{
	delete first;
	delete food;
}

void	Game::Reset()
{
	score = 0;
	progress = 100000;
	object->erase(object->begin(), object->end());
	delete first;
	delete food;
	first = new Player(object, width, height, 1);
	food = new Food(width, height);
	object->push_back(food);
}

ObjectType	Game::Collide()
{
	auto first = object->begin();
	auto current = object->begin();
	auto last = object->end();

	while (current != last)
	{
		current++;
		if (current == last)
			break;
		if ((*first)->GetPosition() == (*current)->GetPosition())
			return (*current)->GetType();
	}
	return VOID;
}

void	Game::Update(eInput value)
{
	if (value == PAUSE)
	{
		state = PAUSEMENU;
		return;
	}
	Snake *snk = first->GetSnake();
	if (value >= UP && value <= RIGHT)
		snk->SetDirection(value);
	if (snk->Move(wall))
	{
		//shouldLeave = true;
		if (hiScores->CheckScore(score, wall))
		{
			state = BESTENDMENU;
			std::cout << "BESTENDMENU\n";
		}
		else
			state = ENDMENU;
	}
	if (snk->IsColliding())
	{
		//shouldLeave = true;//game stat = loose
		if (hiScores->CheckScore(score, wall))
			state = BESTENDMENU;
		else
			state = ENDMENU;
	}
	ObjectType ret = Collide();
	if (ret == VOID)
		snk->Back();
	else
	{
		food->Collision(object);
		progress -= 5000;
		score += 1;
	}
	if (second)
	{
		snk = second->GetSnake();
		if (value >= UP && value <= RIGHT)
			snk->SetDirection(value);
		if (snk->Move(wall))
		{
		//shouldLeave = true;
			state = ENDMENU;
		}
		if (snk->IsColliding())
		{
		//shouldLeave = true;//game stat = loose
			state = ENDMENU;
		}
		ObjectType ret = Collide();
		if (ret == VOID)
			snk->Back();
		else
		{
			food->Collision(object);
			progress -= 1000;
			score += 1;
		}
	}
}

void	Game::UpdateMulti(eInput value)
{
	// char data[128] = {0};

	// while (1);
	// multi.Rcv(data);
	// std::cout << data << std::endl;
	Update(value);
	// multi.Send((void*)"COUCOU\n", 7);
}

void	Game::MultiMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == HOST)
			state = HOSTMENU;
		else if (entry == JOIN)
			state = JOINMENU;
		else if (entry == MMEXIT)
			shouldLeave = true;
		entry = 0;
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = SIZEMULTIMENUCHOICES - 1;
		else
			entry--;
	}
	else if (value == DOWN)
	{
		if (entry == SIZEMULTIMENUCHOICES - 1)
			entry = 0;
		else
			entry++;
	}
	else if (value == PAUSE)
	{
		shouldLeave = true;
		entry = 0;
	}
	gameData->SetChoice(entry);
}

void	Game::HostMenu(eInput value)
{
	char data[128];
	(void)value;
	if (!multi.IsConnect())
		multi.Host();
	else
	{
		state = MULTI;
		//multi.Send((void*)"HOST\n", 5);
		second = new Player(object, width, height, 2);

		auto start = *first->GetSnake()->GetSnake().begin();
		multi.Send((void *)(&start), sizeof(Point));

		multi.Rcv(data);

		auto dir = first->GetSnake()->GetDirection();
		multi.Send((void *)(&dir), sizeof(Point));

		multi.Rcv(data);

		start = *second->GetSnake()->GetSnake().begin();
		multi.Send((void *)(&start), sizeof(Point));

		multi.Rcv(data);

		dir = second->GetSnake()->GetDirection();
		multi.Send((void *)(&dir), sizeof(Point));

		multi.Rcv(data);

		multi.Send((void *) food, sizeof(Food));

		multi.Rcv(data);

		multi.Send((void *)&wall, sizeof(bool));

		multi.Rcv(data);
	}
}

void	Game::JoinMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (!multi.IsConnect())
			multi.Join(addr);
		if (multi.IsConnect())
		{
			object->clear();
			delete first;
			delete food;
			state = MULTI;
			char data[128];

			multi.Rcv(data);
			Point ori(*(Point *)data);

			multi.Send((void*)"done\n", 5);

			multi.Rcv(data);
			Point dir(*(Point *)data);
			first = new Player(object, width, height, ori, dir);

			multi.Send((void*)"done\n", 5);

			multi.Rcv(data);
			Point ori2(*(Point *)data);

			multi.Send((void*)"done\n", 5);

			multi.Rcv(data);
			Point dir2(*(Point *)data);
			second = new Player(object, width, height, ori2, dir2);

			multi.Send((void*)"done\n", 5);

			multi.Rcv(data);
			food = new Food(*(Food *)data);
			object->push_back(food);

			multi.Send((void*)"done\n", 5);

			multi.Rcv(data);
			wall = *(bool *)data;
			gameData->SetWall(wall);

			multi.Send((void*)"done\n", 5);
		}
	}
	else if (value == CHAR)
	{
		auto ch = gameData->GetChar();
		std::cout << (int)ch << std::endl;
		if (ch && ch == 127 && addr.size())
			addr.pop_back();
		else if (ch && ch != 127)
			addr.append(1, ch);
		gameData->SetIp(addr);
	}
	else if (value == PAUSE)
	{
		state = MAINMENU;
	}
}

void Game::MainMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == NEWGAME)
		{
			state = NM;
			entry = 0;
		}
		else if (entry == MULTIPLAYER)
		{
			state = MULTIMENU;
			entry = 0;
		}
		else if (entry == HISCORE)
		{
			state = HISCOREMENU;
			entry = 0;
		}
		else if (entry == WALL)
		{
			wall = !wall;
			gameData->SetWall(wall);
		}
		else if (entry == EXIT)
		{
			shouldLeave = true;
		}
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = SIZEMENUCHOICES -1;
		else
			entry--;
	}
	else if (value == DOWN)
	{
		if (entry == SIZEMENUCHOICES -1)
			entry = 0;
		else
			entry++;
	}
	else if (value == PAUSE)
		shouldLeave = true;
	gameData->SetChoice(entry);
}

void Game::PauseMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
			state = NM;
		else if (entry == 1)
		{
			Reset();
			state = NM;
		}
		else if (entry == 2)
			shouldLeave = true;
		// else if (entry == 3)
		// 	wall = !wall;
		entry = 0;
		gameData->SetChoice(0);
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBACTIONPAUSE -1;
		else
			entry--;
		gameData->SetChoice(entry);
	}
	else if (value == DOWN)
	{
		if (entry == NBACTIONPAUSE -1)
			entry = 0;
		else
			entry++;
		gameData->SetChoice(entry);
	}
	else if (value == PAUSE)
	{
		state = NM;
		entry = 0;
		gameData->SetChoice(0);
	}
}

void Game::BestEndMenu(eInput value)
{
	if (value == VALIDATE)
	{
		hiScores->SetScore(std::string(player), score, wall);
		gameData->SetChoice(0);
		entry = 0;
		state = ENDMENU;
	}
	else if (value == UP)
		player[entry]++;
	else if (value == DOWN)
		player[entry]--;
	else if (value == LEFT)
		entry = (entry - 1 >= 0 ? entry - 1 : entry - 1 + 3);
	else if (value == RIGHT)
		entry = (entry + 1) % 3;
	gameData->SetPlayer(player);
	gameData->SetChoice(entry);
}

void Game::EndMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == 0)
		{
			Reset();
			state = NM;
		}
		else if (entry == 1)
		{
			Reset();
			state = MAINMENU;
		}
		else if (entry == 2)
			shouldLeave = true;
		entry = 0;
		gameData->SetChoice(0);
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBACTIONEND - 1;
		else
			entry--;
		gameData->SetChoice(entry);
	}
	else if (value == DOWN)
	{
		if (entry == NBACTIONEND - 1)
			entry = 0;
		else
			entry++;
		gameData->SetChoice(entry);
	}
	else if (value == PAUSE)
	{
		shouldLeave = true;
	}
}

void	Game::HiScoreMenu(eInput value)
{
	if (value != NONE)
		state = MAINMENU;
}

void	Game::Launch()
{
	value = NONE;
	state = MAINMENU;
	score = 0;
	wall = true;
	music = new Sound(5);
	music->Play();
	gameData->SetScore(score);
	gameData->SetState(state);
	gameData->SetWall(wall);
	gameData->SetScore(hiScores);
	while (!shouldLeave)
	{
		timeval time;
		gettimeofday(&time, NULL);
		double start = time.tv_usec + time.tv_sec * 1000000;
		value = gameData->GetInput();
		if (value == F1)
		{
			delete gameData;
			lib->Close();
			delete lib;
			lib = new loader("ncurses/libcurses.so", width, height, object);
			gameData = lib->GetData();
			gameData->SetWall(wall);
			gameData->SetChoice(entry);
		}
		else if (value == F2)
		{
			delete gameData;
			lib->Close();
			delete lib;
			lib = new loader("sfml/libsfml.so", width, height, object);
			gameData = lib->GetData();
			gameData->SetWall(wall);
			gameData->SetChoice(entry);
		}
		else if (value == F3)
		{
			delete gameData;
			lib->Close();
			delete lib;
			lib = new loader("sdl/libsdl.so", width, height, object);
			gameData = lib->GetData();
			gameData->SetWall(wall);
			gameData->SetChoice(entry);
		}
		else if (state == NM)
			Update(value);
		else if (state == MULTI)
			UpdateMulti(value);
		else if (state == MULTIMENU)
			MultiMenu(value);
		else if (state == PAUSEMENU)
			PauseMenu(value);
		else if (state == MAINMENU)
			MainMenu(value);
		else if (state == ENDMENU)
			EndMenu(value);
		else if (state == HOSTMENU)
			HostMenu(value);
		else if (state == JOINMENU)
			JoinMenu(value);
		else if (state == BESTENDMENU)
			BestEndMenu(value);
		else if (state == HISCOREMENU)
			HiScoreMenu(value);
		gameData->SetScore(score);
		gameData->Draw();
		gameData->SetState(state);
		gettimeofday(&time, NULL);
		double end = (time.tv_usec + time.tv_sec * 1000000);
		double wait = start + progress - end;
		if (wait > 0)
			usleep((int)wait);
	}
	delete hiScores;
	delete music;
	delete gameData;
}

void Game::Logic()
{
	// value = NONE;
	// state = MAINMENU;
	// score = 0;
	// wall = true;
	// music = new Sound(5);
	// music->Play();
	// gameData->SetScore(score);
	// gameData->SetState(state);
	// gameData->SetWall(wall);
	// while (!shouldLeave)
	// {
	// 	timeval time;
	// 	gettimeofday(&time, NULL);
	// 	auto start = time.tv_usec;
	// 	value = gameData->GetInput();
	// 	if (value == F1 || value == F2 || value == F3)
	// 	{
	// 		gameData->Close();
	// 		libIsLoading.lock();
	// 		libIsLoading.unlock();
	// 	}
	// 	else if (state == NM)
	// 		Update(value);
	// 	else if (state == MULTIMENU)
	// 		MultiMenu(value);
	// 	else if (state == PAUSEMENU)
	// 		PauseMenu(value);
	// 	else if (state == MAINMENU)
	// 		MainMenu(value);
	// 	else if (state == ENDMENU)
	// 		EndMenu(value);
	// 	else if (state == HOSTMENU)
	// 		HostMenu(value);
	// 	else if (state == JOINMENU)
	// 		JoinMenu(value);
	// 	gameData->SetState(state);
	// 	gameData->SetScore(score);
	// 	gameData->Draw();
	// 	gameData->CleanInput();
	// 	gettimeofday(&time, NULL);
	// 	auto wait = start + progress - time.tv_usec;
	// 	if (state == NM && wait > 0)
	// 		usleep(wait);
	// }
	// delete music;
	// delete gameData;
}
