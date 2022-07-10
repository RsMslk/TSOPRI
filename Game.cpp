#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <cstdio>
using namespace std;

int* get_one() {
    int one[7][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0}
    };
    return &one[0][0];
}






















class Graphics {
public:
    Graphics() {}
    ~Graphics() {}
    Graphics(vector<int> hitbox_x, vector<int> hitbox_y)
    {
        //set_type(type);
        set_hitbox_x(hitbox_x);
        set_hitbox_y(hitbox_y);
        //set_spawn_time(spawn_time);
    }
    vector<int> get_hitbox_x() {
        return this->hitbox_x;
    }
    vector<int> get_hitbox_y() {
        return this->hitbox_y;
    }
    void add_hitbox_x(int x) {
        this->hitbox_x.push_back(x);
    }
    void add_hitbox_y(int y) {
        this->hitbox_y.push_back(y);
    }
    void set_hitbox_x(vector<int> hitbox_x) {
        this->hitbox_x = hitbox_x;
    }
    void set_hitbox_y(vector<int> hitbox_y) {
        this->hitbox_y = hitbox_y;
    }
private:
    //int type; // 0 -- player, 1 -> N - enemy, -1 - bullet, -2 - rocket.
    vector<int> hitbox_x;
    vector<int> hitbox_y;
    //spawn_time only for enemies, for player/bullet/rocket = -1
};
class Coordinates {
public:
    Coordinates() {}
    Coordinates(int x, int y) {
        set_x(x);
        set_y(y);
    }
    ~Coordinates() {};
    int get_x() {
        return this->x;
    }
    void set_x(int x) {
        this->x = x;
    }
    int get_y() {
        return this->y;
    }
    void set_y(int y) {
        this->y = y;
    }
    void add_x(int add) {
        this->x += add;
    }
    void add_y(int add) {
        this->y += add;
    }
private:
    int x;
    int y;

};

class Enemy_types : public Graphics {
public:
    Enemy_types() {}
    Enemy_types(int type, int spawn_time) {
        set_type(type);
        set_spawn_time(spawn_time);
    }
    int get_type() {
        return this->type;
    }
    void set_type(int type) {
        this->type = type;
    }
    int get_spawn_time() {
        return this->spawn_time;
    }
    void set_spawn_time(int spawn_time) {
        this->spawn_time = spawn_time;
    }
private:
    int type;
    int spawn_time;
}; // Класс типов врагов -- тип -- время спавна

class Enemy : public Coordinates, public Enemy_types {
public:
    Enemy() {}
    ~Enemy() {} //Destructor
}; // Класс созданных врагов

class Boom_types: public Graphics {
public:
    Boom_types(){}
    ~Boom_types(){}
    Boom_types(int type, int duration) {
        set_type(type);
        set_duration(duration);
        
    }
    void set_type(int type) {
        this->type = type;
    }
    void set_duration(int duration) {
        this->duration = duration;
    }
    int get_type() {
        return this->type;
    }
    int get_duration() {
        return this->duration;
    }   
private:
    int type;
    int duration;
};
class Boom : public Coordinates {
public:
    Boom(){}
    ~Boom(){}
    Boom(Boom_types* boom_type, bool active, int duration) {
        set_boom_types(boom_type);
        set_active(active);
        set_duration_now(duration); // чтобы отслеживать длительность взрыва, сколько еще осталось изображать взрыв
    }
    void set_boom_types(Boom_types* boom_types) {
        this->boom_type = boom_types;
    }
    Boom_types* get_boom_types() {
        return this->boom_type;
    }
    void set_active(bool active) {
        this->active = active;
    }
    bool get_active() {
        return this->active;
    }
    void set_duration_now(int duration) {
        this->duration_now = duration;
    }
    int get_duration_now() {
        return this->duration_now;
    }
private:
    Boom_types* boom_type;
    bool active;
    int duration_now;
};

class Bullet_types : public Graphics {
public:
    Bullet_types() {}
    Bullet_types(int type) {
        set_type(type);
    }
    ~Bullet_types() {}
    int get_type() {
        return this->type;
    }
    void set_type(int type) {
        this->type = type;
    }
private:
    int type;
};

class Bullet : public Coordinates {
public:
    Bullet() {}
    Bullet(int direction_x, int direction_y, int x_init, int y_init) {
        set_direction_x(direction_x);
        set_direction_y(direction_y);
        set_x_init(x_init);
        set_y_init(y_init);
    }
    ~Bullet() {}
    
    int get_direction_x() {
        return this->direction_x;
    }
    int get_direction_y() {
        return this->direction_y;
    }
    int get_x_init() {
        return this->x_init;
    }
    int get_y_init() {
        return this->y_init;
    }
    void set_direction_x(int x) {
        this->direction_x = x;
    }
    void set_direction_y(int y) {
        this->direction_y = y;
    }
    void set_x_init(int x) {
        this->x_init = x;
    }
    void set_y_init(int x) {
        this->y_init = x;
    }
    Bullet_types* get_bullet_type() {
        return this->bullet_type;
    }
    void set_bullet_type(Bullet_types* bullet_type_in) {
        this->bullet_type = bullet_type_in;
    }
private:
    int direction_x;
    int direction_y;
    int x_init;
    int y_init;
    Bullet_types* bullet_type;
};
class Player : public Graphics, public Coordinates {
public:
    Player() {}
    Player(string Name, int bullets_type, int freq, int score) {
        set_Name(Name),
            set_bullets_type(bullets_type);
        set_freq(freq);
        set_score(score);
    }
    ~Player() {}
    const int get_type() {
        return this->type;
    }
    string get_Name() {
        return this->Name;
    }
    void set_Name(string Name) {
        this->Name = Name;
    }
    int get_bullets_type() {
        return this->bullets_type;
    }
    void set_bullets_type(int type) {
        this->bullets_type = type;
    }
    int get_freq() {
        return this->freq;
    }
    void set_freq(int freq) {
        this->freq = freq;
    }
    int get_score() {
        return this->score;
    }
    void set_score(int score) {
        this->score = score;
    }
private:
    string Name;
    const int type = 0;
    int bullets_type;
    int freq;
    int score;
};

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

int signum(int in)
{
    if (in > 0) {
        return 1;
    }
    else if (in < 0) {
        return -1;
    }
    return 0;
}

bool GameOver;
bool menu;
const int width = 976;
const int height = 632;
int score, lives;
int timer = 0;
int timer1 = 0;
int timestamp;

//HWND hwnd;

vector<Enemy_types> bib_enemies = {};
vector<Bullet_types> bib_bullets = {};
vector<Boom_types> bib_booms = {};

vector<Boom> booms = {};
vector<Enemy> enemies = {};
vector<Bullet> bullets = {};


Player player;

// initialize game data in this function
void initialize()
{
    int one[7][5] = {};
    one[0][0] = *get_one();
    menu = 1;
    lives = 1;
    score = 0;
    timer = 0;
    timer1 = 0;
    GameOver = 0;
    srand(time(0));
    enemies = {};
    bullets = {};
    booms = {};
    player.set_Name("Default");
    player.set_score(0);
    player.set_freq(200);
    player.set_bullets_type(0);
    player.set_x(SCREEN_WIDTH / 2);
    player.set_y(SCREEN_HEIGHT / 2);
    //vector<int>hitbox_x = {};
    //vector<int>hitbox_y = {};
    player.set_hitbox_x({});
    player.set_hitbox_y({});
    for (int i = -10; i < 11; i++) {
        for (int j = -10; j < 11; j++) {
            player.add_hitbox_x(i);
            player.add_hitbox_y(j);
        }
    }
    
    bib_enemies.push_back(Enemy_types(1, 1000));
    bib_enemies[0].set_hitbox_x({});
    bib_enemies[0].set_hitbox_y({});
    for (int i = -4; i < 5; i++) {
        for (int j = -4; j < 5; j++) {
            if ((abs(i) + abs(j)) == 2  || (abs(i) + abs(j)) == 4) {
                bib_enemies[0].add_hitbox_x(i);
                bib_enemies[0].add_hitbox_y(j);
            }
        }
    }
    bib_enemies.push_back(Enemy_types(2, 2000));
    bib_enemies[1].set_hitbox_x({});
    bib_enemies[1].set_hitbox_y({});
    for (int i = -5; i < 6; i++) {
        for (int j = -5; j < 6; j++) {
            if (abs(i) == abs(j) || abs(i) == 5 || abs(j) == 5) {
                bib_enemies[1].add_hitbox_x(i);
                bib_enemies[1].add_hitbox_y(j);
            }
        }
    }

    bib_bullets.push_back(Bullet_types(0));
    bib_bullets[0].set_hitbox_x({});
    bib_bullets[0].set_hitbox_y({});
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i) + abs(j) <= 1) {
                bib_bullets[0].add_hitbox_x(i);
                bib_bullets[0].add_hitbox_y(j);
            }
        }
    }

    bib_bullets.push_back(Bullet_types(1));
    bib_bullets[1].set_hitbox_x({});
    bib_bullets[1].set_hitbox_y({});
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (abs(i) + abs(j) <= 1) {
                bib_bullets[1].add_hitbox_x(i);
                bib_bullets[1].add_hitbox_y(j);
            }
        }
    }

    bib_bullets.push_back(Bullet_types(2));
    bib_bullets[2].set_hitbox_y({});
    bib_bullets[2].set_hitbox_x({});
    bib_bullets[2].add_hitbox_y(0);
    bib_bullets[2].add_hitbox_x(8);
    bib_bullets[2].add_hitbox_x(0);
    bib_bullets[2].add_hitbox_y(2);
    bib_bullets[2].add_hitbox_x(0);
    bib_bullets[2].add_hitbox_y(-2);
    bib_bullets[2].add_hitbox_x(-1);
    bib_bullets[2].add_hitbox_y(1);
    bib_bullets[2].add_hitbox_x(-1);
    bib_bullets[2].add_hitbox_y(-1);
    bib_bullets[2].add_hitbox_x(-2);
    bib_bullets[2].add_hitbox_y(0);
    for (int i = -2; i < 13; i++) { // y
        for (int j = -4; j < 5; j++) { // x
            if ((abs(j) == 4 || abs(j) == 0) && (i < 12 && i > 8)) {
                bib_bullets[2].add_hitbox_x(i);
                bib_bullets[2].add_hitbox_y(j);
            }
            if (abs(j) == 3 && i < 11 && i > 7) {
                bib_bullets[2].add_hitbox_x(i);
                bib_bullets[2].add_hitbox_y(j);
            }
            if (i > 0 && i < 10 && abs(j) < 3) {
                bib_bullets[2].add_hitbox_x(i);
                bib_bullets[2].add_hitbox_y(3);
                bib_bullets[2].add_hitbox_x(i);
                bib_bullets[2].add_hitbox_y(-3);
                bib_bullets[2].add_hitbox_x(1);
                bib_bullets[2].add_hitbox_y(j);
                bib_bullets[2].add_hitbox_x(9);
                bib_bullets[2].add_hitbox_y(j);
            }
        }
    }
    bib_booms.push_back(Boom_types(-1, 200)); //player_boom_type
    for (int i = -7; i < 8; i++)
    {
        for (int j = -7; j < 8; j++)
        {
            if (abs(i) == abs(j)) {
                bib_booms[0].add_hitbox_x(i);
                bib_booms[0].add_hitbox_y(j);
            }
            if (i == 0) {
                bib_booms[0].add_hitbox_x(i);
                bib_booms[0].add_hitbox_y(j);
            }
            if (j == 0) {
                bib_booms[0].add_hitbox_x(i);
                bib_booms[0].add_hitbox_y(j);
            }
        }
    }

    bib_booms.push_back(Boom_types(0, 150)); // Для врагов
    for (int i = -3; i < 4; i++)
    {
        for (int j = -3; j < 4; j++)
        {
            if (abs(i) == abs(j)) {
                bib_booms[1].add_hitbox_x(i);
                bib_booms[1].add_hitbox_y(j);
            }
            if (i == 0) {
                bib_booms[1].add_hitbox_x(i);
                bib_booms[1].add_hitbox_y(j);
            }
            if (j == 0) {
                bib_booms[1].add_hitbox_x(i);
                bib_booms[1].add_hitbox_y(j);
            }
        }
    }

    bib_booms.push_back(Boom_types(1, 400)); // Для ракеты
    for (int i = -5; i < 6; i++)
    {
        for (int j = -5; j < 6; j++)
        {
            if (i == 0) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == 5) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == 4 && i < 5 && i > -5) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == 3 && i < 2 && i > -2) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == 3 && i < 2 && i > -2) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == -1 && i < 4 && i > -4) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if ((j == -2 || j == -3) && i < 6 && i > -6) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == -4 && i < 5 && i > -5) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }
            if (j == -5 && i < 3 && i > -3) {
                bib_booms[2].add_hitbox_x(i);
                bib_booms[2].add_hitbox_y(j);
            }

        }
    }

    timestamp = 0;
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (!menu)
    {
        timestamp++;
        timer++;
        timer1++;
        if (is_key_pressed(VK_ESCAPE) || lives == 0)
            GameOver = 1;
        if (GameOver == 1)
            schedule_quit_game();

        if (is_key_pressed('A') && player.get_x() > 10 + 24)
            if (timer1 % 10 == 0)
            {
                player.add_x(-1);
            }
        if (is_key_pressed('D') && player.get_x() < width - 10 + 24)
            if (timer1 % 10 == 0)
            {
                player.add_x(+1);
            }
        if (is_key_pressed('W') && player.get_y() > 10 + 68)
            if (timer1 % 10 == 0)
            {
                player.add_y(-1);
            }
        if (is_key_pressed('S') && player.get_y() < height - 10 + 68)
            if (timer1 % 10 == 0)
            {
                player.add_y(+1);
            }
        if (is_mouse_button_pressed(0) && get_cursor_x() < 1024 && get_cursor_x() > 0 && get_cursor_y() > 0 && get_cursor_y() < 768) //Стреляем
        {
            if (player.get_bullets_type() == 0)
            {
                if (timestamp > player.get_freq())
                {
                    Bullet bullet_tmp;
                    bullet_tmp.set_bullet_type(&bib_bullets[0]);
                    bullet_tmp.set_x_init(player.get_x());
                    bullet_tmp.set_y_init(player.get_y());
                    bullet_tmp.set_x(bullet_tmp.get_x_init());
                    bullet_tmp.set_y(bullet_tmp.get_y_init());
                    int direction_x = (get_cursor_x() - bullet_tmp.get_x_init());
                    int direction_y = (get_cursor_y() - bullet_tmp.get_y_init());
                    //bullet_tmp.direction_x = direction_x;
                    //bullet_tmp.direction_y = direction_y;
                    if (direction_x * direction_x + direction_y * direction_y < 990 * 990 + 690 * 690)
                    {
                        bullet_tmp.set_direction_x(direction_x * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)));
                        bullet_tmp.set_direction_y(direction_y * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)));
                    }
                    else
                    {
                        bullet_tmp.set_direction_x(direction_x);
                        bullet_tmp.set_direction_y(direction_y);
                    }
                    bullets.push_back(bullet_tmp);
                    timestamp = 0;
                }
            }
            if (player.get_bullets_type() == 1)
            {
                if (timestamp > player.get_freq())
                {
                    timestamp = 0;
                    for (int j = -4; j < 4; j++)
                    {
                        Bullet bullet_tmp;
                        bullet_tmp.set_bullet_type(&bib_bullets[1]);


                        int direction_x = (get_cursor_x() - player.get_x());
                        int direction_y = (get_cursor_y() - player.get_y());

                        if (direction_x != 0)
                        {
                            bullet_tmp.set_x_init(player.get_x() + j);
                            bullet_tmp.set_y_init(player.get_y()  + j - (direction_y * bullet_tmp.get_x_init() / direction_x) / (direction_x * direction_x + direction_y * direction_y));
                        }
                        else {
                            bullet_tmp.set_y_init(player.get_y() + j);
                            bullet_tmp.set_x_init(player.get_x() + j- (direction_y * bullet_tmp.get_y_init() / direction_y) / (direction_x * direction_x + direction_y * direction_y));
                        }
                        bullet_tmp.set_x(bullet_tmp.get_x_init());
                        bullet_tmp.set_y(bullet_tmp.get_y_init());

                        if (direction_x * direction_x + direction_y * direction_y < 990 * 990 + 690 * 690)
                        {
                            bullet_tmp.set_direction_x(direction_x * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)) + rand() % 200 * j);
                            bullet_tmp.set_direction_y(direction_y * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)) + rand() % 200 * j);
                        }
                        else
                        {
                            bullet_tmp.set_direction_x(direction_x + rand() % 200 * j);
                            bullet_tmp.set_direction_y(direction_y + rand() % 200 * j);
                        }
                        bullets.push_back(bullet_tmp);
                    }

                }
            }
            if (player.get_bullets_type() == 2) {
                if (timestamp > player.get_freq())
                {
                    Bullet bullet_tmp;
                    bullet_tmp.set_bullet_type(&bib_bullets[2]);
                    bullet_tmp.set_x_init(player.get_x());
                    bullet_tmp.set_y_init(player.get_y());
                    bullet_tmp.set_x(bullet_tmp.get_x_init());
                    bullet_tmp.set_y(bullet_tmp.get_y_init());
                    int direction_x = (get_cursor_x() - bullet_tmp.get_x_init());
                    int direction_y = (get_cursor_y() - bullet_tmp.get_y_init());
                    //bullet_tmp.direction_x = direction_x;
                    //bullet_tmp.direction_y = direction_y;
                    if (direction_x * direction_x + direction_y * direction_y < 990 * 990 + 690 * 690)
                    {
                        bullet_tmp.set_direction_x(direction_x * 2 * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)));
                        bullet_tmp.set_direction_y(direction_y * 2 * sqrt((990 * 990 + 690 * 690) / (direction_x * direction_x + direction_y * direction_y)));
                    }
                    else
                    {
                        bullet_tmp.set_direction_x(direction_x);
                        bullet_tmp.set_direction_y(direction_y);
                    }
                    bullets.push_back(bullet_tmp);
                    Boom boom_tmp;
                    boom_tmp.set_x(get_cursor_x());
                    boom_tmp.set_y(get_cursor_y());
                    boom_tmp.set_boom_types(&bib_booms[2]);
                    boom_tmp.set_active(0);
                    boom_tmp.set_duration_now(bib_booms[2].get_duration());
                    booms.push_back(boom_tmp);
                    timestamp = 0;
                }
            }
        }

        for (int i = 0; i < bib_enemies.size(); i++) { // создаем Энеми
            if (timer % bib_enemies[i].get_spawn_time() == 0)
            {
                Enemy enemy_tmp;
                //enemy_tmp.set_type(bib_enemies[i].get_type());
                enemy_tmp.set_x(rand() % (width - 30) + 24);
                enemy_tmp.set_y(rand() % (height - 20) + 68);
                //enemy_tmp.set_type(1);
                enemy_tmp.set_spawn_time(1000);
                
                while (enemy_tmp.get_x() - player.get_x() < 150 && enemy_tmp.get_x() - player.get_x() < 150)
                {
                    enemy_tmp.set_x(rand() % (width - 30) + 24);
                    enemy_tmp.set_y(rand() % (height - 20) + 68);
                }
                enemy_tmp.set_type(bib_enemies[i].get_type());
                enemies.push_back(enemy_tmp);
                if (bib_enemies[i].get_type() > 1 && bib_enemies[i].get_spawn_time() >= 500)
                    bib_enemies[i].set_spawn_time(bib_enemies[i].get_spawn_time() - 100);
            } 
        }// создаем Энеми




        for (int i = 0; i < bullets.size(); i++) // Deleting bullets when limit
        {
            if (bullets[i].get_x() >= width + 24 || bullets[i].get_y() >= height + 68 || bullets[i].get_x() <= 24 || bullets[i].get_y() <= 68)
            {
                bullets.erase(bullets.begin() + i);
            }
            else if (bullets[i].get_bullet_type()->get_type() == 1 && (((bullets[i].get_x() - bullets[i].get_x_init()) * (bullets[i].get_x() - bullets[i].get_x_init()) +
                (bullets[i].get_y() - bullets[i].get_y_init()) * (bullets[i].get_y() - bullets[i].get_y_init()) >= 150 * 150) 
                ||( bullets[i].get_x() >= width + 24 || bullets[i].get_y() >= height + 68 || bullets[i].get_x() <= 24 || bullets[i].get_y() <= 68)))
            {
                bullets.erase(bullets.begin() + i);
            }
            else if (bullets[i].get_bullet_type()->get_type() == 2)
            {
                for (int j = 0; j < booms.size(); j++)
                {
                    if (booms[j].get_boom_types()->get_type() == bib_booms[2].get_type() && bullets[i].get_bullet_type()->get_type() == 2 &&
                        (booms[j].get_x() - bullets[i].get_x()) * (booms[j].get_x() - bullets[i].get_x())
                        + (booms[j].get_y() - bullets[i].get_y()) * (booms[j].get_y() - bullets[i].get_y()) < 50 * 50)
                    {
                        bullets.erase(bullets.begin() + i);
                        booms[j].set_active(1);
                    }
                }
                
            }
        }
        int i = 0;
        int hitt_enemy_tmp_x;
        int hitt_enemy_tmp_y;
        int hitt_enemy_tmp_type;
        int hit_count_type_2 = 0;
        while (i < bullets.size() && enemies.size() > 0) // Deleting bullets, when hit
        {
            for (int j = 0; j < enemies.size(); j++)
            {
                if (bullets.size() == 0 || bullets[i].get_bullet_type()->get_type() == 2) {
                    break;
                }
                if (enemies[j].get_type() == 1)
                {

                    if ((bullets[i].get_x() - enemies[j].get_x()) * (bullets[i].get_x() - enemies[j].get_x()) +
                        (bullets[i].get_y() - enemies[j].get_y()) * (bullets[i].get_y() - enemies[j].get_y()) < 26 &&
                        bullets[i].get_bullet_type()->get_type() <= 1)
                    {
                        bullets.erase(bullets.begin() + i);
                        Boom boom_tmp;
                        boom_tmp.set_x(enemies[j].get_x());
                        boom_tmp.set_y(enemies[j].get_y());
                        boom_tmp.set_boom_types(&bib_booms[1]);
                        boom_tmp.set_active(true);
                        boom_tmp.set_duration_now(bib_booms[1].get_duration());
                        booms.push_back(boom_tmp);


                        if (i > 0) {
                            i--;
                        }
                        enemies.erase(enemies.begin() + j);
                        j--;

                        score += 25;
                        player.set_score(player.get_score() + 25);
                    }
                }
                else if (enemies[j].get_type() == 2)
                {
                    if ((bullets[i].get_x() - enemies[j].get_x()) * (bullets[i].get_x() - enemies[j].get_x()) +
                        (bullets[i].get_y() - enemies[j].get_y()) * (bullets[i].get_y() - enemies[j].get_y()) < 37 &&
                        bullets[i].get_bullet_type()->get_type() <= 1)
                    {
                        bullets.erase(bullets.begin() + i);
                        hitt_enemy_tmp_x = enemies[j].get_x();
                        hitt_enemy_tmp_y = enemies[j].get_y();
                        hitt_enemy_tmp_type = enemies[j].get_type();
                        if (i > 0) {
                            i--;
                        }
                        Boom boom_tmp;
                        boom_tmp.set_x(enemies[j].get_x());
                        boom_tmp.set_y(enemies[j].get_y());
                        boom_tmp.set_boom_types(&bib_booms[1]);
                        boom_tmp.set_active(1);
                        boom_tmp.set_duration_now(bib_booms[1].get_duration());
                        booms.push_back(boom_tmp);
                        enemies.erase(enemies.begin() + j);
                        j--;

                        score += 50;
                        player.set_score(player.get_score() + 50);
                        hit_count_type_2++;
                    }
                }

            }
            i++;
        }  // Попадание во врага 

        for (int i = 0; i < hit_count_type_2; i++) // Спавни из квадратика -> 2 ромбика
        {
            Enemy enemy_tmp;
            enemy_tmp.set_type(hitt_enemy_tmp_type - 1);
            enemy_tmp.set_x(hitt_enemy_tmp_x + signum(hitt_enemy_tmp_x - player.get_x()));
            enemy_tmp.set_y(hitt_enemy_tmp_y + signum(hitt_enemy_tmp_y - player.get_y()));
            //enemy_tmp.set_type(1);
            enemy_tmp.set_spawn_time(1000);
            enemies.push_back(enemy_tmp);
            enemy_tmp.set_type(hitt_enemy_tmp_type - 1);
            enemy_tmp.set_x(hitt_enemy_tmp_x + signum(hitt_enemy_tmp_x - player.get_x()));
            enemy_tmp.set_y(hitt_enemy_tmp_y + signum(hitt_enemy_tmp_y - player.get_y()));
            //enemy_tmp.set_type(1);
            enemy_tmp.set_spawn_time(1000);
            enemies.push_back(enemy_tmp);
        } // Спавни из квадратика -> 2 ромбика

        for (int i = 0; i < bullets.size(); i++) //Движение пуль
        {
            if (timer % 20 == 0)
            {
                bullets[i].set_x(bullets[i].get_x() + bullets[i].get_direction_x() / 200);
                bullets[i].set_y(bullets[i].get_y() + bullets[i].get_direction_y() / 200);
            }
        } //Движение пуль

        for (int i = 0; i < enemies.size(); i++) // Колллизии врагов
        {
            for (int j = 0; j < enemies.size(); j++)
            {
                int dir_x = player.get_x() - enemies[i].get_x();
                int dir_y = player.get_y() - enemies[i].get_y();
                int sign_x = 0;
                int sign_y = 0;
                if (dir_x < 0)
                {
                    sign_x = -1;
                }
                if (dir_x > 0)
                {
                    sign_x = 1;
                }
                if (dir_y < 0)
                {
                    sign_y = -1;
                }
                if (dir_y > 0)
                {
                    sign_y = 1;
                }
                if ( enemies[i].get_type() == 1 && enemies[j].get_type() == 1 && i != j && abs(enemies[i].get_x() - enemies[j].get_x()) < 6 && abs(enemies[i].get_x() - player.get_x()) < abs(enemies[j].get_x() - player.get_x())) {
                    enemies[i].set_x(enemies[i].get_x() + sign_x);
                }
                if (enemies[i].get_type() == 1 && enemies[j].get_type() == 1 && i != j && abs(enemies[i].get_y() - enemies[j].get_y()) < 6 && abs(enemies[i].get_y() - player.get_y()) < abs(enemies[j].get_y() - player.get_y())) {
                    enemies[i].set_y(enemies[i].get_y() + sign_y);
                }

                if (enemies[i].get_type() == 2 && enemies[j].get_type() == 2 && i != j && abs(enemies[i].get_x() - enemies[j].get_x()) < 11 && abs(enemies[i].get_x() - player.get_x()) < abs(enemies[j].get_x() - player.get_x())) {
                    enemies[i].add_x(sign_x);
                }
                if (enemies[i].get_type() == 2 && enemies[j].get_type() == 1 && i != j && abs(enemies[i].get_y() - enemies[j].get_y()) < 10 && abs(enemies[i].get_y() - player.get_y()) < abs(enemies[j].get_y() - player.get_y())) {
                    enemies[i].add_y(sign_y);
                }

                if (enemies[i].get_type() ==1 && enemies[j].get_type() == 2 && i != j && abs(enemies[i].get_x() - enemies[j].get_x()) < 11 && abs(enemies[i].get_x() - player.get_x()) < abs(enemies[j].get_x() - player.get_x())) {
                    enemies[i].add_x(sign_x);
                }
                if (enemies[i].get_type() == 1 && enemies[j].get_type() == 2 && i != j && abs(enemies[i].get_y() - enemies[j].get_y()) < 10 && abs(enemies[i].get_y() - player.get_y()) < abs(enemies[j].get_y() - player.get_y())) {
                    enemies[i].add_y(sign_y);
                }

                if (enemies[i].get_type() == 2 && enemies[j].get_type() == 2 && i != j && abs(enemies[i].get_y() - enemies[j].get_y()) < 11 && abs(enemies[i].get_y() - player.get_y()) < abs(enemies[j].get_y() - player.get_y())) {
                    enemies[i].add_y(sign_y);
                }
                if (enemies[i].get_type() == 2 && enemies[j].get_type() == 1 && i != j && abs(enemies[i].get_x() - enemies[j].get_x()) < 10 && abs(enemies[i].get_x() - player.get_x()) < abs(enemies[j].get_x() - player.get_x())) {
                    enemies[i].add_x(sign_x);
                }
            }
        } // Колллизии врагов
        for (int i = 0; i < enemies.size(); i++) // Движение врагов
        {
            if (timer % 20 == 0)
            {
                if (enemies[i].get_type() == 1)
                {
                    int dir_x = player.get_x() - enemies[i].get_x();
                    int dir_y = player.get_y() - enemies[i].get_y();
                    int sign_x = 0;
                    int sign_y = 0;
                    if (dir_x < 0)
                    {
                        sign_x = -1;
                    }
                    if (dir_x > 0)
                    {
                        sign_x = 1;
                    }
                    if (dir_y < 0)
                    {
                        sign_y = -1;
                    }
                    if (dir_y > 0)
                    {
                        sign_y = 1;
                    }
                    if (abs(dir_x) <= 3 && dir_x != 0)
                    {
                        enemies[i].add_x(dir_x);
                    }
                    else if (abs(dir_y) <= 3 && dir_y != 0)
                    {
                        enemies[i].add_y(dir_y);
                    }
                    else if (abs(dir_x) <= 100 && abs(dir_y) <= 100)
                    {
                        enemies[i].add_x(2 * sign_x);
                        enemies[i].add_y(2 * sign_y);
                    }
                    else
                    {
                        enemies[i].add_x(2 * sign_x);
                        enemies[i].add_y(2 * sign_y);

                    }

                }
                if (enemies[i].get_type() == 2) {
                    bool moved = 0;
                    int dir_x_player_enemy = player.get_x() - enemies[i].get_x();
                    int dir_y_player_enemy = player.get_y() - enemies[i].get_y();
                    int sign_x_player_enemy = 0;
                    int sign_y_player_enemy = 0;
                    int sign_x_bullet_enemy = 0;
                    int sign_y_bullet_enemy = 0;
                    if (dir_x_player_enemy < 0)
                        sign_x_player_enemy = -1;
                    if (dir_x_player_enemy > 0)
                        sign_x_player_enemy = 1;
                    if (dir_y_player_enemy < 0)
                        sign_y_player_enemy = -1;
                    if (dir_y_player_enemy > 0)
                        sign_y_player_enemy = 1;
                    for (int j = 0; j < bullets.size(); j++) {
                        int dir_x_bullet_enemy = bullets[j].get_x() - enemies[i].get_x();
                        int dir_y_bullet_enemy = bullets[j].get_y() - enemies[i].get_y();
                        int sign_x_bullet_enemy = 0;
                        int sign_y_bullet_enemy = 0;
                        if (dir_x_bullet_enemy < 0)
                            sign_x_bullet_enemy = -1;
                        if (dir_y_bullet_enemy < 0)
                            sign_y_bullet_enemy = -1;
                        if (dir_x_bullet_enemy > 0)
                            sign_x_bullet_enemy = 1;
                        if (dir_y_bullet_enemy > 0)
                            sign_y_bullet_enemy = 1;
                        if (dir_x_bullet_enemy * dir_x_bullet_enemy +
                            dir_y_bullet_enemy * dir_y_bullet_enemy < 50 * 50 && !moved)
                        {
                            if (abs(dir_y_bullet_enemy) <= 8 && enemies[i].get_y() <= 700 - 4 - 5)
                            {
                                //enemies[i].add_x(2 * bullets[j].get_direction_y() * sign_y / bullets[j].get_direction_x());
                                enemies[i].add_y(3);
                                //enemies[i].add_y(- enemies[i].get_x() * bullets[j].get_direction_x()/ enemies[i].get_y());
                                moved = 1;
                            } 
                            else if (abs(dir_y_bullet_enemy) <= 8 && enemies[i].get_y() <= 68 + 4 + 5)
                            {
                                enemies[i].add_y(-3);
                                //enemies[i].add_y(- enemies[i].get_x() * bullets[j].get_direction_x()/ enemies[i].get_y());
                                moved = 1;
                            }
                            if (abs(dir_x_bullet_enemy) <= 8 && enemies[i].get_x() <= 1000 - 4 - 5)
                            {
                                //enemies[i].add_x(2 * bullets[j].get_direction_y() * sign_y / bullets[j].get_direction_x());
                                enemies[i].add_x(3);
                                //enemies[i].add_y(- enemies[i].get_x() * bullets[j].get_direction_x()/ enemies[i].get_y());
                                moved = 1;
                            } 
                            else if (abs(dir_x_bullet_enemy) <= 8 && enemies[i].get_x() >= 24 + 4 + 5)
                            {
                                //enemies[i].add_x(2 * bullets[j].get_direction_y() * sign_y / bullets[j].get_direction_x());
                                enemies[i].add_x(-3);
                                //enemies[i].add_y(- enemies[i].get_x() * bullets[j].get_direction_x()/ enemies[i].get_y());
                                moved = 1;
                            }
                        }
                    }

                    if (!moved) {
                        if (abs(dir_x_player_enemy) <= 3 && dir_x_player_enemy != 0)
                        {
                            enemies[i].add_x(dir_x_player_enemy);
                        }
                        else if (abs(dir_y_player_enemy) <= 3 && dir_y_player_enemy != 0)
                        {
                            enemies[i].add_y(dir_y_player_enemy);
                        }
                        else if (abs(dir_x_player_enemy) <= 100 && abs(dir_y_player_enemy) <= 100)
                        {
                            enemies[i].add_x(3 * sign_x_player_enemy);
                            enemies[i].add_y(3 * sign_y_player_enemy);
                        }
                        else
                        {
                            enemies[i].add_x(3 * sign_x_player_enemy);
                            enemies[i].add_y(3 * sign_y_player_enemy);
                        }
                    }
                }
            }
        } // Движение врагов

        for (int i = 0; i < enemies.size(); i++) // Смерть игрока
        {
            if (abs(enemies[i].get_x() - player.get_x()) < 15 && abs(enemies[i].get_y() - player.get_y()) < 15)
            {
                lives--;
                enemies.erase(enemies.begin() + i);
            }
        } // Смерть игрока
        if (score >= 100 + player.get_bullets_type() * 300)
        {
            player.set_bullets_type(player.get_bullets_type() + 1);
            player.set_freq(500);
            lives++;
            score = 0;
            timestamp = 1001;
        }
    } 
    else
    {
        if (is_mouse_button_pressed(0) && get_cursor_x() < 424 + 175 && get_cursor_x() > 424 && get_cursor_y() < 350 && get_cursor_y() > 300)
        {
            menu = 0;
        }
    }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R = i , G = j, B = K) white = 256 * 256 * 256 - 1; 
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    //char Score[6] = "Score";
    if (!menu)
    {
        //sprintf(Score, "%p", hwnd);
        //memset(buffer, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
        for (int j = 0; j < height; j++)
            for (int i = 0; i < width; i++)
            {
                buffer[j + 68][24] = (256 * 256 * 256 - 1);
                buffer[68][i + 24] = (256 * 256 * 256 - 1);
                buffer[j + 68][width - 1 + 24] = (256 * 256 * 256 - 1);
                buffer[height + 68 - 1][i + 24] = (256 * 256 * 256 - 1);
            }


        for (int i = 0; i < player.get_hitbox_x().size(); i++)
            buffer[player.get_y() + player.get_hitbox_y()[i]][player.get_x() + player.get_hitbox_x()[i]] = (255 * 256 * 256 + 255 * 256 + 51);

        for (int k = 0; k < bullets.size(); k++)
        {
            int sign_x = 0;
            int sign_y = 0;
            if ( abs((double) bullets[k].get_direction_x() / bullets[k].get_direction_y()) < 0.4) // cotang..
            {
                sign_y = signum(bullets[k].get_direction_y());
            }
            if ( abs((double)bullets[k].get_direction_x() / bullets[k].get_direction_y()) < 2.4 && abs((double)bullets[k].get_direction_x() / bullets[k].get_direction_y()) >= 0.4)
            {
                sign_y = signum(bullets[k].get_direction_y());
                sign_x = signum(bullets[k].get_direction_x());
            }
            if (abs((double)bullets[k].get_direction_x() / bullets[k].get_direction_y()) >= 2.4)
            {
                sign_x = signum(bullets[k].get_direction_x());
            }
            for (int i = 0; i < bullets[k].get_bullet_type()->get_hitbox_x().size(); i++)
            {
                if (bullets[k].get_bullet_type()->get_type() != 2)
                {
                    buffer[bullets[k].get_y() + bullets[k].get_bullet_type()->get_hitbox_y()[i]][bullets[k].get_x() + bullets[k].get_bullet_type()->get_hitbox_x()[i]]
                        = (255 * 256 * 256 + 255 * 256 + 51);
                }
                else
                {

                    buffer[bullets[k].get_y() - sign_x *  bullets[k].get_bullet_type()->get_hitbox_y()[i]  - sign_y * bullets[k].get_bullet_type()->get_hitbox_x()[i]]
                        [bullets[k].get_x() -  sign_x * bullets[k].get_bullet_type()->get_hitbox_x()[i] + sign_y * bullets[k].get_bullet_type()->get_hitbox_y()[i]] = (255 * 256 * 256 + 255 * 256 + 51);
                }
            }
        }
        
        for (int k = 0; k < enemies.size(); k++)
        {
            for (int j = 0; j < bib_enemies.size(); j++)
            {
                for (int i = 0; i < bib_enemies[j].get_hitbox_x().size(); i++)
                {
                    if (enemies[k].get_type() == bib_enemies[j].get_type())
                        buffer[enemies[k].get_y() + bib_enemies[j].get_hitbox_y()[i]][enemies[k].get_x() + bib_enemies[j].get_hitbox_x()[i]] = 204 * 256 * 256 + 51 * 256 + 153;
                }
            }
        }
        int size = booms.size();
        if (size > 0) {
           int do_nothing = size;
        }
        for (int j = 0; j < booms.size(); j++) {
            if (booms[j].get_active() == true && booms[j].get_duration_now() != 0) {
                for (int il = 0; il < booms[j].get_boom_types()->get_hitbox_x().size(); il++)
                {
                    buffer[booms[j].get_y() + booms[j].get_boom_types()->get_hitbox_y()[il]]
                        [booms[j].get_x() + booms[j].get_boom_types()->get_hitbox_x()[il]] =
                        256 * 256 * (255 - 153 * booms[j].get_duration_now() / 400) + 256 * ((53 - booms[j].get_duration_now() * 53 / 400));
                }
                booms[j].set_duration_now(booms[j].get_duration_now() - 1);
            }
            else if (booms[j].get_active() && booms[j].get_duration_now() == 1) {
                booms.erase(booms.begin() + j);
            }
        }
        
    }
    else 
    {
        for (int i = 300; i < 350; i++) {
            for (int j = 424; j < 424 + 175; j++) {
                buffer[i][424] = (256 * 256 * 256 - 1);
                buffer[i][424 + 175] = (256 * 256 * 256 - 1);
                buffer[300][j] = (256 * 256 * 256 - 1);
                buffer[350][j] = (256 * 256 * 256 - 1);
            }
        }
    }
}

// free game data in this function
void finalize()
{
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    enemies.clear();
    bullets.clear();
    booms.clear();
    bib_enemies.clear();
    bib_enemies.clear();
    bib_booms.clear();
}

