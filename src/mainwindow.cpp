#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent) {

    this->base = new Base("/home/hagen/Desktop/test.mp4");


    this->count_sliders = 1;
    this->grid = new QGridLayout;
    this->controlsLayout = new QGridLayout;


    this->grid->addWidget(createImage("asd"), 0, 0, 3, 2);
    this->grid->addWidget(createControls("Nummber 1"), 3, 0, 1, 2);
    this->setLayout(grid);

    setWindowTitle(tr("Time-Based-Picture"));
    resize(800, 600);

}
void test_f(){
    std::cout<<"test\n";
}

QLabel *MainWindow::createImage(const QString &path){

    QLabel *imageLabel = new QLabel;
    QScrollArea* scrollArea = new QScrollArea;
    QImage image("/home/hagen/Desktop/test.jpg");

    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);
    scrollArea->setWidget(imageLabel);
    //scrollArea->setVisible(false);
    return imageLabel;
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

    int startframe=0;
    int endframe= 10;
    RangeWidget *rangeSlider = new RangeWidget(Qt::Horizontal);
    this->count_sliders += 1;
    //signal connect interfaces!:
    //connect(rangeSlider, SIGNAL(firstValueChanged(int firstValue)), this, SLOT(on_addButoon_click()));

    //rangesliders.push_back(rangeSlider);

    QPushButton *addButton = new QPushButton("Add", this);
    connect(addButton, SIGNAL(clicked()), this, SLOT(on_addButoon_click()));

    this->controlsLayout->addWidget(addButton,      0, 0);
    this->controlsLayout->addWidget(minimumLabel,   0, 1);
    this->controlsLayout->addWidget(minimumSpinBox, 0, 2);
    this->controlsLayout->addWidget(maximumLabel,   0, 3);
    this->controlsLayout->addWidget(maximumSpinBox, 0, 4);
    this->controlsLayout->addWidget(rangeSlider,    1, 0, 1, 5);
    controlsGroup->setLayout(controlsLayout);
    return controlsGroup;
}

void *MainWindow::on_addButoon_click(){
    std::cout << "added slider" << std::endl;
    int startframe=0;
    int endframe= 10;
    RangeWidget *rangeSlider = new RangeWidget(Qt::Horizontal);
    //connect to segment!:

    this->controlsLayout->addWidget(rangeSlider,this->count_sliders + 1, 0, this->count_sliders + 1, 5);
    this->count_sliders += 1;
}


MainWindow::~MainWindow() {}
