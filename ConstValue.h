#ifndef CONSTVALUE_H
#define CONSTVALUE_H
struct GridPoint
{
    int x;
    int y;
    bool operator==(const GridPoint& p){ return (p.x == x && p.y == y); }
};

enum MoveDirction{GoUp,GoDown,GoLeft,GoRight};
const int MAP_COUNT_SNAKE = 20;  //地图由各自组成，这个值表示格子的数量，值为20，表示地图由20X20个格子组成
const int MAP_SIZE_SNAKE = 20;  //每个格子的尺寸均为QSize(MAP_SIZE_SNAKE,MAP_SIZE_SNAKE)
const int MOVE_SPEED_SNAKE = 700;  //设默认移动速度，单位为毫秒
#endif // CONSTVALUE_H
