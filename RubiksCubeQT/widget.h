// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>

class Helper;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;

    std::vector<std::vector<std::vector<std::vector<int>>>> rubiks_cube;

    void turn(int axis, int row, bool cl);

    QPushButton *wcl;
    void turnWCl();
    QPushButton *wccl;
    void turnWCCl();

    QPushButton *bcl;
    void turnBCl();
    QPushButton *bccl;
    void turnBCCl();

    QPushButton *rcl;
    void turnRCl();
    QPushButton *rccl;
    void turnRCCl();

    QPushButton *gcl;
    void turnGCl();
    QPushButton *gccl;
    void turnGCCl();

    QPushButton *ocl;
    void turnOCl();
    QPushButton *occl;
    void turnOCCl();

    QPushButton *ycl;
    void turnYCl();
    QPushButton *yccl;
    void turnYCCl();


};


#endif
