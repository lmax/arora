/*
 * Copyright 2009 Benjamin C. Meyer <ben@meyerhome.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#include "rssbutton.h"

#include "locationbar.h"
#include "webview.h"

#include <qevent.h>
#include <qfile.h>
#include <qmenu.h>
#include <qpainter.h>
#include <qwebpage.h>
#include <qwebframe.h>

#include <qdebug.h>

RssButton::RssButton(QWidget *parent)
    : QAbstractButton(parent)
{
    setCursor(Qt::ArrowCursor);
    setToolTip(tr("Show RSS"));
    setVisible(false);
    setFocusPolicy(Qt::NoFocus);
    setMinimumSize(14, 14);
}

void RssButton::setWebView(WebView *webView)
{
    m_webPage = webView->page();
    connect(m_webPage, SIGNAL(loadFinished(bool)),
            this, SLOT(loadFinished(bool)));
}

void RssButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QImage image(QLatin1String(":feed-icon-14x14.png"));
    painter.drawImage(QPoint(0, 0), image);
}

void RssButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !m_feeds.isEmpty()) {
        if (m_feeds.count() == 1) {
            //emit openUrl(QUrl::fromEncoded(m_feeds.at(0).href), m_feeds.at(1).title);
        } else {
            QMenu menu;
            foreach(const Feed &feed, m_feeds)
                menu.addAction(feed.title);
            menu.exec(mapToGlobal(event->pos()));
        }
        event->accept();
    }
    QAbstractButton::mousePressEvent(event);
}

void RssButton::triggeredAction()
{
}

void RssButton::loadFinished(bool ok)
{
    if (!ok)
        return;

    if (m_script.isEmpty()) {
        QFile file(QLatin1String(":fetchLinks.js"));
        if (!file.open(QFile::ReadOnly))
            return;
        m_script = QString::fromUtf8(file.readAll());
    }

    QVariantList list = m_webPage->mainFrame()->evaluateJavaScript(m_script).toList();
    m_feeds.clear();
    foreach(const QVariant &variant, list) {
        QVariantMap map = variant.toMap();
        QString type = (map[QLatin1String("type")]).toString();
        QString title = (map[QLatin1String("title")]).toString();
        QString href = (map[QLatin1String("href")]).toString();
        m_feeds.append(Feed(title, href));
    }
    setVisible(!m_feeds.isEmpty());
}
