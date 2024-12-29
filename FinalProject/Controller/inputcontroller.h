#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "Commands/command.h"
#include <QObject>
#include <QKeyEvent>
#include <QTimer>

class InputController : public QObject
{
    Q_OBJECT
public:
    InputController(QObject* parent = nullptr);
    void executeCommand(const QString& input) const;

signals:
    void zoomIn();
    void zoomOut();
    void autoplay();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    QHash<int, QTimer*> rateLimitTimers;   // Rate-limiting timers for each key
    QMap<QString, std::shared_ptr<Command>> commands;

    void registerCommands();
    void parseGotoCommand(const QString& input) const;
    void processTextCommand(const int key) const;
};

#endif // INPUTCONTROLLER_H
