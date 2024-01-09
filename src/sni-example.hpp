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
    SNIExample(StatusNotifierItem* sni);
    ~SNIExample();

    void onScroll(int delta, Qt::Orientation orientation);

private:
    StatusNotifierItem* sni_;
    QMenu*              menu_;
    int                 volume_;
};
