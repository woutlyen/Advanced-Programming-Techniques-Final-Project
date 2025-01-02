#include "inputcontroller.h"
#include "Commands/attacknearestenemycommand.h"
#include "Commands/gotocommand.h"
#include "Commands/helpcommand.h"
#include "Commands/movedowncommand.h"
#include "Commands/moveleftcommand.h"
#include "Commands/moverightcommand.h"
#include "Commands/moveupcommand.h"
#include "Commands/takenearesthealthpackcommand.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <iostream>

InputController::InputController(QObject* parent) : QObject(parent)
{
    // Initialize rate-limit timers
    rateLimitTimers[Qt::Key_W] = new QTimer(this);
    rateLimitTimers[Qt::Key_S] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_A] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_D] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_Z] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_Q] = rateLimitTimers[Qt::Key_W];

    rateLimitTimers[Qt::Key_Up] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_Left] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_Down] = rateLimitTimers[Qt::Key_W];
    rateLimitTimers[Qt::Key_Right] = rateLimitTimers[Qt::Key_W];

    rateLimitTimers[Qt::Key_P] = rateLimitTimers[Qt::Key_W];

    // Set interval for rate-limiting
    for (auto& timer : rateLimitTimers) {
        timer->setInterval(460);
        timer->setSingleShot(true); // Ensure the timer runs once per trigger
    }

    registerCommands();
}

bool InputController::eventFilter(QObject *obj, QEvent *event)
{
    /*if(!obj->objectName().compare("lineEdit")){
        qDebug() << obj->objectName() << " - " << event->type();
    }*/

    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        int key = keyEvent->key();

        // Process Text Command when lineEdit has focus
        if(mainWindow->ui->lineEdit->hasFocus()){
            processTextCommand(key);

            if(key == Qt::Key_Tab){
                return true;
            } else {
                return false;
            }
        }

        // Check if the timer for the key is active
        else if (rateLimitTimers.contains(key) && !rateLimitTimers[key]->isActive()) {
            rateLimitTimers[key]->start(); // Start the timer to enforce the delay

            // Emit the appropriate signal
            switch (key) {
            case Qt::Key_Up:   executeCommand("up"); break;
            case Qt::Key_Left: executeCommand("left"); break;
            case Qt::Key_Down: executeCommand("down"); break;
            case Qt::Key_Right:executeCommand("right"); break;

            case Qt::Key_W: executeCommand("up"); break;    // W = Move Up
            case Qt::Key_A: executeCommand("left"); break;  // A = Move Left
            case Qt::Key_S: executeCommand("down"); break;  // S = Move Down
            case Qt::Key_D: executeCommand("right"); break; // D = Move Right

            case Qt::Key_Z: executeCommand("up"); break;    // Z = W = Move Up
            case Qt::Key_Q: executeCommand("left"); break;  // Q = A = Move Left

            case Qt::Key_P: emit autoplay(); break;

            default: break; // Ignore other keys
            }
        }

        return true; // Consume the event
    }

    // Handle zoom functionality with QEvent::Wheel
    if (event->type() == QEvent::Wheel) {
        QWheelEvent* wheelEvent = static_cast<QWheelEvent*>(event);

        // Determine the zoom direction (positive: zoom in, negative: zoom out)
        if (wheelEvent->angleDelta().y() > 0) {
            emit zoomIn();
        } else {
            emit zoomOut();
        }

        return true; // Consume the event
    }

    return false;
    //return QObject::eventFilter(obj, event); // Pass unhandled events to the base class
}

void InputController::registerCommands()
{
    // Register all commands with unique keys
    commands["up"] = std::make_shared<MoveUpCommand>();
    commands["right"] = std::make_shared<MoveRightCommand>();
    commands["down"] = std::make_shared<MoveDownCommand>();
    commands["left"] = std::make_shared<MoveLeftCommand>();
    commands["take"] = std::make_shared<TakeNearestHealthPackCommand>();
    commands["help"] = std::make_shared<HelpCommand>();
    commands["attack"] = std::make_shared<AttackNearestEnemyCommand>();

}

void InputController::executeCommand(const QString &input) const
{
    if (input.isEmpty()){
        return;
    }
    else if (input.startsWith("goto ")) {
        parseGotoCommand(input);
        return;
    }
    else if(commands.contains(input)){
        commands[input]->execute();
    }
    else {
        std::cout << "Unknown command: " << input.toStdString() << std::endl;
    }
}

void InputController::parseGotoCommand(const QString &input) const
{
    QStringList parts = input.split(" ", Qt::SkipEmptyParts);
    if (parts.size() == 3) {
        bool okX, okY;
        int x = parts[1].toInt(&okX);
        int y = parts[2].toInt(&okY);

        if (okX && okY) {
            // Create and execute the GotoCommand
            auto command = std::make_shared<GotoCommand>(x, y);
            command->execute();
        } else {
            std::cout << "Invalid coordinates for goto command." << std::endl;
        }
    } else {
        std::cout << "Usage: goto x y" << std::endl;
    }
}

void InputController::processTextCommand(const int key) const
{
    MainWindow * mainWindow = static_cast<MainWindow*>(QApplication::activeWindow());

    switch (key) {

    // Check for matches, and clear input if a match is found
    case Qt::Key_Return:
        executeCommand(mainWindow->ui->lineEdit->text());
        mainWindow->ui->lineEdit->clear();
        break;

        // Check for matches and autocomplete if a match is found
    case Qt::Key_Tab:

        if(mainWindow->ui->lineEdit->text().isEmpty()){
            break;
        }

        QString matchedCommand;

        //Loop over commands and check for unique match
        for (auto it = commands.begin(); it != commands.end(); ++it) {
            if (it.key().startsWith(mainWindow->ui->lineEdit->text())) {
                if (!matchedCommand.isEmpty()) {
                    std::cout << "Ambiguous command: " << mainWindow->ui->lineEdit->text().toStdString() << std::endl;
                    break;
                }
                matchedCommand = it.key();
            }
        }

        mainWindow->ui->lineEdit->setText(matchedCommand);
        break;
    }
}

