/*
    VolTrayke - Volume tray widget.
    Copyright (C) 2021-2024 Andrea Zanellato <redtid3@gmail.com>
    SPDX-License-Identifier: GPL-2.0-only
*/
#pragma once

#include <QMenu>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QSlider;
QT_END_NAMESPACE

class Volume : public QMenu
{
    Q_OBJECT

public:
    Volume();

    void popUp();
    void setMute(bool);
    void setVolume(int);

Q_SIGNALS:
    void muteToggled(bool);
    void valueChanged(int);

private:
    QCheckBox* chkMute_;
    QLabel*    lblVolume_;
    QSlider*   sldVolume_;
};
