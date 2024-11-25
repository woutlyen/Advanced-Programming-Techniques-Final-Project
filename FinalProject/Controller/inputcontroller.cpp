#include "inputcontroller.h"
#include <iostream>

InputController::InputController() {}

bool InputController::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        handleKeyPress(keyEvent);
        return true; // Event handled
    }
    return QObject::eventFilter(obj, event); // Pass unhandled events to the base class
}

void InputController::handleKeyPress(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up: std::cout << "Up" << std::endl; break;
    case Qt::Key_Left: std::cout << "Left" << std::endl; break;
    case Qt::Key_Down: std::cout << "Down" << std::endl; break;
    case Qt::Key_Right: std::cout << "Right" << std::endl; break;
    default: break; // Ignore other keys
    }
}
