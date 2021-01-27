#include "PaletteWidget.h"
#include "QPainter.h"
#include <QDebug>
#include <QMouseEvent>



PaletteWidget::PaletteWidget(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    resize(800, 400);
    setMouseTracking(true);

    qApp->installEventFilter(this);

    paletteWidthTotal = 0;

    mousePosX = 0;
    mousePosY = 0;

}


void PaletteWidget::paintEvent(QPaintEvent * pxEvent)
{
    QPainter xPainter(this);


    renderPalette(&xPainter);
    renderRGBLabels(&xPainter);

}


void PaletteWidget::renderPalette(QPainter * pxPainter)
{
    pxPainter->save();

    int widgetWidth = this->width();
    int widgetHeight = this->height();

    int x = 50;
    int y = calcPosition(0, widgetHeight, 0.2);
    int y1 = calcPosition(widgetHeight, 0, 0.3);

    int w = 1;
    int h = y1 - y;

    paletteWidthTotal = widgetWidth - x;

    for (int i = 50; i <= paletteWidthTotal; i++)
    {

        QRect rect(i, y, w, h);
        pxPainter->drawRect(rect);

        double proportion = calcProportion(i, 50, paletteWidthTotal);

        QString k = QString::number(i);
        QString p = QString::number(proportion);

        //qDebug() << k << " " << p;

        pxPainter->fillRect(rect, getColor(proportion));
    }


    pxPainter->restore();
}

void PaletteWidget::renderRGBLabels(QPainter * pxPainter)
{
    pxPainter->save();

    QRect rgbRect(50, 300, 130, 100);
    QRect rgbColorRect(175, 300, 25, 25);

    QPixmap pixmap(this->size());
    this->render(&pixmap);
    QImage img(pixmap.toImage());
    QRgb pix = img.pixel(mousePosX, mousePosY);

    QString r = QString::number(qRed(pix));
    QString g = QString::number(qGreen(pix));
    QString b = QString::number(qBlue(pix));

    pxPainter->fillRect(rgbColorRect, QColor(qRed(pix), qGreen(pix), qBlue(pix)));

    QString rgb = "RGB(" + r + ", " + g + ", " + b + ")";
    qDebug() << rgb ;

    pxPainter->drawText(rgbRect, rgb);
    pxPainter->drawRect(rgbColorRect);

    update();
    pxPainter->restore();


}

QColor PaletteWidget::getColor(double x)
{
    QColor color;

    if (x >= 0 && x <= 1)
    {
        for (int i = 0; i < limits.size() - 1; i++)
        {
            if (x > limits[i] && x <= limits[i + 1])
            {
                color = interpolate(colors[i], colors[i + 1], calcProportion(x, limits[i], limits[i + 1]));
                break;
            }
        }
    }

    return color;
}

int PaletteWidget::calcPosition(int start, int end, double percentage)
{

    return start + percentage * (end - start);
}

double PaletteWidget::calcProportion(double x, double limit1, double limit2)
{

    return (x - limit1) / (limit2 - limit1);
}

QColor PaletteWidget::interpolate(QColor a, QColor b, float x)
{
    float sRed = a.red();
    float sGreen = a.green();
    float sBlue = a.blue();

    float gRed = b.red();
    float gGreen = b.green();
    float gBlue = b.blue();

    int newRed = (gRed - sRed) * x + sRed;
    int newGreen = (gGreen - sGreen) * x + sGreen;
    int newBlue = (gBlue - sBlue) * x + sBlue;

    return QColor(newRed, newGreen, newBlue);
}

//void PaletteWidget::mouseMoveEvent(QMouseEvent *event) {
//    qDebug() << event->pos();
//}


bool PaletteWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseMove)
    {

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        mousePosX = mouseEvent->pos().x();
        mousePosY = mouseEvent->pos().y();

        statusBar()->showMessage(QString("Mouse position (%1,%2)").arg(mousePosX).arg(mousePosY));


    }
    return false;
}