#pragma once
#include "przeszkody.h"
using namespace std;
using namespace sf;
class cTir
{
public:
	cTir(Vector2f position)
	{
		makeTir(position);
		
	}
	~cTir()
	{

	}
	void draw(RenderWindow &w)
	{
		w.draw(s);
	}
	void animate()
	{
		srand(time(NULL));
		randomizer = rand() % 10 + 1;
		if (czyMoznaZanimowac)
		{
			switch (randomizer)
			{
			case 1:
			{
				s.rotate(45);
				setVelocity(2, -2);
				czyMoznaZanimowac = false;
				break;
			}
			case 2:
			{
				s.rotate(-45);
				setVelocity(-2, -2);
				czyMoznaZanimowac = false;
				break;
			}
			}
		}
		s.move(velocity);

	}
	bool czyUsunac()
	{
		if (s.getPosition().x > 650 || s.getPosition().x < 150) return true;
		else return false;
	}
	Sprite getTir()
	{
		return s;
	}
	void setVelocity(float x, float y)
	{
		velocity.x = x;
		velocity.y = y;
	}
private:
	void makeTir(Vector2f position)
	{
		t2.loadFromFile("grafiki/enemy2.png");
		
		s.setTexture(t2);
		s.setOrigin(t2.getSize().x / 2, t2.getSize().y / 2);
		s.setScale(3, 3);
		s.setPosition(position);
		velocity = Vector2f(0, -2);
	}
	Texture t2;
	Sprite s;
	Vector2f velocity;
	int randomizer;
	bool czyMoznaZanimowac = true;
};



