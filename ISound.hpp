#ifndef ISOUND_HPP
#define ISOUND_HPP

class ISound
{
public:
	virtual bool Play() = 0;
	virtual bool Stop() = 0;

	virtual ~ISound(){};
};

#endif
