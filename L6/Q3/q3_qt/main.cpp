#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <set>
#include <vector>
#include <queueue>
typedef float decimalValue;
using namespace std;
void leastSquareFit(decimalValue* x,decimalValue* y,int n, decimalValue* a, decimalValue* b)
{
    decimalValue countX = 0,countY = 0;
    for (int i = 0; i < n; ++i)
    {
        countX += x[i];
        countY += y[i];
    }
    decimalValue averageY = countY/n;
    decimalValue averageX = countX/n;

    decimalValue m = 0;
    decimalValue temp = 0;
    for (int i = 0; i < n; ++i)
    {
        m += (x[i] - averageX)*(y[i]-averageY);
        temp += (x[i] - averageX) * (x[i] - averageX);
    }

    *a = m/temp;
    *b = averageY - (*a) * averageX;
}


bool findPointOfIntersection(Segment* segment1, Segment* segment2, decimalValue* x, decimalValue *y)
{
    if (segment1->m == segment2->m)
    {
        return false;
    }
    else
    {
        decimalValue slope1,slope2,intercept1,intercept2;
        slope1 = segment1->m;
        intercept1 = segment1->c;
        slope2 = segment2->m;
        intercept2 = segment2->c;
        *x = (intercept2-intercept1)/(slope1-slope2);
        *y = slope1*(*x) + intercept1;
        if (segment1->check(*x,*y) && segment2->check(*x,*y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}


int main(int argc, char *argv[])
{
    int n;
        cout << "Enter the number of lines : ";
        cin >> n;
        Segment** lineSegment = new Segment*[n];

        priority_queueue <Vertex, vector<Vertex> , CompareQueue> queue;
        cout << "Enter the coordinates space separated" << endl;
        for (int i = 0; i < n; ++i)
        {
            decimalValue x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            lineSegment[i] = new Segment(x1,y1,x2,y2);
            queue.push(*(lineSegment[i]->left));
            queue.push(*(lineSegment[i]->right));
        }

        set<Vertex,CompareSet> output;
        set<Segment*> active;

        while(queue.empty() == false)
        {
            Vertex v = queue.top();
            if (v.isLeft == true)
            {
                Segment* temp = (Segment*)v.segment;
                for (auto it = active.begin() ; it != active.end() ; ++it)
                {
                    Segment* temp = *it;
                    decimalValue x,y;
                    bool findPointOfIntersectionion = findPointOfIntersection(temp, temp,&x,&y);
                    if (findPointOfIntersectionion)
                    {
                        Vertex ins(x,y);
                        output.insert(ins);
                    }
                }
                active.insert((Segment*)v.segment);
            }
            else
            {
                active.erase((Segment*)v.segment);
            }
            queue.pop();
        }

        cout << "No. of findPointOfIntersectionion points: "<< output.size() << endl;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            cout << "(" << it->x << "," << it->y << ")" << endl;
        }

        int n2 = output.size();
        decimalValue* x = new decimalValue[n2];
        decimalValue* y = new decimalValue[n2];
        int i = 0;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            x[i] = it->x;
            y[i] = it->y;
            i++;
        }

        decimalValue a;
        decimalValue b;

        leastSquareFit(x,y,n2,&a,&b);

    QApplication app(argc, argv);
    MainWindow w(nullptr,x,y,n,n2,lineSegment,a,b);
    w.show();
    return app.exec();
}
