#include "Game.h"
#include "GameTester.h"

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
// -------------------- Object class ----------------------

Object::Object()
{
}

Object::Object(string name, int value)
{
  // IMPLEMENT ME

  if (value < 0)
  {
    throw std::invalid_argument("Negative value detected");
  }

  this->name = name;
  this->value = value;
  this->owner_ = nullptr;
}

Object::~Object()
{
}

string Object::getName() const
{
  // IMPLEMENT ME

  return name; // dummy
}

int Object::getValue() const
{
  // IMPLEMENT ME

  return value; // dummy
}

string Object::getType() const
{
  return type;
}

string Object::print() const
{
  // IMPLEMENT ME
  return type + ", name: " + getName() + ", value: " + std::to_string(getValue());
}

std::ostream &operator<<(std::ostream &os, const Object &o)
{
  // IMPLEMENT ME
  return os << o.print();
}

// ------------------- Food class ----------------------

Food::Food(string name, int value) : Object(name, value)
{
  this->type = "Food";
 
}

Food::~Food() {}

string Food::getName() const
{
  // IMPLEMENT ME

  return Object::getName(); // dummy
}

int Food::getValue() const
{
  // IMPLEMENT ME

  return Object::getValue(); // dummy
}

string Food::getType() const
{
  return "Food";
}

string Food::print() const
{
  // IMPLEMENT ME

  return "name: " + getName() + ", value: " + std::to_string(getValue());
}

void Food::use(Player &player)
{
  // IMPLEMENT ME
}

std::ostream &operator<<(std::ostream &os, const Food &o)
{
  // IMPLEMENT ME
  return os << o.print();
}

// ------------------- Weapon class ----------------------

Weapon::Weapon(string name, int value) : Object(name, value)
{
  this->type = "Weapon";
  

}

Weapon::~Weapon() {}

string Weapon::getName() const
{
  // IMPLEMENT ME

  return Object::getName(); // dummy
}

string Weapon::getType() const
{
  return "Weapon";
}

int Weapon::getValue() const
{
  // IMPLEMENT ME

  return Object::getValue(); // dummy
}

string Weapon::print() const
{
  // IMPLEMENT ME
  return "name: " + getName() + ", value: " + std::to_string(getValue());
}

void Weapon::use()
{
  // IMPLEMENT ME
}

std::ostream &operator<<(std::ostream &os, const Weapon &o)
{
  // IMPLEMENT ME
  return os << o.print();
}

// ------------------- Armour class ----------------------

Armour::Armour(string name, int value) : Object(name, value)
{
  this->type = "Armour";
  
}

Armour::~Armour() {}

string Armour::getName() const
{
  // IMPLEMENT ME

  return Object::getName(); // dummy
}

int Armour::getValue() const
{
  // IMPLEMENT ME

  return Object::getValue(); // dummy
}

string Armour::getType() const
{
  return "Armour";
}

string Armour::print() const
{
  // IMPLEMENT ME

  return "name: " + getName() + ", value: " + std::to_string(getValue());
}

std::ostream &operator<<(std::ostream &os, const Armour &o)
{
  // IMPLEMENT ME

  return os << o.print();
}

// ------------------- Player class ----------------------

Player::Player() {} // REMOVE ME

Player::Player(string name)
{
  // IMPLEMENT ME
  this->name = name;
  this->health = 100;
  this->type = type;
  this->stamina = 100;
  armor_ = 0;
  weapon_ = nullptr;
  gold_ = 0;
  inventory_ = new std::vector<Object *>();
}

Player::~Player()
{
}

string Player::getName() const
{
  // IMPLEMENT ME

  return name; // dummy
}

int Player::getHealth() const
{
  // IMPLEMENT ME

  return health; // dummy
}

int Player::getStamina() const
{
  // IMPLEMENT ME

  return stamina; // dummy
}

void Player::pickup(std::unique_ptr<Object> o)
{
  // IMPLEMENT ME
  if (health <= 0)
  {
    throw std::logic_error("Player is dead");
  }
  o->setOwner(this);
  inventory_->push_back(o.release());
}

void Player::addObjectToInventory(Object *o)
{
  o->setOwner(this);
  inventory_->push_back(o);
}

string Player::getInventory() const
{
  // IMPLEMENT ME

  std::stringstream ss;
  ss << "List of items: " << type << ": " << std::endl;
  for (const auto &o : *inventory_)
  {
    ss << o->getName() << std::endl;
  }
  return ss.str();
}

string Player::print() const
{
  // IMPLEMENT ME

  std::stringstream ss;
  ss << "Name: " << name << std::endl;
  ss << "Type: " << type << std::endl;
  ss << "Health: " << health << std::endl;
  ss << "Stamina: " << stamina << std::endl;

  if (inventory_->empty()) {
  ss << "List of items: none" << std::endl;
} else {
  ss << "List of items:" << std::endl;

  for (const auto &o : *inventory_)
  {
    ss << o->getType() << o->print() << std::endl;
  }
}
  if (weapon_)
  {
    ss << "Weapon in use: " << weapon_->getType() << std::endl;
  }
  else
  {
    ss << "Weapon in use: none" << std::endl;
  }
  if (armor_)
  {
    ss << "Armour in use: " << armor_->getType() << std::endl;
  }
  else
  {
    ss << "Armour in use: none" << std::endl;
  }

  return ss.str();
}

bool Player::use(string name)
{

  if (health <= 0)
  {
    throw std::logic_error("Cannot use items when dead");
  }

  for (int i = 0; i < inventory_->size(); i++)
  {
    if (inventory_->at(i)->getName() == name)
    {
      // Call the use() function of the object in inventory
      inventory_->at(i)->use();
      return true;
    }
  }

  // If the object is not found in the inventory, return false
  return false;
}

std::ostream &operator<<(std::ostream &os, const Player &p)
{
  // IMPLEMENT ME
  os << p.print();
  return os;
}

// ------------------- Fighter class ----------------------

Fighter::Fighter(string name) : Player(name)
{
  type = "Fighter";
}

Fighter::~Fighter() {}

bool Fighter::attack(Player &other)
{
  if (health <= 0 || other.health <= 0)
  {
    throw std::logic_error("Stop! " + other.name + " is already dead.");
  }

  if (stamina < 10)
  {
    return false;
  }

  stamina -= 10;

  int attackStrength = (weapons_ ? weapons_->getValue() : 0);
  int defendStrength = 0;
  for (const auto &o : other.inventorys_)
  {
    if (o->getType() == "Armour")
    {
      defendStrength += o->getValue();
    }
  }

  if (attackStrength > defendStrength)
  {
    other.health -= attackStrength - defendStrength;
    return true;
  }

  return false;
}
// ------------------- Healer class ----------------------

Healer::Healer(string name) : Player(name) {
// Set the type of the player to "Healer"
type = "Healer";
}

Healer::~Healer() {}

bool Healer::heal(Player &other)
{
if (other.health >= 100)
{
// Player is already at full health, can't heal any more
return false;
}
else
{
// Heal the player by a certain amount
other.health += 20;
// Make sure player's health doesn't exceed 100
if (other.health > 100)
{
other.health = 100;
}
return true;
}
}
