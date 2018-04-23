#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    std::vector<RangeWidget*> rangesliders;

};

#endif // MAINWINDOW_H
