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

    case Qt::Key_W: emit upPressed(); break;    // W = Move Up
    case Qt::Key_A: emit leftPressed(); break;  // A = Move Left
    case Qt::Key_S: emit downPressed(); break;  // S = Move Down
    case Qt::Key_D: emit rightPressed(); break; // D = Move Right

    case Qt::Key_Home: emit homePressed(); break;
    case Qt::Key_End: emit endPressed(); break;

    default: break; // Ignore other keys
    }
}
