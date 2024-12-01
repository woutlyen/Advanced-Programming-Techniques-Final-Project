#include "inputcontroller.h"
#include <iostream>

InputController::InputController(QObject* parent) : QObject(parent)
{
    // Initialize rate-limit timers
    rateLimitTimers[Qt::Key_W] = new QTimer(this);
    rateLimitTimers[Qt::Key_S] = new QTimer(this);
    rateLimitTimers[Qt::Key_A] = new QTimer(this);
    rateLimitTimers[Qt::Key_D] = new QTimer(this);

    rateLimitTimers[Qt::Key_Up] = new QTimer(this);
    rateLimitTimers[Qt::Key_Left] = new QTimer(this);
    rateLimitTimers[Qt::Key_Down] = new QTimer(this);
    rateLimitTimers[Qt::Key_Right] = new QTimer(this);

    rateLimitTimers[Qt::Key_Home] = new QTimer(this);
    rateLimitTimers[Qt::Key_End] = new QTimer(this);

    rateLimitTimers[Qt::Key_Tab] = new QTimer(this);
    rateLimitTimers[Qt::Key_Return] = new QTimer(this);
    rateLimitTimers[Qt::Key_Backspace] = new QTimer(this);

    // Set interval for rate-limiting
    for (auto timer : rateLimitTimers) {
        timer->setInterval(460);
        timer->setSingleShot(true); // Ensure the timer runs once per trigger
    }
}

bool InputController::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        // Limmit the maximum command size
        if (this->textCommand.size() < 100 && !keyEvent->text().isEmpty()) this->textCommand.append(keyEvent->text());

        this->text.append(keyEvent->text().toStdString());

        QString test = "up";

        // Ignore repeated key events
        //if (keyEvent->isAutoRepeat())
        //    return true;

        // Check if the timer for the key is active
        if (rateLimitTimers.contains(key) && !rateLimitTimers[key]->isActive()) {
            rateLimitTimers[key]->start(); // Start the timer to enforce the delay

            // Emit the appropriate signal
            switch (key) {
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

                // Works
                case Qt::Key_Tab: 
                    emit tabPressed(); 
                    this->text.clear();
                    break;

                // doesn't work for some fucking reason
                case Qt::Key_Return: 
                    emit enterPressed(test);
                    break;

                // doesn't work for some fucking reason
                case Qt::Key_Backspace:
                    break;

                default: break; // Ignore other keys
            }
        }

        return true; // Consume the event
    }

    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        if (pressedKeys.contains(key)) {
            pressedKeys.remove(key);
        }

        return true; // Consume the event
    }

    return QObject::eventFilter(obj, event); // Pass unhandled events to the base class
}

std::string InputController::processCommand(std::string input) {

    std::cout << "Checking for: " << input << std::endl;

    std::vector<std::string> matches = {
    };

    for (std::string &command: commands) {
        std::cout << "Command: " << command << " Find at: " << command.find(input) << std::endl;
        if (command.find(input) == 0){
            std::cout << "Match found: " << command << std::endl;
            matches.push_back(command);
        }
    }

    if (matches.size() == 1) return matches[0];
    
    return "";
}
