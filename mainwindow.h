#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDirIterator>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_button_input_clicked();
    void on_button_output_clicked();
    void on_text_output_textChanged(const QString &arg1);
    void on_text_input_textChanged(const QString &arg1);
    void on_button_yes_clicked();
    void on_button_no_clicked();

    void scan(QString path);
    void next();
    void openPreview(const QString path);


    void on_button_preview_clicked();

private:
    Ui::MainWindow *ui;
    QDir dir;
    QDir target_dir;
    QStringList files;
    QString current;
    QSettings settings;
};
#endif // MAINWINDOW_H
