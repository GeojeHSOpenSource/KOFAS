#include <SFML/Graphics.hpp>
#include "player.h"
#include "skill.h"

enum GameState
{
	START,
	PLAYING,
	ROUND_END
};

GameState gameState = START;

Player survivor(200, 300, false);
Player killer(700, 300, true);

sf::Font font;

sf::Text winnerText;

sf::Text startText;

int killerScore = 0;
int survivorScore = 0;

sf::Text scoreText;

float roundTimer = 0;

float startTextTimer = 0.0f;

void randomSkill() {
    int r = rand() % 3;

    if (r == 0)
        survivor.skill = new StunSkill();
    else if (r == 1)
        survivor.skill = new DashSkill();
    else
        survivor.skill = new ShieldSkill();
    startText.setString(
	"Survivor Skill: " + survivor.skill->name
    );
    startTextTimer = 3.0f;
}
int main()
{   
    AttackSkill* skill = new AttackSkill();

    randomSkill();

    roundTimer = 50.0f;
    gameState = PLAYING;
    font.loadFromFile("arial.ttf");
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Asym 1v1 Game");
	window.setFramerateLimit(60);

    startText.setFont(font);
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(250, 200);
    startTextTimer = 3.0f;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setPosition(10, 10);
    winnerText.setFont(font);
    winnerText.setCharacterSize(50);
    winnerText.setFillColor(sf::Color::White);
    winnerText.setPosition(350, 300);


	sf::Clock clock;

    while (window.isOpen())
	{

        scoreText.setString(
            "Killer: " + std::to_string(killerScore) +
            "  Survivor: " + std::to_string(survivorScore)
        );

        if (sf::Keyboard::isKeyPressed(survivor.skillKey))
        {
            survivor.useSkill(killer);
        }

        // 킬러 스킬
        if (sf::Keyboard::isKeyPressed(killer.skillKey))
        {
            skill->use(killer, survivor, window);
    
        }

		float deltaTime = clock.restart().asSeconds();

		// 이벤트 처리
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        if (startTextTimer > 0)
            startTextTimer -= deltaTime;

		// 입력 / 업데이트
		survivor.update(deltaTime);
		killer.update(deltaTime);

		// 충돌 체크
		if (survivor.body.getGlobalBounds().intersects(
			killer.body.getGlobalBounds()))
		{
			// 맞았을 때 처리
		}

        roundTimer -= deltaTime;

		if (gameState == PLAYING)
        {
            if (survivor.hp <= 0)
            {
                killerScore++;
                gameState = ROUND_END;
                roundTimer = 3.0f;
                winnerText.setString("Killer Wins!");
            }

            if (roundTimer <= 0)
            {
                survivorScore++;
                gameState = ROUND_END;
                roundTimer = 3.0f;
                winnerText.setString("Survivor Wins!");
            }
        }

        if (gameState == ROUND_END)
        {

            if (roundTimer <= 0)
            {
                randomSkill();
                survivor.hp = 100;
                killer.hp = 100;
                roundTimer = 50.0f;
                survivor.body.setPosition(200, 300);
                killer.body.setPosition(700, 300);

                gameState = PLAYING;
            }
        }
		window.clear();

        survivor.draw(window);
        killer.draw(window);

        window.draw(scoreText);

        if (gameState == ROUND_END)
            window.draw(winnerText);

        if (startTextTimer > 0)
        {
            window.draw(startText);
        }
        window.display();
	}

	return 0;
}