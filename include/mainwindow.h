#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/opencv.hpp>
#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QStackedWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScreen>
#include "RangeWidget.h"
#include <lib/libtbp/include/base.hpp>
#include <lib/libtbp/include/segment.hpp>
#include "Segment_Q.hpp"
#include "TimeManager.hpp"


QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
class QGridLayout;
class QPushButton;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void *on_addButoon_click();
    void *routine();

private:
    QGroupBox *createControls(const QString &title);
    QLabel *createImage(const QString &title);
    void *connect_slider(RangeWidget* rangeSlider);


    int count_sliders;
    Base* base;
    QGridLayout *grid;
    TimeManager *timer;
    QLabel *imageLabel;
    QGridLayout *controlsLayout;
    std::vector<Segment*> segments;
    std::vector<RangeWidget*> rangesliders;

};

#endif // MAINWINDOW_H
