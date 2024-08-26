#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <utility>
#include <QMessageBox>
#include <QEvent>
#include "mahjong.h"
#include "ui_mainwindow.h"

#define INPUT_MAIN 1
#define INPUT_SIDE 2
#define INPUT_ANKANG 3

#define INPUT_TONG 1
#define INPUT_TIAO 2
#define INPUT_WAN 3
#define INPUT_FENG 4

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
    void on_clear_mainmahjong_clicked();
    void on_clear_sidemahjong_clicked();
    void on_clear_ankangmahjong_clicked();
    void on_clear_all_clicked();

    void on_switch_TONG_clicked();
    void on_switch_TIAO_clicked();
    void on_switch_WAN_clicked();
    void on_switch_FENG_clicked();

    void on_start_ting_clicked();

private:
    Ui::MainWindow *ui;

    now_mahjongs Now_mahjong;
    void input_mahjong(int button_input);
    void input_main_mahjong(int button_input);
    void input_side_mahjong(int button_input);
    void input_ankang_mahjong(int button_input);

    std::map<std::pair<int, int>, QString> Mahjong_show_unicode;
    void make_Mahjong_show_unicode(void);

    int now_input;
    int now_switch;

    int temp_num_sideMahjong;
    std::vector<mahjong> temp_side;
    int main_num;
    int side_num;
    int ankang_num;

protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (event->type() == QEvent::FocusIn) {
            if (watched == ui->view_mainmahjong) {
                now_input = INPUT_MAIN;
            }
            else if (watched == ui->view_sidemahjong) {
                now_input = INPUT_SIDE;
            }
            else if (watched == ui->view_ankangmahjong) {
                now_input = INPUT_ANKANG;
            }
            return true; // 阻止事件继续传播
        }
        return QMainWindow::eventFilter(watched, event);
    }
};
#endif // MAINWINDOW_H
