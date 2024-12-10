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
    void zoomIn();
    void zoomOut();
    //void zoomChanged(double zoomFactor);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QHash<int, QTimer*> rateLimitTimers;   // Rate-limiting timers for each key


};

#endif // INPUTCONTROLLER_H
