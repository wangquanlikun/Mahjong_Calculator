#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("立直麻将计算器"));

    temp_num_sideMahjong = 0;
    main_num = 0;
    side_num = 0;
    ankang_num = 0;

    now_input = UNDEFINED;
    now_switch = UNDEFINED;
    ui->switch_TONG->setChecked(false);
    ui->switch_TIAO->setChecked(false);
    ui->switch_WAN->setChecked(false);
    ui->switch_FENG->setChecked(false);
    ui->Input_01->setEnabled(false);
    ui->Input_02->setEnabled(false);
    ui->Input_03->setEnabled(false);
    ui->Input_04->setEnabled(false);
    ui->Input_05->setEnabled(false);
    ui->Input_06->setEnabled(false);
    ui->Input_07->setEnabled(false);
    ui->Input_08->setEnabled(false);
    ui->Input_09->setEnabled(false);
    ui->Input_10->setEnabled(false);

    QFont font_Symbola("Symbola");
    font_Symbola.setPointSize(20);
    ui->view_mainmahjong->setFont(font_Symbola);
    ui->view_sidemahjong->setFont(font_Symbola);
    ui->view_ankangmahjong->setFont(font_Symbola);

    make_Mahjong_show_unicode();

    connect(ui->Input_01, &QPushButton::clicked, this, [this](){ input_mahjong(1); });
    connect(ui->Input_02, &QPushButton::clicked, this, [this](){ input_mahjong(2); });
    connect(ui->Input_03, &QPushButton::clicked, this, [this](){ input_mahjong(3); });
    connect(ui->Input_04, &QPushButton::clicked, this, [this](){ input_mahjong(4); });
    connect(ui->Input_05, &QPushButton::clicked, this, [this](){ input_mahjong(5); });
    connect(ui->Input_06, &QPushButton::clicked, this, [this](){ input_mahjong(6); });
    connect(ui->Input_07, &QPushButton::clicked, this, [this](){ input_mahjong(7); });
    connect(ui->Input_08, &QPushButton::clicked, this, [this](){ input_mahjong(8); });
    connect(ui->Input_09, &QPushButton::clicked, this, [this](){ input_mahjong(9); });
    connect(ui->Input_10, &QPushButton::clicked, this, [this](){ input_mahjong(10);});

    ui->view_mainmahjong->installEventFilter(this);
    ui->view_sidemahjong->installEventFilter(this);
    ui->view_ankangmahjong->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::make_Mahjong_show_unicode(void) {
    Mahjong_show_unicode[std::make_pair(TONG, 1)] = "🀙";
    Mahjong_show_unicode[std::make_pair(TONG, 2)] = "🀚";
    Mahjong_show_unicode[std::make_pair(TONG, 3)] = "🀛";
    Mahjong_show_unicode[std::make_pair(TONG, 4)] = "🀜";
    Mahjong_show_unicode[std::make_pair(TONG, 5)] = "🀝";
    Mahjong_show_unicode[std::make_pair(TONG, 6)] = "🀞";
    Mahjong_show_unicode[std::make_pair(TONG, 7)] = "🀟";
    Mahjong_show_unicode[std::make_pair(TONG, 8)] = "🀠";
    Mahjong_show_unicode[std::make_pair(TONG, 9)] = "🀡";

    Mahjong_show_unicode[std::make_pair(TIAO, 1)] = "🀐";
    Mahjong_show_unicode[std::make_pair(TIAO, 2)] = "🀑";
    Mahjong_show_unicode[std::make_pair(TIAO, 3)] = "🀒";
    Mahjong_show_unicode[std::make_pair(TIAO, 4)] = "🀓";
    Mahjong_show_unicode[std::make_pair(TIAO, 5)] = "🀔";
    Mahjong_show_unicode[std::make_pair(TIAO, 6)] = "🀕";
    Mahjong_show_unicode[std::make_pair(TIAO, 7)] = "🀖";
    Mahjong_show_unicode[std::make_pair(TIAO, 8)] = "🀗";
    Mahjong_show_unicode[std::make_pair(TIAO, 9)] = "🀘";

    Mahjong_show_unicode[std::make_pair(WAN, 1)] = "🀇";
    Mahjong_show_unicode[std::make_pair(WAN, 2)] = "🀈";
    Mahjong_show_unicode[std::make_pair(WAN, 3)] = "🀉";
    Mahjong_show_unicode[std::make_pair(WAN, 4)] = "🀊";
    Mahjong_show_unicode[std::make_pair(WAN, 5)] = "🀋";
    Mahjong_show_unicode[std::make_pair(WAN, 6)] = "🀌";
    Mahjong_show_unicode[std::make_pair(WAN, 7)] = "🀍";
    Mahjong_show_unicode[std::make_pair(WAN, 8)] = "🀎";
    Mahjong_show_unicode[std::make_pair(WAN, 9)] = "🀏";

    Mahjong_show_unicode[std::make_pair(DONG_FENG, UNDEFINED)] = "🀀";
    Mahjong_show_unicode[std::make_pair(NAN_FENG, UNDEFINED)] = "🀁";
    Mahjong_show_unicode[std::make_pair(XI_FENG, UNDEFINED)] = "🀂";
    Mahjong_show_unicode[std::make_pair(BEI_FENG, UNDEFINED)] = "🀃";
    Mahjong_show_unicode[std::make_pair(BAI, UNDEFINED)] = "🀆";
    Mahjong_show_unicode[std::make_pair(ZHONG, UNDEFINED)] = "🀄";
    Mahjong_show_unicode[std::make_pair(FA, UNDEFINED)] = "🀅";

    Mahjong_show_unicode[std::make_pair(MAHJONG_BACK, UNDEFINED)] = "🀫";
}

void MainWindow::on_clear_mainmahjong_clicked(){
    ui->view_mainmahjong->clear();
    Now_mahjong.clear_mahjongs(INPUT_MAIN);
    main_num = 0;
}

void MainWindow::on_clear_sidemahjong_clicked(){
    ui->view_sidemahjong->clear();
    Now_mahjong.clear_mahjongs(INPUT_SIDE);
    side_num = 0;
}

void MainWindow::on_clear_ankangmahjong_clicked(){
    ui->view_ankangmahjong->clear();
    Now_mahjong.clear_mahjongs(INPUT_ANKANG);
    ankang_num = 0;
}

void MainWindow::on_clear_all_clicked(){
    ui->view_mainmahjong->clear();
    ui->view_sidemahjong->clear();
    ui->view_ankangmahjong->clear();
    Now_mahjong.clear_mahjongs();
    main_num = 0;
    side_num = 0;
    ankang_num = 0;
}

void MainWindow::on_switch_TONG_clicked(){
    now_switch = INPUT_TONG;
    ui->switch_TONG->setChecked(true);
    ui->switch_TIAO->setChecked(false);
    ui->switch_WAN->setChecked(false);
    ui->switch_FENG->setChecked(false);

    ui->Input_01->setEnabled(true);
    ui->Input_02->setEnabled(true);
    ui->Input_03->setEnabled(true);
    ui->Input_04->setEnabled(true);
    ui->Input_05->setEnabled(true);
    ui->Input_06->setEnabled(true);
    ui->Input_07->setEnabled(true);
    ui->Input_08->setEnabled(true);
    ui->Input_09->setEnabled(true);
    ui->Input_10->setEnabled(false);

    ui->Input_01->setText("一筒 🀙");
    ui->Input_02->setText("二筒 🀚");
    ui->Input_03->setText("三筒 🀛");
    ui->Input_04->setText("四筒 🀜");
    ui->Input_05->setText("五筒 🀝");
    ui->Input_06->setText("六筒 🀞");
    ui->Input_07->setText("七筒 🀟");
    ui->Input_08->setText("八筒 🀠");
    ui->Input_09->setText("九筒 🀡");
    ui->Input_10->setText("");
}

void MainWindow::on_switch_TIAO_clicked(){
    now_switch = INPUT_TIAO;
    ui->switch_TONG->setChecked(false);
    ui->switch_TIAO->setChecked(true);
    ui->switch_WAN->setChecked(false);
    ui->switch_FENG->setChecked(false);

    ui->Input_01->setEnabled(true);
    ui->Input_02->setEnabled(true);
    ui->Input_03->setEnabled(true);
    ui->Input_04->setEnabled(true);
    ui->Input_05->setEnabled(true);
    ui->Input_06->setEnabled(true);
    ui->Input_07->setEnabled(true);
    ui->Input_08->setEnabled(true);
    ui->Input_09->setEnabled(true);
    ui->Input_10->setEnabled(false);

    ui->Input_01->setText("一条 🀐");
    ui->Input_02->setText("二条 🀑");
    ui->Input_03->setText("三条 🀒");
    ui->Input_04->setText("四条 🀓");
    ui->Input_05->setText("五条 🀔");
    ui->Input_06->setText("六条 🀕");
    ui->Input_07->setText("七条 🀖");
    ui->Input_08->setText("八条 🀗");
    ui->Input_09->setText("九条 🀘");
    ui->Input_10->setText("");
}

void MainWindow::on_switch_WAN_clicked(){
    now_switch = INPUT_WAN;
    ui->switch_TONG->setChecked(false);
    ui->switch_TIAO->setChecked(false);
    ui->switch_WAN->setChecked(true);
    ui->switch_FENG->setChecked(false);

    ui->Input_01->setEnabled(true);
    ui->Input_02->setEnabled(true);
    ui->Input_03->setEnabled(true);
    ui->Input_04->setEnabled(true);
    ui->Input_05->setEnabled(true);
    ui->Input_06->setEnabled(true);
    ui->Input_07->setEnabled(true);
    ui->Input_08->setEnabled(true);
    ui->Input_09->setEnabled(true);
    ui->Input_10->setEnabled(false);

    ui->Input_01->setText("一万 🀇");
    ui->Input_02->setText("二万 🀈");
    ui->Input_03->setText("三万 🀉");
    ui->Input_04->setText("四万 🀊");
    ui->Input_05->setText("五万 🀋");
    ui->Input_06->setText("六万 🀌");
    ui->Input_07->setText("七万 🀍");
    ui->Input_08->setText("八万 🀎");
    ui->Input_09->setText("九万 🀏");
    ui->Input_10->setText("");
}

void MainWindow::on_switch_FENG_clicked(){
    now_switch = INPUT_FENG;
    ui->switch_TONG->setChecked(false);
    ui->switch_TIAO->setChecked(false);
    ui->switch_WAN->setChecked(false);
    ui->switch_FENG->setChecked(true);

    ui->Input_01->setEnabled(true);
    ui->Input_02->setEnabled(true);
    ui->Input_03->setEnabled(true);
    ui->Input_04->setEnabled(true);
    ui->Input_05->setEnabled(true);
    ui->Input_06->setEnabled(true);
    ui->Input_07->setEnabled(true);
    ui->Input_08->setEnabled(false);
    ui->Input_09->setEnabled(false);
    ui->Input_10->setEnabled(false);

    ui->Input_01->setText("東风 🀀");
    ui->Input_02->setText("南风 🀁");
    ui->Input_03->setText("西风 🀂");
    ui->Input_04->setText("北风 🀃");
    ui->Input_05->setText("白  🀆");
    ui->Input_06->setText("中  🀄");
    ui->Input_07->setText("發  🀅");
    ui->Input_08->setText("");
    ui->Input_09->setText("");
    ui->Input_10->setText("");
}

void MainWindow::input_mahjong(int button_input){
    if(main_num + 3 * side_num + 3 * ankang_num >= 13 || (now_input == INPUT_SIDE && (main_num + 3 * side_num + 3 * ankang_num + 3) >= 14) || (now_input == INPUT_ANKANG && (main_num + 3 * side_num + 3 * ankang_num + 3) >= 14)){
        QMessageBox::about(this,"输入上限","不能再装入更多的牌了！");
        return;
    }

    if(now_input != UNDEFINED && now_switch != UNDEFINED){
        if(now_switch != INPUT_FENG){
            if(Now_mahjong.count_num[mahjong(now_switch, button_input).get_ID()] >= 4 || (now_input == INPUT_ANKANG && Now_mahjong.count_num[mahjong(now_switch, button_input).get_ID()] != 0)){
                QMessageBox::about(this,"输入上限","不能再装入更多的牌了！");
                return;
            }
        }
        else{
            if(Now_mahjong.count_num[mahjong(DONG_FENG + button_input - 1, UNDEFINED).get_ID()] >= 4 || (now_input == INPUT_ANKANG && Now_mahjong.count_num[mahjong(DONG_FENG + button_input - 1, UNDEFINED).get_ID()] != 0)){
                QMessageBox::about(this,"输入上限","不能再装入更多的牌了！");
                return;
            }
        }
    }

    switch(now_input){
    case UNDEFINED:
        break;
    case INPUT_MAIN:
        input_main_mahjong(button_input);
        break;
    case INPUT_SIDE:
        input_side_mahjong(button_input);
        break;
    case INPUT_ANKANG:
        input_ankang_mahjong(button_input);
        break;
    }
}

void MainWindow::input_main_mahjong(int button_input){
    switch(now_switch){
    case UNDEFINED:
        return;
    case INPUT_TONG:
        Now_mahjong.add_mahjong_main(mahjong(TONG, button_input));
        ui->view_mainmahjong->insertHtml(Mahjong_show_unicode[std::make_pair(TONG, button_input)]);
        break;
    case INPUT_TIAO:
        Now_mahjong.add_mahjong_main(mahjong(TIAO, button_input));
        ui->view_mainmahjong->insertHtml(Mahjong_show_unicode[std::make_pair(TIAO, button_input)]);
        break;
    case INPUT_WAN:
        Now_mahjong.add_mahjong_main(mahjong(WAN, button_input));
        ui->view_mainmahjong->insertHtml(Mahjong_show_unicode[std::make_pair(WAN, button_input)]);
        break;
    case INPUT_FENG:
        Now_mahjong.add_mahjong_main(mahjong(DONG_FENG + button_input - 1, UNDEFINED));
        ui->view_mainmahjong->insertHtml(Mahjong_show_unicode[std::make_pair(DONG_FENG + button_input - 1, UNDEFINED)]);
        break;
    }
    main_num ++;
}

void MainWindow::input_side_mahjong(int button_input){
    switch(now_switch){
    case UNDEFINED:
        return;
    case INPUT_TONG:
        temp_side.push_back(mahjong(TONG, button_input));
        ui->view_sidemahjong->insertHtml(Mahjong_show_unicode[std::make_pair(TONG, button_input)]);
        break;
    case INPUT_TIAO:
        temp_side.push_back(mahjong(TIAO, button_input));
        ui->view_sidemahjong->insertHtml(Mahjong_show_unicode[std::make_pair(TIAO, button_input)]);
        break;
    case INPUT_WAN:
        temp_side.push_back(mahjong(WAN, button_input));
        ui->view_sidemahjong->insertHtml(Mahjong_show_unicode[std::make_pair(WAN, button_input)]);
        break;
    case INPUT_FENG:
        temp_side.push_back(mahjong(DONG_FENG + button_input - 1, UNDEFINED));
        ui->view_sidemahjong->insertHtml(Mahjong_show_unicode[std::make_pair(DONG_FENG + button_input - 1, UNDEFINED)]);
        break;
    }

    temp_num_sideMahjong ++;
    if(temp_num_sideMahjong >= 3){
        //判断是否为一组合法副露
        bool ok = false;
        if(temp_side[0] == temp_side[1] && temp_side[1] == temp_side[2]){
            ok = true;
        }
        if((temp_side[0].type == temp_side[1].type && temp_side[1].type == temp_side[2].type) && (temp_side[0].num + 1 == temp_side[1].num && temp_side[1].num + 1 == temp_side[2].num)){
            ok = true;
        }

        if(ok){
            temp_num_sideMahjong = 0;
            Now_mahjong.add_mahjong_side(temp_side);
            temp_side.clear();
            ui->view_sidemahjong->insertHtml("&nbsp;");
            side_num ++;
        }else{
            QMessageBox::about(this,"输入错误","不是一组吃/碰所能形成的副露！请按顺序输入");
            temp_num_sideMahjong = 0;
            temp_side.clear();

            ui->view_sidemahjong->clear();
            for(const auto& it : Now_mahjong.get_now_mahjongs_side()){
                for(auto itt : it){
                    ui->view_sidemahjong->insertHtml(Mahjong_show_unicode[std::make_pair((int)itt.type, (int)itt.num)]);
                }
                ui->view_sidemahjong->insertHtml("&nbsp;");
            }
        }
    }
}

void MainWindow::input_ankang_mahjong(int button_input){
    switch(now_switch){
    case UNDEFINED:
        return;
    case INPUT_TONG:
        Now_mahjong.add_mahjong_AnKong(mahjong(TONG, button_input));
        ui->view_ankangmahjong->insertHtml("🀫" + Mahjong_show_unicode[std::make_pair(TONG, button_input)] + Mahjong_show_unicode[std::make_pair(TONG, button_input)] + "🀫");
        break;
    case INPUT_TIAO:
        Now_mahjong.add_mahjong_AnKong(mahjong(TIAO, button_input));
        ui->view_ankangmahjong->insertHtml("🀫" + Mahjong_show_unicode[std::make_pair(TIAO, button_input)] + Mahjong_show_unicode[std::make_pair(TIAO, button_input)] + "🀫");
        break;
    case INPUT_WAN:
        Now_mahjong.add_mahjong_AnKong(mahjong(WAN, button_input));
        ui->view_ankangmahjong->insertHtml("🀫" + Mahjong_show_unicode[std::make_pair(WAN, button_input)] + Mahjong_show_unicode[std::make_pair(WAN, button_input)] + "🀫");
        break;
    case INPUT_FENG:
        Now_mahjong.add_mahjong_AnKong(mahjong(DONG_FENG + button_input - 1, UNDEFINED));
        ui->view_ankangmahjong->insertHtml("🀫" + Mahjong_show_unicode[std::make_pair(DONG_FENG + button_input - 1, UNDEFINED)] + Mahjong_show_unicode[std::make_pair(DONG_FENG + button_input - 1, UNDEFINED)] + "🀫");
        break;
    }
    ui->view_ankangmahjong->insertHtml("&nbsp;");
    ankang_num ++;
}

void MainWindow::on_start_ting_clicked(){
    if(main_num + 3 * side_num + 3 * ankang_num < 13){
        QMessageBox::about(this,"输入不全","请输入您的全部手牌！");
        return;
    }

    std::vector<mahjong> mahjongs_waiting_for = Now_mahjong.waiting_for();
    bool can_win_soon = ((int)mahjongs_waiting_for.size() != 0);

    QMessageBox msg;
    QString msg_text;

    if(can_win_soon){
        msg_text = "听牌\n";
        for(auto it : mahjongs_waiting_for){
            msg_text += Mahjong_show_unicode[std::make_pair((int)it.type, (int)it.num)];
            msg_text += "×" + QString::number(4 - Now_mahjong.count_num[it.get_ID()]) + "  ";
        }
    }
    else{
        msg_text = "未听牌";
    }

    msg.setWindowTitle("听牌判断");
    msg.setText(msg_text);

    QFont font;
    font.setFamily("Symbola");  // 设置字体类型
    font.setPointSize(18);    // 设置字体大小
    // 通过 setStyleSheet 设置 QMessageBox 的样式
    msg.setStyleSheet(QString("QLabel{font-family: %1; font-size: %2pt;}").arg(font.family()).arg(font.pointSize()));

    msg.exec();
}

