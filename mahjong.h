#ifndef MAHJONG_H
#define MAHJONG_H

#include <vector>

#define UNDEFINED 0

#define TONG 1 //筒
#define TIAO 2 //条
#define WAN 3 //万

#define DONG_FENG 4
#define NAN_FENG 5
#define XI_FENG 6
#define BEI_FENG 7

#define BAI 8
#define ZHONG 9
#define FA 10

#define MAHJONG_BACK 11

class mahjong {
public:
    mahjong(unsigned char type = UNDEFINED, unsigned int num = UNDEFINED);

    unsigned char type;
    unsigned int num;

    int get_ID(void) const;

    bool operator < (const mahjong& other) const {
        if(this->type < other.type)
            return true;
        else if(this->type == other.type){
            return (this->num < other.num);
        }
        else
            return false;
    }

    bool operator > (const mahjong& other) const {
        if(this->type > other.type)
            return true;
        else if(this->type == other.type){
            return (this->num > other.num);
        }
        else
            return false;
    }

    bool operator == (const mahjong& other) const {
        return ((this->type == other.type)&&(this->num == other.num));
    }
};

class now_mahjongs {
public:
    now_mahjongs() {clear_mahjongs();}
    now_mahjongs(const now_mahjongs& other);

    std::vector<mahjong> get_now_mahjongs_main(void) const;
    std::vector<std::vector<mahjong>> get_now_mahjongs_side(void) const;
    std::vector<mahjong> get_now_mahjongs_AnKong(void) const;

    void add_mahjong_main(mahjong new_mahjong);
    void add_mahjong_side(std::vector<mahjong> new_mahjong);
    void add_mahjong_AnKong(mahjong new_mahjong);

    void order_mahjongs(void);
    void clear_mahjongs(void);
    void clear_mahjongs(int order);

    bool can_win_now(void) const;
    bool can_win_soon(void) const; //听牌
    std::vector<mahjong> waiting_for(void) const;

    bool can_win_ifhas(const mahjong& new_mahjong) const;
    bool can_make_melds(std::vector<mahjong> remain, int remain_melds) const;

    int count_num[101];

private:
    std::vector<mahjong> nowMahjong_main;
    std::vector<std::vector<mahjong>> nowMahjong_side; //副露
    std::vector<mahjong> nowMahjong_AnKong; //暗杠
};

#endif // MAHJONG_H
