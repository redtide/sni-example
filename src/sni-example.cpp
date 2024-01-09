// SPDX-License-Identifier: Unlicense

#include "sni-example.hpp"
#include "sni/statusnotifieritem.h"

#include <QApplication>
#include <QMenu>

SNIExample::SNIExample(StatusNotifierItem* tray)
    : sni_(tray)
    , menu_(new QMenu)
    , volume_(0)
{
    sni_->setTitle(tr("Volume"));
    sni_->setContextMenu(menu_);
    sni_->setIconByName(QLatin1String("audio-volume-muted"));

    // FIXME: Menu seems not working in Qt6 for some reason
    QAction* quit = new QAction(QIcon::fromTheme("application-exit"), tr("&Quit"), menu_);
    menu_->addAction(quit);

    // FIXME: The volume value on scroll should be shown as tooltip, not as notification message
    connect(sni_, &StatusNotifierItem::scrollRequested, this, &SNIExample::onScroll);
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

    delta > 0 ? volume_ += 5 : volume_ -= 5;

    QString iconName = QLatin1String("audio-volume-high");
    if (volume_ <= 0)
        iconName = QLatin1String("audio-volume-muted");
    else if (volume_ <= 33)
        iconName = QLatin1String("audio-volume-low");
    else if (volume_ <= 66)
        iconName = QLatin1String("audio-volume-medium");
    else
        iconName = QLatin1String("audio-volume-medium");

    sni_->setIconByName(iconName);
    sni_->showMessage(QString::number(volume_), QString(), iconName, 250);
}

int main(int argc, char **argv)
{
    QApplication        app(argc, argv);
    StatusNotifierItem* sni =
        new StatusNotifierItem(QApplication::applicationName(), &app);

    new SNIExample(sni);
    return app.exec();
}
