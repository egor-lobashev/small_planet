#include "Head.hpp"
#include "Script.hpp"
#include "CustomScripts.hpp"
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "Singleton.h"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "DataStorage.hpp"
#include "Collider.hpp"
#include "PhysController.hpp"
#include "PhysicScripts.hpp"

//#include "API.hpp"

void PlayerController::execute(Singleton* sing)
{
  float x_obj = objPointer->x;
  float y_obj = objPointer->y;
  float x_center = SCREEN_X / 2;
  float y_center = SCREEN_Y / 2;

  std::vector<float> clockwise_direction = {y_center - y_obj, x_obj - x_center};
  float distance = pow(pow(clockwise_direction[0], 2) + pow(clockwise_direction[1], 2), 0.5);
  float speed = 10;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        objPointer -> x -= speed * clockwise_direction[0] / distance;
        objPointer -> y -= speed * clockwise_direction[1] / distance;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        objPointer -> x += speed * clockwise_direction[0] / distance;
        objPointer -> y += speed * clockwise_direction[1] / distance;        
    }

}

void BWCollided_player::collisionResolving(Collider* source, Collider* enemy)
{
    //logics

    return;
}

void BWCollided_wall::collisionResolving(Collider* source, Collider* enemy)
{
  return;
}

int Spawner::spawned_number = 0;
void Spawner::execute(Singleton* sing)
{
  if ((rand()) % 100 == 0)
  {
    std::string meteorName = "meteor";
    meteorName.append(std::to_string(spawned_number++));

    if(sing -> data -> createObjectInStorage(meteorName))
    {
      float phi = (rand() % 100)/100.0 * (2*M_PI);
      sing -> data -> getObject(meteorName)-> x = 1000*cos(phi);
      sing -> data -> getObject(meteorName)-> y = 1000*sin(phi);
      sing -> data -> getObject(meteorName) -> addComponent<Renderer>(sing);
      sing -> data -> getObject(meteorName) -> getComponent<Renderer>()->loadTexture("resources/meteor.png");
      int size = rand() % 70 + 10;
      sing -> data -> getObject(meteorName) -> getComponent<Renderer>()->setSize(size, size);
      sing -> data -> getObject(meteorName) -> addComponent<Collider>(sing);
      sing -> data -> getObject(meteorName) -> addComponent<BWCollided_player>(sing);
      sing -> data -> getObject(meteorName) -> getComponent<Collider>() -> shape.ifCircle = true;
      sing -> data -> getObject(meteorName) -> getComponent<Collider>() -> shape.r = size/2;
      int speed = rand()%10;
      sing -> data -> getObject(meteorName) -> getComponent<Collider>() -> shape.setVelocity(-speed*cos(phi), -speed*sin(phi));
      sing -> data -> getObject(meteorName) -> addComponent<VelocityPhysic>(sing);
      sing -> data -> getObject(meteorName) -> addComponent<CentralGravity>(sing);
      sing -> data -> getObject(meteorName) -> addComponent<Meteor>(sing);
    }

  }
}

void Meteor::execute(Singleton* sing)
{
  age += 1;
  if (age >= 1000)
  {
    objPointer->x = 1000000 * objPointer->x;
    objPointer->y = 1000000 * objPointer->y;
  }
  if (objPointer->getComponent<Collider>()->checkCollision(sing->data->getObject("player")->getComponent<Collider>()))
  {
    sing->data->getObject("player")->getComponent<HP>()->hp--;
  }
}

void Jump::execute(Singleton* sing)
{
  float x_obj = objPointer->x;
  float y_obj = objPointer->y;
  float x_center = SCREEN_X / 2;
  float y_center = SCREEN_Y / 2;

  std::vector<float> top_direction = {x_obj - x_center, y_obj - y_center};
  float distance = pow(pow(top_direction[0], 2) + pow(top_direction[1], 2), 0.5);

  if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) and (distance <= 176))
  {
    if(objPointer ->getComponent<Collider>())
    {
      int jump_heigth = 16;
      objPointer -> getComponent<Collider>() -> shape.velocityS[0] += top_direction[0] * jump_heigth / distance;
      objPointer -> getComponent<Collider>() -> shape.velocityS[1] += top_direction[1] * jump_heigth / distance;
    }
  }
}

void HP::execute(Singleton* sing)
{
  if (hp <= 0)
  {
    printf("Game over!\n Your result is %d seconds\n", (int) clock.getElapsedTime().asSeconds());
    sing -> grManager -> window -> close();
  }
}

void initScript(std::string name, std::string object, DataStorage* data, Singleton* sing)
{
  if (name == typeid(PlayerController).name())
    data -> getObject(object) -> addComponent<PlayerController>(sing);
  if (name == typeid(Spawner).name())
    data -> getObject(object) -> addComponent<Spawner>(sing);
  if (name == typeid(Jump).name())
    data -> getObject(object) -> addComponent<Jump>(sing);
  if (name == typeid(Meteor).name())
    data -> getObject(object) -> addComponent<Meteor>(sing);
}

void initVelocityPhysic(std::string object, Singleton* sing, std::string component)
{
  sing -> data -> getObject(object) -> addComponent<VelocityPhysic>(sing);
  if (component.substr(0, component.find('\n')) == "true")
    sing -> data -> getObject(object) -> getComponent<VelocityPhysic>() -> isHasInertion = true;
  else
    sing -> data -> getObject(object) -> getComponent<VelocityPhysic>() -> isHasInertion = false;
  component = component.substr(component.find('\n') + 1);
}

void initGravitationPhysic(std::string object, Singleton* sing, std::string component)
{
  sing -> data -> getObject(object) -> addComponent<GravitationPhysic>(sing);
}








