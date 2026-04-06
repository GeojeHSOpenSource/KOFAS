#pragma once
#include <SFML/Graphics.hpp>

class Skill;

class Player {
public:
	sf::RectangleShape body;
	float speed;
	int hp;
	bool isKiller;

	bool stunned;
	float stunTimer;

	sf::RectangleShape attackHitbox;
	float attackTime;

	float shieldTime;
	float skillCooldown;

	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBar;
	int maxHp;

	sf::Keyboard::Key skillKey;
	Skill* skill;

	Player(float x, float y, bool killer);

	void update(float dt);
	void move(float dt);
	void draw(sf::RenderWindow& window);
	void useSkill(Player& target);
};