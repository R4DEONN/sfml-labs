#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

// Инициализирует фигуру-стрелку
void initArrow(sf::ConvexShape& arrow)
{
	arrow.setPosition({ 400, 300 });

	arrow.setPointCount(7);
	arrow.setPoint(0, { -50, -20 });
	arrow.setPoint(1, { 0, -20 });
	arrow.setPoint(2, { 0, -40 });
	arrow.setPoint(3, { 47, 0 });
	arrow.setPoint(4, { 0, 40 });
	arrow.setPoint(5, { 0, 20 });
	arrow.setPoint(6, { -50, 20 });
	arrow.setFillColor(sf::Color(0xF2, 0xFF, 0));
	arrow.setOutlineColor(sf::Color(sf::Color::Black));
	arrow.setOutlineThickness(4);
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

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f& mousePosition, sf::ConvexShape& arrow, sf::Clock& clock)
{
	const sf::Vector2f delta = mousePosition - arrow.getPosition();
	float angle = toDegrees(atan2(delta.y, delta.x));
	const float dt = clock.restart().asSeconds();
	float dA{};
	float prevRotation = arrow.getRotation();

	if (angle < 0)
	{
		angle += 360;
	}

	if (abs(angle - prevRotation) < 0.1)
	{
		return;
	}
//	if (std::abs(angle - prevRotation) > 90)
//	{

//	cout << angle << " " << prevRotation << endl;
//	cout << std::abs(prevRotation - angle) << " " << std::abs(prevRotation - angle + 360) << " "
//		 << (std::abs(prevRotation - angle) > std::abs(prevRotation - angle + 360)) << endl;

	if (std::abs(prevRotation - angle) <= std::abs(prevRotation - angle + 360))
	{
		dA = 90 * dt;
	}
	else
	{
		dA = -90 * dt;
	}
//	}
//	else
//	{
//		dA = angle - prevRotation;
//	}
	arrow.rotate(dA);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& arrow)
{
	window.clear(sf::Color::White);
	window.draw(arrow);
	window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(
		sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Arrow follows mouse", sf::Style::Default, settings);

	sf::ConvexShape arrow;
	sf::Vector2f mousePosition;
	sf::Clock clock;

	initArrow(arrow);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, arrow, clock);
		redrawFrame(window, arrow);
	}
}