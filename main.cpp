#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>

std::string str(double a){
	return std::to_string(a);
}

double random(unsigned int seed, double M, double N) {
	if (seed != 0) srand(seed);
	return M + (rand() / (RAND_MAX / (N - M)));
}

std::string Idontknow1(std::string c, int a, int b){
	std::string ret = "";
	if (b > c.size()){
		b = c.size();
	}
	for (unsigned int x = a; x < b; x++){
		ret += c[x];
	}
	return ret;
}

int main(){
	random(69,-100,100);
	//Define the Window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 500), "De Banu's Adventure",sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(30);

	//Define the Variables
	int MOUSEX = 0;
	int MOUSEY = 0;
	bool RIGHTCLICK = false;
	bool LEFTCLICK = false;
	auto menu = "";
	auto changemenu = "intro";
	double Transition = 0;
	int MOUSEWHEEL = 0;
	std::vector<double> var;
	sf::Font font;
	if (!font.loadFromFile("F1.ttf"))
	{
    	return 1;
	}
	//While window is open
	while (window.isOpen()){
		//If menu change
		if (changemenu != menu){
			Transition += (1-Transition)/10;
			if (Transition > 0.9) {
				if (changemenu == "intro") var = std::vector<double>{0};
				menu = changemenu;
			}
			RIGHTCLICK = false;
			LEFTCLICK = false;
		} else Transition += (0-Transition)/10;

		//Window events
		sf::Event event;
		while (window.pollEvent(event)){
			if(event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == 0) RIGHTCLICK = true;
				else LEFTCLICK = true;
				std::cout << "Pressed " << event.mouseButton.button <<'\n';
			}
			if(event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == 0) RIGHTCLICK = false;
				else LEFTCLICK = false;
				std::cout << "Release " << event.mouseButton.button <<'\n';
			};
			if(event.type == sf::Event::Closed) window.close();
			if(event.type == sf::Event::MouseWheelMoved){
				MOUSEWHEEL = event.mouseWheel.delta;
				std::cout << event.mouseWheel.delta << '\n';
			}
			if(event.type == sf::Event::MouseMoved){
				auto a = sf::Mouse::getPosition(window);
				MOUSEX = a.x;
				MOUSEY = a.y;
			}
		}

		//The Window
		if (menu == "intro"){
			window.clear(sf::Color(200*(1-Transition),200*(1-Transition),200*(1-Transition)));
			var[0] += 1;
			std::cout<< int(var[0]/3) << '\n';
			sf::RectangleShape Rect;
			for (unsigned int x = 0; x < 80; x++){
				for (unsigned int y = 0; y < 50;y++){
					Rect.setSize(sf::Vector2f(10,10));
					double C = random(0,190*(1-Transition),200*(1-Transition));
					Rect.setFillColor(sf::Color(C,C,C));
					Rect.setPosition(x*10,y*10);
					window.draw(Rect);
				}
			}
			sf::Text text;
			text.setFont(font);
			text.setString(Idontknow1("De Banu's Adventure",0,int(var[0]/3)));
			text.setCharacterSize(50);
			if (var[0] < 70) text.setRotation(75*Transition);
			else text.setRotation(0);
			text.setFillColor(sf::Color(200*Transition,200*Transition,200*Transition));
			if ( 70 > var[0] && var[0] > 50 ) {
				text.setPosition(150+random(0,-2,2),200+random(0,-2,2));
			}else{
				if (var[0] < 70)text.setPosition(150*(1-Transition),200*(1-Transition));
				else text.setPosition(150,200);
			}
			window.draw(text);
			if ( var[0] > 150 ){
				changemenu = "menu";
			}
		}
		window.display();
	}
}