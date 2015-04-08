#include "Score.hpp"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

Score::Score()
{
	char buff[128];
	std::ifstream fs ("score");
	fs.getline(buff, 128);
	auto i = 0;
	std::string title(buff);
	if (title == "wall")
	{
		fs.getline(buff, 128);
		title = std::string(buff);
		while (!fs.eof() && fs.good() && i < 5 && title != "nowall")
		{
			std::string pseudo(buff, 3);
			int score;
			score = atoi(buff + 4);
			wallScores[i] = std::pair<std::string, int>(pseudo, score);
			i++;
			fs.getline(buff, 128);
			title = std::string(buff);
		}
	}
	while (i < 5)
	{
		wallScores[i] = std::pair<std::string, int>("AAA", 0);
		i++;
	}
	i = 0;
	if (title == "nowall")
	{
		fs.getline(buff, 128);
		while (!fs.eof() && fs.good() && i < 5)
		{
			std::string pseudo(buff, 3);
			int score;
			score = atoi(buff + 4);
			noWallScores[i] = std::pair<std::string, int>(pseudo, score);
			i++;
			fs.getline(buff, 128);
		}
	}
	while (i < 5)
	{
		noWallScores[i] = std::pair<std::string, int>("AAA", 0);
		i++;
	}
}

Score::Score(Score const & src)
{
	(void)src;
}

Score& Score::operator=(Score const & rhs)
{
	(void)rhs;
	return *this;
}

bool Score::CheckScore(int score, bool wall)
{
	int i = 0;
	while (i < 5 && score < (wall ? std::get<1>(wallScores[i]) : std::get<1>(noWallScores[i])))
		i++;
	if (i < 5)
		return true;
	return false;
}

void Score::SetScore(std::string pseudo, int score, bool wall)
{
	int i = 0;
	while (i < 5 && score < (wall ? std::get<1>(wallScores[i]) : std::get<1>(noWallScores[i])))
		i++;
	if (i < 5)
	{
		auto tmp = (wall ? wallScores[i] : noWallScores[i]);
		(wall ? wallScores[i] : noWallScores[i]) = std::pair<std::string, int>(pseudo, score);
		i++;
		while (i < 5)
		{
			// std::cout << "score[" << i << "]<" << std::get<0>(scores[i]) << ", " << std::get<1>(scores[i]) << ">" << std::endl;
			auto tmp2 = tmp;
			// std::cout << "tmp2 = <" << std::get<0>(tmp2) << ", " << std::get<1>(tmp2) << ">" << std::endl;
			tmp = (wall ? wallScores[i] : noWallScores[i]);
			// std::cout << "tmp = <" << std::get<0>(tmp) << ", " << std::get<1>(tmp) << ">, score[" << i << "]<" << std::get<0>(scores[i]) << ", " << std::get<1>(scores[i]) << ">" << std::endl;
			// sleep(1);
			(wall ? wallScores[i] : noWallScores[i]) = tmp2;
			i++;
		}
	}
}

const char *Score::GetPseudo(int num, bool wall)
{
 	return std::get<0>((wall ? wallScores[num] : noWallScores[num])).c_str();
}

int Score::GetScore(int num, bool wall)
{
	return std::get<1>((wall ? wallScores[num] : noWallScores[num]));
}

Score::~Score()
{
	std::ofstream fs ("score");
	fs << "wall" << std::endl;
	int i = 0;
	while (std::get<1>(wallScores[i]) && i < 5)
	{
		fs << std::get<0>(wallScores[i]) << ":" << std::get<1>(wallScores[i]) << std::endl;
		i++;
	}
	fs << "nowall" << std::endl;
	while (std::get<1>(noWallScores[i]) && i < 5)
	{
		fs << std::get<0>(noWallScores[i]) << ":" << std::get<1>(noWallScores[i]) << std::endl;
		i++;
	}
}

