#ifndef XENEMYVIEWTEXT_H
#define XENEMYVIEWTEXT_H

#include "View/enemyviewtext.h"

class XEnemyViewText : public EnemyViewText {
    Q_OBJECT

  public:
    XEnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font);

  protected:
    int getNrOfFramesIdle() const override { return (transformed) ? 64 : 60; }
    int getNrOfFramesWalking() const override { return 0; }
    int getNrOfFramesFighting() const override { return 0; }
    int getNrOfFramesDying() const override { return 0; }
    void setAnimation() override;

  private:
    bool transformed {false};

  private slots:
    void onDefeated() override;
    void onTransform();
};

#endif // XENEMYVIEWTEXT_H
