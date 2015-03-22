#include "Game.hpp"
#include "unistd.h"
#include <ctime>
#include <sys/time.h>
#include <netdb.h>

typedef struct protoent		t_protoent;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;
typedef struct hostent		t_hostent;
typedef struct in_addr		t_in_addr;

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
	this->width = width;
	this->height = height;
	object = obj;
	gameData = data;
	this->lib = lib;
	first = new Player(object, width, height);
	food = new Food(width, height);
	object->push_back(food);
	shouldLeave = false;
	progress = 200000;
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
	//progress = 200000;
	object->erase(object->begin(), object->end());
	delete first;
	delete food;
	first = new Player(object, width, height);
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
		food->Collision();
		progress -= 1000;
		score += 1;
	}
}

void	Game::UpdateMulti(eInput value)
{
	(void)value;
}

void	Game::MultiMenu(eInput value)
{
	if (value == VALIDATE)
	{
		if (entry == NEWGAME)
			state = HOSTMENU;
		else if (entry == MULTIPLAYER)
			state = JOINMENU;
		else if (entry == EXIT)
			shouldLeave = true;
	}
	else if (value == UP)
	{
		if (entry == 0)
			entry = NBACTIONMULTIMENU - 1;
		else
			entry--;
	}
	else if (value == DOWN)
	{
		if (entry == NBACTIONMULTIMENU - 1)
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
	t_protoent		*prot;
	t_sockaddr_in	sin;
	int				sock;
	(void)value;
	if (!(prot = getprotobyname("tcp")))
		perror("getprotobyname");
	if ((sock = socket(PF_INET, SOCK_STREAM, prot->p_proto)) == -1)
		perror("socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(6666);
	if (bind(sock, (t_sockaddr*)&sin, sizeof(sin)) == -1)
		perror("bind");
	if (listen(sock, 5) == -1)
		perror("listen");
}

void	Game::JoinMenu(eInput value)
{
	int sock;
	(void) value;
	t_sockaddr_in	sin;
	t_protoent	*proto;
	if ((proto = getprotobyname("tcp")) == NULL)
		perror("prot");
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		perror("sock");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(6666);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (connect(sock, (t_sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cout << "fail" << std::endl;
		perror("conn");
		exit(-1);
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
			entry = NBMODE -1;
		else
			entry--;
	}
	else if (value == DOWN)
	{
		if (entry == NBMODE -1)
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

void	Game::Launch()
{
	core = std::thread(&Game::Logic, this);
	while (!shouldLeave)
	{
		if (value == F1)
		{
			lib->Close();
			delete gameData;
			delete lib;
			lib = new loader("ncurses/libcurses.so", width, height, object);
			gameData = lib->GetData();
		}
		else if (value == F2)
		{
			lib->Close();
			delete gameData;
			delete lib;
			lib = new loader("mlx/libmlx.so", width, height, object);
			gameData = lib->GetData();
		}
		else if (value == F3)
		{
			gameData->Close();
			lib->Close();
			delete gameData;
			delete lib;
			lib = new loader("libcurses.so", width, height, object);
			gameData = lib->GetData();
		}
		libIsLoading.unlock();
		libIsLoading.lock();
		gameData->Start();
	}
}

void Game::Logic()
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
	while (!shouldLeave)
	{
		timeval time;
		gettimeofday(&time, NULL);
		auto start = time.tv_usec;
		value = gameData->GetInput();
		if (value == F1 || value == F2 || value == F3)
		{
			gameData->Close();
			libIsLoading.lock();
			libIsLoading.unlock();
		}
		else if (state == NM)
			Update(value);
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
		gameData->SetState(state);
		gameData->SetScore(score);
		gameData->Draw();
		gameData->CleanInput();
		gettimeofday(&time, NULL);
		auto wait = start + progress - time.tv_usec;
		if (wait > 0)
			usleep(wait);
	}
	delete music;
	delete gameData;
	exit(0);
}
