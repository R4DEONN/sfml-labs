#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

void init(sf::ConvexShape& pointer)
{
	pointer.setPointCount(3);
	pointer.setPoint(0, { 40, 0 });
	pointer.setPoint(1, { -20, -20 });
	pointer.setPoint(2, { -20, 20 });
	pointer.setPosition({ 400, 300 });
	pointer.setFillColor(sf::Color(0xFF, 0x80, 0x00));
}

float toDegrees(float radians)
{
	return float(double(radians) * 180.0 / M_PI);
}

float onMouseMove(const sf::Event::MouseMoveEvent& event, sf::Vector2f& mousePosition)
{
	std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

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

void update(const sf::Vector2f& mousePosition, sf::ConvexShape& pointer, sf::Clock& clock)
{
	const sf::Vector2f delta = mousePosition - pointer.getPosition();
	float angle = toDegrees(atan2(delta.y, delta.x));
	const float dt = clock.restart().asSeconds();
	float dA;
	float prevRotation = pointer.getRotation();

	if (angle < 0)
	{
		angle += 360;
	}
	if (std::abs(angle - prevRotation) > 15)
	{
		if (std::abs(prevRotation - angle) > std::abs(prevRotation - angle + 360))
		{
			dA = 15 * dt;
		}
		else
		{
			dA = -15 * dt;
		}
	}
	else
	{
		dA = (angle - prevRotation) * dt;
	}

	pointer.rotate(dA);
}

void redrawFrame(sf::RenderWindow& window, sf::ConvexShape& pointer)
{
	window.clear();
	window.draw(pointer);
	window.display();
}

int main()
{
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;

	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(
			{ WINDOW_WIDTH, WINDOW_HEIGHT }),
		"Prints mouse events to terminal",
		sf::Style::Default, settings);

	sf::ConvexShape pointer;
	sf::Vector2f mousePosition;

	init(pointer);
	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		update(mousePosition, pointer, clock);
		redrawFrame(window, pointer);
	}
}