#include "ft_ingest_config.h"


bool simp_collision_detection(std::vector<ft_custom_rect>& rectangles, std::vector<ft_custom_circle>& circles)
{
	return true;
}


void ft_update_loop(std::vector<sf::Text>& rect_texts, std::vector<ft_custom_rect>& rectangles,
	std::vector<sf::Text>& circles_texts, std::vector<ft_custom_circle>& circles, float deltaTime, 
	float scaleVal, float &prevScale, int currentShape, float *circleColor, bool circleColorTriggered, 
	float *rectColor, bool rectColorTriggered, char* buffer, bool circleTextTriggered, bool &rectTextTriggered)
{
	
	//QUESTO CODICE AGGIORNA LA POSIZIONE DEL CERCHIO NELLO SCHERMO 
	for (size_t i = 0; i < circles.size(); i++) {

		
		circles[i].cerchio.setRadius(circles[i].radius);

		if (circles[i].cerchio.getGlobalBounds().left < 0 || circles[i].cerchio.getGlobalBounds().top < 0 ||
			circles[i].cerchio.getGlobalBounds().left + circles[i].cerchio.getGlobalBounds().width > 1280 ||
			circles[i].cerchio.getGlobalBounds().top + circles[i].cerchio.getGlobalBounds().height > 720)
		{
			if(circles[i].cerchio.getGlobalBounds().left < 0 || circles[i].cerchio.getGlobalBounds().left + circles[i].cerchio.getGlobalBounds().width > 1280)
				circles[i].speed_x = -circles[i].speed_x;
			if(circles[i].cerchio.getGlobalBounds().top < 0 || circles[i].cerchio.getGlobalBounds().top + circles[i].cerchio.getGlobalBounds().height > 720)
				circles[i].speed_y = -circles[i].speed_y;
		}
		 
		circles[i].cerchio.move(circles[i].speed_x * deltaTime, circles[i].speed_y *deltaTime);
	}

	//QUESTO CODICE AGGIORNA LA POSIZIONE DEL TESTO, CENTRATA, DENTRO I CERCHI CHE SI MUOVONO 
	for (size_t i = 0; i < circles.size(); i++) {

		circles_texts[i].setCharacterSize(circles[i].cerchio.getRadius() * 0.3);
		sf::FloatRect textRect = circles_texts[i].getLocalBounds();
		circles_texts[i].setOrigin((textRect.left + textRect.width / 2), (textRect.height + textRect.top / 2));
		circles_texts[i].setPosition(circles[i].cerchio.getPosition().x + circles[i].cerchio.getRadius(),
			circles[i].cerchio.getPosition().y + circles[i].cerchio.getRadius());
	}
	if (currentShape < rect_texts.size() && rectTextTriggered) {
		rect_texts[currentShape].setString(buffer);
		rectTextTriggered = false;
	}
	//update grandezza e posizione dei rettangoli 
	for (size_t i = 0; i < rectangles.size(); i++) {

		if (circleColorTriggered && currentShape >= rectangles.size()) {
			int circleIndex = currentShape - rectangles.size();
			sf::Color newColor(static_cast<sf::Uint8>(circleColor[0] * 255),
				static_cast<sf::Uint8>(circleColor[1] * 255),
				static_cast<sf::Uint8>(circleColor[2] * 255));
			circles[circleIndex].cerchio.setFillColor(newColor);
		}
		if (rectColorTriggered && currentShape < rectangles.size()) {
			
			sf::Color newColor(static_cast<sf::Uint8>(rectColor[0] * 255),
				static_cast<sf::Uint8>(rectColor[1] * 255),
				static_cast<sf::Uint8>(rectColor[2] * 255));
			rectangles[currentShape].rect.setFillColor(newColor);
		}

		if (prevScale != scaleVal) {
			if (currentShape < rectangles.size()) {
				sf::Vector2f new_size = rectangles[i].originalSize * scaleVal;
				//rectangles[i].originalSize = new_size;
				rectangles[currentShape].rect.setSize(new_size);
			}
			else {
				int circleIndex = currentShape - rectangles.size();
				circles[circleIndex].radius *= scaleVal / prevScale;
			}
			prevScale = scaleVal;
		}


		//Update del movimento randomico
		if (rectangles[i].rect.getGlobalBounds().left < 0 || rectangles[i].rect.getGlobalBounds().top < 0 ||
			rectangles[i].rect.getGlobalBounds().left + rectangles[i].rect.getGlobalBounds().width > 1280 ||
			rectangles[i].rect.getGlobalBounds().top + rectangles[i].rect.getGlobalBounds().height > 720)
		{
			if (rectangles[i].rect.getGlobalBounds().left < 0 || rectangles[i].rect.getGlobalBounds().left + rectangles[i].rect.getGlobalBounds().width > 1280)
				rectangles[i].speed_x = -rectangles[i].speed_x;
			if (rectangles[i].rect.getGlobalBounds().top < 0 || rectangles[i].rect.getGlobalBounds().top + rectangles[i].rect.getGlobalBounds().height > 720)
				rectangles[i].speed_y = -rectangles[i].speed_y;
		}

		rectangles[i].rect.move(rectangles[i].speed_x * deltaTime, rectangles[i].speed_y * deltaTime);

		//update del testo dei rect 
		
		for (size_t i = 0; i < rectangles.size(); i++) {

			rect_texts[i].setCharacterSize(rectangles[i].rect.getSize().y * 0.3);
			sf::FloatRect textRect = rect_texts[i].getLocalBounds();
			rect_texts[i].setOrigin((textRect.left + textRect.width / 2), (textRect.height + textRect.top / 2));
			rect_texts[i].setPosition(
				rectangles[i].rect.getPosition().x + rectangles[i].rect.getSize().x /2,
				rectangles[i].rect.getPosition().y + rectangles[i].rect.getSize().y  /2
			);
		}

	}
	




}



