#include "mahjong.h"
#include <cstring>
#include <set>

mahjong::mahjong(unsigned char type, unsigned int num) {
    this->type = type;
    this->num = num;
}

int mahjong::get_ID(void) const{
    return (int)type * 10 + (int)num;
}

now_mahjongs::now_mahjongs(const now_mahjongs& other) {
    nowMahjong_main = other.get_now_mahjongs_main();
    nowMahjong_side = other.get_now_mahjongs_side();
    nowMahjong_AnKong = other.get_now_mahjongs_AnKong();
}

std::vector<mahjong> now_mahjongs::get_now_mahjongs_main(void) const {
    return nowMahjong_main;
}
std::vector<std::vector<mahjong>> now_mahjongs::get_now_mahjongs_side(void) const {
    return nowMahjong_side;
}
std::vector<mahjong> now_mahjongs::get_now_mahjongs_AnKong(void) const {
    return nowMahjong_AnKong;
}

void now_mahjongs::add_mahjong_main(mahjong new_mahjong) {
    nowMahjong_main.push_back(new_mahjong);
    order_mahjongs();
    count_num[new_mahjong.get_ID()]++;
}
void now_mahjongs::add_mahjong_side(std::vector<mahjong> new_mahjong) {
    nowMahjong_side.push_back(new_mahjong);

    count_num[new_mahjong[0].get_ID()]++;
    count_num[new_mahjong[1].get_ID()]++;
    count_num[new_mahjong[2].get_ID()]++;
}
void now_mahjongs::add_mahjong_AnKong(mahjong new_mahjong) {
    nowMahjong_AnKong.push_back(new_mahjong);
    count_num[new_mahjong.get_ID()] += 4;
}

void now_mahjongs::order_mahjongs(void) {
    int nums = (int)nowMahjong_main.size();
    for(int i = 0; i < nums; i++){
        for(int j = i; j < nums; j++){
            if(nowMahjong_main[i] > nowMahjong_main[j]){
                mahjong temp = nowMahjong_main[i];
                nowMahjong_main[i] = nowMahjong_main[j];
                nowMahjong_main[j] = temp;
            }
        }
    }
}

void now_mahjongs::clear_mahjongs(void) {
    nowMahjong_main.clear();
    nowMahjong_side.clear();
    nowMahjong_AnKong.clear();
    std::memset(count_num, 0, sizeof(count_num));
}

void now_mahjongs::clear_mahjongs(int order) {
    switch(order){
    case 1: //main
        for(auto it : nowMahjong_main){
            count_num[it.get_ID()] --;
        }
        nowMahjong_main.clear();
        break;
    case 2: //side
        for(const auto& it : nowMahjong_side){
            for(auto itt : it){
                count_num[itt.get_ID()] --;
            }
        }
        nowMahjong_side.clear();
        break;
    case 3: //ankang
        for(auto it : nowMahjong_AnKong){
            count_num[it.get_ID()] -= 4;
        }
        nowMahjong_AnKong.clear();
        break;
    }
}

bool now_mahjongs::can_win_now(void) const {
    if((int)nowMahjong_main.size() == 14){
        //国士无双
        std::set<int> mahjong_id;
        int _19num = 0;
        for(auto thisMahjong : nowMahjong_main){
            if(thisMahjong.type >= DONG_FENG || (thisMahjong.num == 1 || thisMahjong.num == 9)){
                mahjong_id.insert(thisMahjong.get_ID());
                _19num ++;
            }
            else
                break;
        }
        if((int)mahjong_id.size() == 13 && _19num == 14)
            return true;

        //七对子
        bool _7pairs = true;
        for(int i = 0; i < 13; i += 2){
            if(nowMahjong_main[i].get_ID() != nowMahjong_main[i + 1].get_ID()){
                _7pairs = false;
                break;
            }
            if((i + 2) < 14 && (nowMahjong_main[i].get_ID() == nowMahjong_main[i + 2].get_ID())){
                _7pairs = false;
                break;
            }
        }
        if(_7pairs)
            return true;
    }

    int remain_melds = 4 - (int)nowMahjong_side.size() - (int)nowMahjong_AnKong.size();
    for(int i = 0; i + 1 < (int)nowMahjong_main.size(); i++){
        if(nowMahjong_main[i].get_ID() == nowMahjong_main[i + 1].get_ID()){
            std::vector<mahjong> remain_mahjong;
            for(int j = 0; j < (int)nowMahjong_main.size(); j++){
                if(j != i && j != i + 1)
                    remain_mahjong.push_back(nowMahjong_main[j]);
            }
            if(can_make_melds(remain_mahjong, remain_melds))
                return true;
        }
    }
    return false;
}

bool now_mahjongs::can_make_melds(std::vector<mahjong> remain, int remain_melds) const {
    if(remain_melds == 0)
        return true;
    else if(remain_melds == 1) {
        if(remain[0] == remain[1] && remain[1] == remain[2])
            return true;
        else if(remain[0].type == remain[1].type && remain[1].type == remain[2].type){
            if(remain[0].num + 1 == remain[1].num && remain[1].num + 1 == remain[2].num)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else{
        int ii, jj, kk;
        for(ii = 0; ii < (int)remain.size(); ii++){
            for(jj = ii + 1; jj < (int)remain.size(); jj++){
                for(kk = jj + 1; kk < (int)remain.size(); kk++){
                    if((remain[ii] == remain[jj] && remain[jj] == remain[kk]) || ((remain[ii].type == remain[jj].type && remain[jj].type == remain[kk].type) && (remain[ii].num + 1 == remain[jj].num && remain[jj].num + 1 == remain[kk].num))){
                        std::vector<mahjong> new_remain;
                        for(int i = 0; i < (int)remain.size(); i++){
                            if(i != ii && i != jj && i != kk)
                                new_remain.push_back(remain[i]);
                        }
                        if(can_make_melds(new_remain, remain_melds - 1))
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool now_mahjongs::can_win_ifhas(const mahjong& new_mahjong) const {
    now_mahjongs temp_now_mahjongs(*this);
    temp_now_mahjongs.add_mahjong_main(new_mahjong);
    return temp_now_mahjongs.can_win_now();
}

bool now_mahjongs::can_win_soon(void) const {
    std::vector<mahjong> mahjongs_waiting_for = waiting_for();
    return ((int)mahjongs_waiting_for.size() != 0);
}

std::vector<mahjong> now_mahjongs::waiting_for(void) const {
    std::vector<mahjong> mahjongs_waiting_for;
    for(int temp_type = TONG; temp_type <= WAN; temp_type++){
        for(int temp_num = 1; temp_num <= 9; temp_num++){
            mahjong new_mahjong(temp_type, temp_num);
            if(can_win_ifhas(new_mahjong) && count_num[new_mahjong.get_ID()] < 4)
                mahjongs_waiting_for.push_back(new_mahjong);
        }
    }
    for(int temp_type = DONG_FENG; temp_type <= FA; temp_type++){
        mahjong new_mahjong(temp_type);
        if(can_win_ifhas(new_mahjong) && count_num[new_mahjong.get_ID()] < 4)
            mahjongs_waiting_for.push_back(new_mahjong);
    }
    return mahjongs_waiting_for;
}
