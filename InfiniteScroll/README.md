# InfiniteScroller

how to use

IN 3.x

tips:

ReinInfiniteScroller* picker = ReinInfiniteScroller::create();

picker->setSize(Size(xx, xx)); //size about layout

picker->imageAry = data; //some vector about image path

picker->setPosition(Point(xx,xx));// the pos about this layout

picker->initInfiniteScrollView(Size(xx, xx));//size about unit of scroll

addchild(picker)


also
you can set delegate
like this:

picker->addEventInifiteScroller(this, reinInfinitescrollvieweventselector([some mathod]));

--------------------------------------------------------------------------

IN 2.x

will soon
