/// <summary>
/// @author Alex Byrne
/// @date Feb 2024
///
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1915U, 1097U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouse(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code) 
	{
		counterText();  // scene counter  
	}
}

void Game::processMouse(sf::Event t_event)
{
	m_mouseEnd.x = static_cast<float>(t_event.mouseButton.x); // finding the x value of the mouse click
	m_mouseEnd.y = static_cast<float>(t_event.mouseButton.y); // finding the y value of the mouse click

	// the boarders of the first 2 choice boxes
	sf::Vector2f choiceCornerA1 = { 607.5f , 510.0f }; 
	sf::Vector2f choiceCornerA2 = { 1307.5f , 590.0f }; 
	sf::Vector2f choiceCornerB1 = { 607.5f , 310.0f }; 
	sf::Vector2f choiceCornerB2 = { 1307.5f , 390.0f }; 

	if (counter == 8)
	{
		if (m_mouseEnd.x > choiceCornerA1.x && m_mouseEnd.x < choiceCornerA2.x && m_mouseEnd.y > choiceCornerA1.y && m_mouseEnd.y < choiceCornerA2.y)
		{
			counter++;
			choice1A = true;
		}
		if (m_mouseEnd.x > choiceCornerB1.x && m_mouseEnd.x < choiceCornerB2.x && m_mouseEnd.y > choiceCornerB1.y && m_mouseEnd.y < choiceCornerB2.y) 
		{ 
			counter++; 
			choice1B = true; 
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	akari(); 
	akariText(); 
	HakimeText();
	if (counter == 5 && m_AkariLocation.x > -660.0f)
	{
		movement(); // akari scene 5 movement
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backGround1Sprite); //background 
	if (counter == 0) //first scene 
	{
		m_window.draw(m_AkariSprite); //character sprite 
		m_window.draw(m_textBoxSprite); //text box 
		m_window.draw(m_AkiraTalk); //diologue  
		m_window.draw(m_akiraName); //name in text box 
	}
	if (counter == 1) // second scene
	{
		m_window.draw(m_AkariSprite); //character sprite
		m_window.draw(m_textBoxSprite); //text box
		m_window.draw(m_AkiraTalk); //diologue 
		m_window.draw(m_akiraName); //name in text box
	}
	if (counter == 2) // third scene
	{
		m_window.draw(m_AkariSprite);  //character sprite
		m_window.draw(m_textBoxSprite); //text box
		m_window.draw(m_HajimeText); // player diologue
		m_window.draw(m_HajimeName); // player name
	}
	if (counter == 3) // fourth scene
	{
		m_window.draw(m_AkariSprite); //character sprite
		m_window.draw(m_textBoxSprite); //text box
		m_window.draw(m_AkiraTalk);
		m_window.draw(m_akiraName); // character name
	}
	if (counter == 4) // fifth scene
	{
		m_window.draw(m_AkariSprite); //character sprite 
		m_window.draw(m_textBoxSprite); //text box 
		m_window.draw(m_AkiraTalk); // character diologue 
		m_window.draw(m_akiraName); // character name 
	} 
	if (counter == 5) // sixth scene
	{
		m_window.draw(m_AkariSprite); // character sprite
		m_window.draw(m_textBoxSprite); // text box
	}
	if (counter == 6) // seventh scene
	{
		m_window.draw(m_textBoxSprite); //text box  
		m_window.draw(m_HajimeText); // player diologue
		m_window.draw(m_HajimeName); // player name
	}
	if (counter == 7) // eighth scene
	{
		m_window.draw(m_textBoxSprite);  //text box  
		m_window.draw(m_HajimeText);  // player diologue
		m_window.draw(m_HajimeName);  // player name
	}
	if (counter == 8) // ninth scene
	{
		m_window.draw(m_loadingSprite); // loading screne 
		m_window.draw(m_choice1A);
		m_window.draw(m_choice1A_Boarder);
		m_window.draw(m_choice1B);
		m_window.draw(m_choice1B_Boarder);
		m_window.draw(m_choiceText1A);
		m_window.draw(m_choiceText1B);
	}
	if (counter == 9 && choice1A == true && choice1B == false) // tenth scene choice A
	{
		m_window.draw(m_classroomSprite); 
	}
	if (counter == 9 && choice1B == true && choice1A == false) // tenth scene choice B 
	{
		m_window.draw(m_librarySprite); 
	}
	
	m_window.display();
}

void Game::counterText() //a function to increase the counter which determines what scene is playing
{
	counter++;
}

void Game::akari() // a function for the sprite and textures for the character akari
{
	if (counter == 1) // scene two
	{
		m_AkariSprite.setTexture(m_AkariTextureSerious); 
	}
	if (counter == 2) // scene three 
	{
		m_AkariSprite.setColor(colour); 
	}
	if (counter == 3) // scene four
	{
		m_AkariSprite.setColor(Default);
		m_AkariSprite.setTexture(m_AkariTextureHappy);
	}
	if (counter == 4) // scene five
	{ 
		m_AkariSprite.setTexture(m_AkariTexture); 
	}
}

void Game::akariText() // a function for the dialogue text for the character akari
{
	if (counter == 0) // scene one
	{
		m_AkiraTalk.setString("so your the new kid? \nvery well, all you have to know is follow the rules and dont cause trouble or else.......");
	} 
	if (counter == 1) // scene two 
	{ 
		m_AkiraTalk.setString("Do i make myself clear?"); 
	} 
	if (counter == 3) // scene four
	{
		m_AkiraTalk.setString("Great! then we shouldn't have a problem"); 
	}
	if (counter == 4) // scene five
	{
		m_AkiraTalk.setString("Well i have to get going New kid. \nthe student council work never rests you know!");
	}
}

void Game::HakimeText() // function for the player's dialogue text
{
	if (counter == 2) // scene three
	{
		m_HajimeText.setString("U-Understood ma'am"); 
	} 
	if (counter == 6) // scene seven
	{
		m_HajimeText.setString("so thats the student council president? \nI dont want to get on her bad side.....");
	}
	if (counter == 7) // scene eight
	{
		m_HajimeText.setString("Shoot! the time! i should head to class.....");
	}
}
void Game::movement() // a function to determain the movement of the characters
{
	if (counter == 5)
	{
		m_AkariVilocity += Speed;
		m_AkariLocation += m_AkariVilocity;
		m_AkariSprite.setPosition(m_AkariLocation);
	}
}


/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_akiraName.setFont(m_ArialBlackfont);
	m_akiraName.setString("Akira"); // set up fro character Akira name
	m_akiraName.setStyle(sf::Text::Italic);
	m_akiraName.setPosition(95.0f, 800.0f);
	m_akiraName.setCharacterSize(40U);
	m_akiraName.setOutlineColor(sf::Color::Black); 
	m_akiraName.setFillColor(sf::Color::White); 
	m_akiraName.setOutlineThickness(1.0f); 

	m_AkiraTalk.setCharacterSize(40U);   // set up dialogue for the character Akira
	m_AkiraTalk.setPosition(40.0f, 880.0f);
	m_AkiraTalk.setFillColor(sf::Color::White);
	m_AkiraTalk.setOutlineColor(sf::Color::Black);
	m_AkiraTalk.setOutlineThickness(1.0f);
	m_AkiraTalk.setFont(m_ArialBlackfont); 

	m_HajimeName.setFont(m_ArialBlackfont); 
	m_HajimeName.setString("Hajime"); // set up for player name 
	m_HajimeName.setStyle(sf::Text::Italic); 
	m_HajimeName.setPosition(80.0f, 800.0f); 
	m_HajimeName.setCharacterSize(40U); 
	m_HajimeName.setOutlineColor(sf::Color::Black); 
	m_HajimeName.setFillColor(sf::Color::Yellow); 
	m_HajimeName.setOutlineThickness(1.0f); 

	m_HajimeText.setCharacterSize(40U);  // set up for player dialogue 
	m_HajimeText.setPosition(40.0f, 880.0f); 
	m_HajimeText.setFillColor(sf::Color::Yellow); 
	m_HajimeText.setOutlineColor(sf::Color::Black); 
	m_HajimeText.setOutlineThickness(1.0f); 
	m_HajimeText.setFont(m_ArialBlackfont);  

	m_choiceText1A.setCharacterSize(40U);  // set up for player dialogue
	m_choiceText1A.setPosition(840.0f, 525.0f);
	m_choiceText1A.setFillColor(sf::Color::White);
	m_choiceText1A.setOutlineColor(sf::Color::Black);
	m_choiceText1A.setOutlineThickness(1.0f);
	m_choiceText1A.setFont(m_ArialBlackfont);

	m_choiceText1B.setCharacterSize(35U);  // set up for player dialogue
	m_choiceText1B.setPosition(660.0f, 330.0f);
	m_choiceText1B.setFillColor(sf::Color::White);
	m_choiceText1B.setOutlineColor(sf::Color::Black);
	m_choiceText1B.setOutlineThickness(1.0f);
	m_choiceText1B.setFont(m_ArialBlackfont);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	choice(); 
	setupBackgrounds(); 

	if (!m_AkariTexture.loadFromFile("ASSETS\\IMAGES\\akari_N1.png")) // the nutraul_1 texture for the character Akari
	{
		std::cout << "problem loading Akari" << std::endl;
	}
	if (!m_AkariTextureSerious.loadFromFile("ASSETS\\IMAGES\\akari_S1.png")) // the serious_1 texture for the character Akari
	{
		std::cout << "problem loading Akari" << std::endl;
	}
	if (!m_AkariTextureHappy.loadFromFile("ASSETS\\IMAGES\\akari_H1.png")) // the happy_1 texture for the character Akari
	{
		std::cout << "problem loading Akari" << std::endl;
	}
	m_AkariSprite.setTexture(m_AkariTexture);
	m_AkariSprite.setPosition(0.0f, -250.0f);
	m_AkariSprite.setScale(1.5f, 1.5f); 
}

void Game::setupBackgrounds()
{
	if (!m_backGround1Texture.loadFromFile("ASSETS\\IMAGES\\bg1.jpg")) // texture for background 
	{
		std::cout << "problem loading background" << std::endl; 
	}
	m_backGround1Sprite.setTexture(m_backGround1Texture);  
	m_backGround1Sprite.setPosition(0.0f, 0.0f);  

	if (!m_classroomTexture.loadFromFile("ASSETS\\IMAGES\\class.png")) // texture for background 
	{
		std::cout << "problem loading background" << std::endl; 
	}
	m_classroomSprite.setTexture(m_classroomTexture); 
	m_classroomSprite.setPosition(0.0f, 0.0f); 

	if (!m_libraryTexture.loadFromFile("ASSETS\\IMAGES\\library.png")) // texture for background  
	{
		std::cout << "problem loading background" << std::endl; 
	}
	m_librarySprite.setTexture(m_libraryTexture); 
	m_librarySprite.setPosition(0.0f, 0.0f); 


	if (!m_loadingTexture.loadFromFile("ASSETS\\IMAGES\\loading.jpg")) // texture for loading screne  
	{
		std::cout << "problem with loading" << std::endl; 
	}
	m_loadingSprite.setTexture(m_loadingTexture); 
	m_loadingSprite.setPosition(0.0f, 0.0f); 

	if (!m_textBoxTexture.loadFromFile("ASSETS\\IMAGES\\textbox.png")) // texture for text box 
	{
		std::cout << "problem loading textbox" << std::endl; 
	}
	m_textBoxSprite.setTexture(m_textBoxTexture); 
	m_textBoxSprite.setPosition(0.0f, 800.0f); 
	m_textBoxSprite.setColor(colour); 
}

void Game::choice() // a function to create the choice boxes for the player to select
{
	//setting up the first choice option box
	m_choice1A.setFillColor(sf::Color::White); 
	m_choice1A.setSize(sf::Vector2f{ 700.0f, 80.0f }); 
	m_choice1A.setOrigin(350.0f, 40.0f); 
	m_choice1A.setPosition(957.5f, 550.0f); 

	//setting up the first choice option box boarder
	m_choice1A_Boarder.setFillColor(sf::Color::Black); 
	m_choice1A_Boarder.setSize(sf::Vector2f{ 680.0f, 60.0f }); 
	m_choice1A_Boarder.setOrigin(340.0f, 30.0f); 
	m_choice1A_Boarder.setPosition(957.5f, 550.0f); 

	m_choiceText1A.setString("Go to class"); // setting up the text for the first option box 

	//setting up the second choice option box
	m_choice1B.setFillColor(sf::Color::White); 
	m_choice1B.setSize(sf::Vector2f{ 700.0f, 80.0f }); 
	m_choice1B.setOrigin(350.0f, 40.0f); 
	m_choice1B.setPosition(957.5f, 350.0f); 

	//setting up the second choice option box boarder
	m_choice1B_Boarder.setFillColor(sf::Color::Black); 
	m_choice1B_Boarder.setSize(sf::Vector2f{ 680.0f, 60.0f }); 
	m_choice1B_Boarder.setOrigin(340.0f, 30.0f); 
	m_choice1B_Boarder.setPosition(957.5f, 350.0f); 

	m_choiceText1B.setString("skip class and play videogames");  // setting up the text for the second option box
}
