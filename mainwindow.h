#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:
  void selected_method();
  void on_changed();
  void on_clicked_1();
  void on_clicked_2();
  void update_res();

private:
    Ui::MainWindow *ui;
    QRegExpValidator key_A_valid, key_B_valid, message_valid; // Валидаторы для исходного сообщения и ключей
};
#endif // MAINWINDOW_H
