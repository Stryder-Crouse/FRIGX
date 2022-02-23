#include "pch.h"
#include "Character.h"
#include"char1.h"
Character::Character()
{
}

void Character::updateDelta(float &delta, float currentDelta)
{
	delta = currentDelta;
}

bool Character::isdead(int health)
{
	if (health <= 0) {
		return true;
	}
	else {
		return false;
	}
}




