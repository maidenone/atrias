# Introduction #

Not much to see yet, as we are just now diving into Qt.


# First Impressions #

Qt loves using signals and slots.

Set up slots in a Qt Object class with something like the following:

```
class MyQtClass
{
    ...

protected slots:
    virtual void onEditingFinishd(void);

    ...
};
```

To which you can connect a signal like this:

```
// Create QWidget
widget_ = new QWidget();

// Extend the widget with all attributes and children from UI file
ui_.setupUi(widget_);

connect(ui_.someElement, SIGNAL(editingFinished(void)), this, SLOT(onEditingFinished(void)));
```