#ifndef FIELD_HPP
#define FIELD_HPP

class Field
{
  public:

  int selected;
  sf::Sprite sprite;

  Field();

  Field(sf::Vector2f size, sf::Vector2f position);

  void setPosition(sf::Vector2f position);

  void setCross(sf::Texture &texture);

  void setCircle(sf::Texture &texture);
};

#endif