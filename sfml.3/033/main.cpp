#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

constexpr unsigned WINDOW_WIDTH = 1280;
constexpr unsigned WINDOW_HEIGHT = 720;

struct Eye
{
	sf::CircleShape white;
	sf::CircleShape pupil;
};

// Инициализирует фигуру-стрелку
void initEyes(Eye& leftEye, Eye& rightEye)
{
	leftEye.white.setFillColor(sf::Color(sf::Color::White));
	leftEye.pupil.setFillColor(sf::Color(sf::Color::Black));
	rightEye.white.setFillColor(sf::Color(sf::Color::White));
	rightEye.pupil.setFillColor(sf::Color(sf::Color::Black));

	leftEye.white.setPosition({WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2});
	leftEye.pupil.setPosition({WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2});
	leftEye.white.setRadius(70);
	leftEye.pupil.setRadius(25);
	leftEye.white.setScale(1, 2);
	leftEye.white.setOrigin(35, 70);
	leftEye.pupil.setOrigin(25, 25);

	rightEye.white.setPosition({WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2});
	rightEye.pupil.setPosition({WINDOW_WIDTH / 2 + 75, WINDOW_HEIGHT / 2});
	rightEye.white.setRadius(70);
	rightEye.pupil.setRadius(25);
	rightEye.white.setScale(1, 2);
	rightEye.white.setOrigin(35, 70);
	rightEye.pupil.setOrigin(25, 25);
}

float onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseMoved:
			onMouseMove(event.mouseMove, mousePosition);
			break;
		default:
			break;
		}
	}
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f& mousePosition, Eye& leftEye, Eye& rightEye)
{
	const sf::Vector2f leftEyePos = leftEye.white.getPosition();
	sf::Vector2f leftDelta  = mousePosition - leftEyePos;
	if (leftDelta.x > 35 * cos(abs(leftDelta.y) / 70))
	{
		leftDelta.x = 35 * cos(abs(leftDelta.y / leftDelta.x) * 2);
	}
	else if (leftDelta.x < -35 * cos(abs(leftDelta.y) / 70))
	{
		leftDelta.x = -35 * cos(abs(leftDelta.y / leftDelta.x) * 2);
	}
	if (leftDelta.y > 70)
	{
		cout << leftDelta.x << " " << sin(abs(leftDelta.x) / 35) << endl;
		leftDelta.y = 70 * sin(abs(leftDelta.x) / 35);
	}
	else if (leftDelta.y < -70)
	{
		leftDelta.y = -70 * sin(abs(leftDelta.x) / 35);
	}
	leftEye.pupil.setPosition({
		leftEyePos.x + leftDelta.x + 35,
		leftEyePos.y + leftDelta.y
	});

	const sf::Vector2f rightEyePos = rightEye.white.getPosition();
	sf::Vector2f rightDelta = mousePosition - rightEyePos;
	if (rightDelta.x > 35)
	{
		rightDelta.x = 35 * cos(abs(rightDelta.y) / 70);
	}
	else if (rightDelta.x < -35)
	{
		rightDelta.x = -35 * cos(abs(rightDelta.y) / 70);
	}
	if (rightDelta.y > 70)
	{
		rightDelta.y = 70;
	}
	else if (rightDelta.y < -70)
	{
		rightDelta.y = -70;
	}
	rightEye.pupil.setPosition({
		rightEyePos.x + 35 / (float(WINDOW_WIDTH) / 2) * rightDelta.x + 35,
		rightEyePos.y + 70 / (float(WINDOW_WIDTH) / 2 - 35) * rightDelta.y
	});
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow& window, Eye& leftEye, Eye& rightEye)
{
	window.clear();
	window.draw(leftEye.white);
	window.draw(leftEye.pupil);
	window.draw(rightEye.white);
	window.draw(rightEye.pupil);
	window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Eyes follows mouse", sf::Style::Default, settings);

	Eye leftEye;
	Eye rightEye;
	sf::Vector2f mousePosition;

	initEyes(leftEye, rightEye);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, leftEye, rightEye);
		redrawFrame(window, leftEye, rightEye);
	}
}