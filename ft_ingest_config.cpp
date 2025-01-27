#include "ft_ingest_config.h"


void	ft_marshal_config_file(ft_font &font, std::vector<ft_custom_circle>& circles, std::vector<ft_custom_rect>& rects, unsigned  int &window_height, unsigned int &window_width) {

	std::ifstream configFile("config.txt");

	if (!configFile.is_open()){
		std::cout << "ERROR OPENING CONFIG FILE" << "\n";
		exit(1);
	}
	
	
	std::string line;

	
	int screen_width, screen_height;
	std::string fontPath;
	int font_size, font_red, font_green, font_blue;


	while (std::getline(configFile, line)) {
			
		std::istringstream iss(line);
		std::string token;
		iss >> token;
		
		//TODO:
		//la grandezza finestra e il font non li sto ritornando come informazioni 
		//aggiusta per averli sempre modulari che ritornano al main con una piccola struct loro. 


		if (token == "Window") {
			iss >> screen_width >> screen_height;
			window_height = screen_height;
			window_width = screen_width;
			std::cout << "Window width " << window_width << "\n";
			std::cout << "Window height " << window_height << "\n";
		}
		else if (token == "Font") {
			iss >> fontPath >> font_size >> font_red >> font_green >> font_blue;
			font.font_path = fontPath;
			font.font_size = font_size;
			font.red = font_red;
			font.green = font_green;
			font.blue = font_blue;
		}

		else if (token == "Circle") {
			
			ft_custom_circle circle;
			circle.shape_type = token;
			iss >> circle.circle_name >> circle.init_pos_x >> circle.init_pos_y >> circle.speed_x >> circle.speed_y >> circle.red >> circle.green >> circle.blue >> circle.radius;
			circle.cerchio.setRadius(circle.radius);
			circle.cerchio.setPosition(circle.init_pos_x, circle.init_pos_y);
			circle.cerchio.setFillColor(sf::Color(circle.red, circle.green, circle.blue));

			circles.push_back(circle);
		}
		else if (token == "Rectangle") {
			ft_custom_rect rect;
			rect.shape_type = token;
			iss >> rect.rect_name >> rect.init_pos_x >> rect.init_pos_y >> rect.speed_x >> rect.speed_y >> rect.red >> rect.green >> rect.blue >> rect.size_x >> rect.size_y;
			rect.rect.setSize(sf::Vector2f(rect.size_x, rect.size_y));
			rect.rect.setPosition(rect.init_pos_x, rect.init_pos_y);
			rect.rect.setFillColor(sf::Color(rect.red, rect.green, rect.blue));
			rect.ft_scale = {2, 2};
			rect.originalSize = {rect.size_x, rect.size_y};
			rects.push_back(rect);
		}
	}
}




void set_rects_texts(std::vector<sf::Text>& rect_texts, std::vector<ft_custom_rect> &rectangles, 
					sf::Font &font, ft_font &ex_font) 
{

	for (std::size_t i = 0; i < rectangles.size(); i++) {
		if (rectangles.empty()) exit(2);
		sf::Text text;
		text.setFont(font);
		std::cout << rectangles[i].rect_name << "\n";
		text.setString(rectangles[i].rect_name);
		text.setCharacterSize(ex_font.font_size);
		text.setFillColor({(sf::Uint8)ex_font.red,(sf::Uint8)ex_font.green,(sf::Uint8)ex_font.blue});
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin((textRect.left + textRect.width / 2), (textRect.height + textRect.top / 2));
		
		text.setPosition(rectangles[i].rect.getPosition().x +rectangles[i].rect.getSize().x /2, 
							rectangles[i].rect.getPosition().y + rectangles[i].rect.getSize().y / 2);
		// resize del font in caso di out of bounds
		//TODO 
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		rect_texts.push_back(text);
		
	}
}
void set_circles_texts(std::vector<sf::Text>& circles_texts, std::vector<ft_custom_circle> &circles, 
						sf::Font &font, ft_font &ex_font) 
{
	for (std::size_t i = 0; i < circles.size(); i++) {
		if (circles.empty()) exit(2);
		sf::Text text;
		text.setFont(font);
		std::cout << circles[i].circle_name << "\n";
		text.setString(circles[i].circle_name);
		//text.setCharacterSize(ex_font.font_size);
		text.setCharacterSize(circles[i].cerchio.getRadius() * 0.3);
		text.setFillColor({ (sf::Uint8)ex_font.red,(sf::Uint8)ex_font.green,(sf::Uint8)ex_font.blue });
		sf::FloatRect textRect = text.getLocalBounds();
		text.setOrigin((textRect.left + textRect.width / 2), (textRect.height + textRect.top / 2));

		text.setPosition(circles[i].cerchio.getPosition().x + circles[i].cerchio.getRadius(), circles[i].cerchio.getPosition().y + circles[i].cerchio.getRadius()
							);
		// resize del font in caso di out of bounds
		//TODO 
		
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		circles_texts.push_back(text);

	}
}