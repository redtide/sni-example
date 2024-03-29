// SPDX-License-Identifier: Unlicense

#include "example.hpp"
#include "volume.hpp"

#include <QApplication>
#include <QMenu>
#include <QProxyStyle>
#include <QToolTip>
#include <QDBusInterface>

#include <algorithm>

SNIExample::SNIExample(QObject* parent)
    : QObject(parent)
    , sni_(new StatusNotifierItem(QApplication::applicationName(), qApp))
    , volumeMenu_(new Volume)
    , contextMenu_(new QMenu)
    , actUseMessage_(new QAction(tr("Use &notifications"), contextMenu_))
    , volume_(0)
    , muted_(false)
{
    sni_->setContextMenu(contextMenu_);
    sni_->setTitle(tr("Volume"));
    sni_->setToolTipTitle(tr("Volume"));

    actUseMessage_->setCheckable(true);
    contextMenu_->addAction(actUseMessage_);

#if !defined(KSNI)
    sni_->setStatus(QStringLiteral("Active"));

    QAction* quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), contextMenu_);
    contextMenu_->addAction(quit);
    connect(quit, &QAction::triggered, qApp, &QApplication::exit);
#else
    sni_->setStatus(StatusNotifierItem::ItemStatus::Active);
#endif
    sni_->setIconByName(QLatin1String("audio-volume-muted"));

    connect(sni_, &StatusNotifierItem::scrollRequested,            this, &SNIExample::onScroll);
    connect(sni_, &StatusNotifierItem::activateRequested,          this, &SNIExample::onActivateRequested);
    connect(sni_, &StatusNotifierItem::secondaryActivateRequested, this, &SNIExample::onSecondaryActivateRequested);

    connect(qApp, &QApplication::aboutToQuit, volumeMenu_,  &QObject::deleteLater);
    connect(qApp, &QApplication::aboutToQuit, contextMenu_, &QObject::deleteLater);

    connect(volumeMenu_, &Volume::muteToggled,  this, [this](bool muted) {
        muted_ = muted;
        setVolumeIcon();
    });
    connect(volumeMenu_, &Volume::valueChanged, this, [this](int volume) {
        volume_ = volume;
        setVolumeIcon();
    });
}

SNIExample::~SNIExample()
{
}

void SNIExample::onScroll(int delta, Qt::Orientation)
{
    int volume = volume_;
    if ((volume >= 100 && delta > 0) || (volume <= 0 && delta < 0))
        return;

    delta > 0 ? volume += 10 : volume -= 10;
    volume = std::clamp(volume, 0, 100);

    volumeMenu_->setVolume(volume);
    volume_ = volume;
    setVolumeIcon(true);
}

#if(KSNI)
void SNIExample::onActivateRequested(bool show, const QPoint&)
{
    if (!show) {
        volumeMenu_->hide();
        return;
    }
    volumeMenu_->show();
    volumeMenu_->adjustSize();
    volumeMenu_->popUp();
}
#else
void SNIExample::onActivateRequested(const QPoint&)
{
    volumeMenu_->show();
    volumeMenu_->adjustSize();
    volumeMenu_->popUp();
}
#endif

void SNIExample::onSecondaryActivateRequested(const QPoint&)
{
    muted_ = !muted_;
    setVolumeIcon();
    volumeMenu_->setMute(muted_);
}

void SNIExample::setVolumeIcon(bool showMsg)
{
    QString iconName;
    if (volume_ <= 0 || muted_) {
        iconName = QLatin1String("audio-volume-muted");
    }
    else if (volume_ <= 33) {
        iconName = QLatin1String("audio-volume-low");
    }
    else if (volume_ <= 66) {
        iconName = QLatin1String("audio-volume-medium");
    }
    else {
        iconName = QLatin1String("audio-volume-high");
    }
    sni_->setIconByName(iconName);

    if (!muted_) {
#if(KSNI)
        sni_->setToolTip(iconName, QString("%1\%").arg(volume_), QString());
#else
        sni_->setToolTipIconByName(iconName);
        sni_->setToolTipTitle(QString("%1\%").arg(volume_));
#endif
        if (showMsg) {
            if (actUseMessage_->isChecked()) {
                sni_->showMessage(QString::number(volume_), QString(), iconName, 250, 1);
                return;
            }
            QToolTip::showText(QCursor::pos(), QString("%1\%").arg(volume_));
            QToolTip::hideText();
        }
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    new SNIExample(&app);
    return app.exec();
}
