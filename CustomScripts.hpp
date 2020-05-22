#ifndef CUSTOM_SCRIPTS
#define CUSTOM_SCRIPTS

#include "Head.hpp"

class PlayerController: public Script
{
  public:

  PlayerController()
  {
    this->name = typeid(PlayerController).name();
  }

  void execute(Singleton* sing);

};

class Jump: public Script
{
  public:

  Jump()
  {
    this->name = typeid(Jump).name();
  }

  void execute(Singleton* sing);

};

class Spawner: public Script
{
  public:

  Spawner()
  {
    this->name = typeid(Spawner).name();
  }

  void execute(Singleton* sing);

  static int spawned_number;
};

class Meteor: public Script
{
  public:

  Meteor()
  {
    this->name = typeid(Meteor).name();
  }

  void execute(Singleton* sing);

  int age = 0;
};

class HP: public Script
{
  public:

  HP()
  {
    this->name = typeid(HP).name();
  }

  int hp = 10;
  sf::Clock clock;

  void execute(Singleton* sing);
};

void initScript(std::string name, std::string objName, DataStorage* data, Singleton* sing);
void initVelocityPhysic(std::string object, Singleton* sing, std::string component);
void initGravitationPhysic(std::string object, Singleton* sing, std::string component);

#endif
