//
//  ReinInfiniteScroller.cpp
//  cocostool
//
//  Created by Rein.
//
//

#include "ReinInfiniteScroller.h"
bool ReinInfiniteScroller::init()
{
    bool bRet = false;

    do {
        CC_BREAK_IF(!ui::Layout::init());
        
        bRet = true;
    } while (0);
    return bRet;
}

ReinInfiniteScroller* ReinInfiniteScroller::create(Size size)
{
    ReinInfiniteScroller* pRet = new ReinInfiniteScroller();
    if (pRet && pRet->initWithSize(size))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;

}

bool ReinInfiniteScroller::initWithSize(cocos2d::Size size)
{
    bool bRet = false;
    do {
        CC_BREAK_IF(!ui::Layout::init());
        
        bRet = true;
    } while (0);
    return bRet;
}

void ReinInfiniteScroller::initInfiniteScrollView(const Size& chipSize)
{
    isFirstDrag = false;
    
    beforePointX = 0.0f;
    
    infiniteScrollView = extension::ScrollView::create(getLayoutSize());
    infiniteScrollView->retain();
    infiniteScrollView->setPosition(Point(0, 0));
    
    infiniteScrollView->setBounceable(false);
    infiniteScrollView->setDelegate(this);
    addChild(infiniteScrollView);
    
    
    if (imageAry.size() > 0) {
        itemSize  = chipSize;
    }
 
    if (imageAry.size() > 0) {
        for (int i = 0; i < (imageAry.size() * 5); i++) {
            Sprite* sprite = Sprite::create(imageAry.at(i % imageAry.size()));
            sprite->setTag(i % imageAry.size());
            sprite->setPosition(Point(i * itemSize.width + itemSize.width / 2, getLayoutSize().height / 2));
            imageStore.push_back(sprite);
            infiniteScrollView->addChild(sprite);
        }
    }
    
    infiniteScrollView->setContentSize(Size(imageAry.size() * 5 * itemSize.width, getLayoutSize().height));
    float viewMiddle = imageAry.size() * 2 * itemSize.width;
    
    infiniteScrollView->setContentOffset(Point(-viewMiddle , 0));
    
    
}

void ReinInfiniteScroller::scrollViewDidScroll(extension::ScrollView *view)
{
    float sectionSize = imageAry.size() * itemSize.width;
    log("infinite offset , pointx before:%f,%f",infiniteScrollView->getContentOffset().x,beforePointX);

    if (beforePointX != infiniteScrollView->getContentOffset().x)
    {
        if (infiniteScrollView->getContentOffset().x < 0)
        {
            if (infiniteScrollView->getContentOffset().x >= (-sectionSize + sectionSize / 2))
            {
                view->setContentOffset(Point(-sectionSize * 2 +sectionSize / 2, 0));
            }
            else if (view->getContentOffset().x <= (-sectionSize * 3 - sectionSize / 2))
            {
                view->setContentOffset(Point(-sectionSize * 2 - sectionSize / 2, 0));
            }
            reloadView(view->getContentOffset().x - getLayoutSize().width / 2);
            
        }
        else
        {
            view->setContentOffset(Point(-sectionSize * 2 + sectionSize / 2, 0));
        }
        
        
        if (!infiniteScrollView->isDragging()) {
            
            if (isFirstDrag) {
                beforePointX = -currSprite->getPosition().x + getLayoutSize().width / 2;
                view->setContentOffset(Point(beforePointX, 0));
                if (_infiniteEventListener && _infiniteEventSelector) {
                    (_infiniteEventListener->*_infiniteEventSelector)(currSprite);
                    
                }
            }
            
            isFirstDrag = true;
        }


    }
    log("view->getContentOffset().x = %f",view->getContentOffset().x);
    
    beforePointX = view->getContentOffset().x;
}

void ReinInfiniteScroller::reloadView(float offset)
{
    for (int i = 0; i < imageStore.size(); i++)
    {
        Sprite* sprite = imageStore.at(i);
        
        if (-sprite->getPosition().x > (offset - itemSize.width / 2) && -sprite->getPosition().x < (offset + itemSize.width / 2)) {
            
            currSprite = sprite;
            currNum = i;
            
            //the sprite in the middle
            
        }else
        {
            //other sprite will be
        }
    }
}

void ReinInfiniteScroller::scrollViewDidZoom(extension::ScrollView *view)
{
    
}

void ReinInfiniteScroller::addEventInifiteScroller(cocos2d::Ref *sender, SEL_InfiniteScrollViewEvent type)
{
    _infiniteEventListener = sender;
    _infiniteEventSelector = type;
}


