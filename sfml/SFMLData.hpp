#ifndef MLXDATA_HPP
#define MLXDATA_HPP

#include <Data.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define WIDTH		1920
#define HEIGHT		1080

class SFMLData : public Data
{
	typedef void (SFMLData::*Func)();
	typedef void (SFMLData::*Func2)(GameObject*);
public:
	SFMLData(int width, int height, std::list<GameObject*> *objects);
	void Draw();
	void Close();
	void Lock();
	eInput GetInput();
	void SetInput(int);
	~SFMLData();

private:

	void		DrawMainMenu();
	void		DrawPseudoMenu();
	void		DrawNormalMode();
	void		DrawMulti();
	void		DrawMultiMenu();
	void		DrawHostMenu();
	void		DrawJoinMenu();
	void		DrawPauseMenu();
	void		DrawEndMenu();
	void		DrawSnake(GameObject*);
	void		DrawFood(GameObject*);
	int			width;
	int			height;
	int			x0;
	int			y0;
	Func		funcs[9];
	Func2		funcs2[2];
	sf::RenderWindow	*win;
	sf::Font 			*font;
	sf::Texture			*texture;
	sf::RectangleShape	*background;
	//sf::Sprite			*sprite;
	//SFML_Surface	*screenSurface;
};

#endif
