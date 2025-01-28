#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <string>

using namespace std;

void handleBet(int playerChoice, int randomColor, int& points, int wager, int& streak, sf::Text& resultText, sf::Text& correctAnswerText, sf::Text& pointsText, sf::Text& streakText);

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Roulette Game");

    // Load a font
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    // Create text objects
    sf::Text instructionText("Bet on Red or Black:", font, 30);
    instructionText.setPosition(50, 50);
    instructionText.setFillColor(sf::Color::Black);

    sf::Text resultText("", font, 30);
    resultText.setPosition(50, 150);
    resultText.setFillColor(sf::Color::Red);

    sf::Text guessText("", font, 30);
    guessText.setPosition(50, 250);
    guessText.setFillColor(sf::Color::Black);

    sf::Text correctAnswerText("", font, 30);
    correctAnswerText.setPosition(50, 350);
    correctAnswerText.setFillColor(sf::Color::Red);

    sf::Text pointsText("Points: 3000", font, 30);
    pointsText.setPosition(50, 500);
    pointsText.setFillColor(sf::Color::Black);

    sf::Text wagerText("Wager: 0", font, 30);
    wagerText.setPosition(50, 400);
    wagerText.setFillColor(sf::Color::Black);

    sf::Text streakText("Streak: 0", font, 30);
    streakText.setPosition(50, 450);
    streakText.setFillColor(sf::Color::Black);

    // Create buttons for Red and Black
    sf::RectangleShape redButton(sf::Vector2f(150, 50));
    redButton.setFillColor(sf::Color::Red);
    redButton.setPosition(350, 250);

    sf::Text redButtonText("Red", font, 24);
    redButtonText.setFillColor(sf::Color::White);
    redButtonText.setPosition(400, 260);

    sf::RectangleShape blackButton(sf::Vector2f(150, 50));
    blackButton.setFillColor(sf::Color::Black);
    blackButton.setPosition(500, 250);

    sf::Text blackButtonText("Black", font, 24);
    blackButtonText.setFillColor(sf::Color::White);
    blackButtonText.setPosition(550, 260);

    // Create "Spin Again" button
    sf::RectangleShape spinAgainButton(sf::Vector2f(200, 50));
    spinAgainButton.setFillColor(sf::Color::Yellow);
    spinAgainButton.setPosition(425, 320);

    sf::Text spinAgainText("Spin Again", font, 24);
    spinAgainText.setFillColor(sf::Color::Black);
    spinAgainText.setPosition(455, 330);

    // Create "Cash Out" button
    sf::RectangleShape cashOutButton(sf::Vector2f(150, 50));
    cashOutButton.setFillColor(sf::Color::Green);
    cashOutButton.setPosition(400, 500);

    sf::Text cashOutText("Cash Out", font, 24);
    cashOutText.setFillColor(sf::Color::White);
    cashOutText.setPosition(420, 510);

    // Create "Play Again" button (for the win screen)
    sf::RectangleShape playAgainButton(sf::Vector2f(200, 50));
    playAgainButton.setFillColor(sf::Color::Blue);
    playAgainButton.setPosition(300, 400);

    sf::RectangleShape exitButton(sf::Vector2f(150, 50));
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(600, 500);

    sf::Text exitText("Exit", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(650, 510);

    sf::RectangleShape exitButtonTwo(sf::Vector2f(200, 50));
    exitButtonTwo.setFillColor(sf::Color::Red);
    exitButtonTwo.setPosition(300, 500);

    sf::Text exitTextTwo("Exit", font, 24);
    exitTextTwo.setFillColor(sf::Color::White);
    exitTextTwo.setPosition(330, 510);

    sf::Text playAgainText("Play Again", font, 24);
    playAgainText.setFillColor(sf::Color::White);
    playAgainText.setPosition(330, 410);

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1); // 0 for Red, 1 for Black

    // Game variables
    int randomColor = dis(gen);
    std::string playerInput;
    int streak = 0;
    int points = 3000;
    int wager = 0;
    bool enteringWager = true;
    bool gameEnded = false;

    // Main loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (cashOutButton.getGlobalBounds().contains(mousePos) && !gameEnded) {
                    // Handle cash out
                    gameEnded = true;
                } else if (playAgainButton.getGlobalBounds().contains(mousePos) && gameEnded) {
                    // Handle play again
                    // Reset the game variables
                    enteringWager = true;
                    gameEnded = false;
                    resultText.setString("");
                    correctAnswerText.setString("");
                    wagerText.setString("Wager: 0");
                    playerInput.clear();
                    guessText.setString("");
                } else if (exitButtonTwo.getGlobalBounds().contains(mousePos) && gameEnded) {
                    exit(0);
                } else if (exitButton.getGlobalBounds().contains(mousePos)) {
                    exit(0);
                } else if (redButton.getGlobalBounds().contains(mousePos) && !gameEnded && !enteringWager) {
                    // Player bets on Red
                    playerInput = "Red";
                    guessText.setString(playerInput);
                    handleBet(0, randomColor, points, wager, streak, resultText, correctAnswerText, pointsText, streakText);
                    enteringWager = true;
                    randomColor = dis(gen); // Generate a new color
                } else if (blackButton.getGlobalBounds().contains(mousePos) && !gameEnded && !enteringWager) {
                    // Player bets on Black
                    playerInput = "Black";
                    guessText.setString(playerInput);
                    handleBet(1, randomColor, points, wager, streak, resultText, correctAnswerText, pointsText, streakText);
                    enteringWager = true;
                    randomColor = dis(gen); // Generate a new color
                } else if (spinAgainButton.getGlobalBounds().contains(mousePos)) {
                    // Reset the game for another spin
                    enteringWager = true;
                    resultText.setString("");
                    correctAnswerText.setString("");
                    wagerText.setString("Wager: 0");
                    playerInput.clear();
                    guessText.setString("");
                }
            }

            if (!gameEnded && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                    playerInput += static_cast<char>(event.text.unicode);

                    if (enteringWager) {
                        wager = std::stoi(playerInput);
                        wagerText.setString("Wager: " + std::to_string(wager));
                    }

                }
                else if (event.text.unicode == '\b' && !playerInput.empty()) {
                    playerInput.pop_back();

                    if (enteringWager) {
                        wager = playerInput.empty() ? 0 : std::stoi(playerInput);
                        wagerText.setString("Wager: " + std::to_string(wager));
                    }

                }
                else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    if (enteringWager) {
                        if (wager > points) {
                            resultText.setString("Wager exceeds your points! Try again.");
                        } else if (wager == 0) {
                            resultText.setString("Wager cannot be zero! Enter a valid wager.");
                        } else {
                            playerInput.clear();
                            guessText.setString("");
                            enteringWager = false;
                            resultText.setString("Now, choose Red or Black!");
                        }
                    }
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        if (gameEnded) {
            // Display the win screen
            sf::Text winText("Cash out: " + to_string(points), font, 36);
            winText.setFillColor(sf::Color::Black);
            winText.setPosition(100, 200);

            window.draw(winText);
            window.draw(playAgainButton);
            window.draw(playAgainText);
            window.draw(exitButtonTwo);
            window.draw(exitTextTwo);
        } else {
            // Draw the game interface
            window.draw(instructionText);
            window.draw(resultText);
            window.draw(guessText);
            window.draw(correctAnswerText);
            window.draw(pointsText);
            window.draw(wagerText);
            window.draw(streakText);
            window.draw(cashOutButton);
            window.draw(cashOutText);
            window.draw(redButton);
            window.draw(redButtonText);
            window.draw(blackButton);
            window.draw(blackButtonText);
            window.draw(spinAgainButton);
            window.draw(spinAgainText);
            window.draw(exitButton);
            window.draw(exitText);
        }

        // Display the content
        window.display();
    }

    return 0;
}

void handleBet(int playerChoice, int randomColor, int& points, int wager, int& streak, sf::Text& resultText, sf::Text& correctAnswerText, sf::Text& pointsText, sf::Text& streakText)
{
    if (playerChoice == randomColor) {
        streak++;
        points += wager;
        resultText.setString("Correct! You won the bet.");
        correctAnswerText.setString("");
    } else {
        streak = 0;
        points -= wager;
        resultText.setString("Wrong! You lost the bet.");
        correctAnswerText.setString(randomColor == 0 ? "Correct: Red" : "Correct: Black");
    }

    pointsText.setString("Points: " + std::to_string(points));
    streakText.setString("Streak: " + std::to_string(streak));
}

