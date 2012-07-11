#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <algorithm>
#include <map>
#include <QDesktopServices>
#include <QUrl>

#ifdef WIN32
#include <windows.h>
#endif

using std::cout;
using std::cerr;

using std::vector;
using std::count;
using std::map;
using std::make_pair;

namespace {
QString getPathToMd5deep()
{
#ifdef WIN32
    BOOL isWow64 = FALSE;
    IsWow64Process(GetCurrentProcess(), &isWow64);
    return QString(isWow64 ? "executables/md5deep64.exe"
                           : "executables/md5deep.exe");
#else
    return QString("executables/md5deep");
#endif
}

QString getPathToNsrllookup()
{
#ifdef WIN32
    return QString("executables/nsrllookup.exe");
#else
    return QString("executables/nsrllookup");
#endif
}
}

const QString MainWindow::md5deep_path = getPathToMd5deep();
const QString MainWindow::nsrllookup_path = getPathToNsrllookup();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileCount(0),
    currentFile(),
    md5deep(0),
    nsrllookup(0),
    data(),
    hasUnsavedData(false),
    saveAsFilename(),
    timer(0)
{
    ui->setupUi(this);
    connect(ui->actionAbout_Duffy, SIGNAL(triggered()), this, SLOT(doActionAbout()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(doActionClose()));
    connect(ui->actionHelp_index, SIGNAL(triggered()), this, SLOT(doActionHelpIndex()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(doActionNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(doActionOpen()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(doActionQuit()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(doActionSave()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(doActionSaveAs()));
    connect(ui->knownToggle, SIGNAL(activated(int)), SLOT(toggleClicked(int)));
    connect(ui->fileType, SIGNAL(activated(int)), SLOT(toggleClicked(int)));
    connect(ui->dateEdit, SIGNAL(dateTimeChanged(QDateTime)), SLOT(dateEditChanged(QDateTime)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            SLOT(itemDoubleClicked(QTreeWidgetItem*, int)));
    updateUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/** Callback for double clicking on a row in the QTreeWidget.
  *
  * Side effects: attempts to open a remote URL, updates the UI.
  *
  * Error handling: none
  *
  * Postcondition: none
  *
  * @pre item must not be null
  * @return void
  */
void MainWindow::itemDoubleClicked(QTreeWidgetItem *item, int)
{
    if (0 == item)
    {
        updateUI();
        return;
    }
    if (item->text(2).isNull() || item->text(2) == "")
    {
        return;
    }
    QUrl url("https://www.google.com/search?as_q=" + item->text(2));
    QDesktopServices::openUrl(url);
}

/** Callback for changing the date within the QDateEdit widget.
  *
  * Side effects: updates the UI.
  *
  * Error handling: none
  *
  * Postcondition: none
  *
  * @pre None
  * @return void
  */
void MainWindow::dateEditChanged(QDateTime)
{
    this->updateUI();
}

/** Callback for clicking on either of the two combo boxes.
  *
  * Side effects: updates the UI.
  *
  * Error handling: none
  *
  * Postcondition: none
  *
  * @pre None
  * @return void
  */
void MainWindow::toggleClicked(int)
{
    this->updateTreeWidget();
}

/** Updates the user interface to reflect the current state
  * of the application.
  *
  * Side effects: updates the UI
  *
  * Error handling: none
  *
  * Postcondition: none
  *
  * @pre None
  * @return void
  */
void MainWindow::updateUI()
{
    if (0 != files.size())
    {
        ui->actionClose->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->actionSave_as->setEnabled(true);
    } else {
        ui->actionClose->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->actionSave_as->setEnabled(false);
    }
    updateTreeWidget();
}

/** Displays information about the application.
  *
  * Side effects: displays a window
  *
  * Error handling: none
  *
  * Postcondition: none
  *
  * @pre None
  * @return void
  */
void MainWindow::doActionAbout()
{
    QMessageBox::about(this, "About Sgt. Duffy",
                       "Sgt. Duffy 0.9.1 is (c) 2012, Robert J. Hansen <rjh@sixdemonbag.org>.\n\n"
                       "You are free to use, share and modify this program in accordance with\n"
                       "the ISC License.\n\n"
                       "Sgt. Duffy uses parts of Jesse Kornblum's md5deep suite.  md5deep is\n"
                       "in the public domain.\n\n"
                       "Sgt. Duffy is named after the intrepid analyst from Infocom's series\n"
                       "of classic mystery games.");
    return;
}

void MainWindow::doActionClose()
{
    if (0 == ui->treeWidget->topLevelItemCount())
        return;
    if (hasUnsavedData)
    {
        QMessageBox::StandardButton btn;

        btn = QMessageBox::question(this,
                                    "",
                                    "Would you like to save this analysis?",
                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                    QMessageBox::Yes);
        if (btn == QMessageBox::Yes)
        {
            doActionSave();
        }
        if (btn == QMessageBox::Cancel)
        {
            return;
        }
        files.clear();
        ui->treeWidget->clear();
        saveAsFilename = QString();
        hasUnsavedData = false;
        updateUI();
    }
}

void MainWindow::doActionHelpIndex()
{
    QUrl url("http://keyservers.org/~rjh/duffy");
    QDesktopServices::openUrl(url);
    return;
}

void MainWindow::md5deepEnded(int)
{
    md5deep = 0;
    ui->actionNew->setEnabled(true);
    ui->actionClose->setEnabled(true);
    ui->actionOpen->setEnabled(true);
    ui->actionSave->setEnabled(true);
    ui->actionSave_as->setEnabled(true);

    ui->showing->setEnabled(true);
    ui->changedSince->setEnabled(true);
    ui->knownToggle->setEnabled(true);
    ui->fileType->setEnabled(true);
    ui->dateEdit->setEnabled(true);

    ui->treeWidget->setEnabled(true);

    files.clear();

    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Updating modification times, 0% complete", 2500);

    ModificationTimeWorker* thread = new ModificationTimeWorker(data, files);
    connect(thread, SIGNAL(finished()), this, SLOT(nsrllookupStarted()));
    connect(thread, SIGNAL(completedSome(int)), this, SLOT(updateFractionComplete(int)));
    thread->start();
}

void MainWindow::updateFractionComplete(int frac)
{
    ui->statusBar->clearMessage();
    QString newmsg = QString("Updating modification times, ") + QString::number(frac) + QString("% complete");
    ui->statusBar->showMessage(newmsg, 2500);
    if (frac >= 100)
    {
        QStringList args;
        args << QString("-s") << QString("nsrl.kyr.us");
        nsrllookup = new QProcess(this);
        connect(nsrllookup, SIGNAL(started()), this, SLOT(nsrllookupStarted()));
        connect(nsrllookup, SIGNAL(readyReadStandardOutput()), this, SLOT(processNsrllookupOutput()));
        connect(nsrllookup, SIGNAL(finished(int)), this, SLOT(nsrllookupEnded(int)));
        nsrllookup->start(MainWindow::nsrllookup_path, args);
    }
}

void MainWindow::processMd5deepOutput()
{
    QByteArray barray = md5deep->readAllStandardOutput();
    data += QString::fromAscii(barray.data());
    fileCount += count(barray.begin(), barray.end(), '\n');

    ui->statusBar->clearMessage();
    QString filesProcessed = QString("md5deep: ") + QString::number(fileCount) + QString(" files processed");
    ui->statusBar->showMessage(filesProcessed);
}

void MainWindow::md5deepStarted()
{
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("md5deep: 0 files processed");
}

void MainWindow::doActionNew()
{
    fileCount = 0;
    QString root("");
#ifdef WIN32
    CHAR buf[1024];
    GetLogicalDriveStringsA(1024, buf);
    root = QString(*buf) + QString(":\\");
#else
    root = QString("/");
#endif
    if (hasUnsavedData)
    {
        {
            QMessageBox::StandardButton btn;

            btn = QMessageBox::question(this,
                                        "",
                                        "Would you like to save this analysis?",
                                        QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                        QMessageBox::Yes);
            if (btn == QMessageBox::Yes)
            {
                doActionSave();
            }
            if (btn == QMessageBox::Cancel)
            {
                return;
            }
        }
    }
    QString path = QFileDialog::getExistingDirectory(this, "Choose a directory", root);

    if (path.isNull() || path == "")
    {
        return;
    }

    files.clear();
    ui->treeWidget->clear();
    hasUnsavedData = false;
    updateUI();

    ui->actionNew->setEnabled(false);
    ui->actionClose->setEnabled(false);
    ui->actionOpen->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);

    QStringList args;
    args << QString("-r") << path;
    md5deep = new QProcess(this);
    connect(md5deep, SIGNAL(started()), this, SLOT(md5deepStarted()));
    connect(md5deep, SIGNAL(readyReadStandardOutput()), this, SLOT(processMd5deepOutput()));
    connect(md5deep, SIGNAL(finished(int)), this, SLOT(md5deepEnded(int)));
    md5deep->start(MainWindow::md5deep_path, args);

    return;
}

void MainWindow::doActionOpen()
{
    if (hasUnsavedData)
    {
        QMessageBox::StandardButton btn;

        btn = QMessageBox::question(this,
                                    "",
                                    "Would you like to save this analysis?",
                                    QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,
                                    QMessageBox::Yes);
        if (btn == QMessageBox::Yes)
        {
            doActionSave();
        }
        if (btn == QMessageBox::Cancel)
        {
            return;
        }
    }
    fileCount = 0;
    files.clear();
    ui->treeWidget->clear();
    hasUnsavedData = false;
    updateUI();
    QString filename = QFileDialog::getOpenFileName(this,
                                                    "Open a Duffy file",
                                                    QString(),
                                                    "Duffy files (*.dfy)");
    if (filename.isNull())
    {
        return;
    }
    saveAsFilename = filename;
    QFile infile(saveAsFilename);
    if (! infile.open(QFile::ReadOnly|QFile::Text))
    {
        QMessageBox::warning(this, "Error", "A disk error occurred.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    files.clear();
    while (! infile.atEnd())
    {
        QString fn(QString::fromAscii(infile.readLine()));
        QString hash(QString::fromAscii(infile.readLine()));
        QString date(QString::fromAscii(infile.readLine()));
        QString inNSRL(QString::fromAscii(infile.readLine()));

        fn = fn.left(fn.size() - 1);
        hash = hash.left(hash.size() - 1);
        date = date.left(date.size() - 1);
        inNSRL = inNSRL.left(1);

        files.push_back(FileMetaInformation(fn, hash, date, inNSRL));
    }
    updateTreeWidget();
    updateUI();
}

void MainWindow::doActionQuit()
{
    qApp->quit();
    return;
}

void MainWindow::doActionSave()
{
    if (files.size() == 0)
    {
        return;
    }

    if (saveAsFilename.isNull() || saveAsFilename == "")
    {
        doActionSaveAs();
        return;
    }
    QFile file(saveAsFilename);
    if (! file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QMessageBox::warning(this,
                             "Couldn't save file",
                             "A disk error of some sort occurred.",
                             QMessageBox::Ok,
                             QMessageBox::Ok);
        saveAsFilename = "";
    }
    for (size_t i = 0 ; i < files.size() ; i++) {
        const FileMetaInformation& fmi = files[i];
        file.write(fmi.filename().toAscii());
        file.write("\n");
        file.write(fmi.hash().toAscii());
        file.write("\n");
        file.write(fmi.modified().toString("MM dd yyyy").toAscii());
        file.write("\n");
        file.write(fmi.inNSRL() ? "true" : "false");
        file.write("\n");
    }
    hasUnsavedData = false;
}

void MainWindow::doActionSaveAs()
{
    saveAsFilename = QFileDialog::getSaveFileName(this, "Save as", QString(), "Duffy files (*.dfy)");
    if (!saveAsFilename.isNull()) doActionSave();
}

void MainWindow::nsrllookupStarted()
{
    nsrldata = QString();
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Checking with nsrl.kyr.us...");
    nsrllookup->write(data.toAscii());
    nsrllookup->write("\x1A");
    data = QString();
}

void MainWindow::processNsrllookupOutput()
{
    if (0 == nsrllookup)
    {
        return;
    }
    QByteArray barray = nsrllookup->readAllStandardOutput();
    nsrldata += QString::fromAscii(barray.data());
}

void MainWindow::nsrllookupEnded(int)
{
    nsrllookup = 0;
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage("Analysis finished");
    QStringList as_list = nsrldata.split("\n");
    nsrldata = QString();
    QStringList::iterator qsiter = as_list.begin();
    vector<FileMetaInformation>::iterator viter = files.begin();

    while (qsiter != as_list.end())
    {
        QString notInNsrlFilename = qsiter->right(qsiter->size() - 34);
        notInNsrlFilename = notInNsrlFilename.left(notInNsrlFilename.size() - 1);
        while (viter != files.end() && viter->filename() != notInNsrlFilename)
        {
            viter->presentInNSRL = true;
            ++viter;
        }
        ++qsiter;
        if (viter != files.end())
        {
            ++viter;
        }
    }

    hasUnsavedData = true;
    fileCount = 0;
    updateTreeWidget();
}

void MainWindow::updateTreeWidget()
{
    vector<FileMetaInformation>::iterator viter = files.begin();
    itemMap.clear();
    ui->treeWidget->clear();

    bool show_unknowns = (ui->knownToggle->currentIndex()) ? true : false;
    bool showAllFiles = (ui->fileType->currentIndex()) ? false : true;
    QDateTime since = (ui->dateEdit->dateTime());

    for ( ; viter != files.end() ; ++viter)
    {
        const FileMetaInformation& fmi = *viter;
        const QDateTime& modified = fmi.modified();
        const QString& fn = fmi.filename();
        const QString& hash = fmi.hash();
        bool is_unknown = ! fmi.inNSRL();

        if ((is_unknown != show_unknowns) || (modified < since))
        {
            continue;
        }

        QStringList pathParts = fn.split("\\");
        QString bareName = pathParts.last();
        QString extension = bareName.split(".").last();

        bool isExecutable = (extension == "EXE") ||
                (extension == "exe") ||
                (extension == "DLL") ||
                (extension == "dll") ||
                (extension == "COM") ||
                (extension == "com");
        if (!bareName.isNull() && bareName != "")
        {
            if (! showAllFiles && !isExecutable)
            {
                continue;
            }
        }

        pathParts.removeLast();
        QString justThePath = pathParts.join("\\") + "\\";
        QTreeWidgetItem* pathItem = getItemForPath(justThePath);
        QTreeWidgetItem* item = new QTreeWidgetItem(pathItem);
        item->setText(0, bareName);
        item->setText(1, modified.toString("MMM d, yyyy"));
        item->setText(2, hash);
    }
    ui->treeWidget->expandAll();
    ui->treeWidget->resizeColumnToContents(0);
    ui->treeWidget->resizeColumnToContents(1);
    ui->treeWidget->resizeColumnToContents(2);
}

QTreeWidgetItem* MainWindow::getItemForPath(QString path)
{
    if (path.right(1) != QString("\\"))
    {
        path += "\\";
    }
    QStringList pathParts = path.split("\\");
    // drop the null element on the end
    pathParts.removeLast();

    if (itemMap.end() != itemMap.find(path))
    {
        return itemMap[path];
    }

    if (pathParts.size() == 1)
    {
        QTreeWidgetItem* qti = new QTreeWidgetItem(ui->treeWidget);
        qti->setText(0, path);
        ui->treeWidget->addTopLevelItem(qti);
        itemMap.insert(make_pair(path, qti));
        return qti;
    }

    QString parentPath = "";
    for (int i = 0 ; i < pathParts.size() - 1 ; i += 1)
    {
        parentPath += pathParts[i] + "\\";
    }
    QTreeWidgetItem* parentItem = getItemForPath(parentPath);
    QTreeWidgetItem* thisItem = new QTreeWidgetItem(parentItem);
    thisItem->setText(0, pathParts.last() + "\\");
    itemMap.insert(make_pair(pathParts.join("\\") + "\\", thisItem));
    return thisItem;
}

void ModificationTimeWorker::run()
{
    QStringList entries = md5deep.split("\n");
    int updateEvery = 1;
    if (entries.size() > 100) {
        updateEvery = entries.size() / 100;
    }
    for (int i = 0 ; i < entries.size() ; i += 1)
    {
        const QString& entry = entries[i];
        if (entry.size() <= 34)
        {
            continue;
        }
        QString hash = entry.left(32);
        QString filename = entry.right(entry.size() - 34);
        filename = filename.left(filename.size() - 1);
        files.push_back(FileMetaInformation(filename, hash));

        if (i && (0 == i % updateEvery))
        {
            int frac = i / updateEvery;
            emit completedSome(frac);
        }
    }
    emit completedSome(100);
}
