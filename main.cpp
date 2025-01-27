

#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include "ft_ingest_config.h"

int main()
{
	bool	circleExists = true;
	bool	squareExists = true;
	bool	circleColorTriggered = false;
	bool	rectColorTriggered = false;
	bool	rectTextTriggered = false;
	bool	circleTextTriggered = false;
	float	circleRadius = 100.0f;
	int		circleSegment = 100;
	int		currentShape = 0;
	unsigned int		window_height = 0;
	unsigned int		window_width = 0; 
	float		circleColor[3] = {(float)204/255, (float)77/255, (float)5/255};
	float		rectColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
	float		scaleVal = 2.0;
	float		prevScale = 2.0;

	std::vector<ft_custom_circle> circles;
	std::vector<ft_custom_rect> rectangles;

	//marshal config files passando alle funzioni questi vectors.
	static char buffer[128] = "";
	

	sf::Font font;

	ft_font ex_font;

	ft_marshal_config_file(ex_font, circles, rectangles,window_height, window_width );
	std::cout << "num of circles is " << circles.size() << "\n";
	std::cout << "num of rectangles is " << rectangles.size() << "\n";
	sf::RenderWindow window(sf::VideoMode(window_width, window_height ), "Esercizio numero 1");
	sf::Event e;
	ImGui::SFML::Init(window);

	sf::Time deltaClock;
	sf::Clock dt;

	const int option_size = rectangles.size() + circles.size();
	const char** rect_visibility_option = new const char*[option_size]();

	for ( int i = 0; i < rectangles.size(); i++)
	{
		rect_visibility_option[i] = rectangles[i].rect_name.c_str();
	}
	for (int i = 0; i < circles.size(); i++)
	{
		rect_visibility_option[rectangles.size() + i] = circles[i].circle_name.c_str();
	}


	if (!font.loadFromFile(ex_font.font_path))
	{
		std::cout << "Errore caricamento font" << "\n";
	}

	std::vector<sf::Text> rect_texts;
	std::vector<sf::Text> circles_texts;

	set_rects_texts(rect_texts, rectangles, font, ex_font);
	set_circles_texts(circles_texts, circles, font, ex_font);

while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			ImGui::SFML::ProcessEvent(e);
			if (e.type == sf::Event::Closed)
				window.close();
		}
		float deltaTime = dt.restart().asSeconds();

		ImGui::SFML::Update(window, sf::seconds(deltaTime) );

		ImGui::Begin("Finestra Iniziale");
			ImGui::Text("Ciao benvenuto in questa Demo");
			
			ImGui::Checkbox("Circle", &circleExists);
			ImGui::Checkbox("Square", &squareExists);
			ImGui::Combo("Select shape: ", &currentShape, rect_visibility_option, option_size);
/*
			for (size_t i = 0; i < option_size; i++) {
				if (option_size <= rectangles.size())
					ImGui::SliderFloat("Size", &rectangles[i].size_x, 50.0f, 300.0f);
				else if (option_size > rectangles.size())
					ImGui::SliderFloat("Radius", &circles[i].radius, 50.0f, 300.0f);
			}
			*/
			


			//ImGui::SliderInt("Sides", &circleSegment, 3, 150);

			//if (currentShape < rectangles.size())
			ImGui::SliderFloat("Scale", &scaleVal, 2.0, 10.0);
			
			if (currentShape >= rectangles.size())
			{
				if (ImGui::ColorEdit3("Pick Color for current circle", circleColor)) {
					circleColorTriggered = true;
				}
				else
					circleColorTriggered = false;
				//if (ImGui::InputText("Change Circle Name", buffer, IM_ARRAYSIZE(buffer))) {
				//	circleTextTriggered = true;
				//}
			}
			if (currentShape < rectangles.size()) {
				if (ImGui::ColorEdit3("Color Rect", rectColor)) {
					rectColorTriggered = true;
				}
				else
					rectColorTriggered = false;
				if (ImGui::InputText("Change Rect Name", buffer, IM_ARRAYSIZE(buffer))) {
					rectTextTriggered = true;
					std::cout << rectTextTriggered << "\n";
				}
				
			}

			


		ImGui::End();


	
	/*	circles[0].cerchio.setRadius(circles[0].radius);
		circles_texts[0].setCharacterSize(circles[0].cerchio.getRadius() * 0.3);
		sf::FloatRect textRect = circles_texts[0].getLocalBounds();
		circles_texts[0].setOrigin((textRect.left + textRect.width / 2), (textRect.height + textRect.top / 2));
		circles_texts[0].setPosition(circles[0].cerchio.getPosition().x + circles[0].cerchio.getRadius(), circles[0].cerchio.getPosition().y + circles[0].cerchio.getRadius()
		);
		*/
		//std::cout << rectTextTriggered << "\n";
		ft_update_loop(rect_texts, rectangles, circles_texts, circles, deltaTime, scaleVal, prevScale, currentShape,  circleColor, circleColorTriggered, rectColor, rectColorTriggered, buffer,rectTextTriggered, circleTextTriggered);
		//std::cout << rectTextTriggered << "\n";



		window.clear(sf::Color(18,33,43));

		if (circleExists) {
			for (std::size_t i = 0; i < circles.size(); i++)
			{
				window.draw(circles[i].cerchio);
				window.draw(circles_texts[i]);
			}
		}
		if (squareExists) {

			for (std::size_t i = 0; i < rectangles.size(); i++)
			{
				window.draw(rectangles[i].rect);
				window.draw(rect_texts[i]);
			}	

		}
			ImGui::SFML::Render(window);

		window.display();
	}
	ImGui::SFML::Shutdown();
	delete[] rect_visibility_option;
	window.close();
	return 0;
}