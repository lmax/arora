/*
 * Copyright 2008 Benjamin C. Meyer <ben@meyerhome.net>
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

/****************************************************************************
**
** Copyright (C) 2007-2008 Trolltech ASA. All rights reserved.
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** This file may be used under the terms of the GNU General Public
** License versions 2.0 or 3.0 as published by the Free Software
** Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file.  Alternatively you may (at
** your option) use any later version of the GNU General Public
** License if such license has been publicly approved by Trolltech ASA
** (or its successors, if any) and the KDE Free Qt Foundation. In
** addition, as a special exception, Trolltech gives you certain
** additional rights. These rights are described in the Trolltech GPL
** Exception version 1.2, which can be found at
** http://www.trolltech.com/products/qt/gplexception/ and in the file
** GPL_EXCEPTION.txt in this package.
**
** Please review the following information to ensure GNU General
** Public Licensing requirements will be met:
** http://trolltech.com/products/qt/licenses/licensing/opensource/. If
** you are unsure which license is appropriate for your use, please
** review the following information:
** http://trolltech.com/products/qt/licenses/licensing/licensingoverview
** or contact the sales department at sales@trolltech.com.
**
** In addition, as a special exception, Trolltech, as the sole
** copyright holder for Qt Designer, grants users of the Qt/Eclipse
** Integration plug-in the right for the Qt/Eclipse Integration to
** link to functionality provided by Qt Designer and its related
** libraries.
**
** This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
** INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE. Trolltech reserves all rights not expressly
** granted herein.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef BROWSERMAINWINDOW_H
#define BROWSERMAINWINDOW_H

#include <qmainwindow.h>
#include <qicon.h>
#include <qurl.h>

class AutoSaver;
class BookmarksToolBar;
class ChaseWidget;
class QWebFrame;
class TabWidget;
class ToolbarSearch;
class WebView;
class QSplitter;
class QFrame;
class HistoryMenu;
class BookmarksMenuBarMenu;


/*!
    The MainWindow of the Browser Application.

    Handles the tab widget and all the actions
 */
class BrowserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserMainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~BrowserMainWindow();
    QSize sizeHint() const;

public:
    TabWidget *tabWidget() const;
    WebView *currentTab() const;
    ToolbarSearch *toolbarSearch() const;
    QByteArray saveState(bool withTabs = true) const;
    bool restoreState(const QByteArray &state);
    QAction *showMenuBarAction() const;

public slots:
    void slotHome();
    void slotPrivacyChanged(bool isPrivate);
    void slotZoomTextOnlyChanged(bool textOnly);

protected:
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void changeEvent(QEvent *event);

private slots:
    void save();

    void slotLoadProgress(int);
    void slotUpdateStatusbar(const QString &string);
    void slotUpdateWindowTitle(const QString &title = QString());

    void slotPreferences();

    void slotFileNew();
    void slotFileOpen();
    void slotFilePrintPreview();
    void slotFilePrint();
    void slotPrivateBrowsing();
    void slotFileSaveAs();
    void slotEditFind();
    void slotEditFindNext();
    void slotEditFindPrevious();
    void slotShowBookmarksDialog();
    void slotAddBookmark();
    void slotZoomIn();
    void slotZoomNormal();
    void slotZoomOut();
    void slotViewMenuBar();
    void slotViewToolbar();
    void slotViewBookmarksBar();
    void slotViewStatusbar();
    void slotViewPageSource();
    void slotViewFullScreen(bool enable);

    void slotWebSearch();
    void slotClearPrivateData();
    void slotToggleInspector(bool enable);
    void slotAboutApplication();
    void slotDownloadManager();
    void slotSelectLineEdit();

    void slotAboutToShowBackMenu();
    void slotAboutToShowForwardMenu();
    void slotAboutToShowWindowMenu();
    void slotOpenActionUrl(QAction *action);
    void slotShowWindow();
    void slotSwapFocus();

    void printRequested(QWebFrame *frame);
    void geometryChangeRequested(const QRect &geometry);
    void updateToolbarActionText(bool visible);
    void updateBookmarksToolbarActionText(bool visible);
    void showNetworkMonitor();

private:
    void retranslate();
    void loadDefaultState();
    void setupMenu();
    void setupToolBar();
    void updateStatusbarActionText(bool visible);

private:
    QMenu *m_fileMenu;
    QAction *m_fileNewWindowAction;
    QAction *m_fileOpenFileAction;
    QAction *m_fileOpenLocationAction;
    QAction *m_fileSaveAsAction;
    QAction *m_fileImportBookmarksAction;
    QAction *m_fileExportBookmarksAction;
    QAction *m_filePrintPreviewAction;
    QAction *m_filePrintAction;
    QAction *m_filePrivateBrowsingAction;
    QAction *m_fileCloseWindow;
    QAction *m_fileQuit;

    QMenu *m_editMenu;
    QAction *m_editUndoAction;
    QAction *m_editRedoAction;
    QAction *m_editCutAction;
    QAction *m_editCopyAction;
    QAction *m_editPasteAction;
    QAction *m_editFindAction;
    QAction *m_editFindNextAction;
    QAction *m_editFindPreviousAction;
    QAction *m_editPreferencesAction;

    QMenu *m_viewMenu;
    QAction *m_viewShowMenuBarAction;
    QAction *m_viewToolbarAction;
    QAction *m_viewBookmarkBarAction;
    QAction *m_viewStatusbarAction;
    QAction *m_viewStopAction;
    QAction *m_viewReloadAction;
    QAction *m_viewZoomInAction;
    QAction *m_viewZoomNormalAction;
    QAction *m_viewZoomOutAction;
    QAction *m_viewZoomTextOnlyAction;
    QAction *m_viewSourceAction;
    QAction *m_viewFullScreenAction;

    HistoryMenu *m_historyMenu;
    QAction *m_historyBackAction;
    QAction *m_historyForwardAction;
    QAction *m_historyHomeAction;
    QAction *m_historyRestoreLastSessionAction;

    BookmarksMenuBarMenu *m_bookmarksMenu;
    QAction *m_bookmarksShowAllAction;
    QAction *m_bookmarksAddAction;

    QMenu *m_windowMenu;

    QMenu *m_toolsMenu;
    QAction *m_toolsWebSearchAction;
    QAction *m_toolsClearPrivateDataAction;
    QAction *m_toolsShowNetworkMonitor;
    QAction *m_toolsEnableInspector;

    QMenu *m_helpMenu;
    QAction *m_helpChangeLanguageAction;
    QAction *m_helpAboutQtAction;
    QAction *m_helpAboutApplicationAction;

    // Toolbar
    QToolBar *m_navigationBar;
    QMenu *m_historyBackMenu;
    QMenu *m_historyForwardMenu;
    QAction *m_stopReloadAction;
    QIcon m_reloadIcon;
    QIcon m_stopIcon;
    QSplitter *m_navigationSplitter;
    ToolbarSearch *m_toolbarSearch;
#if defined(Q_WS_MAC)
    QFrame *m_bookmarksToolbarFrame;
#endif
    BookmarksToolBar *m_bookmarksToolbar;

    TabWidget *m_tabWidget;

    AutoSaver *m_autoSaver;
    bool m_menuBarVisible;
    bool m_statusBarVisible;
};

#endif // BROWSERMAINWINDOW_H

