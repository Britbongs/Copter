#pragma once 

#include <iostream> 
#include <vector>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>

#include "State.h"
#include "..\Utils\TextureManager.h"
#include "..\GameObject\GameObject.h"
#include "..\Entities\Player.h"
#include "..\Map\Map.h"

using namespace std;

class PlayState :
	public State
{
public:
	PlayState(sf::RenderWindow*, sf::RenderTexture*);
	~PlayState();
	bool init() override;
	void draw() const override;
	void update(float delta) override;
	void handleEvent(const sf::Event& evnt) override;
	void handleInput(float delta) override;
	int nextStateID() const override { return Menu; }

private:
	void initViewPosition();
	void translateView(float delta);

	void updatePlaying(float delta);
	void updatePaused(float delta);
	void updateDeathScreen(float delta);
	
	void drawPauseScreen()const;
	void drawDeathScreen() const;

	void resetGame();
private:
	TextureManager* p_texMngr_;
	vector<GameObject*> p_objects_;
	Player player_;
	Map map_;
	sf::Font font_;
	sf::Text pauseText_;
	sf::Text deathText_; 
	int collTick_ = 0;
	enum GameplayState
	{
		Playing, DeathScreen, Paused
	};
	GameplayState gameplayState_;
};