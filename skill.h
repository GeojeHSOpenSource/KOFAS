#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Player;

class Skill
{
public:
	std::string name;
	float cooldown;

	virtual void use(Player& user, Player& target) = 0;
	virtual bool canUse(Player& user, Player& target) { return true; }
};

class DashSkill : public Skill
{
public:
	DashSkill();
	void use(Player& user, Player& target) override;
};

class AttackSkill
{
public:
	void use(Player& user, Player& target, sf::RenderWindow& window);

	float getDistance(sf::Vector2f a, sf::Vector2f b);
	void dealDamage(Player& target, int damage);
	sf::Vector2f getDirection(sf::Vector2f from, sf::Vector2f to);
};

class StunSkill : public Skill
{
public:
	StunSkill();
	void use(Player& user, Player& target) override;
	bool canUse(Player& user, Player& target) override;

	float getDistance(sf::Vector2f a, sf::Vector2f b);
};

class ShieldSkill : public Skill
{
public:
	ShieldSkill();
	void use(Player& user, Player& target) override;
};