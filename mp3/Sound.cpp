#include "Sound.hpp"

extern "C" Sound	*dynamic_sound(int music)
{
	return new Sound(music);
}

Sound::Sound()
{

}

Sound::Sound(int i)
{
	willPlay = i;

}

Sound::Sound(Sound const & src)
{
	willPlay = src.willPlay;
	son = src.son;
}

Sound& Sound::operator=(Sound const & src)
{
	willPlay = src.willPlay;
	son = src.son;
	return *this;
}

bool Sound::Play()
{
	son = fork();
	if (son == 0)
	{
		if (willPlay == 5)
			execl("/usr/bin/afplay", "afplay", "mp3/Diablo.mp3", (char *) 0);
		execl("/usr/bin/afplay", "afplay", "mp3/test.mp3", (char *) 0);
		perror("failed music");
		exit(0);
	}
	return true;
}

bool Sound::Stop()
{
	if (!kill(son, SIGTERM))
		return true;
	else if (!kill(son, SIGKILL))
		return true;
	return false;
}

Sound::~Sound()
{
	Stop();
}
