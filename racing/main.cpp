#include "postacie.h"
#include "ekran.h"
#include "fstream"
#include "przycisk.h"
#include "przeszkody.h"
#include "przeciwnicy.h"

using namespace sf;
using namespace std;
bool z = true;
bool isStart = false;
int tryb = 0;
bool isMenu = true;
bool isMeta = false;
int firstPlayer,secondPlayer;
int timer=0;
Sprite meta,win;
Texture metaTex,winTex;
Vector2f mousePos;
vector<cButton*> buttons;
vector<cPlayer*> players;
list<cTraps*> traps;
list<cTir*> tirs;
RenderWindow window(sf::VideoMode(800, 600), "My window");
View widok(FloatRect(0, 0, 800, 600));
void handleTryb()
{
	if (tryb == 1 && z )
	{
		players.pop_back();
		z = false;
	}
}
void makeMenu() 
{
	cButton *t1 = new cButton(Vector2f(400,300),"grafiki/sp",1);
	buttons.push_back(t1);
	cButton *t2 = new cButton(Vector2f(400, 400), "grafiki/mp", 2);
	buttons.push_back(t2);
}
void addPlayers()
{
	cPlayer *t1 = new cPlayer(Vector2f(250, 300), "grafiki/car",1);
	players.push_back(t1);
	cPlayer *t2 = new cPlayer(Vector2f(550, 300), "grafiki/car", 2);
	players.push_back(t2);
}
void drawMenu() 
{
	if (isMenu) 
	{
		for (auto itr = buttons.begin(); itr != buttons.end(); itr++)
		{
			(*itr)->animate(window,isStart,isMenu, tryb);
		}
	}
}
void drawPlayers() 
{
	if (isStart)
	{
		for (auto itr = players.begin(); itr !=players.end(); itr++)
		{
			(*itr)->animate(window);
		}
	}
}
void handleDisplaying()
{
	if(tryb == 1)
	{
		firstPlayer = 1;
		
		float p1 = players[0]->getPosition().y;
		widok.setCenter(400, players[0]->getPosition().y);
	}
	else
	{
		float p1 = players[0]->getPosition().y;
		float p2 = players[1]->getPosition().y;

		if (p1 > p2)
		{
			firstPlayer = 1;
			secondPlayer = 2;
			widok.setCenter(400, players[0]->getPosition().y);
		}
		else
		{
			firstPlayer = 2;
			secondPlayer = 1;
			widok.setCenter(400, players[1]->getPosition().y);
		}
		if (players[firstPlayer - 1]->getPosition().y - players[secondPlayer - 1]->getPosition().y > 400)
		{
			isMeta = true;

		}
	}
	if (players[firstPlayer - 1]->collision(meta))
	{
		isMeta = true;
	}
}
void handlePlayers()
{
	if (tryb == 1) {}
	else
	{
		players[0]->collisiontWithPlayer((*players[1]));
		players[1]->collisiontWithPlayer((*players[0]));
	}
}
void makeTraps()
{
	if (tryb == 1)
	{
		if (timer == 1)
		{
			Vector2f p = players[firstPlayer - 1]->getPosition();
			cTir *t1 = new cTir(Vector2f(p.x, p.y + 400));
			tirs.push_back(t1);
		}
		if (timer == 300)
		{


			Vector2f p = players[firstPlayer - 1]->getPosition();
			cTraps *t1 = new cTraps(Vector2f(((rand() % 5) + 2) * 100, p.y + ((rand() % 4) + 1) * 100), (rand() % 2) + 1);
			traps.push_back(t1);
		}
		if (timer == 300)
		{


			Vector2f p = players[firstPlayer - 1]->getPosition();
			cTraps *t1 = new cTraps(Vector2f(p.x, p.y + ((rand() % 2) + 1) * 100), 3);
			traps.push_back(t1);
		}
	}
	else
	{
		if (timer == 1)
		{
			Vector2f p = players[secondPlayer - 1]->getPosition();
			cTir *t1 = new cTir(Vector2f(p.x, p.y + 400));
			tirs.push_back(t1);
		}
		if (timer == 300)
		{


			Vector2f p = players[firstPlayer - 1]->getPosition();
			cTraps *t1 = new cTraps(Vector2f(p.x, p.y + 200), (rand() % 2) + 1);
			traps.push_back(t1);
		}
		if (timer == 300)
		{


			Vector2f p = players[secondPlayer - 1]->getPosition();
			cTraps *t1 = new cTraps(Vector2f(p.x, p.y + 200), 3);
			traps.push_back(t1);
		}
	}
}
void drawTraps()
{
	
	for (auto i = traps.begin(); i != traps.end(); )
	{

		(*i)->draw(window);
		if (players[firstPlayer - 1]->getPosition().y - (*i)->getPosition().y > 600)
		{
			i = traps.erase(i);
		}
		else i++;
	}
	for (auto i = tirs.begin(); i != tirs.end(); )
	{
		(*i)->animate();
		(*i)->draw(window);
		if ((*i)->czyUsunac())
		{
			i = tirs.erase(i);
		}
		else i++;
	}
}
void handleTraps()
{
	if(tryb == 1)
	{ 
		for (auto i = traps.begin(); i != traps.end(); i++)
		{
			(*i)->makeEffect(*players[0]);
			
		}
		for (auto i = tirs.begin(); i != tirs.end(); i++)
		{
			if (players[0]->collision((*i)->getTir()))
			{
				players[0]->setDeBoost();

			}
			
		}
	}
	else
	{
		for (auto i = traps.begin(); i != traps.end(); i++)
		{
			(*i)->makeEffect(*players[0]);
			(*i)->makeEffect(*players[1]);
		}
		for (auto i = tirs.begin(); i != tirs.end(); i++)
		{
			if (players[0]->collision((*i)->getTir()))
			{
				players[0]->setDeBoost();

			}
			if (players[1]->collision((*i)->getTir()))
			{
				players[1]->setDeBoost();

			}
		}
	}
}
void endGame()
{
	widok.setCenter(400, meta.getPosition().y);
	if (firstPlayer == 1)
	{
		winTex.loadFromFile("grafiki/P1WIN.png");
	}
	else
	{
		winTex.loadFromFile("grafiki/P2WIN.png");
	}
	win.setTexture(winTex);
	win.setOrigin(winTex.getSize().x / 2, winTex.getSize().y / 2);
	win.setScale(5, 3);
	win.setPosition(400, 14900);

	window.draw(win);
}

int main()
{
	
	metaTex.loadFromFile("grafiki/meta.png");
	meta.setTexture(metaTex);
	meta.setOrigin(metaTex.getSize().x / 2, metaTex.getSize().y / 2);
	meta.setScale(4.45, 3);
	meta.setPosition(400, 15000);
	srand(time(NULL));
	Texture tlo_gry;
	tlo_gry.loadFromFile("grafiki/road.png");
	tlo_gry.setRepeated(true);
	Sprite tlo_1(tlo_gry);
	tlo_1.setScale(800.0 / 605.0, 1.0);
	tlo_1.setTextureRect(IntRect(0, 0, 800, 16000));
	
//zmienne
    
	Event event;
	window.setFramerateLimit(60);
    Clock clock;

	makeMenu();
	addPlayers();
  
    //postacie





	while (window.isOpen()) 
	{
		handleTryb();
		timer++;
		
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

		}

		mousePos = Vector2f(Mouse::getPosition(window));
		float delta = float(clock.getElapsedTime().asSeconds());
		clock.restart();



		window.clear(sf::Color::White);
		
		window.setView(widok);
		window.draw(tlo_1);
		window.draw(meta);
		if (isMeta)
		{
			endGame();
		}
		else if (!isMeta)
		{
			
				
			handlePlayers();
			
			handleDisplaying();
			makeTraps();
			drawMenu();
			drawTraps();
			
			handleTraps();
			drawPlayers();







		}
		
		window.display();
		if (timer == 300)
		{
			timer = 0;
		}
	}
    return 0;
}

