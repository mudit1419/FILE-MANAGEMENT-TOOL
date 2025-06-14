// Snake Game using SFML

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 20;

class SnakeGame {
public:
    SnakeGame();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void reset();
    void move();
    void checkCollision();
    void spawnFood();

    sf::RenderWindow window;
    sf::RectangleShape snakeSegment;
    std::vector<sf::Vector2f> snake;
    sf::Vector2f direction;
    sf::Vector2f foodPosition;
    sf::CircleShape food;
    sf::Clock clock;
    float speed;
    int score;
    bool isGameOver;

    sf::Font font;
    sf::Text scoreText;

    sf::SoundBuffer eatBuffer;
    sf::Sound eatSound;
    sf::SoundBuffer gameOverBuffer;
    sf::Sound gameOverSound;
    sf::Music backgroundMusic;
};

SnakeGame::SnakeGame() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game"),
    direction(CELL_SIZE, 0), speed(0.1f), score(0), isGameOver(false) {

    window.setFramerateLimit(60);

    snakeSegment.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    snakeSegment.setFillColor(sf::Color::Green);

    snake.push_back(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

    food.setRadius(CELL_SIZE / 2);
    food.setFillColor(sf::Color::Red);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnFood();

    font.loadFromFile("assets/arial.ttf");
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    eatBuffer.loadFromFile("assets/eat.wav");
    eatSound.setBuffer(eatBuffer);

    gameOverBuffer.loadFromFile("assets/gameover.wav");
    gameOverSound.setBuffer(gameOverBuffer);

    backgroundMusic.openFromFile("assets/background.ogg");
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
}

void SnakeGame::run() {
    while (window.isOpen()) {
        processEvents();
        if (!isGameOver && clock.getElapsedTime().asSeconds() >= speed) {
            update();
            clock.restart();
        }
        render();
    }
}

void SnakeGame::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up && direction.y == 0)
                direction = sf::Vector2f(0, -CELL_SIZE);
            else if (event.key.code == sf::Keyboard::Down && direction.y == 0)
                direction = sf::Vector2f(0, CELL_SIZE);
            else if (event.key.code == sf::Keyboard::Left && direction.x == 0)
                direction = sf::Vector2f(-CELL_SIZE, 0);
            else if (event.key.code == sf::Keyboard::Right && direction.x == 0)
                direction = sf::Vector2f(CELL_SIZE, 0);
            else if (event.key.code == sf::Keyboard::R && isGameOver)
                reset();
        }
    }
}

void SnakeGame::update() {
    move();
    checkCollision();
    scoreText.setString("Score: " + std::to_string(score));
    speed = std::max(0.05f, 0.1f - score * 0.005f);
}

void SnakeGame::render() {
    window.clear();

    for (auto& segment : snake) {
        snakeSegment.setPosition(segment);
        window.draw(snakeSegment);
    }

    food.setPosition(foodPosition);
    window.draw(food);
    window.draw(scoreText);

    if (isGameOver) {
        sf::Text gameOverText("Game Over! Press R to Restart", font, 30);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(150, WINDOW_HEIGHT / 2);
        window.draw(gameOverText);
    }

    window.display();
}

void SnakeGame::move() {
    for (int i = snake.size() - 1; i > 0; --i)
        snake[i] = snake[i - 1];

    snake[0] += direction;
}

void SnakeGame::checkCollision() {
    // Wall collision
    if (snake[0].x < 0 || snake[0].x >= WINDOW_WIDTH ||
        snake[0].y < 0 || snake[0].y >= WINDOW_HEIGHT) {
        isGameOver = true;
        gameOverSound.play();
        return;
    }

    // Self collision
    for (size_t i = 1; i < snake.size(); ++i) {
        if (snake[0] == snake[i]) {
            isGameOver = true;
            gameOverSound.play();
            return;
        }
    }

    // Food collision
    if (snake[0] == foodPosition) {
        snake.push_back(snake.back());
        eatSound.play();
        score++;
        spawnFood();
    }
}

void SnakeGame::spawnFood() {
    foodPosition = sf::Vector2f((rand() % (WINDOW_WIDTH / CELL_SIZE)) * CELL_SIZE,
                                (rand() % (WINDOW_HEIGHT / CELL_SIZE)) * CELL_SIZE);
}

void SnakeGame::reset() {
    snake.clear();
    snake.push_back(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    direction = sf::Vector2f(CELL_SIZE, 0);
    score = 0;
    speed = 0.1f;
    isGameOver = false;
    spawnFood();
    clock.restart();
}

int main() {
    SnakeGame game;
    game.run();
    return 0;
}
