#include "pch.h"
#include "char4.h"

char4::char4()
{
}

char4::char4(bool ishost, float delta, sf::Vector2f windowS)
{
	DamageMulitplyer = 6;
	damage = 9 * DamageMulitplyer;
	healthMulitplyer = 4;
	health = 500 + 100 * healthMulitplyer;
	windowSize = windowS;
	speedMulitplyer = 7;
	speed = windowSize.x / 16 + 5 * speedMulitplyer;
	staminaMulitplyer = 6;
	stamina = 3 * staminaMulitplyer;
	isHost = ishost;
	idleTexture.loadFromFile("sprites/char4Idle.png");
	for (int i = 0; i < 5; i++) {
		idleRect[i] = sf::IntRect(i * 47, 0, 47, 83);
	}
	walkingTexture.loadFromFile("sprites/char4walking.png");
	for (int i = 0; i < 6; i++) {
		walkingRect[i] = sf::IntRect(i * 45, 0, 45, 87);
	}
	LpunchTexture.loadFromFile("sprites/char4Lpunch.png");
	for (int i = 0; i < 3; i++) {
		LpunchRect[i] = sf::IntRect(i * 70, 0, 70, 84);
	}
	character.setTexture(idleTexture);
	character.setTextureRect(idleRect[0]);
	
	character.setOrigin(character.getLocalBounds().width / 2, character.getLocalBounds().height / 2);
	if (isHost == true) {
		character.setPosition(windowSize.x / 6, (windowSize.y / 8)*6.8);
		character.setScale((windowSize.x / 800) + 0.5, (windowSize.y / 600) + 0.5);
		
	}
	else
	{
		character.setPosition(windowSize.x / 6 * 5, (windowSize.y / 8) * 6.8);
		character.setScale(-((windowSize.x / 800) + 0.5), (windowSize.y / 600) + 0.5);
		//std::cout << "scale " << character.getScale().x << std::endl;
	}
	currentAnimation = idle;
	Timer = 0;
	State = 0;
	facingRight = true;
	animationCalled = false;
	AnimationPlayed = true;
	antiSpam = false;


}

void char4::update(bool canControl, float &enemyHealth, sf::Sprite& enemySprite, std::vector<bool> &input)
{
	//::cout << "scale " << character.getScale().x << std::endl;
	if (canControl == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			currentAnimation = walking;

			facingRight = true;
			input[0] = true;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			currentAnimation = walking;


			facingRight = false;
			input[1] = true;

		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AnimationPlayed == true && antiSpam == false) {
			currentAnimation = LPunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpam = true;
			input[2] = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) {

			antiSpam = false;
			input[2] = false;
		}
	}
	else if (canControl == false) {
		if (input[0] == true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = true;


		}
		else if (input[1] == true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = false;


		}
		else if (input[2] == true && antiSpam == false) {
			currentAnimation = LPunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpam = true;
		}
		if (input[2] == false) {

			antiSpam = false;
		}
	}
	if (currentAnimation == idle) {
		//std::cout << facingRight << std::endl;
		//std::cout <<"scale "<< character.getScale().x << std::endl;
		Timer += deltaTime;
		character.setTexture(idleTexture);
		//std::cout << Timer << std::endl;
		if (Timer > 0.15f) {
			if (State < 5) {
				
					character.setTextureRect(idleRect[State]);
					
				State++;

				Timer = 0;
			}
			else
			{
				State = 0;
			}
		}
	}
	else if (currentAnimation == walking) {
		Timer += deltaTime;
		character.setTexture(walkingTexture);
		if (Timer > 0.1f) {
			if (State < 6) {
				if (facingRight == true) {
					character.setTextureRect(walkingRect[State]);
					character.setScale((windowSize.x / 800) + 0.5, (windowSize.y / 600) + 0.5);
					//character.move(speed / 5, 0);
					if (canControl == true) {
						character.move(speed / 5, 0);
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == false) {
							State = 0;
							//prevents flicker
							character.setTextureRect(idleRect[0]);
							input[0] = false;
							input[1] = false;
							currentAnimation = idle;
						}
					}
					else if (canControl == false) {
						if (input[0] == false) {
							State = 0;
							//prevents flicker
							character.setTextureRect(idleRect[0]);
							input[0] = false;
							input[1] = false;
							currentAnimation = idle;
						}
					}
				}
				else
				{
					character.setTextureRect(walkingRect[State]);
					character.setScale(-((windowSize.x / 800) + 0.5), (windowSize.y / 600) + 0.5);
					//character.move(-speed / 5, 0);
					if (canControl == true) {
						character.move(-speed / 5, 0);
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == false) {
							State = 0;
							//prevents flicker
							character.setTextureRect(idleRect[0]);
							input[0] = false;
							input[1] = false;
							currentAnimation = idle;
						}
					}
					else if (canControl == false) {
						if (input[1] == false) {
							State = 0;
							//prevents flicker
							character.setTextureRect(idleRect[0]);
							input[0] = false;
							input[1] = false;
							currentAnimation = idle;
						}
					}
				}
				State++;

				Timer = 0;

			}
			else
			{

				State = 0;
				//prevents flicker
				character.setTextureRect(idleRect[0]);
				input[0] = false;
				input[1] = false;
				currentAnimation = idle;

			}
		}
	}
	else if (currentAnimation == LPunch) {
		if (animationCalled == true) {
			character.setTexture(LpunchTexture);
			character.setTextureRect(LpunchRect[0]);
			State = 0;
			animationCalled = false;
		}
		Timer += deltaTime;

		if (Timer > 0.1f) {
			if (State < 3) {
				character.setTextureRect(LpunchRect[State]);
				if (State == 1) {
					if (canControl == true) {
						if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x > enemySprite.getPosition().x&&facingRight == false) {
							enemyHealth -= damage;
							std::cout << enemyHealth << std::endl;
						}
						else if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x < enemySprite.getPosition().x&&facingRight == true) {
							enemyHealth -= damage;
							std::cout << enemyHealth << std::endl;
						}
					}
				}
				State++;

				Timer = 0;

			}
			else
			{
				AnimationPlayed = true;
				State = 0;
				//prevents flicker
				input[2] = false;
				character.setTextureRect(idleRect[0]);
				currentAnimation = idle;

			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				antiSpam = true;
			}
		}
	}

}
