#ifndef PLAYER_H
#define PLAYER_H

#include "clan.h"
#include "QString"
#include "qmediaplayer.h"
#include <QGraphicsPixmapItem>

class Player: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT;
private:
    static int id;
    QString name;
    int level;
    Clan* clan;
    QMediaPlayer * cannonball_sound;
    QAudioOutput * cannonball_output;
    QString current_state;

public:
    Player(QString name);
    int getId() const;
    void setName(const QString& name);
    QString getName() const;
    void setLevel(int level);
    int getLevel() const;
    void setClan(Clan* clan);
    Clan* getClan() const;


public slots:
    void keyPressEvent(QKeyEvent *Event);
    void createEnemy();
};

#endif // PLAYER_H
