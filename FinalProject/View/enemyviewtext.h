#ifndef ENEMYVIEWTEXT_H
#define ENEMYVIEWTEXT_H

#include "Model/enemywrapper.h"
#include "View/gameobjecttextview.h"

class EnemyViewText : public GameObjectTextView {
    Q_OBJECT

  public:
    EnemyViewText(const std::unique_ptr<EnemyWrapper> &enemy, double tileWidth, double tileHeight, QFont font);
    virtual ~EnemyViewText() = default;

  protected:
    const std::unique_ptr<EnemyWrapper> &enemy;
    int getNrOfFramesIdle() const override{return 60;}
    int getNrOfFramesWalking() const override{ return 0;}
    int getNrOfFramesFighting() const override{ return 0;}
    int getNrOfFramesDying() const override{ return 0;}
    void setAnimation() override;

  private:

  private slots:
    virtual void onDefeated();
};

#endif // ENEMYVIEWTEXT_H
