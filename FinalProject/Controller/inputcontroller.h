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

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QSet<int> pressedKeys;                 // Keeps track of currently pressed keys
    QHash<int, QTimer*> rateLimitTimers;   // Rate-limiting timers for each key
};

#endif // INPUTCONTROLLER_H
