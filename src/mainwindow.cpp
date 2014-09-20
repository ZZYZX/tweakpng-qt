#include <QtGui>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    // Set window icon
    QIcon icon(":/icon.svg"); 
    setWindowIcon(icon);

    // Initial window title
    updateWindowTitle();

    // Set window properties
    setMinimumSize(500, 240);
    resize(768, 360);

    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    // The main widget
    table_view = new QTableView;
    table_model = new ChunkTableModel;
    // table_view->setItemDelegate(new TableDelegate);
    table_view->setModel(table_model);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(table_view);
    widget->setLayout(layout);

    createActions();
    createMenus();

    // Status bar info
    statusLabel = new QLabel(this);
    statusLabel->setText(tr("XXX PNG file size or hint to open/drag a new file XXX"));
    statusBar()->addPermanentWidget(statusLabel, 1);
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(editAct);
    menu.addAction(deleteAct);
    menu.addAction(moveUpAct);
    menu.addAction(moveDownAct);
    menu.addSeparator();
    menu.addAction(cutAct);
    menu.addAction(copyAct);
    menu.addAction(pasteAct);
    menu.exec(event->globalPos());
}

void MainWindow::newFile()
{
   (new MainWindow())->show();
   // XXX Find out if it's going to occupy memory of the parent instance
}

void MainWindow::open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open a new image file"),
                               lastUsedPath, tr("PNG files (*.png *.apng *.mng *.jng);;All files (*.*)"));

    // Don't continue in case
    // the window was closed
    if(filePath.isEmpty()) return;

/////////////////////////////////////

    QString fileType;
    QFileInfo fileInfo = QFileInfo(filePath);

    // Breadcrumbs
    lastUsedPath = fileInfo.path();



    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    fileBlob = file.readAll();
    file.close();



    if ((fileType = isItABirdIsItAPlane(fileBlob)) != "") { // XXX && is either PNG, APNG, MNG or JNG

        // movie->stop();
        // movieLabel->setMovie(movie);
        // movie->setFileName(fileName);
        // movie->start();

        filename = fileInfo.fileName();

        fileSize = fileInfo.size();

        // updateFrameSlider();
        // updateButtons();
        updateWindowTitle();

        statusLabel->setText(
                QString("%1 file size: %2 %3")
                    .arg(fileType) // XXX tr()
                    .arg(fileSize)
                    .arg( tr((fileSize == 1) ? "byte" : "bytes") )
            );
    } else {
        statusLabel->setText(QString("Couldn't open file %1").arg(fileInfo.fileName()));
    }
}

void MainWindow::save()
{
    // statusLabel->setText(tr("Invoked <b>File|Save</b>"));
}

void MainWindow::undo()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Undo</b>"));
}

void MainWindow::redo()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Redo</b>"));
}

void MainWindow::cut()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void MainWindow::copy()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void MainWindow::paste()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void MainWindow::bold()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Bold</b>"));
}

void MainWindow::italic()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Italic</b>"));
}

void MainWindow::leftAlign()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Left Align</b>"));
}

void MainWindow::rightAlign()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Right Align</b>"));
}

void MainWindow::justify()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Justify</b>"));
}

void MainWindow::center()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Center</b>"));
}

void MainWindow::setLineSpacing()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Set Line Spacing</b>"));
}

void MainWindow::setParagraphSpacing()
{
    // statusLabel->setText(tr("Invoked <b>Edit|Format|Set Paragraph Spacing</b>"));
}

void MainWindow::about()
{
    // statusLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About TweakPNG"),
            tr("TweakPNG is a PNG image file manipulation utility\r\n\r\n"
               ""));
}

void MainWindow::aboutQt()
{
    // statusLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions()
{
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    reOpenAct = new QAction(tr("&Repen"), this);
    connect(reOpenAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("&Save As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(save()));

    closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcuts(QKeySequence::Close);
    connect(closeAct, SIGNAL(triggered()), this, SLOT(close()));

    checkValidAct = new QAction(tr("&Check Validity"), this);
    connect(checkValidAct, SIGNAL(triggered()), this, SLOT(open()));

    fileSigAct = new QAction(tr("&File signature..."), this);
    connect(fileSigAct, SIGNAL(triggered()), this, SLOT(close()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));


    // undoAct = new QAction(tr("&Undo"), this);
    // undoAct->setShortcuts(QKeySequence::Undo);
    // connect(undoAct, SIGNAL(triggered()), this, SLOT(undo()));

    // redoAct = new QAction(tr("&Redo"), this);
    // redoAct->setShortcuts(QKeySequence::Redo);
    // connect(redoAct, SIGNAL(triggered()), this, SLOT(redo()));

    editAct = new QAction(tr("Edit Chunk..."), this);
    connect(editAct, SIGNAL(triggered()), this, SLOT(cut()));

    deleteAct = new QAction(tr("Delete"), this);
    connect(deleteAct, SIGNAL(triggered()), this, SLOT(cut()));

    moveUpAct = new QAction(tr("Move Up"), this);
    connect(moveUpAct, SIGNAL(triggered()), this, SLOT(copy()));

    moveDownAct = new QAction(tr("Move Down"), this);
    connect(moveDownAct, SIGNAL(triggered()), this, SLOT(paste()));

    cutAct = new QAction(tr("Cu&t"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));

    copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));

    pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));

/*
    boldAct = new QAction(tr("&Bold"), this);
    boldAct->setCheckable(true);
    boldAct->setShortcut(QKeySequence::Bold);
    connect(boldAct, SIGNAL(triggered()), this, SLOT(bold()));

    QFont boldFont = boldAct->font();
    boldFont.setBold(true);
    boldAct->setFont(boldFont);

    italicAct = new QAction(tr("&Italic"), this);
    italicAct->setCheckable(true);
    italicAct->setShortcut(QKeySequence::Italic);
    connect(italicAct, SIGNAL(triggered()), this, SLOT(italic()));

    QFont italicFont = italicAct->font();
    italicFont.setItalic(true);
    italicAct->setFont(italicFont);

    setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    connect(setLineSpacingAct, SIGNAL(triggered()), this, SLOT(setLineSpacing()));

    setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    connect(setParagraphSpacingAct, SIGNAL(triggered()),
            this, SLOT(setParagraphSpacing()));
*/

    helpContentsAct = new QAction(tr("&Help Contents"), this);
    // helpContentsAct->setShortcut(tr("F1"));
    connect(helpContentsAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutAct = new QAction(tr("&About..."), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));


/*
    leftAlignAct = new QAction(tr("&Left Align"), this);
    leftAlignAct->setCheckable(true);
    leftAlignAct->setShortcut(tr("Ctrl+L"));
    connect(leftAlignAct, SIGNAL(triggered()), this, SLOT(leftAlign()));

    rightAlignAct = new QAction(tr("&Right Align"), this);
    rightAlignAct->setCheckable(true);
    rightAlignAct->setShortcut(tr("Ctrl+R"));
    connect(rightAlignAct, SIGNAL(triggered()), this, SLOT(rightAlign()));

    justifyAct = new QAction(tr("&Justify"), this);
    justifyAct->setCheckable(true);
    justifyAct->setShortcut(tr("Ctrl+J"));
    connect(justifyAct, SIGNAL(triggered()), this, SLOT(justify()));

    centerAct = new QAction(tr("&Center"), this);
    centerAct->setCheckable(true);
    centerAct->setShortcut(tr("Ctrl+E"));
    connect(centerAct, SIGNAL(triggered()), this, SLOT(center()));

    alignmentGroup = new QActionGroup(this);
    alignmentGroup->addAction(leftAlignAct);
    alignmentGroup->addAction(rightAlignAct);
    alignmentGroup->addAction(justifyAct);
    alignmentGroup->addAction(centerAct);
    leftAlignAct->setChecked(true);
*/
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(reOpenAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(checkValidAct);
    fileMenu->addAction(fileSigAct);
    // MENUITEM "Check &Validity\tF5",         ID_CHECKPNG
    // MENUITEM "&File Signature...",          ID_SIGNATURE
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(editAct);
    editMenu->addAction(deleteAct);
    editMenu->addAction(moveUpAct);
    editMenu->addAction(moveDownAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    // MENUITEM SEPARATOR
    // MENUITEM "Combine Selected IDAT ",      ID_COMBINEIDAT
    // MENUITEM "Combine All &IDAT",           ID_COMBINEALLIDAT
    // MENUITEM "Split IDAT...",               ID_SPLITIDAT
    editMenu->addSeparator();
    // MENUITEM "Import Chunk...",             ID_IMPORTCHUNK
    // MENUITEM "Export Chunk...",             ID_EXPORTCHUNK
    // MENUITEM "Import ICC Profile...",       ID_IMPORTICCPROF
    // editMenu->addAction(undoAct);
    // editMenu->addAction(redoAct);

    insertMenu = menuBar()->addMenu(tr("&Insert"));
    // MENUITEM "acTL (APNG animation control)", ID_NEWACTL
    // MENUITEM "bKGD (Background color)",     ID_NEWBKGD
    // MENUITEM "cHRM (Chromaticities)",       ID_NEWCHRM
    // MENUITEM "fcTL (APNG frame control)",   ID_NEWFCTL
    // MENUITEM "gAMA (Gamma)",                ID_NEWGAMA
    // MENUITEM "IEND (End of image)",         ID_NEWIEND
    // MENUITEM "IHDR (Image header)",         ID_NEWIHDR
    // MENUITEM "oFFs (Image offset)",         ID_NEWOFFS
    // MENUITEM "pHYs (Pixel size, aspect ratio)", ID_NEWPHYS
    // MENUITEM "PLTE (Palette)",              ID_NEWPLTE
    // MENUITEM "sBIT (Significant bits per sample)", ID_NEWSBIT
    // MENUITEM "sCAL (Physical scale)",       ID_NEWSCAL
    // MENUITEM "sRGB (sRGB color space indicator)", ID_NEWSRGB
    // MENUITEM "sTER (Stereo image indicator)", ID_NEWSTER
    // MENUITEM "tEXt/zTXt/iTXt (Text)\tCtrl+T",    ID_NEWTEXT
    // MENUITEM "tIME (Time of last modification)", ID_NEWTIME
    // MENUITEM "tRNS (Transparency)",         ID_NEWTRNS
    // MENUITEM "vpAg (Virtual page)",         ID_NEWVPAG

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    // MENUITEM "&Preferences...",             ID_PREFS
    // MENUITEM "Configure &Tools...",         ID_EDITTOOLS

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    // MENUITEM "1",                           ID_TOOL_1
    // MENUITEM "2",                           ID_TOOL_2
    // MENUITEM "3",                           ID_TOOL_3
    // MENUITEM "4",                           ID_TOOL_4
    // MENUITEM "5",                           ID_TOOL_5
    // MENUITEM "6",                           ID_TOOL_6

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(helpContentsAct);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    // formatMenu = editMenu->addMenu(tr("&Format"));
    // formatMenu->addAction(boldAct);
    // formatMenu->addAction(italicAct);
    // formatMenu->addSeparator()->setText(tr("Alignment"));
    // formatMenu->addAction(leftAlignAct);
    // formatMenu->addAction(rightAlignAct);
    // formatMenu->addAction(justifyAct);
    // formatMenu->addAction(centerAct);
    // formatMenu->addSeparator();
    // formatMenu->addAction(setLineSpacingAct);
    // formatMenu->addAction(setParagraphSpacingAct);
}

void
MainWindow::updateWindowTitle()
{
    QString title = tr("TweakPNG");

    if(filename != "")
        title = filename + " - " + title;

    setWindowTitle(title);
}

QString
MainWindow::isItABirdIsItAPlane(QByteArray &blob)
{
    const char pngSignature[] = {(char)0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    const char mngSignature[] = {(char)0x8A, 0x4D, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    const char jngSignature[] = {(char)0x8B, 0x4A, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

    if(blob.startsWith(pngSignature)) {
        // return "APNG"; // it's APNG

        return "PNG"; // it's PNG
    } else if(blob.startsWith(mngSignature)) {
        return "MNG"; // it's MNG
    } else if(blob.startsWith(jngSignature)) {
        return "JNG"; // it's JNG
    }

    return "";
}

