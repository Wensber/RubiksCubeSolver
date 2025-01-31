// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <vector>

//! [0]
class Helper
{
public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event);
    void paintFace(QPainter *painter, int xPos, int yPos, int axis, int row, bool rInv, bool cInv,
                   const std::vector<std::vector<std::vector<std::vector<int>>>>& rubiks_cube);

private:
    QBrush background;
    QBrush blackBrush;
    QBrush buttonBrush;
    std::vector<QBrush> faceBrushes;

};
//! [0]

#endif
