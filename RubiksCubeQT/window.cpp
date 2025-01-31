// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "widget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

//! [0]
Window::Window()
{
    setWindowTitle(tr("Rubik's Cube"));

    Widget *native = new Widget(&helper, this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(native, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, native, &Widget::animate);
    timer->start(50);
}
//! [0]
