#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBrush>
#include <QGraphicsLineItem>
#include <QTime>
#include "snake.h"

#include <QDebug>

const int MAP_COUNT_SNAKE = 20;  //地图由各自组成，这个值表示格子的数量，值为20，表示地图由20X20个格子组成
const int MAP_SIZE_SNAKE = 20;  //每个格子的尺寸均为QSize(MAP_SIZE_SNAKE,MAP_SIZE_SNAKE)
const int MOVE_SPEED_SNAKE = 700;  //设默认移动速度，单位为毫秒

Snake::Snake(QWidget *parent)
    : QDialog(parent)
{
    isMoving_bool = false;
    gameIsOver_bool = false;

    getFoodNumber_int = 0;

	currentDirction_enum = GoLeft;

	newGame_PushButton = new QPushButton(tr("新游戏"));
    goOrStop_PushButton = new QPushButton(tr("开始"));
	close_PushButton = new QPushButton(tr("结束"));

	easy_RadioButton = new QRadioButton(tr("简单"));
	normal_RadioButton = new QRadioButton(tr("普通"));
	hard_RadioButton = new QRadioButton(tr("困难"));

	level_GroupBox = new QGroupBox(tr("游戏难度"));

    info_Label = new QLabel;

	gameView_GraphicsView = new QGraphicsView;
	gameMap_GraphicsScene = new QGraphicsScene;
	clock_Timer = new QTimer(this);

	gameView_GraphicsView->setScene(gameMap_GraphicsScene);
	gameMap_GraphicsScene->setSceneRect(-3, -3, 406, 406);
	food_GraphicsRectItem = NULL;
	snake_GraphicsPathItem = new QGraphicsPathItem;
	snake_GraphicsPathItem->setBrush(QBrush(QColor(Qt::green)));
	gameMap_GraphicsScene->addItem(snake_GraphicsPathItem);
    clock_Timer->setInterval(MOVE_SPEED_SNAKE);
    easy_RadioButton->setChecked(true);
    info_Label->setFixedWidth(120);
    info_Label->setText(tr("准备就绪"));
    info_Label->setAlignment(Qt::AlignCenter);

	createGameMap();
	createWall();
	putFood();
	setSnakeShape();

	QVBoxLayout* button_Layout = new QVBoxLayout;
	button_Layout->addWidget(newGame_PushButton);
    button_Layout->addWidget(goOrStop_PushButton);
	button_Layout->addWidget(close_PushButton);
	QHBoxLayout* level_Layout = new QHBoxLayout;
	level_Layout->addWidget(easy_RadioButton);
	level_Layout->addWidget(normal_RadioButton);
	level_Layout->addWidget(hard_RadioButton);
	level_GroupBox->setLayout(level_Layout);
	QHBoxLayout* option_Layout = new QHBoxLayout;
	option_Layout->addWidget(level_GroupBox);
    option_Layout->addWidget(info_Label);
	option_Layout->addLayout(button_Layout);

	QVBoxLayout* main_Layout = new QVBoxLayout;
	main_Layout->addWidget(gameView_GraphicsView);
	main_Layout->addLayout(option_Layout);
	setLayout(main_Layout);
	main_Layout->setSizeConstraint(QLayout::SetFixedSize);

	connect(clock_Timer, SIGNAL(timeout()), this, SLOT(movingSnake()));
	connect(this, SIGNAL(eatFood()), this, SLOT(movingFood()));
	connect(this, SIGNAL(gameLost()), this, SLOT(gameOver()));
    connect(newGame_PushButton,SIGNAL(clicked()),this,SLOT(resetGame()));
    connect(goOrStop_PushButton,SIGNAL(clicked()),this,SLOT(keepMoving()));
    connect(close_PushButton,SIGNAL(clicked()),this,SLOT(close()));
}

Snake::~Snake()
{

}

void Snake::createGameMap()
{
	for (int i = 1; i < MAP_COUNT_SNAKE ; ++i)
	{
		QGraphicsLineItem* hItem = new QGraphicsLineItem(0, i*MAP_SIZE_SNAKE, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE, i*MAP_SIZE_SNAKE);
		QGraphicsLineItem* vItem = new QGraphicsLineItem(i*MAP_SIZE_SNAKE, 0, i*MAP_SIZE_SNAKE, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE);
		gameMap_GraphicsScene->addItem(hItem);
		gameMap_GraphicsScene->addItem(vItem);
	}
	gameMap_GraphicsScene->setBackgroundBrush(QBrush(QColor(Qt::gray)));
}

void Snake::createWall()
{
	QGraphicsRectItem* upWall_GraphicsRectItem = new QGraphicsRectItem(0, -5, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE, 5);
	QGraphicsRectItem* downWall_GraphicsRectItem = new QGraphicsRectItem(0, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE, 5);
	QGraphicsRectItem* leftWall_GraphicsRectItem = new QGraphicsRectItem(-5, -5, 5, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE + 10);
	QGraphicsRectItem* rightWall_GraphicsRectItem = new QGraphicsRectItem(MAP_COUNT_SNAKE*MAP_SIZE_SNAKE, -5, 5, MAP_COUNT_SNAKE*MAP_SIZE_SNAKE + 10);
	gameMap_GraphicsScene->addItem(upWall_GraphicsRectItem);
	gameMap_GraphicsScene->addItem(downWall_GraphicsRectItem);
	gameMap_GraphicsScene->addItem(leftWall_GraphicsRectItem);
	gameMap_GraphicsScene->addItem(rightWall_GraphicsRectItem);

	upWall_GraphicsRectItem->setBrush(QColor(Qt::black));
	downWall_GraphicsRectItem->setBrush(QColor(Qt::black));
	leftWall_GraphicsRectItem->setBrush(QColor(Qt::black));
	rightWall_GraphicsRectItem->setBrush(QColor(Qt::black));
}

void Snake::putFood(int x, int y)
{
	if (x < 0 || x >=MAP_COUNT_SNAKE || y < 0 || y>=MAP_COUNT_SNAKE)
		return;
	if (food_GraphicsRectItem == NULL)
	{
		food_GraphicsRectItem = new QGraphicsRectItem(0, 0, MAP_SIZE_SNAKE , MAP_SIZE_SNAKE);
		food_GraphicsRectItem->setBrush(QBrush(QColor(Qt::yellow)));
		gameMap_GraphicsScene->addItem(food_GraphicsRectItem);
	}
	food_GraphicsRectItem->setPos(x*MAP_SIZE_SNAKE, y*MAP_SIZE_SNAKE);
}

void Snake::setSnakeShape(const QList<GridPoint>& newSnakePath)
{
	if (newSnakePath.isEmpty())
	{
		for (int i = 0; i < 5; ++i)
		{
			GridPoint p;
			p.x = 10+i;
			p.y = 10;
			snakePath_List.append(p);
		}
	}
	else
		snakePath_List = newSnakePath;

	QPainterPath paths;
	for (auto A : snakePath_List)
	{
		paths.addRect(A.x*MAP_SIZE_SNAKE, A.y*MAP_SIZE_SNAKE, MAP_SIZE_SNAKE, MAP_SIZE_SNAKE);
	}

	snake_GraphicsPathItem->setPath(paths);
	snake_GraphicsPathItem->update();
}

void Snake::keyPressEvent(QKeyEvent* event)
{
    if(gameIsOver_bool)
    {
        QDialog::keyPressEvent(event);
        return;
    }
	switch (event->key())
	{
	case Qt::Key_W:
	{
					  if (currentDirction_enum != GoDown)
					      currentDirction_enum = GoUp;
					  break;
	}
	case Qt::Key_S:
	{
					  if (currentDirction_enum != GoUp)
					      currentDirction_enum = GoDown;
					  break;
	}
	case Qt::Key_A:
	{
					  if (currentDirction_enum != GoRight)
					      currentDirction_enum = GoLeft;
					  break;
	}
	case Qt::Key_D:
	{
					  if (currentDirction_enum != GoLeft)
					      currentDirction_enum = GoRight;
					  break;
	}
	default:
		break;
	}
    QDialog::keyPressEvent(event);
}

void Snake::movingSnake()
{
	GridPoint snakeHead = snakePath_List.first();
	int X = snakeHead.x;
	int Y = snakeHead.y;
	if (currentDirction_enum == GoUp)
		--Y;
	else if (currentDirction_enum == GoDown)
		++Y;
	else if (currentDirction_enum == GoLeft)
		--X;
	else if (currentDirction_enum == GoRight)
		++X;
	snakeHead.x = X;
	snakeHead.y = Y;

	if (X < 0 || X >= MAP_COUNT_SNAKE || Y < 0 || Y >= MAP_COUNT_SNAKE)
	{
		emit gameLost();
		return;
	}
	if (snakePath_List.contains(snakeHead))
	{
		emit gameLost();
		return;
	}
	if (snakeHead.x*MAP_SIZE_SNAKE == food_GraphicsRectItem->pos().x() && snakeHead.y*MAP_SIZE_SNAKE == food_GraphicsRectItem->pos().y())
    {
        ++getFoodNumber_int;
		emit eatFood();
    }
	else
	    snakePath_List.pop_back();

	snakePath_List.push_front(snakeHead);
	setSnakeShape(snakePath_List);
}

void Snake::movingFood()
{
    if(getFoodNumber_int == 10)
    {
        info_Label->setText(tr("游戏胜利"));
        clock_Timer->stop();
        gameIsOver_bool = true;
        return;
    }
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	GridPoint p;
	while (true)
	{
		p.x = qrand() % 20;
		p.y = qrand() % 20;
		if (!(snakePath_List.contains(p)))
			break;
	}
	putFood(p.x, p.y);
}

void Snake::gameOver()
{
	clock_Timer->stop();
    gameIsOver_bool = true;
    info_Label->setText(tr("游戏失败"));
}

void Snake::resetGame()
{
    snakePath_List.clear();
    clock_Timer->stop();
    putFood();
    setSnakeShape();
    if(easy_RadioButton->isChecked())
        clock_Timer->setInterval(700);
    else if(normal_RadioButton->isChecked())
        clock_Timer->setInterval(500);
    else if(hard_RadioButton->isChecked())
        clock_Timer->setInterval(300);

    getFoodNumber_int = 0;
    currentDirction_enum = GoLeft;
    gameIsOver_bool = false;
    isMoving_bool = false;
    goOrStop_PushButton->setText(tr("开始"));
    info_Label->setText(tr("准备就绪"));
}

void Snake::keepMoving()
{
    if(gameIsOver_bool)
        return;
    if(isMoving_bool)
    {
        clock_Timer->stop();
        isMoving_bool = false;
        goOrStop_PushButton->setText(tr("开始"));
        info_Label->setText(tr("游戏暂停"));
    }
    else
    {
        clock_Timer->start();
        isMoving_bool = true;
        goOrStop_PushButton->setText(tr("暂停"));
        info_Label->setText(tr("游戏运行中"));
    }
}

























































