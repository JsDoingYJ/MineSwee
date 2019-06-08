#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "item.h"
#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

#define RECT_WIDTH      40
#define RECT_HEIGHT     40

#define START_X         40
#define START_Y         40


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void InitItems();                   //随机初始化雷点位置
    void ReleaseItems();

    void NewGame();                     //新开一局游戏
    void GameFail();                    //点到雷,游戏失败
    bool FindAll();                     //是否找到所有雷

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private slots:
    void OnMenuNewGame();
    void OnMenuLevel1();
    void OnMenuLevel2();
    void OnMenuLevel3();
    void slotTimerTimeOut();
    void mouseClicked();
    void ExitGame();
    void GameEnd();
    void AboutGame();

private:
    void DrawChessboard();
    void DrawItems();
    void DrawItem(QPainter& painter,Item* pItem);

    void OpenEmptyItem(QPoint pt);			//点击空白元素(相邻雷数为0)时，递归查找相邻的空白元素，以及空白元素附近的数字元素(数字是雷数)
    bool PointInGameArea(QPoint pt);		//判断坐标是否超过游戏区域

private:
    Ui::MainWindow *ui;
    QPixmap m_FlagImage;				//小红旗图片
    QPixmap m_BombImage;                //雷图片

    int m_nRows;						//行数
    int m_nColumes;                     //列数
    int m_nMineCount;					//雷数
    QVector<QPoint> m_Mines;			//雷点
    QVector<QVector<Item*>> m_items;	//所有元素
    bool m_bGameFail;					//是否是游戏失败，失败了需要显示雷
    char *gameInfo;
private:
    QTimer m_cTimer;
    //QMouseEvent *e;
    double pos_x;
    double pos_y;
};

#endif // MAINWINDOW_H
