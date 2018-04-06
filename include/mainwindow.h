#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSpinBox>
#include <QStackedWidget>
#include "RangeWidget.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QSpinBox;
class QStackedWidget;
class QGridLayout;
QT_END_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGroupBox *createControls(const QString &title);

    QLabel          *minimumLabel;
    QLabel          *maximumLabel;
    QSpinBox        *minimumSpinBox;
    QSpinBox        *maximumSpinBox;
};

#endif // MAINWINDOW_H
