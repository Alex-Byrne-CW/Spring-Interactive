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
	setupSound(); // load audio
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

	// boarders of the hide button
	sf::Vector2f hideButtonCornerA = { 1895.0f, 830.0f };
	sf::Vector2f hideButtonCornerB = { 1825.0f, 760.0f };

	// cheaking the player has clicked the hide button, if so hidding text
	if (m_mouseEnd.x > hideButtonCornerB.x && m_mouseEnd.x < hideButtonCornerA.x && m_mouseEnd.y > hideButtonCornerB.y && m_mouseEnd.y < hideButtonCornerA.y && hide == false)
	{
		hide = true;
		m_click.play(); 
	}
	// if the player clicks anywhere on the screen the text will become visable 
	else
	{
		hide = false;
	}

	if (counter == 11) // cheaking if its scene 12
	{
		if (m_mouseEnd.x > choiceCornerA1.x && m_mouseEnd.x < choiceCornerA2.x && m_mouseEnd.y > choiceCornerA1.y && m_mouseEnd.y < choiceCornerA2.y) // cheaking if the mouse is within the first choice option box
		{
			counter++;
			choice1A = true;
			m_click.play(); 
		}
		else if (m_mouseEnd.x > choiceCornerB1.x && m_mouseEnd.x < choiceCornerB2.x && m_mouseEnd.y > choiceCornerB1.y && m_mouseEnd.y < choiceCornerB2.y) // cheaking if the mouse is within the second choice option box
		{ 
			counter++; 
			choice1B = true;
			m_click.play(); 
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
	yuri(); 
	akariText();
	yuriText(); 
	HakimeText();
	choiceText(); 
	if (counter == 5 && m_AkariLocation.x > -670.0f || counter == 8 && m_yuriLocation.x > 750.0f || counter == 14 && choice1A == true && m_yuriLocation.x > -670.0f)
	{
		movement(); // movement for the sprites during scenes
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_backGroundSprite); //background 
	if (akariSprite == true)
	{
		m_window.draw(m_AkariSprite); //character sprite  
	}
	if (yuriSprite == true)
	{
		m_window.draw(m_yuriSprite); //character sprite  
	}
	if (hide == false)
	{
		m_window.draw(m_textBoxCornerSprite);
		m_window.draw(m_textBoxSprite); //text box 
		m_window.draw(m_dialogueName); // dialogue box name
		m_window.draw(m_dialogueText); // dialogue box text
		m_window.draw(m_hideButtonBoarder); // hide buttpn boarder
		m_window.draw(m_hideButton); // hide button
		m_window.draw(m_hideText); // hide button text
	}
	if (counter == 11)  //12th scene 
	{
		m_window.draw(m_choice1A);  // choice box A 
		m_window.draw(m_choice1A_Boarder); // choice box boarder A 
		m_window.draw(m_choice1B); // cxhoice box B 
		m_window.draw(m_choice1B_Boarder); // choicer box boarder B  
		m_window.draw(m_choiceText1A);  // choice box text A 
		m_window.draw(m_choiceText1B);  // choice box text B 
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
	else if (counter == 2) // scene three 
	{
		m_AkariSprite.setColor(colour); 
	}
	else if (counter == 3) // scene four
	{
		m_AkariSprite.setColor(Default);
		m_AkariSprite.setTexture(m_AkariTextureHappy);
	}
	else if (counter == 4) // scene five
	{ 
		m_AkariSprite.setTexture(m_AkariTexture); 
	}
}

void Game::akariText() // a function for the dialogue text for the character akari
{
	if (counter == 0) // scene one
	{
		m_dialogueText.setString("so your the new kid? \nvery well, all you have to know is follow the rules and dont cause trouble or else.......");
		m_dialogueName.setString("Akira");
		m_dialogueName.setFillColor(sf::Color::White);
		m_sigh.play(); // play audio file
	} 
	else if (counter == 1) // scene two 
	{ 
		m_dialogueText.setString("Do i make myself clear?");
	} 
	else if (counter == 3) // scene four
	{
		m_dialogueText.setString("Great! then we shouldn't have a problem");
		m_dialogueName.setString("Akira");
		m_dialogueName.setFillColor(sf::Color::White);	
		m_dialogueText.setFillColor(sf::Color::White); 
	}
	else if (counter == 4) // scene five
	{
		m_dialogueText.setString("Well i have to get going New kid. \nthe student council work never rests you know!");
	}
}

void Game::yuri()
{
	if (counter == 10) // 11th scene
	{
		m_yuriSprite.setTexture(m_yuriTextureNutrual2);
	}
	else if (counter == 11 || counter == 12 && choice1A == true || counter == 12 && choice1B == true) // 12th scene & 13th scene A & 13th scene B 
	{
		m_yuriSprite.setColor(colour);
	}
	else if (counter == 13 && choice1A == true) // 14th scene A
	{
		m_yuriSprite.setColor(Default);
		m_yuriSprite.setTexture(m_yuriTextureSad1);
	}
	else if (counter == 13 && choice1B == true) // 14th scene B
	{
		m_yuriSprite.setColor(Default);
		m_yuriSprite.setTexture(m_yuriTextureHappy1);
	}
	else if (counter == 14 && choice1B == true) // 15th scene B
	{
		m_yuriSprite.setTexture(m_yuriTextureHappy2);
	}
	else if (counter == 15 && choice1B == true) // 16th scene B
	{
		m_yuriSprite.setColor(colour); 
	}
}

void Game::satoru() // function for the satoru character sprite
{
}

void Game::yuriText()
{
	if (counter == 8) // 9th scene
	{
		m_hi.play();  
	}
	else if (counter == 9) //10th scene
	{
		m_dialogueText.setString("h-hello, i'm Yuri. your the new kid right? \nI-I couldn't help but notice.");
		m_dialogueName.setString("Yuri");
		m_dialogueName.setFillColor(sf::Color::Magenta);
		m_dialogueText.setFillColor(sf::Color::Magenta); 

	}
	else if (counter == 10) // 11th scene
	{
		m_dialogueText.setString("t-that you havent spokent to anyone yet. \nso i was wondering if you w-wanted to hang out?");
	}
	else if (counter == 13 && choice1A == true) // 14th scene A
	{
		m_dialogueText.setString("o-oh.... \ns-sorry for annoying you, i'll b-be going t-then.");
		m_dialogueName.setString("Yuri");
		m_dialogueName.setFillColor(sf::Color::Magenta); 
		m_dialogueText.setFillColor(sf::Color::Magenta);
	}
	else if (counter == 13 && choice1B == true) // 14th scene B
	{
		m_dialogueText.setString("really!? you want to hang out!");
		m_dialogueName.setString("yuri");
		m_dialogueName.setFillColor(sf::Color::Magenta);
		m_dialogueText.setFillColor(sf::Color::Magenta);

		m_giggle.play();  
	}
	else if (counter == 14 && choice1B == true) // 15th scene B
	{
		m_dialogueText.setString("we are going to have so much fun, i promise!");
		m_dialogueName.setString("yuri");
	}
}

void Game::satoruText() // function for the satoru text
{
}

void Game::HakimeText() // function for the player's dialogue text
{
	if (counter == 2) // scene three
	{
		m_dialogueText.setString("U-Understood ma'am");
		m_dialogueName.setString("Hakime");
		m_dialogueName.setFillColor(sf::Color::Yellow);
		m_dialogueText.setFillColor(sf::Color::Yellow);

		m_chuckle.play(); 
	} 
	else if (counter == 6) // scene seven
	{
		m_dialogueText.setString("so thats the student council president? \nI dont want to get on her bad side.....");
		m_dialogueName.setString("Hakime");
		m_dialogueName.setFillColor(sf::Color::Yellow);
		m_dialogueText.setFillColor(sf::Color::Yellow);

		akariSprite = false; 
	}
	else if (counter == 7) // scene eight
	{
		m_dialogueText.setString("i still have time before class, what should i do?");
	}
	else if (counter == 12 && choice1A == true) // 13th scene A
	{
		m_dialogueText.setString("no way nerd! go annoy someone else!");
		m_dialogueName.setString("Hakime");
		m_dialogueName.setFillColor(sf::Color::Yellow); 
		m_dialogueText.setFillColor(sf::Color::Yellow);
	}
	else if (counter == 15 && choice1A == true)  // 16th scene A
	{
		m_dialogueText.setString("wow, i suck.........");
		m_dialogueName.setString("Hakime");
		m_dialogueName.setFillColor(sf::Color::Yellow);
		m_dialogueText.setFillColor(sf::Color::Yellow);

		yuriSprite = false;
	}
	else if (counter == 12 && choice1B == true) // 13th scene B
	{
		m_dialogueText.setString("sure thing yuri! let's hang out!");
		m_dialogueName.setString("Hakime");
		m_dialogueName.setFillColor(sf::Color::Yellow);
		m_dialogueText.setFillColor(sf::Color::Yellow);
	}
	else if (counter == 15 && choice1B == true) // 16th scene B
	{
		m_dialogueText.setString("i can't wait yuri!");  
		m_dialogueName.setString("Hakime");  
		m_dialogueName.setFillColor(sf::Color::Yellow); 
		m_dialogueText.setFillColor(sf::Color::Yellow);
	}
}

void Game::movement() // a function to determain the movement of the characters
{
	if (counter == 5) // 6th scene
	{
		m_dialogueText.setString(""); //clearing text during movement
		m_dialogueName.setString(""); //clearing text during movement
		m_AkariVilocity += Speed; // increaseing the distance the sprite is travaling
		m_AkariLocation += m_AkariVilocity; // adding the distandce to the sprite location
		m_AkariSprite.setPosition(m_AkariLocation); // setting the new location
	}
	else if (counter == 8) // 7th scene
	{
		m_dialogueText.setString(""); //clearing text during movement
		m_dialogueName.setString(""); //clearing text during movement
		m_yuriVilocity += Speed; // increaseing the distance the sprite is travaling
		m_yuriLocation += m_yuriVilocity; // adding the distandce to the sprite location
		m_yuriSprite.setPosition(m_yuriLocation); // setting the new location
	} 
	else if (counter == 14 || choice1A == true) // scene 15 A
	{
		m_dialogueText.setString(""); //clearing text during movement
		m_dialogueName.setString(""); //clearing text during movement
		m_yuriVilocity += Speed * 1.50f; // increaseing the distance the sprite is travaling
		m_yuriLocation += m_yuriVilocity; // adding the distandce to the sprite location
		m_yuriSprite.setPosition(m_yuriLocation); // setting the new location
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
	m_dialogueName.setFont(m_ArialBlackfont); // set up for the name in the dialogue box
	m_dialogueName.setPosition(95.0f, 800.0f);
	m_dialogueName.setCharacterSize(40U);
	m_dialogueName.setOutlineColor(sf::Color::Black);
	m_dialogueName.setOutlineThickness(1.0f);

	m_dialogueText.setFont(m_ArialBlackfont);  
	m_dialogueText.setPosition(40.0f, 880.0f);  
	m_dialogueText.setCharacterSize(40U);   // set up for the text in the dialogue box
	m_dialogueText.setOutlineColor(sf::Color::Black);
	m_dialogueText.setOutlineThickness(1.0f);

	m_choiceText1A.setCharacterSize(40U);  // set up for player dialogue choice A
	m_choiceText1A.setPosition(800.0f, 525.0f);
	m_choiceText1A.setFillColor(sf::Color::White);
	m_choiceText1A.setOutlineColor(sf::Color::Black);
	m_choiceText1A.setOutlineThickness(1.0f);
	m_choiceText1A.setFont(m_ArialBlackfont);

	m_choiceText1B.setCharacterSize(35U);  // set up for player dialogue choice B
	m_choiceText1B.setPosition(660.0f, 330.0f);
	m_choiceText1B.setFillColor(sf::Color::White);
	m_choiceText1B.setOutlineColor(sf::Color::Black);
	m_choiceText1B.setOutlineThickness(1.0f);
	m_choiceText1B.setFont(m_ArialBlackfont);
}

void Game::setupSound() // a function to load and play audio files
{
	if (!m_themeMusic.loadFromFile("ASSETS\\AUDIO\\theme.flac")) // setting up the background music
	{
		std::cout << "problem with sound" << std::endl;
	}
	m_theme.setBuffer(m_themeMusic);
	m_theme.setVolume(5.0f); 
	m_theme.setLoop(true);
	m_theme.play();

	if (!m_chuckleSound.loadFromFile("ASSETS\\AUDIO\\chuckle.flac"))  // setting up the chuckle sound effect
	{
		std::cout << "problem with sound" << std::endl; 
	}
	m_chuckle.setBuffer(m_chuckleSound); 

	if (!m_sighSound.loadFromFile("ASSETS\\AUDIO\\sigh.flac")) // setting up the sigh sound effect
	{
		std::cout << "problem with sound" << std::endl;
	}
	m_sigh.setBuffer(m_sighSound);

	if (!m_hiSound.loadFromFile("ASSETS\\AUDIO\\hi.flac"))  // setting up the hi sound effect
	{
		std::cout << "problem with sound" << std::endl; 
	}
	m_hi.setBuffer(m_hiSound);
	m_hi.setVolume(100.0f);

	if (!m_clickSound.loadFromFile("ASSETS\\AUDIO\\click.flac"))  // setting up option select sond effect
	{
		std::cout << "problem with sound" << std::endl; 
	}
	m_click.setBuffer(m_clickSound); 
	m_click.setVolume(25.0f); 

	if (!m_giggleSound.loadFromFile("ASSETS\\AUDIO\\giggle.flac"))
	{
		std::cout << "problem with sound" << std::endl;
	}
	m_giggle.setBuffer(m_giggleSound); 
	m_giggle.setVolume(100.0f); 
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	choice(); 
	setupBackgrounds(); 
	hideTextButton(); 

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

	if (!m_yuriTextureNutrual1.loadFromFile("ASSETS\\IMAGES\\yuri_N1.png")) // the nutrual_1 texture for yuri
	{
		std::cout << "problem loading yuri nutrual1" << std::endl;
	}
	if (!m_yuriTextureNutrual2.loadFromFile("ASSETS\\IMAGES\\yuri_N2.png")) // the nutural_2 texture for yuri
	{
		std::cout << "problem loading yuri nutrual2" << std::endl;
	}
	if (!m_yuriTextureSad1.loadFromFile("ASSETS\\IMAGES\\yuri_S1.png")) // the sad_1 texture for yuri
	{
		std::cout << "problem loading yuri nutrual2" << std::endl;
	}
	if (!m_yuriTextureHappy1.loadFromFile("ASSETS\\IMAGES\\yuri_H1.png")) // the happy_1 texture for yuri
	{
		std::cout << "problem loading yuri Happy1" << std::endl;
	}
	if (!m_yuriTextureHappy2.loadFromFile("ASSETS\\IMAGES\\yuri_H2.png")) // the happy_2 texture for yuri
	{
		std::cout << "problem loading yuri Happy2" << std::endl;
	}
	m_yuriSprite.setTexture(m_yuriTextureNutrual1);
	m_yuriSprite.setPosition(1600.0f, -250.0f);
	m_yuriSprite.setScale(1.5f, 1.5f);

	if (!m_satoruTextureNutrual1.loadFromFile("ASSETS\\IMAGES\\Satoru_N1.png")) // the nutrual_1 texture for satoru
	{
		std::cout << "problem loading satoru Nutrual1" << std::endl;
	}
	if (!m_satoruTextureHappy1.loadFromFile("ASSETS\\IMAGES\\Satoru_H1.png")) // the happy_1 texture for satoru
	{
		std::cout << "problem loading satoru Happy1" << std::endl; 
	}
	if (!m_satoruTextureHappy2.loadFromFile("ASSETS\\IMAGES\\Satoru_H2.png")) // the happy_2 texture for satoru
	{
		std::cout << "problem loading satoru Happy2" << std::endl;
	}
	if (!m_satoruTextureAngry1.loadFromFile("ASSETS\\IMAGES\\Satoru_A2.png")) // the angry_1 texture for satoru
	{
		std::cout << "problem loading satoru Angry1" << std::endl;
	}
	m_satoruSprite.setTexture(m_satoruTextureNutrual1);
	m_satoruSprite.setPosition(-670.0f , -250.0f);
	m_satoruSprite.setScale(1.5f, 1.5f); 
}

void Game::setupBackgrounds()
{
	if (!m_backGroundTexture.loadFromFile("ASSETS\\IMAGES\\bg1.jpg")) // texture for background 
	{
		std::cout << "problem loading background" << std::endl; 
	}
	m_backGroundSprite.setTexture(m_backGroundTexture);  
	m_backGroundSprite.setPosition(0.0f, 0.0f);  

	if (!m_textBoxTexture.loadFromFile("ASSETS\\IMAGES\\textbox.png")) // texture for text box 
	{
		std::cout << "problem loading textbox" << std::endl; 
	}
	m_textBoxSprite.setTexture(m_textBoxTexture); 
	m_textBoxSprite.setPosition(0.0f, 800.0f); 
	m_textBoxSprite.setColor(colour); 

	if (!m_textBoxCornerTexture.loadFromFile("ASSETS\\IMAGES\\textboxCorner.png")) // texture for text box 
	{
		std::cout << "problem loading textbox corner" << std::endl;
	}
	m_textBoxCornerSprite.setTexture(m_textBoxCornerTexture);
	m_textBoxCornerSprite.setPosition(1595.0f, 550.0f);
	m_textBoxCornerSprite.setColor(colour);
	m_textBoxCornerSprite.setScale(2.0f, 2.0f); 
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
}

void Game::choiceText() // a function to determine the text of the choices based of scene number
{
	if (counter == 11) // 12th scene
	{
		m_choiceText1A.setString("'go away nerd!'"); // setting up the text for the first option box 
		m_choiceText1B.setString("'sure thing yuri, i can hang out!'");  // setting up the text for the second option box
	}
}

void Game::hideTextButton() // a function to set up the hide button and its text
{
	m_hideButton.setFillColor(sf::Color::Red);
	m_hideButton.setRadius(30.0f);
	m_hideButton.setOrigin(30.0f, 30.0f);
	m_hideButton.setPosition(1860.0f, 795.0f);

	m_hideButtonBoarder.setFillColor(sf::Color::Black); 
	m_hideButtonBoarder.setRadius(35.0f);
	m_hideButtonBoarder.setOrigin(35.0f, 35.0f);
	m_hideButtonBoarder.setPosition(1860.0f, 795.0f); 

	m_hideText.setString("Hide"); 
	m_hideText.setFont(m_ArialBlackfont); // set up for the name in the dialogue box 
	m_hideText.setPosition(1837.0f, 782.0f);
	m_hideText.setCharacterSize(20U); 
	m_hideText.setOutlineColor(sf::Color::White);
}
