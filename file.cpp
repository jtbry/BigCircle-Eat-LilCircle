#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#define MAXDOTS 120
int WINDOWH = 500;
int WINDOWW = 500;
int dots = 0, runs = 0, eaten= 0, spawned = 0;
using namespace sf;
std::vector<CircleShape> circles;
char score[90];
int oldscore = 0;
void checkCollision(CircleShape o)
{
	for (int i = 0; i < circles.size(); i++)
	{
		if (o.getPosition().x >= (circles.at(i).getPosition().x - 20) && o.getPosition().x <= (circles.at(i).getPosition().x + 20) &&
			o.getPosition().y >= (circles.at(i).getPosition().y - 20) && o.getPosition().y <= (circles.at(i).getPosition().y + 20)) {
			circles.erase(circles.begin() + i);
			dots--;
			eaten++;
			printf("\rEaten %d\n", eaten);
		}
	}
}
int main() {

	RenderWindow window(VideoMode(WINDOWH, WINDOWW), "Particle Eating System (I hate sfml)");
	window.setFramerateLimit(30);
	Font arial;
	if (!arial.loadFromFile("Ubuntu-M.ttf")) {
		printf("Failed to load font...");
		return 1;
	}
	CircleShape object(20, 20);
	object.setFillColor(Color::Cyan);
	object.setPosition(10, 10);
	circles.resize(120);
	while (window.isOpen()) {
		window.clear();
		snprintf(score, sizeof(score), "Score: %d\nSpawned: %d", eaten, spawned);
		oldscore = eaten;
		sf::String scoretext;
		sf::Text text;
		text.setFont(arial);
		text.setString(score);
		text.setCharacterSize(24);
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		object.move(rand() % 61 + (-30), rand() % 61 + (-30));
		if (object.getPosition().x >= WINDOWW - 20) {
			object.move(-15, 0);
		}
		if (object.getPosition().x <= 20) {
			object.move(15, 0);
		}
		if (object.getPosition().y >= WINDOWH - 20) {
			object.move(0, -15);
		}
		if (object.getPosition().y <= 20) {
			object.move(0, 15);
		}
		while (dots != MAXDOTS) {
			CircleShape shape;
			shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255)); // Looks interesting
			shape.setPosition(rand() % 500, rand() % 500);
			shape.setRadius(2);
			window.draw(shape);
			circles.push_back(shape);
			dots++;
			spawned++;
		}
		for (int i = 0; i < circles.size(); i++) {
			window.draw(circles.at(i));
		}
		checkCollision(object);
		window.draw(text);
		window.draw(object);
		window.display();
	}
	return 0;
}