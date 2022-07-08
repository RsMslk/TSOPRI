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
/*Enemy enemy_a = Enemy(1, 1, 1);*/
//Enemy* enemy_arr = (Enemy *) malloc(10 * sizeof(Enemy));

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

bool GameOver;
const int width = 976;
const int height = 632;
int score, lives;
int timer = 0;
int timer1 = 0;
int timestamp;

//HWND hwnd;

vector<Enemy_types> bib_enemies = {};
vector<Bullet_types> bib_bullets = {};
vector<Enemy> enemies = {};
vector<Bullet> bullets = {};

Player player;

// initialize game data in this function
void initialize()
{

    lives = 1;
    score = 0;
    timer = 0;
    timer1 = 0;
    GameOver = 0;
    srand(time(0));
    enemies = {};
    bullets = {};

    player.set_Name("Default");
    player.set_score(0);
    player.set_freq(500);
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
            if (abs(i) + abs(j) % 2 == 0) {
                bib_enemies[0].add_hitbox_x(i);
                bib_enemies[0].add_hitbox_y(j);
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

    timestamp = 500;
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
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
    if (is_mouse_button_pressed(0) && get_cursor_x() < 1024 && get_cursor_x() > 0 && get_cursor_y() > 0 && get_cursor_y() < 768)
    {
        if (player.get_bullets_type() == 0) {
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
            player.set_freq(1000);
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
                        bullet_tmp.set_y_init(player.get_y() - (direction_y * bullet_tmp.get_x_init() / direction_x) / (direction_x * direction_x + direction_y * direction_y));
                    }
                    else {
                        bullet_tmp.set_y_init(player.get_y() + j);
                        bullet_tmp.set_x_init(player.get_x() - (direction_y * bullet_tmp.get_y_init() / direction_y) / (direction_x * direction_x + direction_y * direction_y));
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
    }

    for (int i = 0; i < bib_enemies.size(); i++) {
        if (timer % bib_enemies[i].get_spawn_time() == 0)
        {
            Enemy enemy_tmp;
            enemy_tmp.set_type(bib_enemies[i].get_type());
            enemy_tmp.set_x(rand() % (width - 30) + 24);
            enemy_tmp.set_y(rand() % (height - 20) + 68);
            enemy_tmp.set_type(1);
            enemy_tmp.set_spawn_time(1000);
            vector <int> hitbox_x_tmp;
            vector <int> hitbox_y_tmp;
            for (int k = -4; k < 5; k++)
            {
                for (int j = -4; j < 5; j++)
                {
                    if (abs(k) + abs(j) == 4 || abs(k) + abs(j) == 2)
                    {
                        hitbox_x_tmp.push_back(k);
                        hitbox_y_tmp.push_back(j);
                    }
                }
            }
            enemy_tmp.set_hitbox_x(hitbox_x_tmp);
            enemy_tmp.set_hitbox_y(hitbox_y_tmp);
            enemies.push_back(enemy_tmp);
        }
    }




    for (int i = 0; i < bullets.size(); i++) // Deleting bullets when limit
    {
        if (bullets[i].get_x() >= width + 24 || bullets[i].get_y() >= height + 68 || bullets[i].get_x() <= 24 || bullets[i].get_y() <= 68)
        {
            bullets.erase(bullets.begin() + i);
        }
        else if (bullets[i].get_bullet_type()->get_type() == 1 && (bullets[i].get_x() - bullets[i].get_x_init()) * (bullets[i].get_x() - bullets[i].get_x_init()) +
              (bullets[i].get_y() - bullets[i].get_y_init()) * (bullets[i].get_y() - bullets[i].get_y_init()) >= 150 * 150)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
    int i = 0;
    while (i < bullets.size() && enemies.size() > 0) // Deleting bullets, when hit
    {
        for (int j = 0; j < enemies.size(); j++)
        {
            if (bullets.size() == 0) {
                break;
            }
            if (abs(bullets[i].get_x() - enemies[j].get_x()) < 5 && abs(bullets[i].get_y() - enemies[j].get_y()) < 5 && bullets[i].get_bullet_type()->get_type() <= 1)
            {
                bullets.erase(bullets.begin() + i);

                if (i > 0) {
                    i--;
                }
                enemies.erase(enemies.begin() + j);
                j--;

                score += 25;
                player.set_score(player.get_score() + 25);
            }

        }
        i++;
    }
    /*for (int i = 0; i < bullets_indexes.size(); i++)
    {

    }
    for (int i = 0; i < enemy_indexes.size(); i++)
    {

        ;
    }*/





    for (int i = 0; i < bullets.size(); i++)
    {
        if (timer % 80 == 0)
        {
            bullets[i].set_x(bullets[i].get_x() + bullets[i].get_direction_x() / 150);
            bullets[i].set_y(bullets[i].get_y() + bullets[i].get_direction_y() / 150);
        }
    }

    for (int i = 0; i < enemies.size(); i++)
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
            if (i != j && abs(enemies[i].get_x() - enemies[j].get_x()) < 6 && abs(enemies[i].get_x() - player.get_x()) < abs(enemies[j].get_x() - player.get_x())) {
                enemies[i].set_x(enemies[i].get_x() + sign_x);
            }
            if (i != j && abs(enemies[i].get_y() - enemies[j].get_y()) < 6 && abs(enemies[i].get_y() - player.get_y()) < abs(enemies[j].get_y() - player.get_y())) {
                enemies[i].set_y(enemies[i].get_y() + sign_y);
            }
        }
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        if (timer % 50 == 0)
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
                    enemies[i].set_x(enemies[i].get_x() + dir_x);
                }
                else if (abs(dir_y) <= 3 && dir_y != 0)
                {
                    enemies[i].set_y(enemies[i].get_y() + dir_y);
                }
                else if (abs(dir_x) <= 100 && abs(dir_y) <= 100)
                {
                    /*dir_x = dir_x * 2 * 100 * 100 / (dir_x * dir_x + dir_y * dir_y + 1);
                    dir_y = dir_y * 2 * 100 * 100 / (dir_x * dir_x + dir_y * dir_y + 1);*/
                    enemies[i].set_x(enemies[i].get_x() + 3 * sign_x);
                    enemies[i].set_y(enemies[i].get_y() + 3 * sign_y);
                }
                else
                {
                    enemies[i].set_x(enemies[i].get_x() + 3 * sign_x);
                    enemies[i].set_y(enemies[i].get_y() + 3 * sign_y);
                    //enemies[i].x += 3 * sign_x;
                    //enemies[i].y += 3 * sign_y;
                }

            }
        }
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        if (abs(enemies[i].get_x() - player.get_x()) < 15 && abs(enemies[i].get_y() - player.get_y()) < 15)
        {
            lives--;
            enemies.erase(enemies.begin() + i);
        }
    }
    if (score == 100 + player.get_bullets_type() * 300)
    {
        player.set_bullets_type(player.get_bullets_type() + 1);
        lives++;
        score = 0;
        timestamp = 1001;
    }

}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R = i , G = j, B = K) white = 256 * 256 * 256 - 1; 
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    //char Score[6] = "Score";

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
        for (int i = 0; i < bullets[k].get_bullet_type()->get_hitbox_x().size(); i++)
            buffer[bullets[k].get_y() + bullets[k].get_bullet_type()->get_hitbox_y()[i]] [bullets[k].get_x() + bullets[k].get_bullet_type()->get_hitbox_x()[i]] 
                                                                                                                                                = (256 * 128 * 2 - 1);
    //for (int j = -5; j < 5; j++)
    //    for (int i = -5 + j; i < 5 +j; i++)
      //      buffer[enemy_y[0] + j][enemy_x[0] + i] = (256 * 256 * 1 - 1);
    for (int k = 0; k < enemies.size(); k++)
    {
        for (int j = 0; j < 1/*enemy_types.size()*/; j++)
        {
            if (enemies[k].get_type() == 1/*enemy_types[j].type*/)
            {
                for (int i = 0; i < enemies[k].get_hitbox_x().size(); i++)
                {
                    buffer[enemies[k].get_y() + enemies[k].get_hitbox_y()[i]][enemies[k].get_x() + enemies[k].get_hitbox_x()[i]] = 204 * 256 * 256 + 51 * 256 + 153;
                }
            }
        }
    }
}

// free game data in this function
void finalize()
{
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
}

