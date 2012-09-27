/* $Id$
 * Copyright (c) 2012, Robert J. Hansen <rjh@secret-alchemy.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QFileInfo>
#include <QThread>
#include <QMutex>
#include <QTreeWidgetItem>
#include <QCryptographicHash>
#include <QDebug>

#include <vector>
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow;
class Worker;

class FileMetaInformation
{
friend class Worker;
public:
    FileMetaInformation(QString filename) :
        fn(filename),
        hashValue("(could not access file)"),
        modificationDate(QDateTime::fromString("12 31 2999", "MM dd yyyy")),
        presentInNSRL(false)
    {
        QFile f(filename);
        QCryptographicHash engine(QCryptographicHash::Md5);

        if (! f.open(QIODevice::ReadOnly))
        {
            return;
        }

        modificationDate = QFileInfo(filename).lastModified();

        while (!f.atEnd())
            engine.addData(f.read(1 << 20));

        hashValue = QString(engine.result().toHex());
    }

    FileMetaInformation(QString filename,
                        QString hash,
                        QString modified,
                        QString present) :
        fn(filename),
        hashValue(hash),
        modificationDate(QDateTime::fromString(modified, "MM dd yyyy")),
        presentInNSRL((present.left(1) == "t") ? true : false)
    {
    }

    const QString& filename() const { return fn; }
    const QString& hash() const { return hashValue; }
    const QDateTime& modified() const { return modificationDate; }
    bool inNSRL() const { return presentInNSRL; }
private:
    QString fn;
    QString hashValue;
    QDateTime modificationDate;
    bool presentInNSRL;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void doActionNew();
    void doActionOpen();
    void doActionClose();
    void doActionSave();
    void doActionSaveAs();
    void doActionQuit();
    void doActionHelpIndex();
    void doActionAbout();
    void doActionExportAsCSV();
    void toggleClicked(int);
    void dateEditChanged(QDateTime);
    void itemDoubleClicked(QTreeWidgetItem* item, int column);
    void updateMessage(QString message);
    void updateFileMetaInformation(std::vector<FileMetaInformation>* ptr);

private:
    void updateUI();
    void updateTreeWidget();
    QTreeWidgetItem* getItemForPath(QString path);
    Ui::MainWindow *ui;
    bool hasUnsavedData;
    QString saveAsFilename;
    std::vector<FileMetaInformation> files;
    std::map<QString, QTreeWidgetItem*> itemMap;
    Worker* worker;
};

class Worker : public QThread
{
    Q_OBJECT
public:
    Worker(QString& path) :
        root(path)
    {}
    void run();
signals:    
    void updateMessage(QString message);
    void updateFileMetaInformation(std::vector<FileMetaInformation>* ptr);

private:
    QStringList getFilenames();
    const QString root;
};

#endif // MAINWINDOW_H
