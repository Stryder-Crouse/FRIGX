#include "pch.h"
#include "char1.h"

char1::char1()
{
}

char1::char1(bool ishost, float delta, sf::Vector2f windowS)
{
	DamageMulitplyer = 6;
	damage = 3*DamageMulitplyer;
	healthMulitplyer = 7;
	health = 500 + 100 * healthMulitplyer;
	windowSize = windowS;
	speedMulitplyer = 4;
	speed = windowSize.x / 16 + 5 * speedMulitplyer;
	staminaMulitplyer = 9;
	stamina = 3 * staminaMulitplyer;
	isHost = ishost;
	idleTexture.loadFromFile("sprites/character1Idle.png");
	for (int i = 0; i < 4;i++) {
		idleRect[i] = sf::IntRect(i* 43,0,43,82);
	}
	walkingTexture.loadFromFile("sprites/character1 Wlaking.png");
	for (int i = 0; i < 5; i++) {
		walkingRect[i] = sf::IntRect(i * 43, 0, 43, 83);
	}
	LpunchTexture.loadFromFile("sprites/character1LPunch.png");
	for (int i = 0; i < 3; i++) {
		LpunchRect[i] = sf::IntRect(i * 57, 0, 57, 81);
	}
	MHpunchTexture.loadFromFile("sprites/character1MHPunch.png");
	for (int i = 0; i < 5; i++) {
		MHpunchRect[i] = sf::IntRect(i * 72, 0, 72, 85);
	}
	FLpunchTexture.loadFromFile("sprites/characterFLPunch.png");
	for (int i = 0; i < 3; i++) {
		FLpunchRect[i] = sf::IntRect(i * 47, 0, 47, 88);
	}
	FHpunchTexture.loadFromFile("sprites/character1FHPunch.png");
	for (int i = 0; i < 5; i++) {
		
			FHpunchRect[i] = sf::IntRect(i * 60, 0, 60, 103);
		
	}
	FMpunchTexture.loadFromFile("sprites/character1FMPunch.png");
	for (int i = 0; i < 7; i++) {

		FMpunchRect[i] = sf::IntRect(i * 61, 0, 61, 85);

	}

	character.setTexture(idleTexture);
	character.setTextureRect(idleRect[0]);
	
	character.setOrigin(character.getLocalBounds().width/2,character.getLocalBounds().height/2);
	if (isHost == true) {
		character.setPosition(windowSize.x/6,(windowSize.y/8)*6.8);
		character.setScale((windowSize.x / 800) + 0.5, (windowSize.y / 600) + 0.5);
		
	}
	else
	{
		character.setPosition(windowSize.x / 6*5, (windowSize.y / 8) * 6.8);
		character.setScale(-((windowSize.x / 800) + 0.5), (windowSize.y / 600) + 0.5);
		
	}
	currentAnimation = idle;
	Timer = 0;
	State = 0;
	facingRight = true;
	animationCalled = false;
	AnimationPlayed = true;
	antiSpam = false;
	//pervents combos from happening when the game starts
	combo1Timer=1;
	combo1State = 0;
	comboState1Done = false;
	comboState2Done = false;
	comboState3Done = false;

	antiSpamRight = false;
	combo2Timer=1;
	combo2State=0;
	combo2State1Done=0;
}

void char1::update(bool canControl, float &enemyHealth, sf::Sprite &enemySprite, std::vector<bool> &input)
{
	combo1Timer += deltaTime;
	combo2Timer += deltaTime;
	if (combo1Timer > 1.f) {
		combo1State = 0;
		comboState1Done = false;
		comboState2Done = false;
		comboState3Done = false;
	}
	if (combo2Timer > 1.f) {
		combo2State = 0;
		combo2State1Done = false;
		
	}
	if (canControl == true) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && AnimationPlayed == true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = true;
			input[0] = true;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && AnimationPlayed == true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = false;
			input[1] = true;

		}
		//combos will be done before the base attack o make sure they are cheaked
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AnimationPlayed == true && antiSpam == false && combo1Timer<1.f&&combo1State == 3 && comboState3Done == false) {
			std::cout << "hello2" << std::endl;
			combo1Timer = 0;
			animationCalled = true;
			AnimationPlayed = false;

			input[5] = true;
			comboState3Done = true;
			currentAnimation = FHpunch;
		}
		//combos will be done before the base attack o make sure they are cheaked
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AnimationPlayed == true && antiSpam == false && combo1Timer<1.f&&combo1State == 2 && comboState2Done == false) {
			std::cout << "hello2" << std::endl;
			combo1Timer = 0;
			animationCalled = true;
			AnimationPlayed = false;

			input[4] = true;
			comboState2Done = true;
			currentAnimation = FLpunch;
		}
		//combos will be done before the base attack o make sure they are cheaked
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AnimationPlayed == true && antiSpam == false&& combo1Timer<1.f&&combo1State==1&&comboState1Done==false) {
			std::cout << "hello" << std::endl;
			combo1Timer = 0;
			animationCalled = true;
			AnimationPlayed = false;
			
			input[3] = true;
			comboState1Done = true;
			currentAnimation = MHpunch;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && AnimationPlayed == true && antiSpam == false&&combo1State!=1 && combo1State != 2 && combo1State != 3) {
			currentAnimation = LPunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpam = true;
			input[2] = true;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && AnimationPlayed == true && antiSpamRight == false ) {
			currentAnimation = FMpunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpamRight = true;
			input[6] = true;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false) {

			antiSpam = false;
			input[2] = false;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == false) {

			antiSpamRight = false;
			input[6] = false;
		}
	}
	else if(canControl==false){
		//std::cout << "Other runing" << std::endl;
		if (input[0]==true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = true;


		}
		else if (input[1] == true) {
			currentAnimation = walking;
			AnimationPlayed = true;

			facingRight = false;


		}
		else if (input[5] == true && antiSpam == false && comboState3Done == false) {
			//combo1Timer = 0;
			std::cout << "ran 4" << std::endl;
			animationCalled = true;
			AnimationPlayed = false;
			comboState3Done = true;
			antiSpam = true;
			currentAnimation = FHpunch;
		}
		else if (input[4] == true && antiSpam == false && comboState2Done == false) {
			//combo1Timer = 0;
			//std::cout << "ran 4" << std::endl;
			animationCalled = true;
			AnimationPlayed = false;
			comboState2Done = true;
			antiSpam = true;
			currentAnimation = FLpunch;
		}
		else if (input[3] == true && antiSpam == false && comboState1Done == false) {
			//combo1Timer = 0;
			//std::cout << "ran 3" << std::endl;
			animationCalled = true;
			AnimationPlayed = false;
			comboState1Done = true;
			antiSpam = true;
			currentAnimation = MHpunch;
		}
		else if (input[6] == true && antiSpamRight == false) {
			currentAnimation = FMpunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpamRight = true;
			
		}
		else if (input[2] == true&& antiSpam==false ) {
			currentAnimation = LPunch;
			animationCalled = true;
			AnimationPlayed = false;
			antiSpam = true;
		}
		
		if (input[2] == false) {

			antiSpam = false;
		}
		if (input[6] == false) {

			antiSpamRight = false;
			
		}
	}

	if (currentAnimation == idle) {
		//std::cout << facingRight << std::endl;
		//std::cout <<"scale "<< character.getScale().x << std::endl;
				Timer += deltaTime;
				character.setTexture(idleTexture);
				//std::cout << Timer << std::endl;
		if (Timer > 0.15f) {
			if (State < 4) {
				
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
	else if (currentAnimation==walking) {
		Timer += deltaTime;
		character.setTexture(walkingTexture);
		if (Timer > 0.1f) {
			if (State < 5) {
				if (facingRight == true) {
					character.setTextureRect(walkingRect[State]);
					character.setScale((windowSize.x / 800) + 0.5, (windowSize.y / 600) + 0.5);
					//character.move(speed / 5, 0);
					if (canControl == true) {
						character.move(speed / 5, 0);
						if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)==false) {
							State = 0;
							//prevents flicker
							character.setTextureRect(idleRect[0]);
							input[0] = false;
							input[1] = false;
							currentAnimation = idle;
						}
					}
					else if (canControl == false) {
						if (input[0]== false) {
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
				//at punch frame do damage
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
				character.setTextureRect(idleRect[0]);
				input[2] = false;
				antiSpam = true;
				currentAnimation = idle;
				//sets up combo
				combo1Timer = 0;
				combo1State = 1;
				//Timer = 0;

			}
			//cheak if spam clicking
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				
				antiSpam = true;
			}
		}
	}
	else if (currentAnimation == MHpunch) {
		
		if (animationCalled == true&&antiSpam==false) {
			character.setTexture(MHpunchTexture);
			character.setTextureRect(MHpunchRect[0]);
			State = 0;
			animationCalled = false;
		}
		Timer += deltaTime;
		//std::cout << "timer "<< Timer << std::endl;
		
		if (Timer > 0.1f) {
			if (State < 5) {
				//std::cout << "state " << State << std::endl;
				character.setTextureRect(MHpunchRect[State]);
				//at punch frame do damage
				if (State == 2) {
					if (canControl == true) {
						if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x > enemySprite.getPosition().x&&facingRight == false) {
							enemyHealth -= damage*1.5;
							std::cout << enemyHealth << std::endl;
						}
						else if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x < enemySprite.getPosition().x&&facingRight == true) {
							enemyHealth -= damage*1.5;
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
				character.setTextureRect(idleRect[0]);
				input[3] = false;
				antiSpam = false;
				comboState1Done = false;
				currentAnimation = idle;
				//sets up next combo
				combo1Timer = 0;
				combo1State = 2;
				//Timer = 0;
			}
			//cheak if spam clicking
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || input[3]==true) {

				antiSpam = true;
			}
		}
	}
	else if (currentAnimation == FLpunch) {

		if (animationCalled == true && antiSpam == false) {
			character.setTexture(FLpunchTexture);
			character.setTextureRect(FLpunchRect[0]);
			State = 0;
			animationCalled = false;
		}
		Timer += deltaTime;
		//std::cout << "timer "<< Timer << std::endl;

		if (Timer > 0.15f) {
			if (State < 3) {
				//std::cout << "state " << State << std::endl;
				character.setTextureRect(FLpunchRect[State]);
				//at punch frame do damage
				if (State == 1) {
					if (canControl == true) {
						if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x > enemySprite.getPosition().x&&facingRight == false) {
							enemyHealth -= damage * 2;
							std::cout << enemyHealth << std::endl;
						}
						else if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x < enemySprite.getPosition().x&&facingRight == true) {
							enemyHealth -= damage * 2;
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
				character.setTextureRect(idleRect[0]);
				input[4] = false;
				antiSpam = false;
				comboState2Done = false;
				currentAnimation = idle;
				//sets up next combo
				combo1Timer = 0;
				combo1State = 3;
				//Timer = 0;
			}
			//cheak if spam clicking
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || input[4] == true) {

				antiSpam = true;
			}
		}
	}
	else if (currentAnimation == FHpunch) {

		if (animationCalled == true && antiSpam == false) {
			character.setTexture(FHpunchTexture);
			character.setTextureRect(FHpunchRect[0]);
			State = 0;
			animationCalled = false;
		}
		Timer += deltaTime;
		//std::cout << "timer "<< Timer << std::endl;

		if (Timer > 0.1f) {
			if (State < 5) {
				//std::cout << "state " << State << std::endl;
				character.setTextureRect(FHpunchRect[State]);
				//at punch frame do damage
				if (State == 2) {
					if (canControl == true) {
						if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x > enemySprite.getPosition().x&&facingRight == false) {
							enemyHealth -= damage * 2.5;
							std::cout << enemyHealth << std::endl;
						}
						else if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x < enemySprite.getPosition().x&&facingRight == true) {
							enemyHealth -= damage * 2.5;
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
				
				character.setTextureRect(idleRect[0]);
				input[5] = false;
				antiSpam = false;
				comboState3Done = false;
				currentAnimation = idle;
				//sets up next combo
				combo1Timer = 0;
				combo1State = 4;
				//Timer = 0;
			}
			//cheak if spam clicking
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || input[5] == true) {

				antiSpam = true;
			}
		}
	}
	else if (currentAnimation == FMpunch) {
		
		if (animationCalled == true ) {
			character.setTexture(FMpunchTexture);
			character.setTextureRect(FMpunchRect[0]);
			State = 0;
			animationCalled = false;
		}
		Timer += deltaTime;
		//std::cout << "timer "<< Timer << std::endl;

		if (Timer > 0.1f) {
			if (State < 7) {
				//std::cout << "state " << State << std::endl;
				character.setTextureRect(FMpunchRect[State]);
				//at punch frame do damage
				if (State == 3) {
					if (canControl == true) {
						if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x > enemySprite.getPosition().x&&facingRight == false) {
							enemyHealth -= damage * 2;
							std::cout << enemyHealth << std::endl;
						}
						else if (character.getGlobalBounds().intersects(enemySprite.getGlobalBounds()) && character.getPosition().x < enemySprite.getPosition().x&&facingRight == true) {
							enemyHealth -= damage * 2;
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

				character.setTextureRect(idleRect[0]);
				input[6] = false;
				antiSpamRight = false;
				
				currentAnimation = idle;
				//sets up next combo
				combo2Timer = 0;
				combo2State = 1;
				//Timer = 0;
			}
			//cheak if spam clicking
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || input[6] == true) {

				antiSpamRight = true;
			}
		}
	}

}











