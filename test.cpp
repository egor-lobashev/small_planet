#include "Head.hpp"


#include "Script.hpp"
#include "GraphicManager.hpp"
#include "ScriptController.hpp"
#include "GameObject.hpp"
#include "DataStorage.hpp"
#include "Renderer.hpp"
#include "CustomScripts.hpp"

#include "Collider.hpp"
#include "PhysController.hpp"
#include "PhysicScripts.hpp"
#include "Animator.hpp"
#include "Singleton.h"
Singleton* sing;
#include "API.hpp"
#include "gameRun.hpp"


main()
{ 
    sing = sing -> getInstance();
    std::srand(time(nullptr));

    API::createObject("planet");
    API::getObject("planet") -> addComponent<Renderer>(sing);
    API::getObject("planet") -> getComponent<Renderer>()->loadTexture("resources/planet.png");
    API::getObject("planet") -> getComponent<Renderer>()->setSize(300, 300);

    API::getObject("planet") -> addComponent<Collider>(sing);
    API::getObject("planet") -> getComponent<Collider>() -> shape.ifMoveable = false;
    API::getObject("planet") -> getComponent<Collider>() -> shape.ifCircle = true;
    API::getObject("planet") -> getComponent<Collider>() -> shape.r = 150;

    API::getObject("planet") -> x = SCREEN_X / 2;
    API::getObject("planet") -> y = SCREEN_Y / 2;


    API::createObject("player");
    API::getObject("player") -> addComponent<Renderer>(sing);
    API::getObject("player") -> getComponent<Renderer>()->loadTexture("resources/pers.png");
    API::getObject("player") -> getComponent<Renderer>()->setSize(50, 50);
    API::getObject("player") -> addComponent<Collider>(sing);
    
    
    API::getObject("player") -> getComponent<Collider>() -> shape.ifCircle = true;
    API::getObject("player") -> getComponent<Collider>() -> shape.r = 25;
    API::getObject("player") -> x = SCREEN_X / 2;
    API::getObject("player") -> y = SCREEN_Y / 2 - 200;



    API::getObject("player") -> addComponent<PlayerController>(sing);
    API::getObject("player") -> addComponent<VelocityPhysic>(sing);
    API::getObject("player") -> addComponent<CentralGravity>(sing);

    API::getObject("player") -> addComponent<Jump>(sing);

    API::getObject("player") -> addComponent<HP>(sing);


    API::createObject("background");
    API::getObject("background") -> addComponent<Renderer>(sing);
    API::getObject("background") -> getComponent<Renderer>() -> loadTexture("resources/background.png");
    API::getObject("background") -> getComponent<Renderer>() -> setSize(SCREEN_X + 20, SCREEN_Y);
    API::getObject("background") -> x = SCREEN_X / 2;
    API::getObject("background") -> y = SCREEN_Y / 2;
    API::getObject("background") -> getComponent<Renderer>() -> layer = 3;


    API::createObject("meteor_spawner");
    API::getObject("meteor_spawner") -> addComponent<Spawner>(sing);


    // API::saveGame("newSave");
    // API::readGame("newSave");
    // API::saveGame("afterReading");
    // //return 0;
    
    while (gameRun())
    {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        API::readGame("newSave");
    }

  sing -> deleteInstance();       
}
