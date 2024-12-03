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
    void zoomChanged(double zoomFactor);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QHash<int, QTimer*> rateLimitTimers;   // Rate-limiting timers for each key
    const double zoomFactor {1.15};  // Factor to zoom in/out by
    int currentZoomLevel {0};     // Track zoom level (to prevent over-zooming)

    void zoomIn();
    void zoomOut();
};

#endif // INPUTCONTROLLER_H
