#ifndef LEVELCONTROLLER_H
#define LEVELCONTROLLER_H

#include "Level.h"
#include "Model/worldrevised.h"
#include "View/worldview2d.h"
#include "View/worldviewtext.h"
#include <QPixmap>
#include <QColor>

class LevelController: public QObject
{
    Q_OBJECT
public:
    // Static method to get the singleton instance
    static LevelController& getInstance();

    // Delete copy constructor and assignment operator
    LevelController(const LevelController&) = delete;
    LevelController& operator=(const LevelController&) = delete;

    // Level management functions
    void initializeLevels(const QString& filePath);
    Level& getCurrentLevel();
    size_t getCurrentLevelNr() const;
    void setCurrentLevelNr(const size_t levelNumber);
    std::vector<Level>& getAllLevels();
    void generatePoisonedTiles(int xPos, int yPos, int expansionStage);
    void addPoisonedTile(int x, int y);
    QGraphicsEllipseItem* generatePoisonedCircle(int x, int y, int value);
    void removePoisonedCircle(QGraphicsEllipseItem* poisonCircle);

    void setPEnemyConnection(PEnemyWrapper* penemy);
private:
    // Private constructor
    LevelController() = default;

    // Functions
    void fetchLevels(const QString& filePath);
    void generateLevels();
    void generateLevel(Level& level);

    // Member variables
    std::vector<Level> levels;
    size_t currentLevelIndex = 0;

    WorldRevised world;
    WorldView2D worldView2D;
    WorldViewText worldViewText;

private slots:
    void updatePoisonedTileValue(int poisonLevel);
    void clearPoisonedTiles();
};

#endif // LEVELCONTROLLER_H
