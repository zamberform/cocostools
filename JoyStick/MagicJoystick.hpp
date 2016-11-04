//
//  MagicJoystick.hpp
//  MyCppGame
//
//  Created by Wang Chun on 2016/11/01.
//
//

#ifndef MagicJoystick_hpp
#define MagicJoystick_hpp

#include "cocos2d.h"

using namespace cocos2d;

class MagicJoystick : public Node
{
private:
    Point _direction;
    Sprite* _knob;
    Point _offset;
    
    std::function< void(Point) > joystickDirection;
    std::function< void() > joystickReleased;
    
public:
    MagicJoystick();
    ~MagicJoystick();
    
    static MagicJoystick* create(std::string plistname, std::vector<std::string> bottomLayers, std::string stick, std::string knob);
    
    bool init(std::string plistname, std::vector<std::string> bottomLayers, std::string stick, std::string knob);
    
    void setBaseDirectionAmount(float amount);
    
    void addDirectionListener(std::function< void(Point) > func);
    void addReleasedListener(std::function< void() > func);
    
private:
    float angleBetween(Point startPoint, Point endPoint);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};

#endif /* MagicJoystick_hpp */
