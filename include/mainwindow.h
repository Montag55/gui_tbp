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

private:
    QGroupBox *createControls(const QString &title);
    QLabel *createImage(const QString &title);


    int count_sliders;
    QGridLayout *grid;
    QGridLayout *controlsLayout;
    Base* base;
    std::vector<RangeWidget*> rangesliders;
    std::vector<Segment*> segments;

};

#endif // MAINWINDOW_H
