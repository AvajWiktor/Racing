#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
using namespace std;
using namespace sf;




class cPlayer
{
public:
	cPlayer(Vector2f pos, string dir, int typ) 
	{
		_type = typ;
		makePlayer(pos,dir);
	}
	~cPlayer() {}
	void move(float x, float y)
	{
		_car.move(x,y);
	}
	Vector2f getVelocity()
	{
		return _velocity;
	}
	Vector2f getPosition()
	{
		return _car.getPosition();
	}
	void animate(RenderWindow &w ) 
	{
		if (_Timer)
		{
			_boostTimer++;
		}
		switch (_type)
		{
			case 1:
			{
				if (Keyboard::isKeyPressed(Keyboard::A))
				{
					_car.setTexture(_carRight);
					setVelocity(-1.0);
				}
				else if (Keyboard::isKeyPressed(Keyboard::D))
				{
					_car.setTexture(_carLeft);
					setVelocity(1.0);
				}
				else
				{
					_car.setTexture(_carStraight);
					setVelocity(0.0);
				}
				if (Keyboard::isKeyPressed(Keyboard::S))
				{
					if (_velocity.y < 2.0)
					{
						_velocity.y += 0.1;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::W))
				{
					if (_velocity.y > 0.0)
					{
						_velocity.y -= 0.1;
					}
				}
				else
				{
					if (_velocity.y > 1.0)
					{
						_velocity.y -= 0.1;
					}
				}
				break;
			}
			case 2:
			{
				if (Keyboard::isKeyPressed(Keyboard::Left))
				{
					_car.setTexture(_carRight);
					setVelocity(-1.0);
				}
				else if (Keyboard::isKeyPressed(Keyboard::Right))
				{
					_car.setTexture(_carLeft);
					setVelocity(1.0);
				}
				else
				{
					_car.setTexture(_carStraight);
					setVelocity(0.0);
				}
				if (Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (_velocity.y < 2.0)
					{
						_velocity.y += 0.1;
					}
				}
				else if (Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (_velocity.y > 0.0)
					{
						_velocity.y -= 0.1;
					}
				}
				else
				{
					if (_velocity.y > 1.0)
					{
						_velocity.y -= 0.1;
					}
				}
				break;
			}
		}
		
		move();
		draw(w);
		if (_boostTimer == 60)
		{
			_boostTimer = 0;
			_Timer = false;
			_velocity.y = 1;
		}
	}
	bool collision(Sprite s)
	{
		if (_car.getGlobalBounds().intersects(s.getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool collision(cPlayer s)
	{
		if (_car.getGlobalBounds().intersects(s.getCar().getGlobalBounds()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void collisiontWithPlayer( cPlayer &p)
	{
		bool b = collision(p);
		Vector2f v = p.getVelocity();
		Vector2f pos = p.getPosition();
		if (b)
		{
			if (v.x < 0)
			{
				_car.move(-3, 0);
				p.move(3,0);
			}
			if (v.x > 0)
			{
				_car.move(3, 0);
				p.move(-3, 0);
			}
			if (pos.y < _car.getPosition().y)
			{
				_car.move(0, 3);
				p.move(0, -3);
			}
			if (pos.y > _car.getPosition().y)
			{
				_car.move(0, -3);
				p.move(0, 3);
			}
		}
		
	}
	void setVelocity(float x, float y)
	{
		_velocity.x = x;
		_velocity.y = y;
	}
	void setBoost()
	{
		_velocity.y = 4;
		_Timer = true;
	}
	void setDeBoost()
	{
		_velocity.y = 0;
		_Timer = true;
	}
private:
	Sprite getCar()
	{
		return _car;
	}
	void draw(RenderWindow &w)
	{
		w.draw(_car);
	}
	void move()
	{
		if (_car.getPosition().x > 175 && _car.getPosition().x < 625) 
		{
			_car.move(_velocity);
		}
		else if(_car.getPosition().x>=625)
		{
			
			_car.move(-5,_velocity.y);
		}
		else if (_car.getPosition().x <= 175)
		{
			_car.move(5, _velocity.y);
		}
	}
	
	void setVelocity(float vx)
	{
		_velocity = Vector2f(vx*_wsp,_velocity.y);
	}
	void setReverseVelocity()
	{

		_velocity = Vector2f(-_velocity.x*_wsp, _velocity.y);
	}
	void setReverseVelocityPlus()
	{
		_velocity = Vector2f(-_velocity.x*_wsp, -_velocity.y);
	}
	void makePlayer(Vector2f position, string dir)
	{
		switch (_type)
		{
			case 1:
			{
				string direction = dir;
				direction += "1.png";
				_carLeft.loadFromFile(direction);
				direction = dir;
				direction += "2.png";
				_carStraight.loadFromFile(direction);
				direction = dir;
				direction += "3.png";
				_carRight.loadFromFile(direction);
				break;
			}
			case 2:
			{
				string direction = dir;
				direction += "4.png";
				_carLeft.loadFromFile(direction);
				direction = dir;
				direction += "5.png";
				_carStraight.loadFromFile(direction);
				direction = dir;
				direction += "6.png";
				_carRight.loadFromFile(direction);
				break;
			}
		}
		_car.setTexture(_carStraight);
		_car.setOrigin(_carStraight.getSize().x / 2, _carStraight.getSize().y / 2);
		_car.setScale(1, 1);
		_car.setPosition(position);
	}
	Vector2f _velocity = Vector2f(0.0,1.0);
	Texture _carLeft, _carStraight,_carRight;
	Sprite _car;
	int _type;
	float _wsp = 2.0;
	bool _Timer = false;
	int _boostTimer = 0;

};
















