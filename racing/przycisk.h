#pragma once
#include "postacie.h"
using namespace sf;
using namespace std;
class cButton
{
public:
	cButton(Vector2f position, string dir, int typ)
	{
		makeButton(position, dir, typ);
	}
	~cButton() {}
	
	void animate(RenderWindow &w, bool &start, bool &menu, int &tryb ) 
	{
		if (_button.getGlobalBounds().contains(Vector2f(Mouse::getPosition(w))))
		{
			_button.setTexture(_buttonPressed);
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (_type == 1)
				{
				
				menu = false;
				start = true;
				tryb = 1;
				}
				else if (_type == 2)
				{
					menu = false;
					start = true;
					tryb = 2;
				}
			}
		}
		else
		{
			_button.setTexture(_buttonUnPressed);
		}
		
		draw(w);
	}
private:
	void draw(RenderWindow &w)
	{
		w.draw(_button);
	}
	void makeButton(Vector2f position, string dir, int typ) 
	{
		_type = typ;
		string direction = dir;
		direction += "1.png";
		_buttonPressed.loadFromFile(direction);
		direction = dir;
		direction += "2.png";
		_buttonUnPressed.loadFromFile(direction);
		_button.setTexture(_buttonUnPressed);
		_button.setOrigin(_buttonPressed.getSize().x/2, _buttonPressed.getSize().y / 2);
		_button.setScale(1,1);
		_button.setPosition(position);
	}

	Texture _buttonPressed,_buttonUnPressed;
	Sprite _button;
	int _type;

};

