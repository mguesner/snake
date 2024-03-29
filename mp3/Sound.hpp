#ifndef SOUND_HPP
# define SOUND_HPP

#include <unistd.h>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include "../ISound.hpp"

class Sound : public  ISound
{
public:
	Sound(int);
	Sound(Sound const & src);
	Sound& operator=(Sound const & rhs);
	bool Play();
	bool Stop();
	~Sound();
private:
	Sound();
	int 	willPlay;
	pid_t son;

};

#endif
