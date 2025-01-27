#pragma once

#include "SFML/Graphics.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/System/Vector2.hpp>
//Functions to handle the marshaling and ingesting of config files as specified by exercise 1 of COMP4300 

#define CONFIG_PATH ".\config.txt"


enum ShapeType {
	Circle,
	Rectangle
};


typedef struct ft_custom_circle {
	std::string		shape_type;
	sf::CircleShape cerchio;
	std::string		circle_name;
	float			init_pos_x;
	float			init_pos_y;
	float			speed_x;
	float			speed_y;
	float			radius;
	int				red;
	int				blue;
	int				green;
}ft_custom_circle;

typedef struct ft_custom_rect {
	std::string			shape_type;
	sf::RectangleShape	rect;
	std::string			rect_name;
	float				init_pos_x;
	float				init_pos_y;
	float				speed_x;
	float				speed_y;
	float				size_x;
	float				size_y;
	sf::Vector2f		ft_scale;
	sf::Vector2f		originalSize;
	int					red;
	int					blue;
	int					green;
}ft_custom_rect;


typedef struct ft_font {
	std::string font_path;
	int			font_size;
	int			red;
	int			green;
	int			blue;
} ft_font;
void ft_marshal_config_file(ft_font &font, std::vector<ft_custom_circle>& circles, std::vector<ft_custom_rect>& rects, unsigned int &window_height, unsigned int &window_width);
void set_rects_texts(std::vector<sf::Text>& rect_texts, std::vector<ft_custom_rect> &rectangles, sf::Font &font, ft_font &ex_font);
void set_circles_texts(std::vector<sf::Text>& circles_texts, std::vector<ft_custom_circle> &circles, sf::Font &font, ft_font &ex_font);

void ft_update_loop(std::vector<sf::Text>& rect_texts, std::vector<ft_custom_rect>& rectangles, std::vector<sf::Text>& circles_texts, std::vector<ft_custom_circle>& circles, float deltaTime, float scaleVal, float& prevScale, int currentShape, float *circleColor, bool circleColorTriggered, float *rectColor, bool rectColorTriggered,  char *buffer, bool circleTextTriggered, bool &rectTextTriggered);
bool simp_collision_detection(std::vector<ft_custom_rect>& rectangles, std::vector<ft_custom_circle>& circles);
