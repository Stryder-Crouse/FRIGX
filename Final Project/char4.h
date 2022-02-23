#pragma once
#include "Character.h"
//enherantance in c++ :)
class char4: public Character {
public:
	sf::Texture idleTexture;
	sf::IntRect idleRect[5];

	sf::Texture walkingTexture;
	sf::IntRect walkingRect[6];

	sf::Texture LpunchTexture;
	sf::IntRect LpunchRect[3];

	float Timer;
	int State;
	bool animationCalled;
	enum currentAnim { idle, walking, LPunch };
	currentAnim currentAnimation;
	bool facingRight;
	bool AnimationPlayed;
	bool antiSpam;
	char4();
	char4(bool ishost, float delta, sf::Vector2f windowS);
	void update(bool canControl, float &enemyHealth, sf::Sprite &enemySprite, std::vector<bool> &input);
};