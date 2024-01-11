/*
    VolTrayke - Volume tray widget.
    Copyright (C) 2021-2024 Andrea Zanellato <redtid3@gmail.com>
    SPDX-License-Identifier: GPL-2.0-only
*/
#include "volume.hpp"

#include <QApplication>
#include <QCheckBox>
#include <QLabel>
#include <QScreen>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidgetAction>

Volume::Volume()
    : chkMute_(new QCheckBox(tr("Mute"), this))
    , lblVolume_(new QLabel("0", this))
    , sldVolume_(new QSlider(Qt::Vertical, this))
{
    QWidget*       container    = new QWidget(this);
    QWidgetAction* actContainer = new QWidgetAction(this);
    QVBoxLayout*   layout       = new QVBoxLayout(this);

    lblVolume_->setAlignment(Qt::AlignCenter);

    sldVolume_->setRange(0, 100);
    sldVolume_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    sldVolume_->setMinimumHeight(120);
    sldVolume_->setTickPosition(QSlider::TicksBothSides);
    sldVolume_->setTickInterval(10);

    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->addWidget(chkMute_);
    layout->addWidget(lblVolume_);
    layout->addWidget(sldVolume_);
    layout->setAlignment(sldVolume_, Qt::AlignHCenter);
    layout->addSpacing(6);

    container->setLayout(layout);
    actContainer->setDefaultWidget(container);
    addAction(actContainer);

    connect(chkMute_,   &QCheckBox::clicked, this, &Volume::muteToggled);
    connect(sldVolume_, &QSlider::valueChanged, this, [=](int value) {
        lblVolume_->setText(QString::number(value));
        emit valueChanged(value);
    });
}

void Volume::popUp()
{
    QRect rect;
    QPoint pos = QCursor::pos();
    rect.setSize(sizeHint());
    pos.setX(pos.x() - width() / 2);
    rect.moveTopLeft(pos);

    if (const QScreen* screen = qApp->screenAt(pos)) {
        const auto& geometry = screen->availableGeometry();

        if (rect.right() > geometry.right())
            rect.moveRight(geometry.right());

        if (rect.bottom() > geometry.bottom())
            rect.moveBottom(geometry.bottom());
    }
    popup(rect.topLeft());
}

void Volume::setMute(bool mute)
{
    chkMute_->blockSignals(true);
    chkMute_->setChecked(mute);
    chkMute_->blockSignals(false);
}

void Volume::setVolume(int volume)
{
    sldVolume_->blockSignals(true);
    sldVolume_->setValue(volume);
    lblVolume_->setText(QString::number(volume));
    sldVolume_->blockSignals(false);
}
