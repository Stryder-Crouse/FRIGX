#pragma once
#include "imports.h"

class Character {
public:
	float damage;
	float DamageMulitplyer;
	float health;
	float healthMulitplyer;
	float speed;
	float speedMulitplyer;
	float stamina;
	float staminaMulitplyer;
	bool isHost;
	float deltaTime;
	sf::Vector2f windowSize;
	sf::Sprite character;
	
	Character();
	//virtual allow the function to be defined in its sub classes
	virtual void update( bool canControl ,float& enemyHealth, sf::Sprite& enemySprite, std::vector<bool> &input) = 0;
	void updateDelta(float &delta,float currentDelta);
	bool isdead(int health);
	

};
