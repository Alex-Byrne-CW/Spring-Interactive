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
#include <SFML/Audio.hpp> 

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
	void processMouse(sf::Event t_event); 
	void update(sf::Time t_deltaTime);
	void render();
	
	void counterText();  // a function to increase a counter veriable which is used to go from scene to scene
	void akari(); // a function to set up the sprite textures for the character akari 
	void akariText(); // a function to set and change the dialogue of the character akari 

	void yuri(); // function for the yuri character sprite details
	void yuriText(); // function for the yuri character text
	
	void HakimeText(); // a function to set up and change the text for the player character

	void movement(); // a function to determain the movement of the characters


	void setupFontAndText(); // setting up fonts and text
	void setupSound(); // setting up sound
	void setupSprite(); // setting up sprites
	void setupBackgrounds(); // setting up backgrounds
	void choice(); // setting up choice boxes

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message

	int counter = 0;  // scene counter
	
	sf::Texture m_backGround1Texture; // texture for the background
	sf::Sprite m_backGround1Sprite;  // sprite for the background

	sf::Texture m_classroomTexture; // texture for the classroom
	sf::Sprite m_classroomSprite; // sprite for the classroom

	sf::Texture m_libraryTexture; // texture for the library
	sf::Sprite m_librarySprite; // sprite for the library

	sf::Texture m_loadingTexture; // texture for the loadings creen
	sf::Sprite m_loadingSprite;  // sprite for the losading screen


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

	sf::Texture m_yuriTextureNutrual1; // the first nutural texture for the yuri character
	sf::Texture m_yuriTextureNutrual2; // the second nutural texture for the yuri character
	sf::Texture m_yuriTextureHappy1;  // the first Happy texture for the yuri character
	sf::Texture m_yuriTextureHappy2;  // the second Happy texture for the yuri character
	sf::Texture m_yuriTextureSad1;  // the first sad texture for the yuri character
	sf::Sprite m_yuriSprite; // the sprite for the yri character

	sf::Text m_yuriName; // the yuri character dialogue name tag
	sf::Text m_yuriTalk; // the yuri character dialogue text

	sf::Vector2f m_yuriLocation = { 1600.0f, -250.0f};
	sf::Vector2f m_yuriVilocity = { 0.0f , 0.0f };

	sf::Text m_HajimeName; // used to store the players name in the text box 
	sf::Text m_HajimeText; // userd to store the players dialogue text 


	sf::Color colour{ 255u , 255u, 255u, 155u };  // used to make the text box see though and the characters see through when not talking
	sf::Color Default{ 255u , 255u, 255u, 255u }; // used to set the characters textures to normal 
	sf::Color Purple{ 160u , 32u, 240u, 255u };
	sf::Vector2f Speed = { -5.0f , 0.0f }; 

	sf::RectangleShape m_choice1A; // choice block A
	sf::RectangleShape m_choice1A_Boarder; // choice boarder A
	sf::Text m_choiceText1A; // choice text A

	sf::RectangleShape m_choice1B; // choice block B
	sf::RectangleShape m_choice1B_Boarder; // choice boarder B
	sf::Text m_choiceText1B;  // choice text B

	sf::Vector2f m_mouseEnd; // to find where the mouse is
	bool choice1A = { false }; // the cheaker for the choice A
	bool choice1B = { false }; // the cheaker for the choice A

	sf::SoundBuffer m_themeMusic; // background music
	sf::Sound m_theme; 

	sf::SoundBuffer m_chuckleSound; // chuckle sound effect
	sf::Sound m_chuckle; 

	sf::SoundBuffer m_sighSound; // sigh sound effect 
	sf::Sound m_sigh; 

	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

