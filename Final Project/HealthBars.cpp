#include "pch.h"
#include "HealthBars.h"

void Ui::getHostMaxHealth(float maxhealth)
{
	maxHealthHost = maxhealth;
}

void Ui::updateHostHealthBar(float hostHealth)
{
	hostBoarder.setFillColor(sf::Color::Blue);
	hostBoarder.setPointCount(4);
	hostBoarder.setPoint(0,sf::Vector2f(0,0));
	hostBoarder.setPoint(1, sf::Vector2f(20+maxHealthHost/3, 0));
	hostBoarder.setPoint(2, sf::Vector2f(20+maxHealthHost / 3, 70));
	hostBoarder.setPoint(3, sf::Vector2f(0, 70));

	hostBlackspace.setFillColor(sf::Color::Black);
	hostBlackspace.setPointCount(4);
	hostBlackspace.setPoint(0, sf::Vector2f(10, 10));
	hostBlackspace.setPoint(1, sf::Vector2f(10+(maxHealthHost / 3) , 10));
	hostBlackspace.setPoint(2, sf::Vector2f(10+(maxHealthHost / 3) , 60));
	hostBlackspace.setPoint(3, sf::Vector2f(10, 60));

	hostHealthbar.setFillColor(sf::Color::Red);
	hostHealthbar.setPointCount(4);
	hostHealthbar.setPoint(0, sf::Vector2f(10, 10));
	hostHealthbar.setPoint(1, sf::Vector2f(10+(hostHealth / 3) , 10));
	hostHealthbar.setPoint(2, sf::Vector2f(10+(hostHealth / 3) , 60));
	hostHealthbar.setPoint(3, sf::Vector2f(10, 60));

}

void Ui::getClientMaxHealth(float maxhealth)
{
	maxHealthClient = maxhealth;
}

void Ui::updateClientHealthBar(float clientHealth)
{
	clientBoarder.setFillColor(sf::Color::Cyan);
	clientBoarder.setPointCount(4);
	clientBoarder.setPoint(0, sf::Vector2f(1200, 0));
	clientBoarder.setPoint(1, sf::Vector2f(1200-(maxHealthClient / 3)-20, 0));
	clientBoarder.setPoint(2, sf::Vector2f(1200 - (maxHealthClient / 3)-20, 70));
	clientBoarder.setPoint(3, sf::Vector2f(1200, 70));

	clientBlackspace.setFillColor(sf::Color::Black);
	clientBlackspace.setPointCount(4);
	clientBlackspace.setPoint(0, sf::Vector2f(1190, 10));
	clientBlackspace.setPoint(1, sf::Vector2f(1190 - ((maxHealthClient / 3)), 10));
	clientBlackspace.setPoint(2, sf::Vector2f(1190 - ((maxHealthClient / 3) ), 60));
	clientBlackspace.setPoint(3, sf::Vector2f(1190, 60));

	clientHealthbar.setFillColor(sf::Color::Green);
	clientHealthbar.setPointCount(4);
	clientHealthbar.setPoint(0, sf::Vector2f(1190, 10));
	clientHealthbar.setPoint(1, sf::Vector2f(1190 - ((clientHealth / 3)), 10));
	clientHealthbar.setPoint(2, sf::Vector2f(1190 - ((clientHealth / 3) ), 60));
	clientHealthbar.setPoint(3, sf::Vector2f(1190, 60));
}
