#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <algorithm>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Vertex
{
public:
    float x,y;
    void* segment;
    bool isLeft;
    Vertex(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->segment = nullptr;
    }
};




class Segment
{
public:
    Vertex* left;
    Vertex* right;
    float m,c;
    Segment(float abscissa1, float ordinate1, float abscissa2, float ordinate2)
    {
        left = new Vertex(abscissa1,ordinate1);
        left->isLeft = true;

        right = new Vertex(abscissa2,ordinate2);
        right->isLeft = false;

        left->segment = this;
        right->segment = this;

        m = (ordinate2-ordinate1)/(abscissa2-abscissa1);
        c = ordinate1 - m*abscissa1;
    }

    bool check(float x, float y)
    {
        float abscissa1 = left->x;
        float ordinate1 = left->y;
        float abscissa2 = right->x;
        float ordinate2 = right->y;
        if (x >= min(abscissa1,abscissa2) && x <= max(abscissa1,abscissa2))
        {
            if (y >= min(ordinate1,ordinate2) && y <= max(ordinate1,ordinate2))
            {
                return true;
            }
        }
        return false;
    }

};

class CompareQueue
{
public:
    int operator() (Vertex v1, Vertex v2)
    {
        if(v1.x != v2.x)
            return v1.x > v2.x;
        else
            return v1.y > v2.y;
    }
};

class CompareSet
{
public:
    int operator() (Vertex v1, Vertex v2)
    {
        if(v1.x != v2.x)
            return v1.x < v2.x;
        else
            return v1.y < v2.y;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    float* x;
    float* y;
    int n1;
    int n2;
    float a;
    float b;
    Segment** segments;
    MainWindow(QWidget *parent = nullptr,float* x = nullptr, float* y = nullptr,int n1 = 0,int n2 = 0, Segment** segments = nullptr, float a = 0, float b = 0);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
};






#endif // MAINWINDOW_H
