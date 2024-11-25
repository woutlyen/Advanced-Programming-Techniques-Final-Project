#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>
#include <QKeyEvent>

class InputController : public QObject
{
    Q_OBJECT
public:
    InputController();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    void handleKeyPress(QKeyEvent* event);
};

#endif // INPUTCONTROLLER_H
