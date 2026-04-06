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
	{
		skillKey = sf::Keyboard::Slash;
		speed = 150;
	}
	else
	{
		skillKey = sf::Keyboard::F;
		speed = 140;
	}

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
		body.setFillColor(sf::Color(100, 100, 255, 120));
		if (stunTimer <= 0)
			body.setFillColor(sf::Color(255, 255, 255, 255));
			stunned = false;
		return;
	}

	if (isKiller) {
		body.setFillColor(sf::Color(255, 255, 0, 120));
	}
	else if (shieldTime > 0) {
		body.setFillColor(sf::Color(100, 255, 100, 120));
	}
	else {
		body.setFillColor(sf::Color(255, 255, 255, 255));
	}

	move(dt);

	if (skillCooldown > 0)
		skillCooldown -= dt;

	if (shieldTime > 0)
		shieldTime -= dt;
}

void Player::useSkill(Player &target)
{
	if (!skill)
		return;
	if (skillCooldown > 0)
		return;
	if (!skill->canUse(*this, target))
		return;

	skill->use(*this, target);
	skillCooldown = skill->cooldown;
}

void Player::draw(sf::RenderWindow &window)
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

	sf::Vector2f pos = body.getPosition();

    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x > 1000 - body.getSize().x) pos.x = 1000 - body.getSize().x;
    if (pos.y > 700 - body.getSize().y) pos.y = 700 - body.getSize().y;

    body.setPosition(pos);
}