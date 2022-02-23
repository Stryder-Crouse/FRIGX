#pragma once
#include "imports.h"
#include "Character.h"
//enherantance in c++ :)
class char1 : public Character {
public:
	
	
	sf::Texture idleTexture;
	sf::IntRect idleRect[4];
	
	sf::Texture walkingTexture;
	sf::IntRect walkingRect[5];

	sf::Texture LpunchTexture;
	sf::IntRect LpunchRect[3];

	sf::Texture MHpunchTexture;
	sf::IntRect MHpunchRect[5];

	sf::Texture FLpunchTexture;
	sf::IntRect FLpunchRect[3];

	sf::Texture FHpunchTexture;
	sf::IntRect FHpunchRect[5];

	sf::Texture FMpunchTexture;
	sf::IntRect FMpunchRect[7];

	float Timer;
	int State;
	bool animationCalled;
	enum currentAnim {idle,walking,LPunch,MHpunch,FLpunch, FHpunch, FMpunch};
	currentAnim currentAnimation;
	bool facingRight;
	bool AnimationPlayed;
	bool antiSpam;
	//combo1
	float combo1Timer;
	int combo1State;
	bool comboState1Done;
	bool comboState2Done;
	bool comboState3Done;
	//combo2
	bool antiSpamRight;
	float combo2Timer;
	int combo2State;
	bool combo2State1Done;
	
	char1();
	char1(bool ishost, float delta,sf::Vector2f windowS);
	void update(bool canControl, float &enemyHealth ,sf::Sprite &enemySprite, std::vector<bool> &input);
	
	
};

