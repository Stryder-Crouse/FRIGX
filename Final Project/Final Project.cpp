// Final Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//narpwhal


#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <Windows.h>
#include <SFML/Network.hpp>

#include "Final Project.h"
#include"Character.h"
#include"char1.h"
#include"char4.h"
#include"imports.h"
#include"HealthBars.h"
//dont do this nathen did it for easyer codeing
using namespace sf;


	
int main()
{
	//this code was ment to be used by nathan to allow him to display all the characters sprites easy he never used it though
	//so it is kept here for documentation
	std::vector<Texture*> characterTextures;//createas an array of pointers that stores the textures for each character
	std::vector<Sprite*> characters;//createas an array of pointers that stores the sprites for each characters
	
	//loads textures for each character and loads them into the vector
	Texture* newTexture = new Texture();
	newTexture->loadFromFile("sprites/a.png");
	characterTextures.push_back(newTexture);
	Texture* newTexture2 = new Texture();
	newTexture->loadFromFile("sprites/char2face.png");
	characterTextures.push_back(newTexture);
	Texture* newTexture3 = new Texture();
	newTexture->loadFromFile("sprites/char3face.png");
	characterTextures.push_back(newTexture);
	Texture* newTexture4= new Texture();
	newTexture->loadFromFile("sprites/char4face.png");
	characterTextures.push_back(newTexture);

	//sets each tecture to the corraponding sprite
	for (int i = 0; i < characterTextures.size();i++) {
		Sprite* newSprite = new Sprite();
		newSprite->setTexture(*characterTextures[i]);// the * deponters the vector allow the data to be derectly accessed by the function
		characters.push_back(newSprite);
	}
	//end of useless code

	//stores 
	std::vector<Character*> players;//stores the players objects in the game
	Clock deltaTime;//creates a clock to create delta time to allow for framerate independent game play (delta time is the time between each frame, by makeing movement scale with delta time it allows the game to be played at any frame rate)
	float keepDeltaTimee;//stores delta time
	bool hostHasPicked = false;// stores weather or not the host has picked a character
	
	//speaical type for int for sending over the internet
	sf::Int32 whopickedHost = -1;//stores the character the host has picked as an interger
	sf::Int32 whopickedClient = -1;//stores the character the client has picked as an interger
	
	int State = 0;//stores the frames of the idle anmation when billy is beaing picked
	int State4 = 0;//stores the frames of the idle anmation when billeta is beaing picked
	
	int characterStatHealth = 0;//stores the health stat shown when picking characters
	int characterStatSpeed = 0;//stores the Speed stat shown when picking characters
	int characterStatStrength = 0;//stores the Strength stat shown when picking characters
	int characterStatStamina = 0;//stores the Stamina stat shown when picking characters
	int dotState = 0;//stores amount of dots shown when the host is waiting

	RenderWindow window(sf::VideoMode(1200, 800), "FRIG-X");//creates the window called FRIG-X with resolution of 1200 by 800

	//creates statemachine with an enum that stores the state of the game shown the the user
	enum gameState { title, play, controls, controlsBilly, controlsBillieta, howToPlay, hostselect , clientIpEnter, hostWaiting, clientWait, billy, billieta, player1Wins, player2Wins};

	static gameState state = title;//creates a vararble useing the enum defined above to store the state of the game shown to the user (no idea why nathan delaired as static or why the program is allowing a static varable to be rewriten it should not allow that )
	//Buttons (nathains code)------------------------------------------------------------------------------------------------------------------
	Sprite startButton;
	Sprite controlsButton;
	Sprite backButton;
	Sprite BG;
	Sprite BGPlay;
	Sprite leftArrow;
	Sprite rightArrow;
	Sprite idlechar1;
	Sprite charFace;
	Sprite logo;
	Sprite computermouse1;
	Sprite computermouse2;
	Sprite computermouse3;
	Sprite computermouse4;
	Sprite computermouse5;
	Sprite computermouse6;
	Sprite computermouse7;
	Sprite computermouse8;
	Sprite computermouse9;
	Sprite computermouse10;
	Sprite computermouse11;
	Sprite computermouse12;
	Sprite computermouse13;
	Sprite computermouse14;
	Sprite computermouse15;
	Sprite computermouse16;
	Texture logoTexture;
	Texture computermouseleft;
	Texture computermouseright;
	Texture charFaceTexture;
	Texture char2FaceTexture;
	Texture char3FaceTexture;
	Texture char4FaceTexture;
	Texture buttonTexture;
	Texture wallBG;
	Texture dojoBG;
	Texture controlsBG;
	Texture stageBG;
	Texture arrowTexture;
	Texture idleTexture;
	Texture idleTexture4;
	IntRect idleRect[4];
	IntRect idleRect4[5];
	
	computermouseleft.loadFromFile("sprites/computermousel.png");
	computermouseright.loadFromFile("sprites/computermouser.png");
	charFaceTexture.loadFromFile("sprites/a.png");
	char2FaceTexture.loadFromFile("sprites/char2face.png");
	char3FaceTexture.loadFromFile("sprites/char3face.png");
	char4FaceTexture.loadFromFile("sprites/char4face.png");
	wallBG.loadFromFile("sprites/wallbg.jpg");
	dojoBG.loadFromFile("sprites/dojobg.jpg");
	controlsBG.loadFromFile("sprites/controls.png");
	stageBG.loadFromFile("sprites/stagebg.png");
	logoTexture.loadFromFile("sprites/logo.png");
	buttonTexture.loadFromFile("sprites/button.png");
	arrowTexture.loadFromFile("sprites/arrow1.png");
	logo.setTexture(logoTexture);
	startButton.setTexture(buttonTexture);
	controlsButton.setTexture(buttonTexture);
	backButton.setTexture(buttonTexture);
	leftArrow.setTexture(arrowTexture);
	rightArrow.setTexture(arrowTexture);
	charFace.setTexture(charFaceTexture);
	float delayBetween = 0;//stotes the delay bewteen frames of idle animation when selcting a character
	float dotTimer = 0;//stotes the delay bewteen each dot beaing added when the host is waiting
	//Text and Font
	Text loadingText;
	Text gameNameText;
	Text startText;
	Text controlsText;
	Text howToPlayText;
	Text backText;
	Text readyText;
	Text characterNameText; 
	Text healthText;
	Text strengthText;
	Text speedText;
	Text staminaText;
	Text strongComboText;
	Text fastComboText;
	Text stunComboText;
	Text damageComboText;
	Text lightAttackText;
	Text heavyAttackText;
	Text rightMovementText;
	Text leftMovementText;
	Text playAgainText;
	Text playerWinsText;
	Font Candal;
	Candal.loadFromFile("Font/Candal/Candal.ttf");
	//loops create rect's that tell were the each frame of the idle anmation is from the animation file
	for (int i = 0; i < 4; i++) {
		idleRect[i] = sf::IntRect(i * 43, 0, 43, 82);
	}
	for (int i = 0; i < 5; i++) {
		idleRect4[i] = sf::IntRect(i * 47, 0, 47, 83);
	}

	//TEXT----------------------------------------------------------------------------
	
	
	//"Start" text
	startText.setFont(Candal);
	startText.setString("Start Game");
	startText.setCharacterSize(30);
	startText.setFillColor(Color::White);
	startText.setPosition(550, 400);
	//"Controls" text
	controlsText.setFont(Candal);
	controlsText.setString("Controls");
	controlsText.setCharacterSize(30);
	controlsText.setFillColor(Color::White);
	controlsText.setPosition(575, 600);
	//"Back" text
	backText.setFont(Candal);
	backText.setString("Back");
	backText.setCharacterSize(24);
	backText.setFillColor(Color::White);
	backText.setPosition(1050, 750);
	//Character name Text
	characterNameText.setFont(Candal);
	characterNameText.setCharacterSize(75);
	characterNameText.setFillColor(Color::White);
	characterNameText.setPosition(600, 100);
	//Character health text
	healthText.setFont(Candal);
	healthText.setString("Health: " + std::to_string(characterStatHealth));
	healthText.setCharacterSize(24);
	healthText.setFillColor(Color::Black);
	healthText.setPosition(250, 400);
	//Character strength text
	strengthText.setFont(Candal);
	strengthText.setString("Strength: " + std::to_string(characterStatStrength));
	strengthText.setCharacterSize(24);
	strengthText.setFillColor(Color::Black);
	strengthText.setPosition(250, 300);
	//Character speed text
	speedText.setFont(Candal);
	speedText.setString("Speed: " + std::to_string(characterStatSpeed));
	speedText.setCharacterSize(24);
	speedText.setFillColor(Color::Black);
	speedText.setPosition(750, 300);
	//Character stamina text
	staminaText.setFont(Candal);
	staminaText.setString("Stamina: " + std::to_string(characterStatStamina));
	staminaText.setCharacterSize(24);
	staminaText.setFillColor(Color::Black);
	staminaText.setPosition(750, 400);
	//Strong Combo Text
	strongComboText.setFont(Candal);
	strongComboText.setString("Strong Combo");
	strongComboText.setCharacterSize(50);
	strongComboText.setFillColor(Color::White);
	strongComboText.setPosition(300, 325);
	//Fast Combo Text
	fastComboText.setFont(Candal);
	fastComboText.setString("Fast Combo");
	fastComboText.setCharacterSize(50);
	fastComboText.setFillColor(Color::White);
	fastComboText.setPosition(300, 425);
	//Stun Combo Text
	stunComboText.setFont(Candal);
	stunComboText.setString("Stun Combo");
	stunComboText.setCharacterSize(50);
	stunComboText.setFillColor(Color::White);
	stunComboText.setPosition(300, 525);
	//Damage Combo Text
	damageComboText.setFont(Candal);
	damageComboText.setString("Damage Combo");
	damageComboText.setCharacterSize(50);
	damageComboText.setFillColor(Color::White);
	damageComboText.setPosition(300, 625);
	//Light Attack Text
	lightAttackText.setFont(Candal);
	lightAttackText.setString("Light Attack");
	lightAttackText.setCharacterSize(50);
	lightAttackText.setFillColor(Color::White);
	lightAttackText.setPosition(300, 325);
	//Heavy Attack Text
	heavyAttackText.setFont(Candal);
	heavyAttackText.setString("Heavy Attack");
	heavyAttackText.setCharacterSize(50);
	heavyAttackText.setFillColor(Color::White);
	heavyAttackText.setPosition(300, 425);
	//Right Movement Text
	rightMovementText.setFont(Candal);
	rightMovementText.setString("Move Right               D");
	rightMovementText.setCharacterSize(50);
	rightMovementText.setFillColor(Color::White);
	rightMovementText.setPosition(300, 525);
	//Left Movement Text
	leftMovementText.setFont(Candal);
	leftMovementText.setString("Move Left                  A");
	leftMovementText.setCharacterSize(50);
	leftMovementText.setFillColor(Color::White);
	leftMovementText.setPosition(300, 625);
	//Loading text
	loadingText.setFont(Candal);
	loadingText.setCharacterSize(50);
	loadingText.setFillColor(Color::White);
	loadingText.setPosition(300, 300);
	//Play Again text
	playAgainText.setFont(Candal);
	playAgainText.setString("Play Again?");
	playAgainText.setCharacterSize(50);
	playAgainText.setFillColor(Color::White);
	playAgainText.setPosition(500, 500);
	//Player (1/2) Wins text
	playerWinsText.setFont(Candal);
	playerWinsText.setCharacterSize(100);
	playerWinsText.setFillColor(Color::White);
	playerWinsText.setPosition(400, 300);

	//BUTTONs-----------------------------------------------------------------
	//Start button
	startButton.setScale(1, 1);
	startButton.setPosition(475, 290);
	//Controls button
	controlsButton.setScale(1, 1);
	controlsButton.setPosition(475, 490);
	//Back button
	backButton.setScale(0.5,0.5);
	backButton.setPosition(995, 700);
	//Arrows
	rightArrow.setColor(Color::White);
	rightArrow.setPosition(1000, 300);
	rightArrow.setScale(1, 1);
	leftArrow.setColor(Color::White);
	leftArrow.setPosition(200, 300);
	leftArrow.setScale(-1, 1);

	logo.setScale(0.75, 0.75);
	logo.setPosition(300, 100);

	
	computermouse1.setScale(0.25, 0.25);
	computermouse2.setScale(0.25, 0.25);
	computermouse3.setScale(0.25, 0.25);
	computermouse4.setScale(0.25, 0.25);
	computermouse5.setScale(0.25, 0.25);
	computermouse6.setScale(0.25, 0.25);
	computermouse7.setScale(0.25, 0.25);
	computermouse8.setScale(0.25, 0.25);
	computermouse9.setScale(0.25, 0.25);
	computermouse10.setScale(0.25, 0.25);
	computermouse11.setScale(0.25, 0.25);
	computermouse12.setScale(0.25, 0.25);
	computermouse13.setScale(0.25, 0.25);
	computermouse14.setScale(0.25, 0.25);
	computermouse15.setScale(0.25, 0.25);
	computermouse16.setScale(0.25, 0.25);
	computermouse1.setPosition(750, 325);
	computermouse2.setPosition(800, 325);
	computermouse3.setPosition(850, 325);
	computermouse4.setPosition(900, 325);
	computermouse5.setPosition(750, 425);
	computermouse6.setPosition(800, 425);
	computermouse7.setPosition(850, 425);
	computermouse8.setPosition(900, 425);
	computermouse9.setPosition(750, 525);
	computermouse10.setPosition(800, 525);
	computermouse11.setPosition(850, 525);
	computermouse12.setPosition(900, 525);
	computermouse13.setPosition(750, 625);
	computermouse14.setPosition(800, 625);
	computermouse15.setPosition(850, 625);
	computermouse16.setPosition(900, 625);

	//nathan code end --------------------------------------------------------------------------------------------------------------------------------


	//sets bg scale
	BG.setScale(window.getSize().x/800.f,window.getSize().y/600.f);//sets the back grounds scale inorder to fill the window the code also allows the sprite to scale with the window
	BG.setPosition(0, 0);//sets the background to be drawn from the right coner of the window.


	BGPlay.setTexture(stageBG);//sets texture to the background texture when the game starts
	BGPlay.setPosition(0, 0);//sets the background to be drawn from the right coner of the window.

	Vector2i mousePosition = Mouse::getPosition(window);//stores the mouse postion on the screen in x and y cordents
	
	//text for host selecet
	Text whoAre;
	whoAre.setFont(Candal);
	whoAre.setCharacterSize(50);
	whoAre.setString("Host a sever or Join one");
	whoAre.setOrigin(whoAre.getLocalBounds().width / 2, whoAre.getLocalBounds().height / 2);
	whoAre.setPosition(600,100);
	
	Text areHost;
	areHost.setFont(Candal);
	areHost.setCharacterSize(50);
	areHost.setString("Host");
	areHost.setOrigin(areHost.getLocalBounds().width / 2, areHost.getLocalBounds().height / 2);
	areHost.setPosition(300, 400);

	Text areClient;
	areClient.setFont(Candal);
	areClient.setCharacterSize(50);
	areClient.setString("Join");
	areClient.setOrigin(areClient.getLocalBounds().width / 2, areClient.getLocalBounds().height / 2);
	areClient.setPosition(900, 400);

	//ip enter defs
	std::string ip;//stores ip that is beaing inputed

	//creates the text that displays the ip that is beaing entered
	Text ipShow;
	ipShow.setFont(Candal);
	ipShow.setCharacterSize(50);
	ipShow.setString(ip);
	ipShow.setOrigin(ipShow.getLocalBounds().width / 2, ipShow.getLocalBounds().height / 2);//sets the origen to the center of the sprite to allow for the text to be centered
	ipShow.setPosition(600,350);//sets postion to the middle of the frame

	//creates the blue box behind the ip adgress to allow it to be read
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(900, 70));
	box.setPosition(150, 330);
	box.setFillColor(sf::Color::Blue);// makes box blue

	//connection definations

	//UDP is fast but it can lose packets
	//TCP is slow but it cannot messup and lose a packet
	sf::UdpSocket socket;//creates the UDP socket allowing UDP communication bewteen divices

	sf::Packet magic;//creates a packet object that stores data to be sent to the other computer
	
	
	
	unsigned short port = 6899;//stores the port that the game is hosted on
	
	//left blank to allow for any ip or port to fill them afther the magic paket is reacived
	unsigned short clientPort;
	
	sf::IpAddress clientIP;
	//
	sf::IpAddress HostIP;
	//packet for character select
	sf::Packet characterSend;
	sf::Packet characterReceave;
	float canEnter=0;
	//adds magic bool to packet
	//magic << magicBool; this is commeted out as if you write any data to a parket then try to recive a paket with the same name it will fail to recive the packet
	//you can use paket.clear() to remove any data in the paket allowing pakets with the same name to be recived shown in magic paket recived code
	bool isHost =false ;
	bool ipFound = false;
	//play net code
	bool characterCreated = false;

	std::vector<bool> inputsHost{false,false,false,false,false,false ,false};

	std::vector<bool> inputsClient{ false ,false ,false,false,false,false ,false};

	float ticRate = 0;
	sf::Packet sendInputs;
	sf::Packet reaciveInputs;

	float clientHealth;
	float HostHealth;

	sf::Int32 getHostX;
	sf::Int32 getHostY;
	float getHostScaleX;
	float getHostScaleY;

	sf::Int32 getClientX;
	sf::Int32 getClientY;
	float getClientScaleX;
	float getClientScaleY;
	int delay = 0;

	bool isDeadHost = false;
	bool isDeadClient = false;
	//sf::Packet isDead;
	float isDeadtime = 0;

	//ui code
	Ui gui;

	//window.setFramerateLimit(60);
	while (window.isOpen())
	{
		//code for cheaking who is host and who is player.
		//for know "bool isHost will act as the code
		//end
		keepDeltaTimee = deltaTime.getElapsedTime().asSeconds();
		deltaTime.restart();
		//std::cout << keepDeltaTimee << std::endl;
		mousePosition = Mouse::getPosition(window);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::TextEntered&&state==clientIpEnter)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) == true) {
					//connection to host code
					sf::IpAddress sendAddress;
					sendAddress = sendAddress.getLocalAddress();
					std::string localIP;
					localIP = sendAddress.toString();
					sf::Int16 localport = socket.getLocalPort();
					//sends local ip to host
					magic << localIP;
					magic << localport;
					if (socket.send(magic, ip, 6899) != sf::Socket::Done) {
						std::cout << "mangic packet failed to send wrong or non-existing ip " << std::endl;
					}
					else {
						std::cout << "mangic packet sent!!" << std::endl;
						//stores HostIP
						sf::IpAddress temp(ip);
						HostIP = temp;
						state = clientWait;
					}
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == false) {
					ip += event.text.unicode;
					ipShow.setString(ip);
					ipShow.setOrigin(ipShow.getLocalBounds().width / 2, ipShow.getLocalBounds().height / 2);
				}
				else {
					if (ip.size()>0) {
						ip.pop_back();
						ipShow.setString(ip);
						ipShow.setOrigin(ipShow.getLocalBounds().width / 2, ipShow.getLocalBounds().height / 2);
					}
				}


			}
		}

		switch (state) {
		case hostselect:

			//if host is clicked
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 3 && mousePosition.x < window.getSize().x / 12* 3 + startButton.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 4 && mousePosition.y < (window.getSize().y / 8) * 4+ startButton.getLocalBounds().height) {
					//std::cout << "workd" << std::endl;
					//code for soket binding
					if (socket.bind(6899) != sf::Socket::Done) {
						std::cout << "socket failed to start" << std::endl;
					}
					isHost = true;
					state = hostWaiting;
				}
				//client
				if (mousePosition.x > window.getSize().x / 12 * 9 && mousePosition.x < window.getSize().x / 12 * 9 + startButton.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 4 && mousePosition.y < (window.getSize().y / 8) * 4 + startButton.getLocalBounds().height) {
					//std::cout << "workd" << std::endl;
					//code for soket lissening
					if (socket.bind(6900) != sf::Socket::Done) {
						std::cout << "socket failed to start" << std::endl;
					}
					isHost = false;
					state = clientIpEnter;
				}
			}

		
			window.clear();
			window.draw(whoAre);
			window.draw(areClient);
			window.draw(areHost);
			window.display();

			break;
		case hostWaiting:
			dotTimer += keepDeltaTimee;
			if (dotTimer > 1.f){
				if (dotState == 0) {
					
					loadingText.setString("Waiting for client");
				
					dotState += 1;
				}
				else if (dotState == 1) {
					
					loadingText.setString("Waiting for client.");
					
				
					dotState += 1;
				}
				else if (dotState == 2) {
					
					loadingText.setString("Waiting for client..");
					
				
					dotState += 1;
				}
				else if (dotState == 3) {
					
					loadingText.setString("Waiting for client...");
					
			
					dotState = 0;
				}
				dotTimer = 0;
			}
			window.clear();
			window.draw(loadingText);
			window.display();
			socket.setBlocking(false);//forces the program to wait until a paket is recived

			magic.clear();
			//ematy to allow for any ip and any port to send a parket to the host
			if (socket.receive(magic, clientIP,clientPort) != sf::Socket::Done) {//sf::Soket::NotReady could also work???


				std::cout << "could not receive magic packet" << std::endl;
			}
			else
			{
				std::cout << "magic packet received" << std::endl;
				std::string tempClientIP;
				magic >> tempClientIP >>clientPort;
				sf::IpAddress tempClientAddress(tempClientIP);
				clientIP = tempClientAddress;
				//std::cout << "this is IP of CLient " << clientIP.toString() << std::endl << "this is clients port " << clientPort << std::endl;
				magic.clear();
				std::cout << clientIP << std::endl<<clientPort;
				if (socket.send(magic, clientIP, clientPort)!= Socket::Done) {
					
				}
				else
				{
					std::cout << "second magic packet sendt" << std::endl;
					state = billy;
				}

				
			}
			
			break;
		case clientIpEnter:



			window.clear();
			window.draw(box);
			window.draw(ipShow);
			window.display();
			break;

		case clientWait:
			window.clear();

			window.display();

			magic.clear();

			if (socket.receive(magic, HostIP, port) != Socket::Done) {
			
			}
			else {
				std::cout << "second magic packet recived" << std::endl;
				state = billy;
			}

			
			break;
		case title:
			window.clear();
			BG.setPosition(0, 0);
			BG.setScale(window.getSize().x / 800.f, window.getSize().y / 600.f);
			BG.setPosition(0, 0);
			BG.setTexture(wallBG);
			window.draw(BG);
			//window.draw(startButton);
			//window.draw(controlsButton);
			window.draw(startText);
			window.draw(controlsText);
			window.draw(howToPlayText);
			window.draw(logo);
			window.display();

			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 5.5 && mousePosition.x < window.getSize().x / 12 * 5.5 + startText.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 4 && mousePosition.y < (window.getSize().y / 8) * 4 + startText.getLocalBounds().height) {
					window.draw(startButton);
					window.draw(startText);
					window.display();
					sf::sleep(sf::Time(sf::milliseconds(1000)));
					state = hostselect;
				}
	
				if (mousePosition.x > window.getSize().x / 12 * 5.75 && mousePosition.x < window.getSize().x / 12 * 5.75 + controlsText.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 6 && mousePosition.y < (window.getSize().y / 8) * 6 + controlsText.getLocalBounds().height) {
					window.draw(controlsButton);
					window.draw(controlsText);
					window.display();
					sf::sleep(sf::Time(sf::milliseconds(1000)));
					state = controls;
				}
			}
			break;
		case play:
			
			socket.setBlocking(false);
			ticRate += keepDeltaTimee;
			isDeadtime += keepDeltaTimee;
			if (characterCreated==false) {
				if (whopickedHost==0) {
					//this is host pick so hostpick is ==true
					players.push_back(new char1(true, keepDeltaTimee, sf::Vector2f(window.getSize())));
					gui.getHostMaxHealth(players[0]->health);
				}
				else if (whopickedHost == 1) {
					//this is host pick so hostpick is ==true
					//code for maiking character
				}
				else if (whopickedHost == 2) {
					//this is host pick so hostpick is ==true
					//code for maiking character
				}
				else if (whopickedHost == 3) {
					//this is host pick so hostpick is ==true
					players.push_back(new char4(true, keepDeltaTimee, sf::Vector2f(window.getSize())));
					gui.getHostMaxHealth(players[0]->health);
				}
				if (whopickedClient == 0) {
					//this is host pick so hostpick is ==true
					players.push_back(new char1(false, keepDeltaTimee, sf::Vector2f(window.getSize())));
					gui.getClientMaxHealth(players[1]->health);
				}
				else if (whopickedClient == 1) {
					//this is host pick so hostpick is ==true
					//code for maiking character
				}
				else if (whopickedClient == 2) {
					//this is host pick so hostpick is ==true
					//code for maiking character
				}
				else if (whopickedClient == 3) {
					//this is host pick so hostpick is ==true
					players.push_back(new char4(false, keepDeltaTimee, sf::Vector2f(window.getSize())));
					gui.getClientMaxHealth(players[1]->health);
				}
				characterCreated = true;
			}

			if (isDeadHost == false && isDeadClient == false) {
				if (isHost == true) {


					players[0]->updateDelta(players[0]->deltaTime, keepDeltaTimee);
					players[0]->update(true, players[1]->health, players[1]->character, inputsHost);
					gui.updateClientHealthBar(players[1]->health);


					if (ticRate > 0.0078125) {
						//send inputs
						sendInputs.clear();
						getHostX = players[0]->character.getPosition().x;
						getHostY = players[0]->character.getPosition().y;
						getHostScaleX = players[0]->character.getScale().x;
						getHostScaleY = players[0]->character.getScale().y;
						// std::cout << getHostScaleX << "scaleX    " << getHostScaleY << "scaleY    " << getHostX << " X        " << getHostY << " Y        " << std::endl;
						sendInputs.clear();
						clientHealth = players[1]->health;
						sendInputs << inputsHost[0] << inputsHost[1] << inputsHost[2] <<inputsHost[3]<<inputsHost[4] << inputsHost[5] << inputsHost[6] <<clientHealth << getHostX << getHostY << getHostScaleX << getHostScaleY;

						if (socket.send(sendInputs, clientIP, clientPort) != sf::Socket::Done) {
							//std::cout << "missed a paket did you dissconecct" << std::endl;
						}
						sendInputs.clear();
						//reacive inputs
						reaciveInputs.clear();
						if (socket.receive(reaciveInputs, clientIP, clientPort) != sf::Socket::Done) {
							//std::cout << "no paket did you dissconecct" << std::endl;
						}
						else {
							bool temps[100];
							reaciveInputs >> temps[0] >> temps[1] >> temps[2] >> temps[3]>>temps[4] >> temps[5] >> temps[6] >>HostHealth >> getClientX >> getClientY >> getClientScaleX >> getClientScaleY;

							players[1]->character.setPosition(getClientX, getClientY);
							players[1]->character.setScale(getClientScaleX, getClientScaleY);
							players[0]->health = HostHealth;
							inputsClient[0] = temps[0];
							inputsClient[1] = temps[1];
							inputsClient[2] = temps[2];
							inputsClient[3] = temps[3];
							inputsClient[4] = temps[4];
							inputsClient[5] = temps[5];
							inputsClient[6] = temps[6];
							//std::cout << "Host Health " << players[0]->health << "Client health " << players[1]->health << std::endl;
							//std::cout << getClientScaleX << "CCCC scaleX    " << getClientScaleY << "scaleY    " << getClientX << " X        " << getClientY << " Y        " << std::endl;
							//std::cout << "inputClient 0 "<< inputsClient[0] << "inputClient 1 " << inputsClient[1] << "inputClient 2 " << inputsClient[2] << std::endl;
							reaciveInputs.clear();
						}
						
						ticRate = 0;
					}

					if (isDeadtime>=10.f) {
						isDeadHost = players[1]->isdead(players[0]->health);
						isDeadClient = players[0]->isdead(players[1]->health);
						//isDeadtime = 0;f
					}

					players[1]->updateDelta(players[1]->deltaTime, keepDeltaTimee);
					players[1]->update(false, players[0]->health, players[0]->character, inputsClient);
					gui.updateHostHealthBar(players[0]->health);


				}
				else {

					//client

					players[1]->updateDelta(players[1]->deltaTime, keepDeltaTimee);
					players[1]->update(true, players[0]->health, players[0]->character, inputsClient);
					gui.updateHostHealthBar(players[0]->health);

					if (ticRate > 0.0078125) {
						
						//send inputs
						sendInputs.clear();
						getClientX = players[1]->character.getPosition().x;
						getClientY = players[1]->character.getPosition().y;
						getClientScaleX = players[1]->character.getScale().x;
						getClientScaleY = players[1]->character.getScale().y;
						sendInputs.clear();
						HostHealth = players[0]->health;

						sendInputs << inputsClient[0] << inputsClient[1] << inputsClient[2] << inputsClient[3] <<inputsClient[4] << inputsClient[5] << inputsClient[6] << HostHealth << getClientX << getClientY << getClientScaleX << getClientScaleY;
						if (socket.send(sendInputs, HostIP, port) != sf::Socket::Done) {
							//std::cout << "missed a paket did you dissconecct" << std::endl;
						}
						sendInputs.clear();
						//reacive inputs
						reaciveInputs.clear();
						if (socket.receive(reaciveInputs, HostIP, port) != sf::Socket::Done) {
							//std::cout << "no paket did you dissconecct" << std::endl;
						}
						else {
							bool temp[100];

							reaciveInputs >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5] >> temp[6] >> clientHealth >> getHostX >> getHostY >> getHostScaleX >> getHostScaleY;
							inputsHost[0] = temp[0];
							inputsHost[1] = temp[1];
							inputsHost[2] = temp[2];
							inputsHost[3] = temp[3];
							inputsHost[4] = temp[4];
							inputsHost[5] = temp[5];
							inputsHost[6] = temp[6];
							players[1]->health = clientHealth;
							players[0]->character.setPosition(getHostX, getHostY);
							//std::cout << getHostScaleX << "HHHH scaleX    " << getHostScaleY << "scaleY    " << getHostX << " X        " << getHostY << " Y        " << std::endl;
							players[0]->character.setScale(getHostScaleX, getHostScaleY);
							//std::cout << "inputHost 0 " << inputsHost[0] << "inputHost 1 " << inputsHost[1] << "inputHost 2 " << inputsHost[2] << std::endl;
							//std::cout << "Host Health " << players[0]->health << "Client health " << players[1]->health << std::endl;
							//std::cout << players[0]->character.getPosition().x <<std::endl<< players[0]->character.getPosition().y << std::endl;
							reaciveInputs.clear();
						}
						
						ticRate = 0;
					}

					if (isDeadtime >= 10.f) {
						isDeadHost = players[1]->isdead(players[0]->health);
						isDeadClient = players[0]->isdead(players[1]->health);
						//isDeadtime = 0;
					}

					players[0]->updateDelta(players[0]->deltaTime, keepDeltaTimee);
					players[0]->update(false, players[1]->health, players[1]->character, inputsHost);
					gui.updateClientHealthBar(players[1]->health);
				

				}



				window.clear();
			
				window.draw(BGPlay);
				window.draw(gui.hostBoarder);
				window.draw(gui.hostBlackspace);
				window.draw(gui.hostHealthbar);
				window.draw(gui.clientBoarder);
				window.draw(gui.clientBlackspace);
				window.draw(gui.clientHealthbar);
				window.draw(players[0]->character);
				window.draw(players[1]->character);
				
				window.display();
			}

			else {
				if (isDeadHost==true) {
					std::cout << "Client Wins" << std::endl;
						//client will allwas figher out the host is dead before the host user so only send the host health
						sendInputs.clear();
						getClientX = players[1]->character.getPosition().x;
						getClientY = players[1]->character.getPosition().y;
						getClientScaleX = players[1]->character.getScale().x;
						getClientScaleY = players[1]->character.getScale().y;
						sendInputs.clear();
						HostHealth = players[0]->health;

						sendInputs << inputsClient[0] << inputsClient[1] << inputsClient[2] << HostHealth << getClientX << getClientY << getClientScaleX << getClientScaleY;
						if (socket.send(sendInputs, HostIP, port) != sf::Socket::Done) {
							//std::cout << "missed a paket did you dissconecct" << std::endl;
						}
						sendInputs.clear();
					
					delete players[0];
					delete players[1];
					state = player2Wins;
				}
				if (isDeadClient == true) {
					std::cout << "Host Wins" << std::endl;
					sendInputs.clear();
					//host will figire out client is dead befre the client user so only send the clinets health to the client
					getHostX = players[0]->character.getPosition().x;
					getHostY = players[0]->character.getPosition().y;
					getHostScaleX = players[0]->character.getScale().x;
					getHostScaleY = players[0]->character.getScale().y;
					// std::cout << getHostScaleX << "scaleX    " << getHostScaleY << "scaleY    " << getHostX << " X        " << getHostY << " Y        " << std::endl;
					sendInputs.clear();
					clientHealth = players[1]->health;
					sendInputs << inputsHost[0] << inputsHost[1] << inputsHost[2] << clientHealth << getHostX << getHostY << getHostScaleX << getHostScaleY;

					if (socket.send(sendInputs, clientIP, clientPort) != sf::Socket::Done) {
						//std::cout << "missed a paket did you dissconecct" << std::endl;
					}
					sendInputs.clear();
					delete players[0];
					delete players[1];
					state = player1Wins;
				}
			}

			break;
		case controls:
			window.clear();
			BG.setTexture(controlsBG);
			BG.setScale(1.2, 0.8);
			computermouse3.setTexture(computermouseleft);
			computermouse7.setTexture(computermouseright);
			characterNameText.setPosition(310, 150);
			characterNameText.setString("Basic Controls");
			window.draw(BG);
			window.draw(backText);
			window.draw(rightArrow);
			window.draw(lightAttackText);
			window.draw(heavyAttackText);
			window.draw(rightMovementText);
			window.draw(leftMovementText);
			window.draw(computermouse3);
			window.draw(computermouse7);
			window.draw(characterNameText);
			window.display();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 10.5 && mousePosition.x < window.getSize().x / 12 * 10.5 + backText.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 7.5 && mousePosition.y < (window.getSize().y / 8) * 7.5 + backText.getLocalBounds().height) {
					window.draw(backButton);
					window.draw(backText);
					window.display();
					sf::sleep(sf::Time(sf::milliseconds(1000)));
					state = title;
				}
				if (mousePosition.x > window.getSize().x / 12 * 10 && mousePosition.x < window.getSize().x / 12 * 10 + rightArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + rightArrow.getLocalBounds().height) {
					state = controlsBilly;
					sf::sleep(sf::Time(sf::milliseconds(200)));
				}
			break;
		case controlsBilly:
			window.clear();		
			charFace.setScale(2, 2);
			charFace.setPosition(400, 100);
			charFace.setTexture(charFaceTexture);
			BG.setTexture(controlsBG);
			BG.setScale(1.2, 0.8);
			//BG.setPosition(100, 0);
			characterNameText.setPosition(650, 150);
			characterNameText.setString("Billy");
			computermouse1.setTexture(computermouseright);
			computermouse2.setTexture(computermouseright);
			computermouse3.setTexture(computermouseright);
			computermouse4.setTexture(computermouseright);

			computermouse5.setTexture(computermouseleft);
			computermouse6.setTexture(computermouseleft);
			computermouse7.setTexture(computermouseleft);
			computermouse8.setTexture(computermouseleft);

			computermouse9.setTexture(computermouseleft);
			computermouse10.setTexture(computermouseleft);
			computermouse11.setTexture(computermouseright);
			computermouse12.setTexture(computermouseright);

			computermouse13.setTexture(computermouseleft);
			computermouse14.setTexture(computermouseright);
			computermouse15.setTexture(computermouseleft);
			computermouse16.setTexture(computermouseright);

			window.draw(BG);
			window.draw(backText);
			window.draw(rightArrow);
			window.draw(leftArrow);
			window.draw(charFace);
			window.draw(characterNameText);
			window.draw(strongComboText);
			window.draw(fastComboText);
			window.draw(stunComboText);
			window.draw(damageComboText);
			window.draw(computermouse1);
			window.draw(computermouse2);
			window.draw(computermouse3);
			window.draw(computermouse4);
			window.draw(computermouse5);
			window.draw(computermouse6);
			window.draw(computermouse7);
			window.draw(computermouse8);
			window.draw(computermouse9);
			window.draw(computermouse10);
			window.draw(computermouse11);
			window.draw(computermouse12);
			window.draw(computermouse13);
			window.draw(computermouse14);
			window.draw(computermouse15);
			window.draw(computermouse16);

			window.display();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 10.5 && mousePosition.x < window.getSize().x / 12 * 10.5 + backText.getLocalBounds().width && mousePosition.y > (window.getSize().y / 8) * 7.5 && mousePosition.y < (window.getSize().y / 8) * 7.5 + backText.getLocalBounds().height) {
					window.draw(backButton);
					window.draw(backText);
					window.display();
					sf::sleep(sf::Time(sf::milliseconds(1000)));
					state = title;
				}
				if (mousePosition.x > window.getSize().x / 12 * 10 && mousePosition.x < window.getSize().x / 12 * 10 + rightArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + rightArrow.getLocalBounds().height) {
					state = controlsBillieta;
					sf::sleep(sf::Time(sf::milliseconds(200)));
				}
				if (mousePosition.x > window.getSize().x / 12 && mousePosition.x < window.getSize().x / 12 + leftArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + leftArrow.getLocalBounds().height) {
					state = controls;
					sf::sleep(sf::Time(sf::milliseconds(200)));
				}
			}
				break;
		case controlsBillieta:
			window.clear();
			charFace.setScale(2, 2);
			charFace.setPosition(400, 100);
			charFace.setTexture(char4FaceTexture);
			BG.setTexture(controlsBG);
			BG.setScale(1.2, 0.8);
			//BG.setPosition(100, 0);
			characterNameText.setPosition(625, 150);
			characterNameText.setString("Billieta");
			
			computermouse1.setTexture(computermouseright);
			computermouse2.setTexture(computermouseleft);
			computermouse3.setTexture(computermouseleft);
			computermouse4.setTexture(computermouseleft);

			computermouse5.setTexture(computermouseleft);
			computermouse6.setTexture(computermouseleft);
			computermouse7.setTexture(computermouseleft);
			computermouse8.setTexture(computermouseleft);

			computermouse9.setTexture(computermouseright);
			computermouse10.setTexture(computermouseright);
			computermouse11.setTexture(computermouseleft);
			computermouse12.setTexture(computermouseright);

			computermouse13.setTexture(computermouseleft);
			computermouse14.setTexture(computermouseright);
			computermouse15.setTexture(computermouseright);
			computermouse16.setTexture(computermouseleft);

			window.draw(BG);
			window.draw(backText);
			window.draw(leftArrow);
			window.draw(charFace);
			window.draw(characterNameText);
			window.draw(strongComboText);
			window.draw(fastComboText);
			window.draw(stunComboText);
			window.draw(damageComboText);
			window.draw(computermouse1);
			window.draw(computermouse2);
			window.draw(computermouse3);
			window.draw(computermouse4);
			window.draw(computermouse5);
			window.draw(computermouse6);
			window.draw(computermouse7);
			window.draw(computermouse8);
			window.draw(computermouse9);
			window.draw(computermouse10);
			window.draw(computermouse11);
			window.draw(computermouse12);
			window.draw(computermouse13);
			window.draw(computermouse14);
			window.draw(computermouse15);
			window.draw(computermouse16);
			window.display();
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 10.5 && mousePosition.x < window.getSize().x / 12 * 10.5 + backText.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 7.5 && mousePosition.y < (window.getSize().y / 8) * 7.5 + backText.getLocalBounds().height) {
					window.draw(backButton);
					window.draw(backText);
					window.display();
					sf::sleep(sf::Time(sf::milliseconds(1000)));
					state = title;
				}
				if (mousePosition.x > window.getSize().x / 12 && mousePosition.x < window.getSize().x / 12 + leftArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + leftArrow.getLocalBounds().height) {
					state = controlsBilly;
					sf::sleep(sf::Time(sf::milliseconds(200)));
				}
			}
			break;
		case billy:
			BG.setTexture(dojoBG);
			window.clear();
			window.draw(BG);
			characterNameText.setString("Billy");
			characterNameText.setOrigin(characterNameText.getLocalBounds().width / 2, characterNameText.getLocalBounds().height / 2);
			characterNameText.setPosition(600, 100);
			window.draw(characterNameText);
			window.draw(rightArrow);
			delayBetween += keepDeltaTimee;	
			idleTexture.loadFromFile("sprites/character1Idle.png");
			idlechar1.setTexture(idleTexture);
			if (delayBetween > 0.20f) {
				if (State < 4) {
					idlechar1.setTextureRect(idleRect[State]);
					idlechar1.setScale((window.getSize().x / 800) , (window.getSize().y / 600));					
					State++;
					delayBetween = 0;
				}
				else{
					State = 0;
				}
			}

			idlechar1.setScale(4, 4);
			idlechar1.setOrigin(idlechar1.getLocalBounds().width / 2, idlechar1.getLocalBounds().height / 2);
			idlechar1.setPosition(600, 400);
			window.draw(idlechar1);

			staminaText.setString("Stamina: " + std::to_string(characterStatStamina = 9));
			healthText.setString("Health: " + std::to_string(characterStatHealth = 7));
			speedText.setString("Speed: " + std::to_string(characterStatSpeed = 4));
			strengthText.setString("Strength: " + std::to_string(characterStatStrength = 6));
			window.draw(healthText);
			window.draw(strengthText);
			window.draw(staminaText);
			window.draw(speedText);
			window.display();
			
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (mousePosition.x > window.getSize().x / 12 * 10 && mousePosition.x < window.getSize().x / 12 * 10 + rightArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + rightArrow.getLocalBounds().height) {
					idlechar1.setTextureRect(idleRect4[0]);
					state = billieta;
				}
				
			}
			canEnter += keepDeltaTimee;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&& canEnter>2.f) {
				socket.setBlocking(true);
				//mousePosition.x  >window.getSize().x / 12 * 6 && mousePosition.x < window.getSize().x / 12 * 6 + idlechar1.getLocalBounds().width && mousePosition.y  >window.getSize().y / 8 * 4 && mousePosition.y < window.getSize().y / 8 * 4 + idlechar1.getLocalBounds().height
				socket.setBlocking(true);
				if (isHost == true) {
					whopickedHost = 0;
					characterSend.clear();
					characterSend << whopickedHost;
					if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
						std::cout << "HHHH a parket failed to send did you disconect?" << std::endl;
						std::cout << "HHHH client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
					}

					if (socket.receive(characterReceave, clientIP, clientPort) != sf::Socket::Done) {
						std::cout << "HHHH Fail" << std::endl;
					}
					else {
						characterReceave >> whopickedClient;
						std::cout << "HHHH this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						//sends the packet angan to allow the client to receave it
						if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
							std::cout << "HHHH a parket failed to send did you disconect?" << std::endl;
							std::cout << "HHHH client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
						}
						std::cout << "HHHH this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						state = play;
					}

				}
				else if(isHost==false) {
					whopickedClient = 0;
					characterSend.clear();
					characterSend << whopickedClient;
					if (socket.send(characterSend, HostIP, port) != sf::Socket::Done) {
						std::cout << "CCCC a parket failed to send did you disconect?" << std::endl;
					}

					if (socket.receive(characterReceave, HostIP, port) != sf::Socket::Done) {
						std::cout << "CCCC Fail" << std::endl;
					}
					else {
						characterReceave >> whopickedHost;
						if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
							std::cout << "CCCC a parket failed to send did you disconect?" << std::endl;
							std::cout << "CCCC client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
						}
						std::cout << "CCCC this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						state = play;
					}
				}
			}
			break;
		case billieta:
			BG.setTexture(dojoBG);
			window.clear();
			window.draw(BG);
			characterNameText.setString("Billieta");
			characterNameText.setOrigin(characterNameText.getLocalBounds().width / 2, characterNameText.getLocalBounds().height / 2);
			window.draw(characterNameText);
			window.draw(leftArrow);
			delayBetween += keepDeltaTimee;
			idleTexture4.loadFromFile("sprites/char4Idle.png");
			idlechar1.setTexture(idleTexture4);
			if (delayBetween > 0.20f) {
				if (State4 < 5) {
					idlechar1.setTextureRect(idleRect4[State4]);
					idlechar1.setScale((window.getSize().x / 800), (window.getSize().y / 600));
					State4++;
					delayBetween = 0;
				}
				else {
					State4 = 0;
				}
			}

			idlechar1.setScale(4, 4);
			idlechar1.setOrigin(idlechar1.getLocalBounds().width / 2, idlechar1.getLocalBounds().height / 2);
			idlechar1.setPosition(600, 400);
			
			window.draw(idlechar1);

			staminaText.setString("Stamina: " + std::to_string(characterStatStamina = 6));
			healthText.setString("Health: " + std::to_string(characterStatHealth = 4));
			speedText.setString("Speed: " + std::to_string(characterStatSpeed = 7));
			strengthText.setString("Strength: " + std::to_string(characterStatStrength = 9));
			window.draw(healthText);
			window.draw(strengthText);
			window.draw(staminaText);
			window.draw(speedText);
			window.display();
				if (mousePosition.x > window.getSize().x / 12 && mousePosition.x < window.getSize().x / 12 + leftArrow.getLocalBounds().width && mousePosition.y >(window.getSize().y / 8) * 3 && mousePosition.y < (window.getSize().y / 8) * 3 + leftArrow.getLocalBounds().height) {
					idlechar1.setTextureRect(idleRect[0]);
					state = billy;
				}
			
			}
			canEnter += keepDeltaTimee;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)&&canEnter>2.f) {
				//mousePosition.x  >window.getSize().x / 12 * 6 && mousePosition.x < window.getSize().x / 12 * 6 + idlechar1.getLocalBounds().width && mousePosition.y  >window.getSize().y / 8 * 4 && mousePosition.y < window.getSize().y / 8 * 4 + idlechar1.getLocalBounds().height
				//mousePosition.x > (window.getSize().x/12*6) - idlechar1.getLocalBounds().width / 2 && mousePosition.x < (window.getSize().x / 12 * 6) + idlechar1.getLocalBounds().width / 2 && mousePosition.y > (window.getSize().y / 8 * 6) - idlechar1.getLocalBounds().height / 2 && mousePosition.y < (window.getSize().y / 8 * 6) + idlechar1.getLocalBounds().height / 2
				std::cout << "work" << std::endl;
				if (isHost == true) {
					whopickedHost = 3;
					characterSend.clear();

					characterSend << whopickedHost;
					if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
						std::cout << "HHHH a parket failed to send did you disconect?" << std::endl;
						std::cout << "HHHH client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
					}

					if (socket.receive(characterReceave, clientIP, clientPort) != sf::Socket::Done) {
						std::cout << "HHHH Fail" << std::endl;
					}
					else {
						characterReceave >> whopickedClient;
						std::cout << "HHHH this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						//sends the packet angan to allow the client to receave it
						if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
							std::cout << "HHHH a parket failed to send did you disconect?" << std::endl;
							std::cout << "HHHH client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
						}
						std::cout << "HHHH this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						state = play;
					}

				}
				else if (isHost == false) {
					whopickedClient = 3;
					characterSend.clear();
					characterSend << whopickedClient;
					if (socket.send(characterSend, HostIP, port) != sf::Socket::Done) {
						std::cout << "CCCC a parket failed to send did you disconect?" << std::endl;
					}

					if (socket.receive(characterReceave, HostIP, port) != sf::Socket::Done) {
						std::cout << "CCCC Fail" << std::endl;
					}
					else {
						characterReceave >> whopickedHost;
						if (socket.send(characterSend, clientIP, clientPort) != sf::Socket::Done) {
							std::cout << "CCCC a parket failed to send did you disconect?" << std::endl;
							std::cout << "CCCC client ip =" << clientIP << std::endl << "HHHH clientport" << std::endl;
						}
						std::cout << "CCCC this is hostPick " << whopickedHost << std::endl << "this is clientPick " << whopickedClient << std::endl;
						state = play;
					}
				}
			}
			break;
			case player1Wins:
				window.clear();
				playerWinsText.setString("Player 1 Wins!");
				window.draw(playerWinsText);
				window.draw(playAgainText);
				window.display();
				break;
			case player2Wins:
				window.clear();
				playerWinsText.setString("Player 2 Wins!");
				window.draw(playerWinsText);
				window.draw(playAgainText);
				window.display();
				break;
		}

	}
		
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source 
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
