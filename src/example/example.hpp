// SPDX-License-Identifier: Unlicense

#pragma once

#include <QObject>

#if(KSNI)
    #include "kstatusnotifieritem/kstatusnotifieritem.h"
    typedef KStatusNotifierItem StatusNotifierItem;
#else
    #include "statusnotifieritem/statusnotifieritem.h"
#endif

QT_BEGIN_NAMESPACE
class QMenu;
QT_END_NAMESPACE

class Volume;

class SNIExample : public QObject
{
    Q_OBJECT

public:
    SNIExample(QObject* parent = nullptr);
    ~SNIExample();

private:
    void setMute(bool);
    void setVolume(int);
    void setVolumeIcon(bool showMessage = false);

    void onScroll(int delta, Qt::Orientation);
#if(KSNI)
    void onActivateRequested(bool, const QPoint&);
#else
    void onActivateRequested(const QPoint&);
#endif
    void onSecondaryActivateRequested(const QPoint&);

    StatusNotifierItem* sni_;
    Volume*  volumeMenu_;
    QMenu*   contextMenu_;
    QAction* actUseMessage_;
    int      volume_;
    bool     muted_;
};
