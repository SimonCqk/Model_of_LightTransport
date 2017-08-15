#include "confparas.h"
#include "ui_confparas.h"
#include<QPainter>
#include<QStyleOption>
ConfParas::ConfParas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfParas)
{
    ui->setupUi(this);
    ui->PhoNumSpinBox->setMaximum(99999);
    ui->PhoNumSlider->setMaximum(99999);
    ui->PhoNumSlider->setStyleSheet("QSlider::groove:horizontal {  \
                                    border: 1px solid #bbb;  \
                                    background: white;  \
                                    height: 10px;  \
                                    border-radius: 4px;  \
                                    }  \
                                      \
                                    QSlider::sub-page:horizontal {  \
                                    background: qlineargradient(x1: 0, y1: 0,    x2: 0, y2: 1, \
                                        stop: 0 #66e, stop: 1 #bbf);  \
                                    background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1,  \
                                        stop: 0 #bbf, stop: 1 #55f);  \
                                    border: 1px solid #777;  \
                                    height: 10px;  \
                                    border-radius: 4px;  \
                                    }  \
                                      \
                                    QSlider::add-page:horizontal {  \
                                    background: #fff;  \
                                    border: 1px solid #777;  \
                                    height: 10px;  \
                                    border-radius: 4px;  \
                                    }  \
                                      \
                                    QSlider::handle:horizontal {  \
                                    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, \
                                        stop:0 #eee, stop:1 #ccc);  \
                                    border: 1px solid #777;  \
                                    width: 13px;  \
                                    margin-top: -2px;  \
                                    margin-bottom: -2px;  \
                                    border-radius: 4px;  \
                                    }  \
                                      \
                                    QSlider::handle:horizontal:hover {  \
                                    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,  \
                                        stop:0 #fff, stop:1 #ddd);  \
                                    border: 1px solid #444;  \
                                    border-radius: 4px;  \
                                    }  \
                                      \
                                    QSlider::sub-page:horizontal:disabled {  \
                                    background: #bbb;  \
                                    border-color: #999;  \
                                    }  \
                                      \
                                    QSlider::add-page:horizontal:disabled {  \
                                    background: #eee;  \
                                    border-color: #999;  \
                                    }  \
                                      \
                                    QSlider::handle:horizontal:disabled {  \
                                    background: #eee;  \
                                    border: 1px solid #aaa;  \
                                    border-radius: 4px;  \
                                    }");
}

ConfParas::~ConfParas()
{
    delete ui;
}

void ConfParas::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
