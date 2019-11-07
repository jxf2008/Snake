#ifndef SNAKE_H
#define SNAKE_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include "FoodItem.h"
#include "SnakeItem.h"


class Snake : public QDialog
{
    Q_OBJECT
private:
    bool isMoving_bool;
    bool gameIsOver_bool;

    int getFoodNumber_int;

	MoveDirction currentDirction_enum;

	QGraphicsView* gameView_GraphicsView;
	QGraphicsScene* gameMap_GraphicsScene;

    //QGraphicsRectItem* food_GraphicsRectItem;
    FoodItem* food_GraphicsRectItem;

    //QGraphicsPathItem* snake_GraphicsPathItem;
    SnakeItem* snake_GraphicsPathItem;

	QTimer* clock_Timer;

	QList<GridPoint> snakePath_List;

	QPushButton* newGame_PushButton;
    QPushButton* goOrStop_PushButton;
	QPushButton* close_PushButton;

	QRadioButton* easy_RadioButton;
	QRadioButton* normal_RadioButton;
	QRadioButton* hard_RadioButton;

    QLabel* info_Label;

	QGroupBox* level_GroupBox;

	void createGameMap();
	void createWall();
	void putFood(int x = 5, int y = 15);
	void setSnakeShape(const QList<GridPoint>& newSnakePath = QList<GridPoint>());
public:
    Snake(QWidget *parent = 0);
    ~Snake();
protected:
	void keyPressEvent(QKeyEvent* event);
signals:
	void gameLost();
	void eatFood();
private slots:
	void movingSnake();
	void movingFood();
	void gameOver();
    void resetGame();
    void keepMoving();
};

#endif // SNAKE_H












































