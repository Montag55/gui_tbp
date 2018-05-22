#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent) {

    this->base = new Base("/home/lucas/Videos/1.mp4");

    this->count_sliders = 1;
    this->grid = new QGridLayout;
    this->controlsLayout = new QGridLayout;


    this->grid->addWidget(createImage("asd"), 0, 0, 3, 2);
    this->grid->addWidget(createControls("Nummber 1"), 3, 0, 1, 2);
    this->setLayout(grid);

    setWindowTitle(tr("Time-Based-Picture"));
    resize(800, 600);

}

QLabel *MainWindow::createImage(const QString &path){

    QLabel *imageLabel = new QLabel;
    QScrollArea* scrollArea = new QScrollArea;
    QImage image("/home/lucas/Pictures/1.jpg");

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
    minimumSpinBox->setRange(0, base->get_video_size());
    minimumSpinBox->setSingleStep(1);

    QSpinBox *maximumSpinBox = new QSpinBox;
    maximumSpinBox->setRange(0, base->get_video_size());
    maximumSpinBox->setSingleStep(1);


    RangeWidget *rangeSlider = new RangeWidget(Qt::Horizontal, base->get_video_size());
    this->count_sliders += 1;

    connect(rangeSlider, SIGNAL(firstValueChanged(int)), minimumSpinBox, SLOT(setValue(int)));
    connect(rangeSlider, SIGNAL(secondValueChanged(int)), maximumSpinBox, SLOT(setValue(int)));

    connect_slider(rangeSlider);

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

void *MainWindow::connect_slider(RangeWidget* rangeSlider){

    int startframe = 0;
    int endframe   = 10;

    Segment_Q *seg = new Segment_Q(base->add_segment(startframe, endframe));
    connect(rangeSlider, SIGNAL(firstValueChanged(int)), seg, SLOT(set_firstVal(int)));
    connect(rangeSlider, SIGNAL(secondValueChanged(int)), seg, SLOT(set_secondVal(int)));
    //connect: set_localIntensity(float)
    //connect: set_globalIntensity(float)
}

void *MainWindow::on_addButoon_click(){

    int startframe=0;
    int endframe= 10;

    RangeWidget *rangeSlider = new RangeWidget(Qt::Horizontal, base->get_video_size());
    Segment_Q *seg = new Segment_Q(base->add_segment(startframe, endframe));

    connect(rangeSlider, SIGNAL(firstValueChanged(int)), seg, SLOT(set_firstVal(int)));

    this->controlsLayout->addWidget(rangeSlider,this->count_sliders + 1, 0, this->count_sliders + 1, 5);
    this->count_sliders += 1;
}

MainWindow::~MainWindow() {}
