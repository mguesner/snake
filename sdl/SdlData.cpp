#include "SdlData.hpp"


SdlData::SdlData(int width, int height, std::list<GameObject*> *objects)
{
	this->width = width;
	this->height = height;
	this->objects = objects;
	//win = new Windows(this);
	SDL_Window      *win;
    SDL_Event       event;
    SDL_Texture     *tex;
    SDL_Renderer    *rd;
    SDL_Point       *p;
	Uint32				*texturebuf;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINX, WINY, SDL_WINDOW_SHOWN, &win, &rd);
    tex = SDL_CreateTexture(rd, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_STREAMING, WINX, WINY);
    if (win == NULL)
        //aillle
    
	SDL_PollEvent(&event);
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyWindow(win);
		SDL_Quit();
		exit(0);
	}
	SDL_UpdateTexture(tex, NULL, texturebuf, WINX * sizeof(Uint32));
	SDL_RenderCopy(rd, tex, NULL, NULL);
	SDL_RenderPresent(rd);

	value = NONE;
	inputs[13] = UP;
	inputs[1] = DOWN;
	inputs[0] = LEFT;
	inputs[2] = RIGHT;
	inputs[35] = PAUSE;
	inputs[54] = UP;
	inputs[125] = DOWN;
	inputs[54] = LEFT;
	inputs[54] = RIGHT;
	inputs[53] = PAUSE;
	inputs[18] = F1;
	inputs[20] = F3;
	inputs[36] = VALIDATE;
	shouldDraw = false;
	closeIsCall = false;
	locker.lock();
}

void MLXData::Start()
{
	win->Run();
}

void MLXData::Draw()
{
	shouldDraw = true;
}

void MLXData::Lock()
{

}

void MLXData::SetInput(int keycode)
{
	std::cout << keycode << std::endl;
	value = inputs[keycode];
}

eInput MLXData::GetInput()
{
	return value;
}

MLXData::~MLXData()
{
	delete win;
}
