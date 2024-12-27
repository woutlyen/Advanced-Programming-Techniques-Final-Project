#include "levelcontroller.h"
#include "qgraphicsitem.h"
#include "qtimer.h"

#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

// Static method to get the singleton instance
LevelController& LevelController::getInstance() {
    static LevelController instance;
    return instance;
}

// Add a level to the controller
void LevelController::initializeLevels(const QString &FilePath) {
    fetchLevels(FilePath);
    generateLevels();
}

// Get the current level
Level& LevelController::getCurrentLevel() {
    return levels[currentLevelIndex];
}

// Get the current level Nr
size_t LevelController::getCurrentLevelNr() const{
    return currentLevelIndex;
}

// Set the current level Nr
void LevelController::setCurrentLevelNr(const size_t levelNumber) {
    if (levelNumber >= 0 && levelNumber < levels.size()){
        currentLevelIndex = levelNumber;
    }
}

// Get all levels
std::vector<Level>& LevelController::getAllLevels() {
    return levels;
}

void LevelController::fetchLevels(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file:" << filePath;
        return;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();

        if (xml.isStartElement() && !xml.name().toString().compare("level")) {
            Level level;
            while (!(xml.isEndElement() && !xml.name().toString().compare("level"))) {
                xml.readNext();
                if (xml.isStartElement()) {
                    QString elementName = xml.name().toString();

                    if (elementName == "number") {
                        level.number = xml.readElementText().toInt();
                    } else if (elementName == "xpos") {
                        level.xpos = xml.readElementText().toInt();
                    } else if (elementName == "ypos") {
                        level.ypos = xml.readElementText().toInt();
                    } else if (elementName == "healthpacks") {
                        level.healthpacks = xml.readElementText().toInt();
                    } else if (elementName == "enemies") {
                        level.enemyNr = xml.readElementText().toInt();
                    } else if (elementName == "pratio") {
                        level.pratio = xml.readElementText().toFloat();
                    } else if (elementName == "xratio") {
                        level.xratio = xml.readElementText().toFloat();
                    } else if (elementName == "visual_map") {
                        level.visual_map = xml.readElementText();
                    } else if (elementName == "data_map") {
                        level.data_map = xml.readElementText();
                    } else if (elementName == "grid_size") {
                        level.grid_size = xml.readElementText().toInt();
                    } else if (elementName == "visual_grid_size") {
                        level.visual_grid_size = xml.readElementText().toInt();
                    } else if (elementName == "prev_level_x_pos") {
                        level.prev_level_x_pos = xml.readElementText().toInt();
                    } else if (elementName == "prev_level_y_pos") {
                        level.prev_level_y_pos = xml.readElementText().toInt();
                    } else if (elementName == "next_level_x_pos") {
                        level.next_level_x_pos = xml.readElementText().toInt();
                    } else if (elementName == "next_level_y_pos") {
                        level.next_level_y_pos = xml.readElementText().toInt();
                    }
                }
            }
            levels.push_back(std::move(level));
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML Error:" << xml.errorString();
    }

    file.close();
}

void LevelController::generateLevels()
{
    // Output the parsed levels
    for (Level& level : levels) {
        qDebug() << "Level:";
        qDebug() << "  Number:" << level.number;
        qDebug() << "  X Position:" << level.xpos;
        qDebug() << "  Y Position:" << level.ypos;
        qDebug() << "  Healthpacks:" << level.healthpacks;
        qDebug() << "  Enemies:" << level.enemyNr;
        qDebug() << "  Pratio:" << level.pratio;
        qDebug() << "  Xratio:" << level.xratio;
        qDebug() << "  Path:" << level.visual_map;
        qDebug() << "  Data:" << level.data_map;
        qDebug() << "  GridSize:" << level.grid_size;
        qDebug() << "  VisualGridSize:" << level.visual_grid_size;
        qDebug() << "  prev_level_x_pos:" << level.prev_level_x_pos;
        qDebug() << "  prev_level_y_pos:" << level.prev_level_y_pos;
        qDebug() << "  next_level_x_pos:" << level.next_level_x_pos;
        qDebug() << "  next_level_y_pos:" << level.next_level_y_pos;

        generateLevel(level);
        currentLevelIndex++;
    }

    currentLevelIndex = 0;
}

void LevelController::generateLevel(Level &level)
{
    world.createWorld(level.data_map, level.enemyNr, level.healthpacks);
    level.tiles = world.getTiles();
    level.enemies = world.getEnemies();

    level.healthPacks = world.getHealthPacks();
    auto player = world.getPlayer();
    player->setPos(level.xpos, level.ypos);
    level.protagonist = std::move(player);
    level.width = world.getCols();
    level.height = world.getRows();

    level.scenes2D = worldView2D.makeScene();
    level.scenesText = worldViewText.makeScene();
}

void LevelController::updatePoisonedTileValue(int poisonLevel)
{
    for (auto& tile : getCurrentLevel().poisonedTiles) {
        tile->setValue(poisonLevel);
    }
}

void LevelController::generatePoisonedTiles(int xPos, int yPos, int expansionStage)
{
    switch(expansionStage){
    case 1:
        addPoisonedTile(xPos + 1, yPos);
        addPoisonedTile(xPos - 1, yPos);
        addPoisonedTile(xPos, yPos + 1);
        addPoisonedTile(xPos, yPos - 1);
        QTimer::singleShot(2000, this, [this, xPos, yPos]() {generatePoisonedTiles(xPos, yPos, 2);});
        break;
    case 2:
        addPoisonedTile(xPos + 2, yPos);
        addPoisonedTile(xPos - 2, yPos);
        addPoisonedTile(xPos, yPos + 2);
        addPoisonedTile(xPos, yPos - 2);
        addPoisonedTile(xPos - 1, yPos - 1);
        addPoisonedTile(xPos + 1, yPos - 1);
        addPoisonedTile(xPos + 1, yPos + 1);
        addPoisonedTile(xPos - 1, yPos + 1);
        break;
    }
}

void LevelController::addPoisonedTile(int x, int y)
{
    for (auto& tile : getCurrentLevel().tiles) {
        if (tile->getXPos() == x && tile->getYPos() == y) {
            auto poisonedTile = std::make_unique<Tile>(x,y, tile->getValue());
            getCurrentLevel().poisonedTiles.push_back(std::move(poisonedTile));
        }
    }
}

QGraphicsEllipseItem *LevelController::generatePoisonedCircle(int x, int y, int value)
{
    return worldView2D.addPoisonCircle(x ,y, 3*getCurrentLevel().grid_size, getCurrentLevel().scenes2D, value);
}

void LevelController::removePoisonedCircle(QGraphicsEllipseItem *poisonCircle)
{
    if(poisonCircle){
        worldView2D.removePoisonCircle(poisonCircle, getCurrentLevel().scenes2D);
    }
}

void LevelController::clearPoisonedTiles()
{
    getCurrentLevel().poisonedTiles.clear();
}

void LevelController::setPEnemyConnection(PEnemyWrapper* penemy)
{
    connect(penemy, &PEnemyWrapper::poisonLevelUpdated, this, &LevelController::updatePoisonedTileValue);
    connect(penemy, &PEnemyWrapper::dead, this, &LevelController::clearPoisonedTiles);
}
