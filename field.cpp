#include <SFML/Graphics.hpp>

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