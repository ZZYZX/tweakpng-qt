#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <zlib.h>
#include <png.h>

#include "table.h"

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    QTableView* table_view;
    TableModel* table_model;

    QString isItABirdIsItAPlane(QByteArray &blob);

protected:
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void updateWindowTitle();

    void newFile();
    void open();
    void save();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void bold();
    void italic();
    void leftAlign();
    void rightAlign();
    void justify();
    void center();
    void setLineSpacing();
    void setParagraphSpacing();
    void about();
    void aboutQt();

private:
    void createActions();
    void createMenus();

    // XXX convert below to a struct
    QString filename; // name of the currently open file
    int fileSize; // bytesize of the current file
    QByteArray fileBlob;
    bool fileHasUnsavedChanges;

    QString lastUsedPath; // last used path

    QLabel *statusLabel; // status bar permanent value

    // Main window top-level toolbar menu
    QMenu *fileMenu;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *exitAct;
    QMenu *editMenu;
        QAction *undoAct;
        QAction *redoAct;
        QAction *cutAct;
        QAction *copyAct;
        QAction *pasteAct;
    QMenu *insertMenu;
    QMenu *optionsMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;
        QAction *helpContentsAct;
        QAction *aboutAct;
        QAction *aboutQtAct;

    QActionGroup *alignmentGroup;
    // QAction *boldAct;
    // QAction *italicAct;
    // QAction *leftAlignAct;
    // QAction *rightAlignAct;
    // QAction *justifyAct;
    // QAction *centerAct;
    // QAction *setLineSpacingAct;
    // QAction *setParagraphSpacingAct;

};

#endif
