#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>
#include <QKeyEvent>
#include <QTimer>

class InputController : public QObject
{
    Q_OBJECT
public:
    InputController(QObject* parent = nullptr);

signals:
    void upPressed();
    void downPressed();
    void leftPressed();
    void rightPressed();
    void homePressed();
    void endPressed();
    void shiftPressed();
    void enterPressed(QString textCommand);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QSet<int> pressedKeys;                 // Keeps track of currently pressed keys
    QSet<int> pressedLetters;                 // Keeps track of currently pressed letters for a command
    QString textCommand;
    QHash<int, QTimer*> rateLimitTimers;   // Rate-limiting timers for each key

    std::vector<QString> commands = {
        "up",
        "down",
        "left",
        "right"
    };
    QString processCommand(QString input);
};

#endif // INPUTCONTROLLER_H
