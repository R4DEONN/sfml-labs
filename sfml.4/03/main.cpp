#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

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
		default:
			break;
		}
	}
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow& window, sf::Sprite& cat)
{
	window.clear(sf::Color::White);
	window.draw(cat);
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
		sf::VideoMode::getDesktopMode(),
		"Arrow follows mouse", sf::Style::Fullscreen, settings);

	sf::Vector2f mousePosition;
	sf::Texture playerTexture;
	if (!playerTexture.loadFromFile("img.png"))
	{
		wcerr << L"Не удалось загрузить изображение" << endl;
		exit(1);
	}

	sf::Sprite player(playerTexture);
	player.setPosition(
		sf::VideoMode::getDesktopMode().width / 2,
		sf::VideoMode::getDesktopMode().height / 2
		);
	sf::Vector2f targetSize(sf::VideoMode::getDesktopMode().height / 16, sf::VideoMode::getDesktopMode().height / 16); //целевой размер

	player.setScale(
		targetSize.x / player.getLocalBounds().width,
		targetSize.y / player.getLocalBounds().height);

	while (window.isOpen())
	{
		pollEvents(window, mousePosition);
		redrawFrame(window, player);
	}
}