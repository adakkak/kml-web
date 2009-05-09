#ifndef KMLWEB_H
#define KMLWEB_H

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QRegExp>
#include <QFileInfo>
#include <QTextStream>

namespace Ui
{
    class KMLWeb;
}

class KMLWeb : public QMainWindow
{
    Q_OBJECT

public:
    KMLWeb(QWidget *parent = 0);
    ~KMLWeb();

private:
    Ui::KMLWeb *ui;

private slots:
    void on_createButton_clicked();
    void on_browseHTMLButton_clicked();
    void on_browseKMLButton_clicked();
    QString createHTML(QString title, QString description, QString & kmlBase);
};

#endif // KMLWEB_H
