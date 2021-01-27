#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaletteWidget.h"

class PaletteWidget : public QMainWindow
{
    Q_OBJECT

public:
    PaletteWidget(QWidget *parent = Q_NULLPTR);

private:
    Ui::PaletteWidgetClass ui;
    void paintEvent(QPaintEvent * pxEvent);
    void PaletteWidget::renderPalette(QPainter * pxPainter);
    void PaletteWidget::renderRGBLabels(QPainter * pxPainter);
    //void PaletteWidget::mouseMoveEvent(QMouseEvent *event);
    bool PaletteWidget::eventFilter(QObject *obj, QEvent *event);

    QColor interpolate(QColor b, QColor a, float x);

    QColor getColor(double index);

    int PaletteWidget::calcPosition(int start, int end, double percentage);


    double PaletteWidget::calcProportion(double x, double limit1, double limit2);

    QVector<float> limits{ {0.0, 0.3, 0.6, 1.0} };
    QVector<QColor> colors{ { QColor(0,0,0),QColor(13, 201, 31), QColor(249, 167, 18), QColor(255, 82, 21)} };

    int paletteWidthTotal;
    int paletteHeightTotal;

    int mousePosX;
    int mousePosY;

};
