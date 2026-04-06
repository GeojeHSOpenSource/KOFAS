#include "Skill.h"
#include "Player.h"
#include <cmath>

class Player;
DashSkill::DashSkill()
{
	name = "Dash";
	cooldown = 5.0f;
}

void DashSkill::use(Player& user, Player& target)
{
	user.body.move(100, 0);
}


// AttackSkill
AttackSkill::AttackSkill()
{
	name = "Slash";
	cooldown = 1.0f;
}

float AttackSkill::getDistance(sf::Vector2f a, sf::Vector2f b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

void AttackSkill::dealDamage(Player& target, int damage)
{
	if (target.shieldTime > 0)
		damage /= 2;

	target.hp -= damage;
	if (target.hp < 0)
		target.hp = 0;
}

sf::Vector2f AttackSkill::getDirection(sf::Vector2f from, sf::Vector2f to)
{
	sf::Vector2f dir = to - from;
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length != 0)
		dir /= length;

	return dir;
}

void AttackSkill::use(Player& user, Player& target)
{
	sf::Vector2i mousePixel = sf::Mouse::getPosition();
	sf::Vector2f mouse = sf::Vector2f(mousePixel.x, mousePixel.y);

	sf::Vector2f dir = getDirection(user.body.getPosition(), mouse);

	user.attackHitbox.setPosition(
		user.body.getPosition() + dir * 40.0f
	);

	user.attackTime = 0.2f;

	if (user.attackHitbox.getGlobalBounds().intersects(
		target.body.getGlobalBounds()))
	{
		dealDamage(target, 10);
	}
}


// StunSkill
StunSkill::StunSkill()
{
	name = "Stun";
	cooldown = 5.0f;
}

float StunSkill::getDistance(sf::Vector2f a, sf::Vector2f b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool StunSkill::canUse(Player& user, Player& target)
{
	return getDistance(user.body.getPosition(), target.body.getPosition()) < 120;
}

void StunSkill::use(Player& user, Player& target)
{
	target.stunned = true;
	target.stunTimer = 2.0f;
}


// ShieldSkill
ShieldSkill::ShieldSkill()
{
	name = "Shield";
	cooldown = 6.0f;
}

void ShieldSkill::use(Player& user, Player& target)
{
	user.shieldTime = 3;
}