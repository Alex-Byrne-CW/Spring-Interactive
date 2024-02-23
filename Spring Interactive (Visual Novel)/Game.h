/// <summary>
/// author Alex Byrne Feb 2024
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void counterText();  // a function to increase a counter veriable which is used to go from scene to scene
	void akari(); // a function to set up the sprite textures for the character akari 
	void akariText(); // a function to set and change the dialogue of the character akari 
	void HakimeText(); // a function to set up and change the text for the player character

	void movement(); // a function to determain the movement of the characters


	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	int counter = 0;  
	
	sf::Texture m_backGround1Texture; // texture for the background
	sf::Sprite m_backGround1Sprite;  // sprite for the background


	sf::Texture m_textBoxTexture; // texture for the text box 
	sf::Sprite m_textBoxSprite; // sprite for the text box 

	sf::Texture m_AkariTexture; // the nutrual texture for the chararacter akari 
	sf::Texture m_AkariTextureSerious; // the serious texture for the character akari 
	sf::Texture m_AkariTextureHappy; // the happy texture for the character akari 
	sf::Sprite m_AkariSprite; // the sprite for the character akari 
	sf::Text m_akiraName; // text used for displaying the characters name in the text box 
	sf::Text m_AkiraTalk; // used to store and change what text the character is saying 
	sf::Vector2f m_AkariLocation = { 0.0f , -250.0f }; // used to make the text box see though and the characters see through when not talking
	sf::Vector2f m_AkariVilocity = { 0.0f, 0.0f }; // used to set the characters textures to normal

	sf::Text m_HajimeName; // used to store the players name in the text box 
	sf::Text m_HajimeText; // userd to store the players dialogue text 


	sf::Color colour{ 255u , 255u, 255u, 155u };  // used to make the text box see though and the characters see through when not talking
	sf::Color Default{ 255u , 255u, 255u, 255u }; // used to set the characters textures to normal 
	sf::Vector2f Speed = { -5.0f , 0.0f }; 

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

