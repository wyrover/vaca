namespace Vaca {

/**

@page page_tn_011 TN011: Layout Managers

When you use @link Vaca::Widget#setLayout setLayout@endlink or
@link Vaca::Widget#setConstraint setConstraint@endlink, you must to specify a
pointer to a @link Vaca::Layout Layout@endlink or a
@link Vaca::Constraint Constraint@endlink respectively. These pointers are
deleted automatically when the widget is destroyed, but they're not
destroyed when you change the layout manager or the constraint. E.g.:

@code
  {
    Layout* betterLayout = new MyBetterLayout();
    ...
    {
      Frame frame(...);
      frame.setLayout(new MyLayout(...));
      MyLayout* oldLayout = frame.setLayout(betterLayout);

      delete oldLayout; // <-- we must to destroy the layout: it isn't 
                        //     deleted automatically because it isn't
                        //     the 'frame' layout manager anymore
    }
    ...
    // here betterLayout doesn't exist (was automatically deleted 
    // in the Frame destructor)
  }
@endcode

Remember to use the following code if you make instances of
@c Layout (or @c Constraint) in the stack:

@code
  {
    Frame frame(...);
    ClientLayout layout;
    frame.setLayout(&layout);
    ...
    frame.setLayout(NULL); // you have to do this because "layout" would be
                           // deleted in ~Frame() by second time
  }
@endcode

@see @link Vaca::Layout Layout@endlink,
     @link Vaca::Constraint Constraint@endlink,
     @link Vaca::Widget#setLayout Widget::setLayout@endlink,
     @link Vaca::Widget#setConstraint Widget::setConstraint@endlink

*/

}