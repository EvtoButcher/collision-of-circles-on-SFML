#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
using namespace sf;

#define game_W 640
#define game_H 480
float x1 = game_W / 4;
float y_1 = game_H / 2;
float x2 = game_H / 3;
float y2 = game_W / 4 ;
float dx1 = rand() % 4;//кординаты векторов 
float dy1 = rand() % 4;
float dx2 = rand() % 4;
float dy2 = rand() % 2;
float r1 = 50;
float r2 = 30;
int collision = 0;

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode(game_W, game_H), "Shape Collision", Style::Close);
	window.setFramerateLimit(120);

	CircleShape shape(100.f);
	shape.setFillColor(Color::Green);

	CircleShape shape2(100.f);
	shape.setFillColor(Color::Red);

	Font font;
	font.loadFromFile("C:\\AdobeClean-Bold.ttf");
	Text text("", font, 35);
	
	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			
			if (event.type == Event::Closed)
				window.close();
		}

		x1 += dx1;
		y_1 += dy1;
		if ((x1 + r1 > game_W) || (x1 - r1 < 0)) {
			dx1 = -dx1;
		}
		if ((y_1 + r1 > game_H) || (y_1 - r1 < 0)) {
			dy1 = -dy1;
		}
		x2 += dx2;
		y2 += dy2;
		if ((x2 + r2 > game_W) || (x2 - r2 < 0)) {
			dx2 = -dx2;
		}
		if ((y2 + r2 > game_H) || (y2 - r2 < 0)) {
			dy2 = -dy2;
		}

		float Dx = x1 - x2;
		float Dy = y_1 - y2;
		float G = sqrt(Dx * Dx + Dy * Dy); // гипотинуза 
		if (G == 0) {
			G = 0.01;
		}
		float s = Dx / G; // sin
		float e = Dy / G; // cos

		if (G < r1 + r2) { // если прризошло столкновение, поворачиваем кординаты 

			collision++;

			float Vn1 = dx2 * s + dy2 * e; 
			float Vn2 = dx1 * s + dy1 * e;

			float Vt1 = -dx2 * e + dy2 * s;
			float Vt2 = -dx1 * e + dy1 * s;

			float o = Vn2;
			Vn2 = Vn1;
			Vn1 = o;

			dx1 = Vn2 * s - Vt2 * e;
			dy1 = Vn2 * e + Vt2 * s;
			dx2 = Vn1 * s - Vt1 * e;
			dy2 = Vn1 * e + Vt1 * s;
		}
		
		window.clear();
	
			shape.setRadius(r1);
			shape.setOrigin(r1, r1);
			shape.setPosition(x1, y_1);

		window.draw(shape);

			shape2.setRadius(r2);
			shape2.setOrigin(r2, r2);
			shape2.setPosition(x2, y2);

		window.draw(shape2);

			std::ostringstream playerCkor;
			playerCkor << collision;
			text.setFillColor(Color::White);
			text.setString("collision: " + playerCkor.str());
			text.setPosition(10,10);

		window.draw(text);
		
		window.display();
	}

	return 0;
}