#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QProcess>
#include <QDateTime>
#include <QFileInfo>
#include <QThread>
#include <vector>
#include <map>
#include <QTreeWidgetItem>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow;

class FileMetaInformation
{
friend class MainWindow;
public:
    FileMetaInformation(QString filename, QString md5) :
        fn(filename),
        hashValue(md5),
        modificationDate(QFileInfo(filename).lastModified()),
        presentInNSRL(false)
    {
    }
    const QString& filename() const { return fn; }
    const QString& hash() const { return hashValue; }
    const QDateTime& modified() const { return modificationDate; }
    bool inNSRL() const { return presentInNSRL; }
private:
    FileMetaInformation(QString filename, QString md5, QString dateTime,
                        QString inNSRL) :
        fn(filename),
        hashValue(md5),
        modificationDate(QDateTime::fromString(dateTime, "MM dd yyyy")),
        presentInNSRL(false)
    {
        if (inNSRL.left(1) == "t" || inNSRL.left(1) == "T")
        {
            presentInNSRL = true;
        }
    }

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
    void md5deepStarted();
    void processMd5deepOutput();
    void md5deepEnded(int code);
    void nsrllookupStarted();
    void processNsrllookupOutput();
    void nsrllookupEnded(int code);
    void updateFractionComplete(int frac);
    void toggleClicked(int);
    void dateEditChanged(QDateTime);
    void itemDoubleClicked(QTreeWidgetItem* item, int column);

private:
    void updateUI();
    void updateTreeWidget();
    QTreeWidgetItem* getItemForPath(QString path);
    Ui::MainWindow *ui;
    const static QString md5deep_path;
    const static QString nsrllookup_path;
    unsigned long fileCount;
    QString currentFile;
    QProcess *md5deep;
    QProcess *nsrllookup;
    QString data;
    QString nsrldata;
    bool hasUnsavedData;
    QString saveAsFilename;
    QTimer* timer;
    std::vector<FileMetaInformation> files;
    std::map<QString, QTreeWidgetItem*> itemMap;
};

class ModificationTimeWorker : public QThread
{
    friend class MainWindow;
    Q_OBJECT
public:
    ModificationTimeWorker(const QString fromMd5deep,
                           std::vector<FileMetaInformation>& f) :
        md5deep(fromMd5deep),
        files(f)
    {}
    void run();
signals:
    void completedSome(int frac);

private:
    const QString md5deep;
    std::vector<FileMetaInformation>& files;
};

#endif // MAINWINDOW_H
