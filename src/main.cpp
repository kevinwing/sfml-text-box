/**
 * @file main.cpp
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief Main file for using the TextBox class to instantiate a text input object
 * @version 0.1
 * @date 2021-07-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "textbox.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Text Box");
	TextBox input;

	input.setPosition((window.getSize().x - input.getSize().x) / 2.f, (window.getSize().y - input.getSize().y) / 2.f);
	input.setBorderColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				int mouseX = sf::Mouse::getPosition(window).x;
                int mouseY = sf::Mouse::getPosition(window).y;

				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (mouseX >= input.getPosition().x &&
                        mouseX <= (input.getPosition().x + input.getSize().x) &&
                        mouseY >= input.getPosition().y &&
                        mouseY <= (input.getPosition().y + input.getSize().y))
                    {
                        input.setSelect(true);
                    }
                    else
                    {
                        input.setSelect(false);
                    }
				}
				
			}

			input.update(event);
			
		}

		window.clear(sf::Color(201, 201, 201));
		input.draw(window);
		window.display();
	}
	

}