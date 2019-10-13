#pragma once
#include "postacie.h"
#include <ctime>
#include <cstdlib>
using namespace sf;
using namespace std;

class cTraps
{
public:
	cTraps(Vector2f position, int typ)
	{
		makeTrap(position, typ);
	}
	~cTraps()
	{

	}
	void makeEffect(cPlayer &p)
	{
		
		if (p.collision(this->p))
		{
			
			switch (typ)
			{
			case 1:
			{
				srand(time(NULL));
				float x = (rand() % 5) - 2;
				float y = rand() % 2;
				cout << x << ", " << y << endl;
				p.move(x,y);
				break;
			}
			case 2:
			{
				p.setVelocity(0, 0.2);
				break;
			}
			case 3:
			{
				p.setBoost();
				break;
			}
			}
		}
	}
	void draw(sf::RenderWindow &w)
	{
		w.draw(p);
	}
	Vector2f getPosition()
	{
		return p.getPosition();
	}
private:
	void makeTrap(Vector2f position, int typ)
	{
			string direction;
			this->typ = typ;
			if (typ == 1)
			{
				 direction = "grafiki/trap1.png";
			}
			else if (typ == 2)
			{
				 direction = "grafiki/trap2.png";
			}
			else if (typ == 3)
			{
				direction = "grafiki/booster.png";
			}
			
			
			
			t.loadFromFile(direction);
			
		
		
		
		p.setTexture(t);
		p.setOrigin(t.getSize().x / 2, t.getSize().y / 2);
		p.setScale(3, 3);
		p.setPosition(position);
	}

	Sprite p;
	Texture t;
	int typ;
};



