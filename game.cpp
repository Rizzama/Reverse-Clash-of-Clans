#include "Player.h"
#include <QTimer>
#include <QBrush>
#include <QImage>
#include <QGraphicsItem>
#include "game.h"
#include <qDebug>
#include "score.h"


Game::Game(QWidget *parent, const QString& playerName)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)), playerName(playerName) { // Modified constructor

    maxPoint.setX(800);
    maxPoint.setY(600);

    if (parent){
        setFixedSize(parent->size()); // Set the size to match the parent widget's size
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        scene->setSceneRect(0, 0, parent->size().width(), parent->size().height()); // Set the scene size to match the view's size
        // Directly specify the dimensions of the background image as 1334 x 750
        QImage backgroundImage(":/Sprites/GameBackground.jpg");
        int backgroundImageWidth = 1334;
        int backgroundImageHeight = 750;

        scene->setBackgroundBrush(QBrush(backgroundImage.scaled(backgroundImageWidth, backgroundImageHeight))); // Scale the background image to fit the scene
        setScene(scene);
    }else{

        setFixedSize(800,600); // Set the size to match the parent widget's size
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        scene->setSceneRect(0, 0, 800, 600); // Set the scene size to match the view's size
        // Directly specify the dimensions of the background image as 1334 x 750
        QImage backgroundImage(":/Sprites/GameBackground.jpg");
        int backgroundImageWidth = 1334;
        int backgroundImageHeight = 750;

        scene->setBackgroundBrush(QBrush(backgroundImage.scaled(backgroundImageWidth, backgroundImageHeight))); // Scale the background image to fit the scene
        setScene(scene);
    }



    player = new Player(playerName); // Pass the playerName argument
    player->setPixmap(QPixmap(":/Sprites/Cannon21B.png"));
    scene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    //    QPixmap playerPixmap = player->pixmap();
    //    qDebug() << playerPixmap.size();
    if (parent){
        player->setPos(parent->size().width() / 2, parent->size().height() / 2); // Center the player on the screen
    }else{
        player->setPos(400-100, 300-82); // Center the player on the screen
    }

    health = new Health();
    health->setPos(health->x(), health->y());
    scene->addItem(health);

    score  = new Score();
    score->setPos(health->x(), health->y() + 25);
    scene->addItem(score);

    wave = new Wave(player);
    wave->setPos(health->x(), score->y() + 25);
    scene->addItem(wave);

    addVillageHouse();

    player->createWall();

    //call enemies
    player->createEnemy();

}

void Game::decreaseHealth(){
    health->decrease();
}
void Game::increaseScore(){
    score->increase();
    increaseHealth();
    setWaves();
}
void Game::addVillageHouse() {
    // Define dimensions for the village house
    int villageWidth = 100; // Adjust as needed
    int villageHeight = 100; // Adjust as needed

    // Calculate the coordinates for the village house
    int centerX = player->x(); // Get the center x-coordinate of the player
    int centerY = player->y(); // Get the center y-coordinate of the player
    int villageX = centerX - villageWidth / 2; // Calculate the x-coordinate for the village house
    int villageY = centerY - villageHeight / 2; // Calculate the y-coordinate for the village house

    // Create and add the village house item to the scene
    QGraphicsPixmapItem *village1 = new QGraphicsPixmapItem(QPixmap(":/Sprites/VillageHouseA.png"));
    village1->setPos(villageX+140, villageY+80);
    village1->setScale(0.1); // Adjust the scale of the village item
    scene->addItem(village1);

    // Create and add the village house item to the scene
    QGraphicsPixmapItem *village2 = new QGraphicsPixmapItem(QPixmap(":/Sprites/Goblin_Hut_House.png"));
    village2->setPos(villageX+80, villageY+120);
    village2->setScale(0.8);
    scene->addItem(village2);
}

QPointF Game::getmaxPoint(){
    return maxPoint;
}

void Game::increaseHealth(){
    if (score->getScore() % 100 == 0){
        health->maxHealthIncrease();
    }
}

void Game::setWaves(){
    if (score->getScore() % 100 == 0){
        player->setTimes();
        wave->displayWave();
    }
}
