#ifndef SCORE_HPP
#define SCORE_HPP

#include <utility>
#include <string>

class Score
{
public:
	Score();
	Score(Score const & src);
	Score& operator=(Score const & rhs);
	bool CheckScore(int, bool);
	void SetScore(std::string, int, bool);
	const char *GetPseudo(int, bool);
	int GetScore(int, bool);
	~Score();

private:
	std::pair<std::string, int> wallScores[5];
	std::pair<std::string, int> noWallScores[5];

};

#endif
