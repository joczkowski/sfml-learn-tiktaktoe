#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

class Field
{
  public:
    int selected;
    sf::Sprite sprite;

    Field()
    {
      selected = false;
    }

    Field(sf::Vector2f size, sf::Vector2f position)
    {
      this->sprite.setPosition(position);
      this->selected = false;
    }

    void setPosition(sf::Vector2f position)
    {
      this->sprite.setPosition(position);
    }

    void setCross(sf::Texture &texture)
    {
      if (!this->selected != 0)
      {
        this->sprite.setTexture(texture);
        this->selected = 1;
      }
    }

    void setCircle(sf::Texture &texture)
    {
      if (!this->selected != 0)
      {
        this->sprite.setTexture(texture);
        this->selected = 2;
      }
    }
};

int main() {
  int horizontalStep = 128;
  int verticalStep = 128;

  int width = 3 * verticalStep;
  int height = 3 * horizontalStep;

  sf::Vertex firstVerticalLine[] =
  {
      sf::Vertex(sf::Vector2f(0, verticalStep)),
      sf::Vertex(sf::Vector2f(height, verticalStep))
  };

  sf::Vertex secondVerticalLine[] =
  {
      sf::Vertex(sf::Vector2f(0, 2 * verticalStep)),
      sf::Vertex(sf::Vector2f(height, 2 * verticalStep))
  };

  sf::Vertex firstHorizontalLine[] =
  {
      sf::Vertex(sf::Vector2f(horizontalStep, 0)),
      sf::Vertex(sf::Vector2f(horizontalStep, height))
  };

  sf::Vertex secondHorizontalLine[] =
  {
      sf::Vertex(sf::Vector2f(2 * horizontalStep, 0)),
      sf::Vertex(sf::Vector2f(2 * horizontalStep, height))
  };

  sf::RenderWindow window(sf::VideoMode(width, height), "Tic-tac-toe");

  sf::Texture circle;
  circle.loadFromFile("assets/circle.png", sf::IntRect(0, 0, verticalStep, horizontalStep));
  
  sf::Texture cross;
  cross.loadFromFile("assets/cross.png", sf::IntRect(0, 0, verticalStep, horizontalStep));

  Field board[3][3];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      sf::Vector2f position(i * verticalStep, j * horizontalStep);
      board[i][j].setPosition(position);
    }
  }

  int currentPlayer = 1;
  int moveCount = 0;

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
        int x = mousePosition.x / verticalStep;
        int y = mousePosition.y / horizontalStep;
        if (currentPlayer == 1) {
          moveCount++;
          board[x][y].setCircle(circle);
          currentPlayer = 2;
        } else if (currentPlayer == 2) {
          moveCount++;
          board[x][y].setCross(cross);
          currentPlayer = 1;
        }


        for(int i = 0; i < 3; i++){
            if(board[x][i].selected != currentPlayer)
                break;
            if(i == 3-1){
              std::cout << "Player " << currentPlayer << " wins!" << std::endl;
            }
        }
        
        //check row
        for(int i = 0; i < 3; i++){
            if(board[i][y].selected != currentPlayer)
                break;
            if(i == 3-1){
              std::cout << "Player " << currentPlayer << " wins!" << std::endl;
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