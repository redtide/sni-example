// SPDX-License-Identifier: Unlicense

#include "sni-example.hpp"
#include "sni/statusnotifieritem.h"

#include <QApplication>
#include <QMenu>

SNIExample::SNIExample(QObject* parent)
    : QObject(parent)
    , sni_(new StatusNotifierItem(QApplication::applicationName(), qApp))
    , menu_(new QMenu)
    , volume_(0)
    , muted_(false)
{
    sni_->setContextMenu(menu_);
    sni_->setTitle(tr("Volume"));
    sni_->setToolTipTitle(tr("Volume"));
    sni_->setStatus(QStringLiteral("Active"));
    sni_->setIconByName(QLatin1String("audio-volume-muted"));

    // FIXME: Menu seems not working in Qt6 for some reason
    QAction* quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), menu_);
    menu_->addAction(quit);

    connect(sni_, &StatusNotifierItem::scrollRequested, this, &SNIExample::onScroll);
    connect(sni_, &StatusNotifierItem::secondaryActivateRequested, this, &SNIExample::onSecondaryActivateRequested);
    connect(quit, &QAction::triggered, qApp, &QApplication::exit);
}

SNIExample::~SNIExample()
{
    delete menu_;
}

void SNIExample::onScroll(int delta, Qt::Orientation)
{
    if ((volume_ == 100 && delta > 0) || (!volume_ && delta < 0))
        return;

    delta > 0 ? volume_ += 10 : volume_ -= 10;
    setVolumeIcon();
}

void SNIExample::onSecondaryActivateRequested(const QPoint&)
{
    muted_ = !muted_;
    setVolumeIcon();
}

void SNIExample::setVolumeIcon()
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
        sni_->setToolTipIconByName(iconName);

        // FIXME: The volume value on scroll should be shown as tooltip, not as notification message
        sni_->showMessage(QString::number(volume_), QString(), iconName, 250);
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    new SNIExample(&app);
    return app.exec();
}
