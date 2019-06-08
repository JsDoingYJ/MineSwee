#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPaintEvent>
#include <QPainter>
#include <QTime>
#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();


    setFixedSize(800,480);
    connect(ui->gameStart,SIGNAL(triggered()),this,SLOT(OnMenuNewGame()));
    connect(ui->gameEnd,SIGNAL(triggered()),this,SLOT(GameEnd()));
    connect(ui->menuClose,SIGNAL(aboutToShow()),this,SLOT(ExitGame()));
    connect(ui->action_9_9, SIGNAL(triggered()), this, SLOT(OnMenuLevel1()));
    connect(ui->action_10_15, SIGNAL(triggered()), this, SLOT(OnMenuLevel2()));
    connect(ui->action_10_17, SIGNAL(triggered()), this, SLOT(OnMenuLevel3()));

    connect(ui->author,SIGNAL(triggered()),this,SLOT(AboutGame()));

    connect(&m_cTimer,SIGNAL(timeout()),this,SLOT(slotTimerTimeOut()));

    m_FlagImage = QPixmap(":/game/pic/flag.png");	//旗帜
    m_BombImage = QPixmap(":/game/pic/bomb.png");	//雷

    m_nRows = 9;
    m_nColumes = 15;
    m_nMineCount = 10;

    gameInfo = "作者：电子信息工程学院  16物联网2班    游家";

    NewGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitItems()
{
    //随机初始化雷
    m_Mines.clear();
    for(int i = 0; i<m_nMineCount; i++)
    {
        qsrand(QTime::currentTime().msec());
        int x = qrand()%m_nColumes;
        int y = qrand()%m_nRows;
        while(m_Mines.contains(QPoint(x,y)))
        {
            x = qrand()%m_nColumes;
            y = qrand()%m_nRows;
        }
        m_Mines.append(QPoint(x,y));
    }
    //建立2维数组保存所有元素位置，方便索引
    for(int i=0; i<m_nColumes; i++)
    {
        QVector<Item*> rowItems;
        for(int j=0; j<m_nRows; j++)
        {
            QPoint pos = QPoint(i,j);
            Item* pItem = new Item(pos);
            if(m_Mines.contains(pos))   //该位置是雷
            {
                pItem->m_bIsMine = true;
            }
            rowItems.append(pItem);
        }
        m_items.append(rowItems);
    }
    //计算雷附近格子的数字
    for(int i=0; i<m_nColumes; i++)
    {
        for(int j=0; j<m_nRows; j++)
        {
            if (m_items[i][j]->m_bIsMine)
            {
                continue;
            }
            int nCountMines = 0;
            //求每个点附近的8个点的是雷的总数
            for (int m=-1;m<=1;m++)
            {
                for (int n=-1; n<=1;n++)
                {
                    if (m==0 && n==0)
                    {
                        continue;
                    }
                    QPoint ptNew = QPoint(i+m,j+n);
                    if (!PointInGameArea(ptNew))
                    {
                        continue;
                    }

                    if (m_items[i+m][j+n]->m_bIsMine)
                    {
                        nCountMines++;
                    }
                }
            }
            m_items[i][j]->m_nNumber = nCountMines;
        }
    }
}

void MainWindow::ReleaseItems()
{
    for (int i=0; i<m_items.size(); i++)
    {
        for (int j=0;j<m_items[i].size(); j++)
        {
            if (m_items[i][j] != NULL)
            {
                delete m_items[i][j];
                m_items[i][j] = NULL;
            }
        }
    }
    m_items.clear();
}

void MainWindow::NewGame()
{
    m_bGameFail = false;
    resize(START_X*2 + m_nColumes*RECT_WIDTH  ,START_Y*2 + m_nRows*RECT_HEIGHT);

    ReleaseItems();
    InitItems();
}

void MainWindow::GameFail()
{
    m_bGameFail = true;
    for (int i=0; i<m_items.size(); i++)
    {
        for (int j=0;j<m_items[i].size(); j++)
        {
            if (m_items[i][j]->m_bIsMine)
            {
                m_items[i][j]->m_bMarked = true;
            }
            else
            {
                m_items[i][j]->m_bMarked = false;
                m_items[i][j]->m_bOpen = true;
            }
        }
    }
    //QMessageBox::information(NULL,  "GAME OVER","FAILED!", QMessageBox::Yes , QMessageBox::Yes);
}

//是否找完
bool MainWindow::FindAll()
{
    bool bFindAll = true;
    //遍历二维数组 QVector<QVector<Item*>> m_items
    for (int i=0; i<m_items.size(); i++)
    {
        for (int j=0;j<m_items[i].size(); j++)
        {
            //只要存在一个雷没被标记，或存在一个非雷被没打开，都不算找完
            Item* pItem = m_items[i][j];
            if (pItem->m_bIsMine)
            {
                if (!pItem->m_bMarked)
                {
                    bFindAll = false;
                }
            }
            else
            {
                if (!pItem->m_bOpen)
                {
                    bFindAll = false;
                }
            }
        }
    }
    return bFindAll;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    DrawChessboard();
    DrawItems();

    update();
}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
    m_cTimer.start(500);
    pos_x = e->pos().x();
    pos_y = e->pos().y();
    qDebug("Position_Pressed: x: %f \n" , pos_x);



}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    e = e;
    //m_cTimer.stop();
    //得到鼠标处的格子坐标
    QPoint pt;
    pt.setX( (e->pos().x() - START_X ) / RECT_WIDTH);
    pt.setY( (e->pos().y() - START_X ) / RECT_HEIGHT);
    //是否点在游戏区域内
    if (!PointInGameArea(pt))
    {
        return;
    }
    //获取所点击矩形元素
    Item* pItem = m_items[pt.x()][pt.y()];
    //已标记过的，取消标记
    if (pItem->m_bMarked)
    {
        pItem->m_bMarked = false;
    }
    else if (!pItem->m_bOpen)
    {
        //没标记也没打开，就是未处理的，就插旗帜标记上
        pItem->m_bMarked = true;
        if (FindAll())
        {
            QMessageBox::information(NULL,  "GAME OVER","SUCCESS!", QMessageBox::Yes , QMessageBox::Yes);
            //GameSuccess();
            return;
        }
    }

}

void MainWindow::OnMenuNewGame()
{
    NewGame();
}

void MainWindow::OnMenuLevel1()
{
    m_nRows = 9;
    m_nColumes = 9;
    m_nMineCount = 10;
    NewGame();
}

void MainWindow::OnMenuLevel2()
{
    m_nRows = 10;
    m_nColumes = 15;
    m_nMineCount = 25;
    NewGame();
}

void MainWindow::OnMenuLevel3()
{
    m_nRows = 10;
    m_nColumes = 18;
    m_nMineCount = 40;
    NewGame();
}

void MainWindow::DrawChessboard()
{
    QPainter painter(this);
    painter.setBrush(Qt::lightGray);
    painter.drawRect( 0,0,width(),height());
}

void MainWindow::DrawItems()
{
    QPainter painter(this);
    painter.setBrush(Qt::lightGray);
    painter.setPen(QPen(QColor(Qt::black),2));

    for(int i=0; i<m_nColumes; i++)
    {
        for(int j=0; j<m_nRows; j++)
        {
            DrawItem(painter,m_items[i][j]);
        }
    }
}
void MainWindow::DrawItem(QPainter& painter,Item* pItem)
{
    if(pItem->m_bMarked)
    {
        if (m_bGameFail)
        {
            //游戏结束，显示为雷
            QRect rcSrc(0,0,m_FlagImage.width(),m_FlagImage.height());
            QRect rcTarget(START_X + pItem->m_pos.x()*RECT_WIDTH + 2,START_Y + pItem->m_pos.y()*RECT_HEIGHT + 2,RECT_WIDTH-4,RECT_HEIGHT-4);
            painter.drawPixmap(rcTarget,m_BombImage,rcSrc);
        }
        else
        {
            //游戏没结束，显示为旗子
            QRect rcSrc(0,0,m_FlagImage.width(),m_FlagImage.height());
            QRect rcTarget(START_X + pItem->m_pos.x()*RECT_WIDTH + 2,START_Y + pItem->m_pos.y()*RECT_HEIGHT + 2,RECT_WIDTH-4,RECT_HEIGHT-4);
            painter.drawPixmap(rcTarget,m_FlagImage,rcSrc);
        }
        painter.setBrush(Qt::transparent);
        painter.drawRect( START_X + pItem->m_pos.x()*RECT_WIDTH,START_Y + pItem->m_pos.y()*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
        return;
    }
    else if (pItem->m_bOpen)
    {
        if(pItem->m_nNumber == 0)
        {
            painter.setBrush(Qt::white);
        }
        else
        {
            QFont font;
            font.setPointSize(15);
            font.setFamily(("msyh"));
            font.setBold(true);

            //float f = pItem->m_nNumber/8;
            //painter.setBrush(QColor(f*255,f*255,0));
            painter.setBrush(Qt::white);
            painter.drawRect( START_X + pItem->m_pos.x()*RECT_WIDTH,START_Y + pItem->m_pos.y()*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);

            painter.setBrush(Qt::black);
            painter.setFont(font);
            painter.drawText( START_X + pItem->m_pos.x()*RECT_WIDTH  + 12,START_Y + pItem->m_pos.y()*RECT_HEIGHT + 28,QString("%1").arg(pItem->m_nNumber));
            return;
        }
    }
    else
    {
        painter.setBrush(Qt::blue);

        //调试使用：显示各个雷
        //if (pItem->m_bIsMine)
        //{
        //	painter.setBrush(Qt::red);
        //	painter.drawRect( START_X + pItem->m_pos.x()*RECT_WIDTH,START_Y + pItem->m_pos.y()*RECT_HEIGHT,10,10);
        //	return;
        //}
    }
    painter.drawRect( START_X + pItem->m_pos.x()*RECT_WIDTH,START_Y + pItem->m_pos.y()*RECT_HEIGHT,RECT_WIDTH,RECT_HEIGHT);
}


//运气好时点到一个空白元素，可能打开挨着的一大片
void MainWindow::OpenEmptyItem(QPoint pt)
{
    //对于空白元素，有上下左右4个方向挨着的空白元素，就打开并继续查找空白元素
    QVector<QPoint> directions;
    directions.push_back(QPoint(-1,0));
    directions.push_back(QPoint(1,0));
    directions.push_back(QPoint(0,-1));
    directions.push_back(QPoint(0,1));
    for (int i=0; i<directions.size(); i++)
    {
        QPoint ptNew = pt + directions[i];
        if (!PointInGameArea(ptNew))
        {
            continue;
        }
        Item* pItem = m_items[ptNew.x()][ptNew.y()];
        if (!pItem->m_bIsMine && !pItem->m_bOpen && !pItem->m_bMarked && pItem->m_nNumber == 0)
        {
            pItem->m_bOpen = true;

            //对于找到的空白元素，在它的8个方向上有数字元素就打开
            QVector<QPoint> directions2 = directions;
            directions2.push_back(QPoint(-1,-1));
            directions2.push_back(QPoint(1,1));
            directions2.push_back(QPoint(1,-1));
            directions2.push_back(QPoint(-1,1));
            for (int j=0; j<directions2.size(); j++)
            {
                QPoint ptNew2 = ptNew + directions2[j];
                if(!PointInGameArea(ptNew2))
                {
                    continue;
                }
                Item* pItem2 = m_items[ptNew2.x()][ptNew2.y()];
                if (!pItem2->m_bIsMine && !pItem2->m_bOpen && !pItem2->m_bMarked && pItem2->m_nNumber > 0)
                {
                    pItem2->m_bOpen = true;
                }
            }
            //递归查找上下左右4个方向的空白元素
            OpenEmptyItem(ptNew);
        }
    }
}

bool MainWindow::PointInGameArea(QPoint pt)
{
    if(pt.x()>=0 && pt.x()< m_nColumes && pt.y()>=0 && pt.y()< m_nRows)
    {
        return true;
    }
    return false;
}

void MainWindow::slotTimerTimeOut()
{
    m_cTimer.stop();
    mouseClicked();
}

void MainWindow::mouseClicked()
{
    //QString Qpos_y(pos_y);
    //qDebug("Position_Pressed: x: %f \n" , pos_y);
    qDebug()<<"CButton::mouseClicked"<<endl;

    //得到鼠标处的格子坐标
    QPoint pt;
    pt.setX( (pos_x - START_X ) / RECT_WIDTH);
    pt.setY( (pos_y - START_X ) / RECT_HEIGHT);
    //是否点在游戏区域内
    if (!PointInGameArea(pt))
    {
        return;
    }
    //获取所点击矩形元素
    Item* pItem = m_items[pt.x()][pt.y()];
    //左键打开元素，右键插旗帜标记
        //不是已标记的或已打开的空白点，也就是未处理的
        if(!pItem->m_bMarked && !pItem->m_bOpen)
        {
            //如果是雷，就GAME OVER
            if (pItem->m_bIsMine)
            {
                //QMessageBox::information(NULL,  "GAME OVER","FAIL!", QMessageBox::Yes , QMessageBox::Yes);
                GameFail();
                return;
            }
            else
            {
                //打开
                pItem->m_bOpen = true;
                if (pItem->m_nNumber == 0)
                {
                    //如果数字是0，也就是不含任何相邻雷的元素，那么递归打开所有的相邻数字是0的元素
                    //也就是点到一个空白处，一下打开一大片的效果
                    OpenEmptyItem(pt);
                }
                //如果已找到所有雷
                if (FindAll())
                {
                    QMessageBox::information(NULL,  "GAME OVER","SUCCESS!", QMessageBox::Yes , QMessageBox::Yes);
                    //GameSuccess();
                    return;
                }
            }
        }



}

void MainWindow::GameEnd(){
    m_bGameFail = true;
    for (int i=0; i<m_items.size(); i++)
    {
        for (int j=0;j<m_items[i].size(); j++)
        {
            if (m_items[i][j]->m_bIsMine)
            {
                m_items[i][j]->m_bMarked = true;
            }
            else
            {
                m_items[i][j]->m_bMarked = false;
                m_items[i][j]->m_bOpen = true;
            }
        }
    }
}

void MainWindow::AboutGame(){
    //QMessageBox::information(NULL,  "关于本游戏",gameInfo, QMessageBox::Yes , QMessageBox::Yes);
    QMessageBox::about(NULL,"关于本游戏",gameInfo);
}

void MainWindow::ExitGame(){
    close();
}



