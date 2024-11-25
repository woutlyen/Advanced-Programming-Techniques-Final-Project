#include "inputcontroller.h"

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
    case Qt::Key_Up: emit upPressed(); break;
    case Qt::Key_Left: emit leftPressed(); break;
    case Qt::Key_Down: emit downPressed(); break;
    case Qt::Key_Right: emit rightPressed(); break;
    default: break; // Ignore other keys
    }
}
