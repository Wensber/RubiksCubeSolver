// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <iostream>


Helper::Helper()
{
    background = QBrush(QColor(210, 210, 210));
    blackBrush = QBrush(Qt::black);
    buttonBrush = QBrush(QColor(100, 100, 100));

    faceBrushes.emplace_back(QBrush(Qt::white));
    faceBrushes.emplace_back(QBrush(QColor(173, 216, 230)));
    faceBrushes.emplace_back(QBrush(Qt::red));
    faceBrushes.emplace_back(QBrush(Qt::green));
    faceBrushes.emplace_back(QBrush(QColor(255, 165, 0)));
    faceBrushes.emplace_back(QBrush(Qt::yellow));


}



void Helper::paint(QPainter *painter, QPaintEvent *event)
{

    painter->fillRect(event->rect(), background);

    painter->fillRect(QRect(210, 25, 30, 20), faceBrushes.at(2));
    painter->fillRect(QRect(310, 25, 30, 20), faceBrushes.at(4));

    painter->fillRect(QRect(210, 505, 30, 20), faceBrushes.at(2));
    painter->fillRect(QRect(310, 505, 30, 20), faceBrushes.at(4));

    painter->fillRect(QRect(25, 210, 20, 30), faceBrushes.at(3));
    painter->fillRect(QRect(25, 310, 20, 30), faceBrushes.at(1));

    painter->fillRect(QRect(655, 210, 20, 30), faceBrushes.at(3));
    painter->fillRect(QRect(655, 310, 20, 30), faceBrushes.at(1));

    painter->fillRect(QRect(360, 175, 30, 20), faceBrushes.at(0));
    painter->fillRect(QRect(460, 175, 30, 20), faceBrushes.at(5));

    painter->fillRect(QRect(360, 355, 30, 20), faceBrushes.at(0));
    painter->fillRect(QRect(460, 355, 30, 20), faceBrushes.at(5));

}

void Helper::paintFace(QPainter *painter, int xPos, int yPos, int axis, int row, bool cInv, bool rInv,
                       const std::vector<std::vector<std::vector<std::vector<int>>>>& rubiks_cube)
{
    painter->fillRect(QRect(xPos, yPos, 150, 150), blackBrush);

    switch(axis)
    {
    case 0:
    {
        int y, z, c, r, face;
        for(y=0;y<3;++y){
            for(z=0;z<3;++z){
                c = (cInv ? 2-z : z);
                r = (rInv ? 2-y : y);
                face = rubiks_cube[row][y][z][axis];
                painter->fillRect(QRect(xPos+4+c*48, yPos+4+r*48, 46, 46), faceBrushes.at(face));
            }
        }
        break;
    }
    case 1:
    {
        int x, z, c, r, face;
        for(x=0;x<3;++x){
            for(z=0;z<3;++z){
                c = (cInv ? 2-x : x);
                r = (rInv ? 2-z : z);
                face = rubiks_cube[x][row][z][axis];
                painter->fillRect(QRect(xPos+4+c*48, yPos+4+r*48, 46, 46), faceBrushes.at(face));
            }
        }
        break;
    }
    case 2:
    {
        int x, y, c, r, face;
        for(x=0;x<3;++x){
            for(y=0;y<3;++y){
                c = (cInv ? 2-x : x);
                r = (rInv ? 2-y : y);
                face = rubiks_cube[x][y][row][axis];
                painter->fillRect(QRect(xPos+4+c*48, yPos+4+r*48, 46, 46), faceBrushes.at(face));
            }
        }
        break;
    }
    }

}











