#ifndef PHYSSCRIPTS
#define PHYSSCRIPTS

#include "Head.hpp"
#include "PhysController.hpp"
#include <cmath>


class VelocityPhysic: public PhysicScript
{
    public:

        bool isHasInertion = true;

        VelocityPhysic()
        {
            this->name = typeid(VelocityPhysic).name();
        }

        std::string writeDown()
        {
          std::string s = "***";
          s += this -> name;
          s += '\n';
          s += BTS(isHasInertion);
          s += '\n';
          return s;
        }

        void executePhysic(Singleton* sing)
        {
            if(objPointer ->getComponent<Collider>())
            {
                objPointer -> x += objPointer -> getComponent<Collider>() -> shape.velocityS[0];
                objPointer -> y += objPointer -> getComponent<Collider>() -> shape.velocityS[1];
                
                if(isHasInertion)
                {
                    objPointer -> getComponent<Collider>() -> shape.velocityS[0] *= 0.97;
                    objPointer -> getComponent<Collider>() -> shape.velocityS[1] *= 0.97;
                }

            }
        }
};

class GravitationPhysic: public PhysicScript
{
    public:

        GravitationPhysic()
        {
            this->name = typeid(GravitationPhysic).name();
        }

        std::string writeDown()
        {
          std::string s = "***";
          s += this -> name;
          s += '\n';
          return s;
        }

        

        void executePhysic(Singleton* sing)
        {
            if(objPointer ->getComponent<Collider>())
            {
                objPointer -> getComponent<Collider>() -> shape.velocityS[1] += g;
            }
        }
};

class CentralGravity: public PhysicScript
{
public:

    CentralGravity()
    {
        this->name = typeid(CentralGravity).name();
    }

    void executePhysic(Singleton* sing)
    {
        float x_obj = objPointer->x;
        float y_obj = objPointer->y;
        float x_center = SCREEN_X / 2;
        float y_center = SCREEN_Y / 2;

        std::vector<float> to_center = {x_center - x_obj, y_center - y_obj};
        float distance = pow(pow(to_center[0], 2) + pow(to_center[1], 2), 0.5);

        int GMm = 30000;

        if(objPointer ->getComponent<Collider>())
        {
            objPointer -> getComponent<Collider>() -> shape.velocityS[0] += to_center[0] * GMm / pow(distance, 3);
            objPointer -> getComponent<Collider>() -> shape.velocityS[1] += to_center[1] * GMm / pow(distance, 3);
        }
    }
};


#endif
