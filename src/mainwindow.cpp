#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent) {
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(createControls("Nummber 1"), 0, 0);
    grid->addWidget(createControls("Nummber 2"), 1, 0);
    grid->addWidget(createControls("Nummber 3"), 0, 1);
    grid->addWidget(createControls("Nummber 4"), 1, 1);
    setLayout(grid);

   setWindowTitle(tr("Gui Example"));
   resize(800, 600);
}


QGroupBox *MainWindow::createControls(const QString &title) {

    QGroupBox *controlsGroup = new QGroupBox(title);

    QLabel *minimumLabel = new QLabel(tr("min. value:"));
    QLabel *maximumLabel = new QLabel(tr("max. value:"));

    QSpinBox *minimumSpinBox = new QSpinBox;
    minimumSpinBox->setRange(0, 100);
    minimumSpinBox->setSingleStep(1);

    QSpinBox *maximumSpinBox = new QSpinBox;
    maximumSpinBox->setRange(0, 100);
    maximumSpinBox->setSingleStep(1);

    RangeWidget *rangeSlider = new RangeWidget(Qt::Horizontal);

    QGridLayout *controlsLayout = new QGridLayout;
    controlsLayout->addWidget(minimumLabel, 0, 0);
    controlsLayout->addWidget(maximumLabel, 0, 2);
    controlsLayout->addWidget(minimumSpinBox, 0, 1);
    controlsLayout->addWidget(maximumSpinBox, 0, 3);
    controlsLayout->addWidget(rangeSlider, 1, 0);
    controlsGroup->setLayout(controlsLayout);

    return controlsGroup;
}


MainWindow::~MainWindow() {}
