//
//  ReinInfiniteScroller.h
//  cocostool
//
//  Created by Rein.
//
//

#ifndef __ReinInfiniteScroller__
#define __ReinInfiniteScroller__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
typedef enum
{
    sc = 0,
    sc1
}ScType;

typedef void (Ref::*SEL_InfiniteScrollViewEvent)(Ref*);

#define reinInfinitescrollvieweventselector(_SELECTOR) (SEL_InfiniteScrollViewEvent)(&_SELECTOR)


class ReinInfiniteScroller : public ui::Layout,public extension::ScrollViewDelegate
{
    //value
public:
    extension::ScrollView* infiniteScrollView;
    
    std::vector<std::string> imageAry;
    Size itemSize;
    
private:
    std::vector<Sprite*> imageStore;
    float beforePointX;
    
    Sprite* currSprite;
    bool isFirstDrag;
    int currNum;
    
    Ref* _infiniteEventListener;
    SEL_InfiniteScrollViewEvent _infiniteEventSelector;
    
    //method
public:
    CREATE_FUNC(ReinInfiniteScroller);
    virtual bool init();
    
    static ReinInfiniteScroller* create(Size wsize);
    virtual bool initWithSize(Size wsize);
    
    virtual void scrollViewDidScroll(extension::ScrollView* view);
    virtual void scrollViewDidZoom(extension::ScrollView* view);
    
    void initInfiniteScrollView(const Size& chipSize);
    
    void initInfiniteScrollView(const Vector<Sprite *> chips);
    
    void addEventInifiteScroller(Ref* sender,SEL_InfiniteScrollViewEvent type);
   
private:
    void reloadView(float offset);

};

#endif /* defined(__ReinInfiniteScroller__) */
