#include "gamecontroller.h"

#include <QTimer>
#include <unordered_map>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>

GameController::GameController(QObject *parent) : QObject(parent) {
    // Install the InputController as an event filter
    qApp->installEventFilter(&inputController);

    // Populate methodMap
    gamecontrollerMethodMap["up"] = [this]() {moveProtagonistUp();};
    gamecontrollerMethodMap["down"] = [this]() {moveProtagonistDown();};
    gamecontrollerMethodMap["left"] = [this]() {moveProtagonistLeft();};
    gamecontrollerMethodMap["right"] = [this]() {moveProtagonistRight();};



    // Connect InputController signals to GameController slots
    connect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
    connect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
    connect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
    connect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);

    connect(&inputController, &InputController::homePressed, this, &GameController::onHomePressed);
    connect(&inputController, &InputController::endPressed, this, &GameController::onEndPressed);

    connect(&inputController, &InputController::shiftPressed, this, &GameController::changeViewMode);
    connect(&inputController, &InputController::enterPressed, this, &GameController::processCommand);

    connect(&inputController, &InputController::zoomIn, this, &GameController::onZoomInEvent);
    connect(&inputController, &InputController::zoomOut, this, &GameController::onZoomOutEvent);

}

void GameController::start(QString& filePath)
{
    parseLevels(filePath);

    // Output the parsed levels
    for (const Level& level : levels) {
        qDebug() << "Level:";
        qDebug() << "  Number:" << level.number;
        qDebug() << "  X Position:" << level.xpos;
        qDebug() << "  Y Position:" << level.ypos;
        qDebug() << "  Healthpacks:" << level.healthpacks;
        qDebug() << "  Enemies:" << level.enemies;
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

        generateLevel(currentLevel);
        currentLevel++;
    }

    currentLevel = 0;
    mainWindow.setScene(scenes2D.at(currentLevel), scenesText.at(currentLevel));
    mainWindow.updateConnections(protagonist.at(currentLevel));
    mainWindow.show();
    playerController.moveRight(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
}

bool GameController::checkForPrevLevel()
{
    if(protagonist.at(currentLevel)->getXPos() == levels.at(currentLevel).prev_level_x_pos && protagonist.at(currentLevel)->getYPos() == levels.at(currentLevel).prev_level_y_pos){
        currentLevel--;
        mainWindow.setScene(scenes2D.at(currentLevel), scenesText.at(currentLevel));
        mainWindow.updateConnections(protagonist.at(currentLevel));
        return true;
    }
    return false;
}

bool GameController::checkForNextLevel()
{

    if(protagonist.at(currentLevel)->getXPos() == levels.at(currentLevel).next_level_x_pos && protagonist.at(currentLevel)->getYPos() == levels.at(currentLevel).next_level_y_pos){
        currentLevel++;
        mainWindow.setScene(scenes2D.at(currentLevel), scenesText.at(currentLevel));
        mainWindow.updateConnections(protagonist.at(currentLevel));
        return true;
    }
    return false;
}

void GameController::parseLevels(QString &filePath)
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
                        level.enemies = xml.readElementText().toInt();
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
            levels.append(level);
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML Error:" << xml.errorString();
    }

    file.close();
}

void GameController::generateLevel(int levelNumber)
{
    world.createWorld(levels.at(levelNumber).data_map, levels.at(levelNumber).enemies, levels.at(levelNumber).healthpacks);
    tiles.push_back(world.getTiles());
    enemies.push_back(world.getEnemies());
    healthPacks.push_back(world.getHealthPacks());
    auto pro = world.getProtagonist();
    auto player = std::move(*reinterpret_cast<std::unique_ptr<Player>*>(&pro));
    player->setPos(levels.at(levelNumber).xpos, levels.at(levelNumber).ypos);
    protagonist.push_back(std::move(player));
    width.push_back(world.getCols());
    height.push_back(world.getRows());

    scenesText.push_back(worldViewText.makeScene(enemies.at(levelNumber), healthPacks.at(levelNumber), protagonist.at(levelNumber), height.at(levelNumber), width.at(levelNumber), levels.at(levelNumber).data_map, levels.at(levelNumber).grid_size));
    scenes2D.push_back(worldView2D.makeScene(enemies.at(levelNumber), healthPacks.at(levelNumber), protagonist.at(levelNumber), height.at(levelNumber), width.at(levelNumber), levels.at(levelNumber).visual_map, levels.at(levelNumber).grid_size, levels.at(levelNumber).visual_grid_size));

}


void GameController::moveProtagonistUp() {
    playerController.updatePlayerDirection(protagonist.at(currentLevel), Player::Back);
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), heigth.at(currentLevel), EnemyController::Position::Up)){
        playerController.moveUp(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        playerController.checkForHealthPack(protagonist.at(currentLevel), healthPacks.at(currentLevel));
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveUp(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        }
    }
}


void GameController::moveProtagonistDown() {
    playerController.updatePlayerDirection(protagonist.at(currentLevel), Player::Front);
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), height.at(currentLevel), EnemyController::Position::Down)) {
        playerController.moveDown(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel), height.at(currentLevel));
        playerController.checkForHealthPack(protagonist.at(currentLevel), healthPacks.at(currentLevel));
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveDown(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel), height.at(currentLevel));
        }
    }
}

void GameController::moveProtagonistLeft() {
    playerController.updatePlayerDirection(protagonist.at(currentLevel), Player::Left);
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), height.at(currentLevel), EnemyController::Position::Left)) {
        playerController.moveLeft(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        playerController.checkForHealthPack(protagonist.at(currentLevel), healthPacks.at(currentLevel));
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveLeft(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        }
    }
}

void GameController::moveProtagonistRight() {
    playerController.updatePlayerDirection(protagonist.at(currentLevel), Player::Right);
    if (!enemyController.checkForEnemy(enemies.at(currentLevel), protagonist.at(currentLevel), width.at(currentLevel), height.at(currentLevel), EnemyController::Position::Right)) {
        playerController.moveRight(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        playerController.checkForHealthPack(protagonist.at(currentLevel), healthPacks.at(currentLevel));
        if (checkForPrevLevel() || checkForNextLevel()){
            playerController.moveRight(protagonist.at(currentLevel), tiles.at(currentLevel), width.at(currentLevel));
        }
    }
}

void GameController::onHomePressed() {
}

void GameController::onEndPressed() {
}

void GameController::onZoomInEvent(){
    mainWindow.zoomIn();
}

void GameController::onZoomOutEvent(){
    mainWindow.zoomOut();
}

void GameController::changeViewMode() {
    switch (currentMode) {
        case TextView:
            currentMode = Graphics2DView;
            //mainWindow.setScene(scenes2D.at(currentLevel));
            connect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
            connect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
            connect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
            connect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);
            break;

        case Graphics2DView:
            currentMode = TextView;
            //mainWindow.setScene(scenesText.at(currentLevel));
            disconnect(&inputController, &InputController::upPressed, this, &GameController::moveProtagonistUp);
            disconnect(&inputController, &InputController::downPressed, this, &GameController::moveProtagonistDown);
            disconnect(&inputController, &InputController::leftPressed, this, &GameController::moveProtagonistLeft);
            disconnect(&inputController, &InputController::rightPressed, this, &GameController::moveProtagonistRight);
            break;
    }
}

void GameController::processCommand(QString textCommand) {

    // Ignore commands in 2D mode
    if (currentMode == Graphics2DView) return;

    // Check if the methodMap contains the command
    if (gamecontrollerMethodMap.find(textCommand.toStdString()) == gamecontrollerMethodMap.end()) return;

    // Exectute method mapped to textCommand
    gamecontrollerMethodMap[textCommand.toStdString()]();
}
