#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "field.hpp"

const int STEP = 128;
const int WIDTH = 3 * STEP;
const int HEIGHT = 3 * STEP;

int main() {
  sf::Vertex firstVerticalLine[] =
  {
      sf::Vertex(sf::Vector2f(0, STEP)),
      sf::Vertex(sf::Vector2f(HEIGHT, STEP))
  };

  sf::Vertex secondVerticalLine[] =
  {
      sf::Vertex(sf::Vector2f(0, 2 * STEP)),
      sf::Vertex(sf::Vector2f(HEIGHT, 2 * STEP))
  };

  sf::Vertex firstHorizontalLine[] =
  {
      sf::Vertex(sf::Vector2f(STEP, 0)),
      sf::Vertex(sf::Vector2f(STEP, HEIGHT))
  };

  sf::Vertex secondHorizontalLine[] =
  {
      sf::Vertex(sf::Vector2f(2 * STEP, 0)),
      sf::Vertex(sf::Vector2f(2 * STEP, HEIGHT))
  };

  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tic-tac-toe");

  sf::Texture circle;
  circle.loadFromFile("assets/circle.png", sf::IntRect(0, 0, STEP, STEP));
  
  sf::Texture cross;
  cross.loadFromFile("assets/cross.png", sf::IntRect(0, 0, STEP, STEP));

  sf::Texture strikev;
  strikev.loadFromFile("assets/strikev.png", sf::IntRect(0, 0, WIDTH, STEP));
  sf::Sprite strikevSprite;
  strikevSprite.setTexture(strikev);

  sf::Texture strikeh;
  strikeh.loadFromFile("assets/strikeh.png", sf::IntRect(0, 0, STEP, HEIGHT));
  sf::Sprite strikehSprite;
  strikehSprite.setTexture(strikeh);

  sf::Texture strikec;
  strikec.loadFromFile("assets/strikec.png", sf::IntRect(0, 0, WIDTH, HEIGHT));
  sf::Sprite strikecSprite;
  strikecSprite.setTexture(strikec);

  sf::Texture rstrikec;
  rstrikec.loadFromFile("assets/reversestrikec.png", sf::IntRect(0, 0, WIDTH, HEIGHT));
  sf::Sprite reversStrikecSprite;
  reversStrikecSprite.setTexture(rstrikec);

  Field board[3][3];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      sf::Vector2f position(i * STEP, j * STEP);
      board[i][j].setPosition(position);
    }
  }

  int currentPlayer = 1;
  int moveCount = 0;

  sf::Sprite strike;

  while (window.isOpen())
  {
    sf::Event event;

    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }

      window.clear();

      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int x = mousePosition.x / STEP;
        int y = mousePosition.y / STEP;
        if (currentPlayer == 1) {
          moveCount++;
          board[x][y].setCircle(circle);
          currentPlayer = 2;
        } else if (currentPlayer == 2) {
          moveCount++;
          board[x][y].setCross(cross);
          currentPlayer = 1;
        }


        //check coll
        for(int i = 0; i < 3; i++){
            if(board[x][i].selected != currentPlayer)
                break;
            if(i == 3-1){
              std::cout << "Player " << currentPlayer << " wins!" << std::endl;

              strike = strikehSprite;
              sf::Vector2f position(x * STEP, 0);
              strike.setPosition(position);
            }
        }
        
        //check row
        for(int i = 0; i < 3; i++){
            if(board[i][y].selected != currentPlayer)
                break;
            if(i == 3-1){
              std::cout << "Player " << currentPlayer << " wins!" << std::endl;

              strike = strikevSprite;
              sf::Vector2f position(0, y * STEP);
              strike.setPosition(position);
            }
        }
        
        //check diag
        if(x == y){
            //we're on a diagonal
            for(int i = 0; i < 3; i++){
                if(board[i][i].selected != currentPlayer)
                    break;
                if(i == 3-1){
                  std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                  strike = reversStrikecSprite;
                }
            }
        }
            
        //check anti diag (thanks rampion)
        if(x + y == 3 - 1){
            for(int i = 0; i < 3; i++){
                if(board[i][(3-1)-i].selected != currentPlayer)
                    break;
                if(i == 3-1){
                  std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                  strike = strikecSprite;
                }
            }
        }

        if(moveCount == (pow(3, 2) - 1)){
          std::cout << "Draw!" << std::endl;
        }
      }

      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          window.draw(board[i][j].sprite);
        }
      }

      window.draw(firstVerticalLine, 2, sf::Lines);
      window.draw(secondVerticalLine, 2, sf::Lines);
      window.draw(firstHorizontalLine, 2, sf::Lines);
      window.draw(secondHorizontalLine, 2, sf::Lines);

      window.draw(strike);

      window.display();
    }
  }
}


// TODO
// - refactor wind conditions
// add animations
// add reste button
// display move counter
// display info about who win
// turn off when someone on wins