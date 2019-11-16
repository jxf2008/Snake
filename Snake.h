#ifndef SNAKE_H
#define SNAKE_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPathItem>
#include <QTimer>
#include <QKeyEvent>

struct GridPoint
{
	int x;
	int y;
	bool operator==(const GridPoint& p){ return (p.x == x && p.y == y); }
};

enum MoveDirction{GoUp,GoDown,GoLeft,GoRight};

class Snake : public QDialog
{
    Q_OBJECT
private:
	MoveDirction currentDirction_enum;

	QGraphicsView* gameView_GraphicsView;
	QGraphicsScene* gameMap_GraphicsScene;

	QGraphicsRectItem* food_GraphicsRectItem;

	QGraphicsPathItem* snake_GraphicsPathItem;

	QTimer* clock_Timer;

	QList<GridPoint> snakePath_List;

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
};

#endif // SNAKE_H
