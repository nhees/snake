#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"
#include <string>

struct Coordinate{
	int x, y;
};

class SnakeObject{
private:
	int snakePieceWidth, snakePieceHeight, xvel, yvel;

	Coordinate incomingVelocity;

	// Used for moving the snake
	int frameCount;
public:
	std::vector<Coordinate> snakePieceLocations;
	SnakeObject();

	int getSnakePieceWidth();

	void update();

	void moveSnake();

	void setVelocity(int x, int y);

	Coordinate getVelocity();
};

// Game Object, duh!
class GameObject{

	private:
		// Flag to determine if the game is running
		bool running;

		// Flag to determine if the game is over
		bool gameOver;

		// The snake object reference
		SnakeObject * snake;

		sf::Font font;
		sf::Text gameOverText;
		sf::Text scoreText;

		int score;

	public:
		GameObject();
		~GameObject();

		void processEvents(sf::RenderWindow &window);

		void processLogic(sf::RenderWindow &window);

		void render(sf::RenderWindow &window);

		bool isRunning();

		void drawSnake(sf::RenderWindow &window);
};