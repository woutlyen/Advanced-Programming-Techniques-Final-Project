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

    rateLimitTimers[Qt::Key_Shift] = new QTimer(this);
    rateLimitTimers[Qt::Key_Return] = new QTimer(this);

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

        QString processedCommand;

        // Proccess the textCommand
        switch (key) {
            // Remove the last char on backspace
            case Qt::Key_Backspace:
                this->textCommand.removeLast();
                break;
            // Check for matches, and clear input if a match is found
            case Qt::Key_Return:
                processedCommand = this->processCommand(textCommand);
                if (processedCommand != nullptr) textCommand.clear();
                break;
            // Check for matches and autocomplete if a match is found
            case Qt::Key_Tab:
                processedCommand = this->processCommand(textCommand);
                if (processedCommand != nullptr) textCommand = processedCommand;
                break;
            // Append character to the textCommand
            default:
                if (this->textCommand.size() < 100 && !keyEvent->text().isEmpty()) this->textCommand.append(keyEvent->text());
                break;
        }

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

                case Qt::Key_Shift: emit shiftPressed(); break;

                case Qt::Key_Return: 
                    // Do nothing if no match is found
                    if (processedCommand == "") break;
                    emit enterPressed(processedCommand);
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

// Check if input uniqly matches with one of the commands
// Returns input if no unique match found, else the match
QString InputController::processCommand(QString input) {

    std::cout << "Checking for: " << input.toStdString() << std::endl;

    std::vector<QString> matches = {
    };

    for (QString &command: commands) {
        if (command.startsWith(input) == true){
            std::cout << "Match found: " << command.toStdString() << std::endl;
            matches.push_back(command);
        }
    }

    // Only return if there is an unique match
    if (matches.size() == 1) return matches[0];
    
    return QString("");
}
