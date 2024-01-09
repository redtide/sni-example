// SPDX-License-Identifier: Unlicense

#pragma once

#include <QObject>

class StatusNotifierItem;

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class SNIExample : public QObject
{
    Q_OBJECT

public:
    SNIExample(QObject* parent = nullptr);
    ~SNIExample();

    void onScroll(int delta, Qt::Orientation);
    void onSecondaryActivateRequested(const QPoint&);

private:
    void setVolumeIcon();

    StatusNotifierItem* sni_;
    QMenu*              menu_;
    int                 volume_;
    bool                muted_;
};
