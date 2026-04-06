#include "player.h"
#include "Skill.h"

Player::Player(float x, float y, bool killer)
{
	isKiller = killer;
	stunned = false;
	shieldTime = 0;
	skillCooldown = 0;

	attackHitbox.setSize(sf::Vector2f(80, 30));
	attackHitbox.setFillColor(sf::Color(255, 255, 0, 120));
	attackTime = 0;

	if (isKiller)
		skillKey = sf::Keyboard::RControl;
	else
		skillKey = sf::Keyboard::F;

	body.setSize(sf::Vector2f(50, 50));
	body.setPosition(x, y);

	maxHp = 100;
	hp = 100;

	hpBarBack.setSize(sf::Vector2f(50, 5));
	hpBarBack.setFillColor(sf::Color(50, 50, 50));

	hpBar.setSize(sf::Vector2f(50, 5));
	hpBar.setFillColor(sf::Color::Green);
}

void Player::update(float dt)
{
	hpBarBack.setPosition(body.getPosition().x, body.getPosition().y - 10);
	hpBar.setPosition(body.getPosition().x, body.getPosition().y - 10);

	float hpPercent = (float)hp / maxHp;
	hpBar.setSize(sf::Vector2f(50 * hpPercent, 5));

	if (attackTime > 0)
		attackTime -= dt;

	if (stunned)
	{
		stunTimer -= dt;
		if (stunTimer <= 0)
			stunned = false;
		return;
	}

	move(dt);

	if (skillCooldown > 0)
		skillCooldown -= dt;

	if (shieldTime > 0)
		shieldTime -= dt;
}

void Player::useSkill(Player& target)
{
	if (!skill) return;
	if (skillCooldown > 0) return;
	if (!skill->canUse(*this, target)) return;

	skill->use(*this, target);
	skillCooldown = skill->cooldown;
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
	window.draw(hpBarBack);
	window.draw(hpBar);

	if (attackTime > 0)
		window.draw(attackHitbox);
}

void Player::move(float dt)
{
	if (!isKiller)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			body.move(0, -speed * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			body.move(0, speed * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			body.move(-speed * dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			body.move(speed * dt, 0);
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			body.move(0, -speed * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			body.move(0, speed * dt);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			body.move(-speed * dt, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			body.move(speed * dt, 0);
	}
}