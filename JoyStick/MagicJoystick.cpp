//
//  MagicJoystick.cpp
//  MyCppGame
//
//  Created by Wang Chun on 2016/11/01.
//
//

#include "MagicJoystick.hpp"

#define kNumberOfStickLayers 20.0
#define kMaxDistance 50.0
#define kStiffness 10.0

#define joystickNormalizedCenter Point(.50,.50)

#define kStickTag "stick"

MagicJoystick::MagicJoystick(){

}

MagicJoystick::~MagicJoystick(){
    
}

MagicJoystick* MagicJoystick::create(std::string plistname, std::vector<std::string> bottomLayers, std::string stick, std::string knob){
    MagicJoystick *pRet = new(std::nothrow) MagicJoystick();
    
    if (pRet && pRet->init(plistname, bottomLayers, stick, knob))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MagicJoystick::init(std::string plistname, std::vector<std::string> bottomLayers, std::string stick, std::string knob)
{
    if (!Node::init()) {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistname);
    
    setBaseDirectionAmount(1);
    
    for (int i = 0; i < bottomLayers.size(); i ++) {
        auto layer = Sprite::createWithSpriteFrameName(bottomLayers.at(i));
        addChild(layer);
        
        layer->setPosition(joystickNormalizedCenter);
    }
    
    for (size_t i = bottomLayers.size(); i < bottomLayers.size() + kNumberOfStickLayers; i ++) {
        auto stickFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(stick);
        
        auto stickLayer = Sprite::createWithSpriteFrame(stickFrame);
        addChild(stickLayer);
        
        float stickScale = .98;
        float scaleSubtraction = ((kNumberOfStickLayers - (i - bottomLayers.size())) /kNumberOfStickLayers);
        stickScale = stickScale - (scaleSubtraction * .5);
        stickLayer->setScale(stickScale);
        stickLayer->setPosition(joystickNormalizedCenter);
        stickLayer->setName(kStickTag);
    }
    
    _knob = Sprite::createWithSpriteFrameName(knob);
    addChild(_knob);
    _knob->setPosition(joystickNormalizedCenter);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MagicJoystick::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MagicJoystick::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MagicJoystick::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void MagicJoystick::setBaseDirectionAmount(float amount){
    setContentSize(Size(amount, amount));
}

void MagicJoystick::addDirectionListener(std::function< void(Vec2) > func){
    joystickDirection = func;
}

void MagicJoystick::addReleasedListener(std::function< void() > func){
    joystickReleased = func;
}

float MagicJoystick::angleBetween(Point startPoint, Point endPoint){
    auto originPoint = Point(endPoint.x - startPoint.x, endPoint.y - startPoint.y);
    float bearingRadians = atan2f(originPoint.y, originPoint.x);
    float bearingDegrees = bearingRadians * (180.0 / M_PI);
    bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees));
    return bearingDegrees;
}

bool MagicJoystick::onTouchBegan(Touch* touch, Event* event)
{
    stopAllActions();
    
    return true;
}

void MagicJoystick::onTouchMoved(Touch* touch, Event* event)
{
    float distance = touch->getLocation().getDistance( this->getPosition());
    distance =  clampf(distance, 0, kMaxDistance);
    float angle = angleBetween(getPosition(), touch->getLocation());
    
    float vx = cos(angle * M_PI / 180) * (distance * 1.5);
    float vy = sin(angle * M_PI / 180) * (distance * 1.5);
    
    _direction = Point(vx / distance, vy / distance);
    
    float darkness = (127 * (vy / kMaxDistance));
    
    float i = 0;
    float count = this->getChildren().size();
    for (Node *layer : this->getChildren()) {
        Point addition = Point(vx / getContentSize().width,vy / getContentSize().height) * i / count;
        layer->setPosition(joystickNormalizedCenter + addition);
        if (std::strcmp(layer->getName().c_str(), kStickTag) == 0) {
            layer->setColor(Color3B(0,0,.8 - (( darkness / 200.0) * (i / count))));
        }
        i ++;
    }
    if (joystickDirection) {
        joystickDirection(Point(vx / getContentSize().width,vy / getContentSize().height));
    }
}

void MagicJoystick::onTouchEnded(Touch* touch, Event* event)
{
    stopAllActions();
    float duration = 1.0 - (kStiffness / 100.0);
    
    for (Node *sprite : this->getChildren()) {
        auto resetAction = EaseElasticOut::create(MoveTo::create(duration, joystickNormalizedCenter));
        sprite->runAction(resetAction);
    }
    _direction = Point::ZERO;
    
    if (joystickReleased) {
        joystickReleased();
    }
}
