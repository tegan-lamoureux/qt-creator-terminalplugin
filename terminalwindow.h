/*
 * Copyright (C) 2012 Adam Treat. All rights reserved.
 */

#ifndef TERMINALWINDOW_H
#define TERMINALWINDOW_H

#include <coreplugin/outputwindow.h>
#include <coreplugin/ioutputpane.h>

QT_FORWARD_DECLARE_CLASS(QLabel);
QT_FORWARD_DECLARE_CLASS(QSettings);
QT_FORWARD_DECLARE_CLASS(QVBoxLayout);
QT_FORWARD_DECLARE_CLASS(QTermWidget);
QT_FORWARD_DECLARE_CLASS(QToolButton);

namespace Terminal {
namespace Internal {

class TerminalContainer : public QWidget
{
    Q_OBJECT

public:
    TerminalContainer(QWidget *parent);
    void initializeTerm(const QString & workingDirectory = QString());

    QTermWidget *termWidget() const { return m_termWidget; }

signals:
    void termWidgetChanged(QTermWidget * termWdiget);
    void finished();

private slots:
    void contextMenuRequested(const QPoint &);
    void copyAvailable(bool);
    void copyInvoked();
    void pasteInvoked();
    void closeInvoked();

private:
    QVBoxLayout *m_layout;
    QTermWidget *m_termWidget;
    QAction *m_copy;
    QAction *m_paste;
    QAction *m_close;
    QWidget *m_parent;
	QString currentColorScheme; // FIXME: change to m_, also switch to QSettings for persistence and config
								//        also font settings.
};

class TerminalWindow : public Core::IOutputPane
{
    Q_OBJECT

public:
    TerminalWindow(QObject *parent = 0);

    // Pure virtual in IOutputPane
    virtual QWidget *outputWidget(QWidget *parent);
    virtual QList<QWidget *> toolBarWidgets() const;
    virtual QString displayName() const;
    virtual int priorityInStatusBar() const;
    virtual void clearContents();
    virtual void visibilityChanged(bool visible);
    virtual void setFocus();
    virtual bool hasFocus() const;
    virtual bool canFocus() const;
    virtual bool canNavigate() const;
    virtual bool canNext() const;
    virtual bool canPrevious() const;
    virtual void goToNext();
    virtual void goToPrev();

private slots:
    void terminalFinished();
    void sync();

private:
    QString currentDocumentPath() const;
    Core::IContext *m_context;
    TerminalContainer *m_terminalContainer;
    QToolButton *m_sync;
};

} // namespace Internal
} // namespace Terminal

#endif // TERMINALWINDOW_H
