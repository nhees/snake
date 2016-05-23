#include "game_object.h"

GameObject::GameObject(): running(true), gameOver(false), score(0) {
	// Create snake object
	snake = new SnakeObject();

	// Load font
	font.loadFromFile("data-latin.ttf");

	// Create game over text
	gameOverText.setFont(font);
	gameOverText.setString("Game Over");
	gameOverText.setCharacterSize(24);
	gameOverText.setColor(sf::Color::White);
	gameOverText.setPosition((WINDOW_WIDTH - 100) / 2, WINDOW_HEIGHT / 2);

	// Create score text
	scoreText.setFont(font);
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(12);
	scoreText.setColor(sf::Color::White);
	scoreText.setPosition(5, 5);
}

GameObject::~GameObject(){
	delete snake;
	snake = NULL;
}

// Process Game events
void GameObject::processEvents(sf::RenderWindow &window){
	// SFML Event object
	sf::Event event;

	// Coordinate to hold the current velocity of the snake
	Coordinate temp;
	// Deqeue events on event queue
	while( window.pollEvent(event)){
		// Check if the event is a user close window
		if( event.type == sf::Event::Closed)
			running = false;

		else if( event.type == sf::Event::KeyPressed ){

			// Get the current velocity
			temp = snake->getVelocity();

			// Only move left as long as we're not moving right, etc...
			if( event.key.code == sf::Keyboard::Left && temp.x != 10)
				snake->setVelocity(-10, 0);
			else if( event.key.code == sf::Keyboard::Right && temp.x != -10)
				snake->setVelocity(10, 0);
			else if( event.key.code == sf::Keyboard::Up && temp.y != 10)
				snake->setVelocity(0, -10);
			else if( event.key.code == sf::Keyboard::Down && temp.y != -10)
				snake->setVelocity(0, 10);
		}
	}
}

void GameObject::processLogic(sf::RenderWindow &window){
	// Coordinate holds head location, and get the location of the head
	Coordinate head;
	head.x = snake->snakePieceLocations[0].x;
	head.y = snake->snakePieceLocations[0].y;

	// Check if the snake has moved off screen, it dies if it does.
	if( head.x < 0 || head.x > WINDOW_WIDTH - 10)
		gameOver = true;
	else if( head.y < 0 || head.y > WINDOW_HEIGHT -10 )
		gameOver = true;

	if( !gameOver )	
		// Update snake
		snake->update();
}

void GameObject::render(sf::RenderWindow &window){
	// Fill Window with background black
	window.clear(sf::Color::Black);

	// Draw score text
	scoreText.setString("Score: " + std::to_string(score));
	window.draw(scoreText);

	drawSnake(window);

	// Draw game over screen if neccessary
	if( gameOver )
		window.draw(gameOverText);

	// Update the window with what we've drawn
	window.display();
}

bool GameObject::isRunning(){
	return running;
}

void GameObject::drawSnake(sf::RenderWindow &window){
	// Create a circle object for the snake piece
	sf::CircleShape snakePiece(snake->getSnakePieceWidth());

	// Iterate through the snake pieces
	for( Coordinate coor : snake->snakePieceLocations ){
		snakePiece.setPosition(coor.x, coor.y);
		window.draw(snakePiece);
	}
}

SnakeObject::SnakeObject() : snakePieceWidth(5), snakePieceHeight(5), frameCount(0), xvel(-10), yvel(0) {
	
	incomingVelocity.x = -10;
	incomingVelocity.y = 0;

	// Create a starting position for the snake
	Coordinate startingPosition;
	startingPosition.x = 400;
	startingPosition.y = 300;
	snakePieceLocations.push_back(startingPosition);

	// Create two more pieces of the snake
	startingPosition.x += 10;
	snakePieceLocations.push_back(startingPosition);

	startingPosition.x += 10;
	snakePieceLocations.push_back(startingPosition);
}

int SnakeObject::getSnakePieceWidth() {
	// Can you guess what this does?
	return snakePieceWidth;
}

void SnakeObject::update(){
	
	// Since we want a "choppy" motion, only update the snake every 10 frames
	frameCount++;

	if( frameCount >= 10 ){
		frameCount = 0;
		xvel = incomingVelocity.x;
		yvel = incomingVelocity.y;
		moveSnake();
	}
}

void SnakeObject::moveSnake(){

	// Move through vector and move each piece of the snake towards the head
	for( int i = snakePieceLocations.size() - 1; i > 0; i-- ){
		snakePieceLocations[i].x = snakePieceLocations[i-1].x;
		snakePieceLocations[i].y = snakePieceLocations[i-1].y;
	}

	// Move the head forward
	snakePieceLocations[0].x += xvel;
	snakePieceLocations[0].y += yvel;
}

void SnakeObject::setVelocity(int x, int y){
	incomingVelocity.x = x;
	incomingVelocity.y = y;
}

Coordinate SnakeObject::getVelocity(){
	Coordinate temp;
	temp.x = xvel;
	temp.y = yvel;

	return temp;
}