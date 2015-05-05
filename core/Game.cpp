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
	powerUp = new PowerUp(width, height);
	obstacle = new Obstacle(width, height);
	object->push_back(food);
	object->push_back(powerUp);
	object->push_back(obstacle);
	shouldLeave = false;
	progress = 100000;
	entry = 0;
	addr = "127.0.0.1";
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
	delete powerUp;
	first = new Player(object, width, height, 1);
	powerUp = new PowerUp(width, height);
	food = new Food(width, height);
	object->push_back(food);
	object->push_back(powerUp);
	object->push_back(obstacle);
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
		if ((*first)->GetPosition() == (*current)->GetPosition() && (*current)->IsActivate())
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
	if (!(rand() % 30) && !powerUp->IsActivate())
		powerUp->Activate();
	Snake *snk = first->GetSnake();
	if (value >= UP && value <= RIGHT)
		snk->SetDirection(value);
	if (snk->Move(wall))
	{
		//shouldLeave = true;
		if (hiScores->CheckScore(score, wall))
			state = BESTENDMENU;
		else
			state = ENDMENU;
	}
	if (snk->IsColliding())
	{
		if (hiScores->CheckScore(score, wall))
			state = BESTENDMENU;
		else
			state = ENDMENU;
	}
	ObjectType ret = Collide();
	if (ret == VOID)
		snk->Back();
	else if (ret == FOOD)
	{
		food->Collision(object);
		progress -= 5000;
		score += 1;
	}
	else if (ret == OBSTACLE)
	{
		if (hiScores->CheckScore(score, wall))
			state = BESTENDMENU;
		else
			state = ENDMENU;
	}
	else
	{
		powerUp->Collision(object);
		score += 5;
	}
}

int		Game::CollideMulti()
{
	Point foodPosition = food->GetPosition();
	Point firstPosition = first->GetSnake()->GetPosition();
	Point secondPosition = second->GetSnake()->GetPosition();
	int ret = 0;
	if (foodPosition == firstPosition)
		ret += 1;
	if (foodPosition == secondPosition)
		ret += 2;
	return ret;
}

void	Game::UpdateMulti(eInput value)
{
	char data[128] = {0};

	if (isHost)
	{
		try
		{
			multi.Rcv(data, sizeof(eInput));
		}
		catch (std::exception *e)
		{
			state = ENDMENU;
			Reset();
			return ;
		}
		eInput value2 = (eInput)*data;
		Snake *snk = first->GetSnake();
		Snake *snk2 = second->GetSnake();
		if (value >= UP && value <= RIGHT)
			snk->SetDirection(value);
		if (value2 >= UP && value2 <= RIGHT)
			snk2->SetDirection(value2);

		if (snk2->Move(wall) || snk->Move(wall) || snk2->IsColliding() || snk->IsColliding())
		{
			multi.Disconnect();
			Reset();
			state = MAINMENU;
			return;
		}
		int ret = CollideMulti();
		if (ret == 0)
		{
			snk->Back();
			snk2->Back();
		}
		else if (ret == 1)
		{
			snk2->Back();
			food->Collision(object);
			progress -= 5000;
			score += 1;
		}
		else if (ret == 2)
		{
			snk->Back();
			food->Collision(object);
			progress -= 5000;
			score += 1;
		}
		else
		{
			food->Collision(object);
			progress -= 5000;
			score += 1;
		}




		DataEx seri;
		auto serialize = seri.Serialize(snk, snk2, food);
		multi.Send((void*)&serialize, sizeof(Serializer));
	}
	else
	{
		multi.Send((void*)&value, sizeof(eInput));
		if (value == PAUSE)
		{
			multi.Disconnect();
			Reset();
			state = MAINMENU;
			return;
		}
		DataEx unseri;
		try
		{
			auto tmp = multi.Rcv();
		}
		catch (std::exception *e)
		{
			state = ENDMENU;
			Reset();
			return ;
		}
		unseri.UnSerialize(tmp);
		first->SetSnake(unseri.GetSnake());
		second->SetSnake(unseri.GetSecondSnake());
		object->remove(food);
		delete food;
		food = unseri.GetFood();
		object->push_front(food);

	}
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
			state = MAINMENU;
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
		state = MAINMENU;
		entry = 0;
	}
	gameData->SetChoice(entry);
}

void	Game::HostMenu(eInput value)
{
	//char data[128];
	isHost = true;
	if (value == PAUSE)
	{
		state = MAINMENU;
		return ;
	}
	if (!multi.IsConnect())
		multi.Host();
	if (multi.IsConnect())
	{
		state = MULTI;
		second = new Player(object, width, height, 2);
		multi.Send((void *)&wall, sizeof(bool));
	}
}

void	Game::JoinMenu(eInput value)
{
	char data[128] = {0};
	if (value == VALIDATE)
	{
		if (!multi.IsConnect())
			multi.Join(addr);
		if (multi.IsConnect())
		{
			object->clear();
			second = new Player(object, width, height, 2);
			state = MULTI;
			try
			{
					if (!multi.Rcv(data, sizeof(bool)))
						state = MAINMENU;
			}
			catch(std::exception *e)
			{

			}
			wall = *(bool *)data;
			gameData->SetWall(wall);
		}
	}
	else if (value == CHAR)
	{
		auto ch = gameData->GetChar();
		// std::cout << (int)ch << std::endl;
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
			if (multi.IsConnect())
				multi.Disconnect();
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
	loader charge(5);
	music = charge.GetMusic();
	music->Play();

	gameData->SetWall(wall);
	gameData->SetScore(score);
	gameData->SetState(state);
	gameData->SetScore(hiScores);
	gameData->SetIpInfo(multi.GetMyAccessPoint());
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
			gameData->SetState(state);
			gameData->SetIpInfo(multi.GetMyAccessPoint());
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
			gameData->SetState(state);
			gameData->SetIpInfo(multi.GetMyAccessPoint());
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
			gameData->SetState(state);
			gameData->SetIpInfo(multi.GetMyAccessPoint());
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
		gameData->SetState(state);
		gameData->Draw();
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
