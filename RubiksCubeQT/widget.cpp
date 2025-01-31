// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widget.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>
#include <iostream>



Widget::Widget(Helper *helper, QWidget *parent)
    : QWidget(parent), helper(helper)
{
    setFixedSize(700, 550);

    int n = 3;
    int x, y, z, i;
    for(x=0; x<n; ++x) {
        std::vector<std::vector<std::vector<int>>> next_x;
        for(y=0; y<n; ++y) {
            std::vector<std::vector<int>> next_y;
            for(z=0; z<n; ++z) {
                std::vector<int> next_z;
                for(i=0; i<3; ++i) {
                    next_z.emplace_back(-1);
                }
                next_y.emplace_back(next_z);
            }
            next_x.emplace_back(next_y);
        }
        rubiks_cube.emplace_back(next_x);
    }
    for(x=0; x<n; ++x) {
        for(y=0; y<n; ++y) {
            rubiks_cube[x][y][0][2] = 0;
            rubiks_cube[x][y][n-1][2] = 5;
        }
    }
    for(x=0; x<n; ++x) {
        for(z=0; z<n; ++z) {
            rubiks_cube[x][0][z][1] = 3;
            rubiks_cube[x][n-1][z][1] = 1;
        }
    }
    for(y=0; y<n; ++y) {
        for(z=0; z<n; ++z) {
            rubiks_cube[0][y][z][0] = 2;
            rubiks_cube[n-1][y][z][0] = 4;
        }
    }

    wcl = new QPushButton(this);
    wcl->setGeometry(QRect(360, 355, 30, 20));
    connect(wcl, &QPushButton::released, this, &Widget::turnWCl);

    wccl = new QPushButton(this);
    wccl->setGeometry(QRect(360, 175, 30, 20));
    connect(wccl, &QPushButton::released, this, &Widget::turnWCCl);

    bcl = new QPushButton(this);
    bcl->setGeometry(QRect(655, 310, 20, 30));
    connect(bcl, &QPushButton::released, this, &Widget::turnBCl);

    bccl = new QPushButton(this);
    bccl->setGeometry(QRect(25, 310, 20, 30));
    connect(bccl, &QPushButton::released, this, &Widget::turnBCCl);

    rcl = new QPushButton(this);
    rcl->setGeometry(QRect(210, 505, 30, 20));
    connect(rcl, &QPushButton::released, this, &Widget::turnRCl);

    rccl = new QPushButton(this);
    rccl->setGeometry(QRect(210, 25, 30, 20));
    connect(rccl, &QPushButton::released, this, &Widget::turnRCCl);

    gcl = new QPushButton(this);
    gcl->setGeometry(QRect(25, 210, 20, 30));
    connect(gcl, &QPushButton::released, this, &Widget::turnGCl);

    gccl = new QPushButton(this);
    gccl->setGeometry(QRect(655, 210, 20, 30));
    connect(gccl, &QPushButton::released, this, &Widget::turnGCCl);

    ocl = new QPushButton(this);
    ocl->setGeometry(QRect(310, 25, 30, 20));
    connect(ocl, &QPushButton::released, this, &Widget::turnOCl);

    occl = new QPushButton(this);
    occl->setGeometry(QRect(310, 505, 30, 20));
    connect(occl, &QPushButton::released, this, &Widget::turnOCCl);

    ycl = new QPushButton(this);
    ycl->setGeometry(QRect(460, 175, 30, 20));
    connect(ycl, &QPushButton::released, this, &Widget::turnYCl);

    yccl = new QPushButton(this);
    yccl->setGeometry(QRect(460, 355, 30, 20));
    connect(yccl, &QPushButton::released, this, &Widget::turnYCCl);

}



void Widget::animate()
{
    update();
}



void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    helper->paint(&painter, event);
    helper->paintFace(&painter, 200, 200, 2, 0, false, false, rubiks_cube);
    helper->paintFace(&painter, 200, 350, 1, 2, false, false, rubiks_cube);
    helper->paintFace(&painter,  50, 200, 0, 0,  true, false, rubiks_cube);
    helper->paintFace(&painter, 200,  50, 1, 0, false,  true, rubiks_cube);
    helper->paintFace(&painter, 350, 200, 0, 2, false, false, rubiks_cube);
    helper->paintFace(&painter, 500, 200, 2, 2,  true, false, rubiks_cube);
    painter.end();
}


void Widget::turn(int axis, int row, bool cl)
{
    switch(axis)
    {
    case 0:
    {
        std::vector<int> temp1 = rubiks_cube[row][0][0];
        std::vector<int> temp2 = rubiks_cube[row][0][1];
        if(cl){
            rubiks_cube[row][0][0] = rubiks_cube[row][2][0];
            rubiks_cube[row][0][1] = rubiks_cube[row][1][0];

            rubiks_cube[row][2][0] = rubiks_cube[row][2][2];
            rubiks_cube[row][1][0] = rubiks_cube[row][2][1];

            rubiks_cube[row][2][2] = rubiks_cube[row][0][2];
            rubiks_cube[row][2][1] = rubiks_cube[row][1][2];

            rubiks_cube[row][0][2] = temp1;
            rubiks_cube[row][1][2] = temp2;
        }else{
            rubiks_cube[row][0][0] = rubiks_cube[row][0][2];
            rubiks_cube[row][0][1] = rubiks_cube[row][1][2];

            rubiks_cube[row][0][2] = rubiks_cube[row][2][2];
            rubiks_cube[row][1][2] = rubiks_cube[row][2][1];

            rubiks_cube[row][2][2] = rubiks_cube[row][2][0];
            rubiks_cube[row][2][1] = rubiks_cube[row][1][0];

            rubiks_cube[row][2][0] = temp1;
            rubiks_cube[row][1][0] = temp2;
        }
        int y, z, temp;
        for(y=0; y<3; ++y){
            for(z=0; z<3; ++z){
                temp = rubiks_cube[row][y][z][1];
                rubiks_cube[row][y][z][1] = rubiks_cube[row][y][z][2];
                rubiks_cube[row][y][z][2] = temp;
            }
        }
        break;
    }
    case 1:
    {
        std::vector<int> temp1 = rubiks_cube[0][row][0];
        std::vector<int> temp2 = rubiks_cube[0][row][1];
        if(cl){
            rubiks_cube[0][row][0] = rubiks_cube[2][row][0];
            rubiks_cube[0][row][1] = rubiks_cube[1][row][0];

            rubiks_cube[2][row][0] = rubiks_cube[2][row][2];
            rubiks_cube[1][row][0] = rubiks_cube[2][row][1];

            rubiks_cube[2][row][2] = rubiks_cube[0][row][2];
            rubiks_cube[2][row][1] = rubiks_cube[1][row][2];

            rubiks_cube[0][row][2] = temp1;
            rubiks_cube[1][row][2] = temp2;
        }else{
            rubiks_cube[0][row][0] = rubiks_cube[0][row][2];
            rubiks_cube[0][row][1] = rubiks_cube[1][row][2];

            rubiks_cube[0][row][2] = rubiks_cube[2][row][2];
            rubiks_cube[1][row][2] = rubiks_cube[2][row][1];

            rubiks_cube[2][row][2] = rubiks_cube[2][row][0];
            rubiks_cube[2][row][1] = rubiks_cube[1][row][0];

            rubiks_cube[2][row][0] = temp1;
            rubiks_cube[1][row][0] = temp2;
        }
        int x, z, temp;
        for(x=0; x<3; ++x){
            for(z=0; z<3; ++z){
                temp = rubiks_cube[x][row][z][0];
                rubiks_cube[x][row][z][0] = rubiks_cube[x][row][z][2];
                rubiks_cube[x][row][z][2] = temp;
            }
        }
        break;
    }
    case 2:
    {
        std::vector<int> temp1 = rubiks_cube[0][0][row];
        std::vector<int> temp2 = rubiks_cube[0][1][row];
        if(cl){
            rubiks_cube[0][0][row] = rubiks_cube[2][0][row];
            rubiks_cube[0][1][row] = rubiks_cube[1][0][row];

            rubiks_cube[2][0][row] = rubiks_cube[2][2][row];
            rubiks_cube[1][0][row] = rubiks_cube[2][1][row];

            rubiks_cube[2][2][row] = rubiks_cube[0][2][row];
            rubiks_cube[2][1][row] = rubiks_cube[1][2][row];

            rubiks_cube[0][2][row] = temp1;
            rubiks_cube[1][2][row] = temp2;
        }else{
            rubiks_cube[0][0][row] = rubiks_cube[0][2][row];
            rubiks_cube[0][1][row] = rubiks_cube[1][2][row];

            rubiks_cube[0][2][row] = rubiks_cube[2][2][row];
            rubiks_cube[1][2][row] = rubiks_cube[2][1][row];

            rubiks_cube[2][2][row] = rubiks_cube[2][0][row];
            rubiks_cube[2][1][row] = rubiks_cube[1][0][row];

            rubiks_cube[2][0][row] = temp1;
            rubiks_cube[1][0][row] = temp2;
        }
        int x, y, temp;
        for(x=0; x<3; ++x){
            for(y=0; y<3; ++y){
                temp = rubiks_cube[x][y][row][0];
                rubiks_cube[x][y][row][0] = rubiks_cube[x][y][row][1];
                rubiks_cube[x][y][row][1] = temp;
            }
        }
        break;
    }
    }
}


void Widget::turnWCl()
{
    std::cout << "W Cl" << std::endl;
    turn(2, 0, false);
}

void Widget::turnWCCl()
{
    std::cout << "W CCl" << std::endl;
    turn(2, 0, true);
}

void Widget::turnBCl()
{
    std::cout << "B Cl" << std::endl;
    turn(1, 2, false);
}

void Widget::turnBCCl()
{
    std::cout << "B CCl" << std::endl;
    turn(1, 2, true);
}

void Widget::turnRCl()
{
    std::cout << "R Cl" << std::endl;
    turn(0, 0, false);
}

void Widget::turnRCCl()
{
    std::cout << "R CCl" << std::endl;
    turn(0, 0, true);
}

void Widget::turnGCl()
{
    std::cout << "G Cl" << std::endl;
    turn(1, 0, true);
}

void Widget::turnGCCl()
{
    std::cout << "G CCl" << std::endl;
    turn(1, 0, false);
}

void Widget::turnOCl()
{
    std::cout << "O Cl" << std::endl;
    turn(0, 2, true);
}

void Widget::turnOCCl()
{
    std::cout << "O CCl" << std::endl;
    turn(0, 2, false);
}

void Widget::turnYCl()
{
    std::cout << "Y Cl" << std::endl;
    turn(2, 2, true);
}

void Widget::turnYCCl()
{
    std::cout << "Y CCl" << std::endl;
    turn(2, 2, false);
}









