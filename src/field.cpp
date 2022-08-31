#include <SFML/Graphics.hpp>
#include "field.hpp"

Field::Field()
{
  selected = false;
}

Field::Field(sf::Vector2f size, sf::Vector2f position)
{
  this->sprite.setPosition(position);
  this->selected = false;
}

void Field::setPosition(sf::Vector2f position)
{
  this->sprite.setPosition(position);
}

void Field::setCross(sf::Texture &texture)
{
  if (!this->selected != 0)
  {
    this->sprite.setTexture(texture);
    this->selected = 1;
  }
}

void Field::setCircle(sf::Texture &texture)
{
  if (!this->selected != 0)
  {
    this->sprite.setTexture(texture);
    this->selected = 2;
  }
}