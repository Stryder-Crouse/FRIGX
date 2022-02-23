#pragma once
#include "imports.h"
class Ui {
public:
	float maxHealthHost;
	float maxHealthClient;

	sf::ConvexShape hostBoarder;//stores healths boarder rectangle
	sf::ConvexShape hostHealthbar;//stores green Health bar based off player current health
	sf::ConvexShape hostBlackspace;//stores boarder rectangle behind health

	sf::ConvexShape clientBoarder;//stores sheilds boarder rectangle
	sf::ConvexShape clientHealthbar;//stores blue Sheald bar based off player current sheild
	sf::ConvexShape clientBlackspace;//stores boarder rectangle behind sheild bar
	void getHostMaxHealth(float maxhealth);
	void updateHostHealthBar(float hostHealth);
	void getClientMaxHealth(float maxhealth);
	void updateClientHealthBar(float clientHealth);
};