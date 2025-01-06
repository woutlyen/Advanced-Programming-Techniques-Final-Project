#ifndef PENEMYVIEWTEXT_H
#define PENEMYVIEWTEXT_H

#include "View/enemyviewtext.h"

class PEnemyViewText : public EnemyViewText {
    Q_OBJECT

  public:
    PEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font);
    void setPoisonCircle(int value);

  protected:
    int getNrOfFramesIdle() const override { return 50; }
    int getNrOfFramesWalking() const override { return 0; }
    int getNrOfFramesFighting() const override { return 0; }
    int getNrOfFramesDying() const override { return 0; }
    void setAnimation() override;

  private:
    QGraphicsTextItem *poisonCircle;
    void expandPoisonCircle(int value);
    bool died;

  private slots:
    void onDefeated() override;
    void onPoisonLevelValueUpdated(int value);
};

#endif // PENEMYVIEWTEXT_H
