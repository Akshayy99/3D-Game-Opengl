#include "main.h"
#include "timer.h"
#include "plane.h"
#include "sea.h"
#include "volcano.h"
#include "speedometer.h"
#include "checkpoint.h"
#include "smoke.h"
#include "fuelmeter.h"
#include "needle.h"
#include "fuel.h"
#include "cannon.h"
#include "score.h"
#include "cannonballs.h"
#include "parachute.h"
#include "missile.h"
#include "bomb.h"
#include "arrow.h"
#include "compass.h"
#include "boundary.h"

using namespace std;

GLMatrices Matrices;
GLMatrices Matrices1;
GLuint     programID;
GLFWwindow *window;

#define TOWER_X 20.0f
#define TOWER_Z 20.0f
#define num_volcanoes 50
#define num_checkpoints 8
#define num_fuelups 50
#define num_cannonballs 10
#define num_parachutes 10
#define num_missiles 20
#define max_speed 15
#define num_bombs 20

int width  = 2000;
int height = 2000;
char display[200];
double xcur, ycur;
int view = 1;
int score = 0, level = 1, lives = 10;
int timer = 0;
float dist = 30.0f;
double direction;

bool looping_the_loop = false, barrel_roll = false;
bool roll_seedha = false, full_turn = false;
bool landed = false;
bool flying_close = false;

int cannonballs_zinda = 0;
int missiles_zinda = 0;
int bombs_zinda = 0;

int a0, a1, a2, a3, b0, b1, b2, b3, c0, c1, c2, c3, d0, d1, d2, d3, e0, e1, e2, e3, f0, f1, f2, f3, g0, g1, g2, g3;
int al, bl, cl, dl, el, fl, gl;
int a4, a5, b4, b5, c4, c5, d4, d5, e4, e5, f4, f5, g4, g5;
int ones, tens, huns, thou;
int onel, tenl;

Plane plane;
Sea sea;
Volcano volcanoes[num_volcanoes];
Speedometer speedometer; Needle needle;
Fuelmeter fuelmeter;
Checkpoint checkpoints[num_checkpoints];
Smoke rings[num_volcanoes];
Fuel fuelups[num_fuelups];
Parachute parachutes[num_parachutes];
Cannon cannons[num_checkpoints];
Cannonballs cannonballs[num_checkpoints*num_cannonballs];
Missile missiles[num_missiles];
Bomb bombs[num_bombs];
Arrow arrow;
Compass compass;
Boundary boundary[10];

bool zinda_cannonballs[num_cannonballs*num_checkpoints];
bool zinda_missiles[num_missiles];
bool zinda_bombs[num_bombs];

Score scorr[4];
Score levels[6];
Score live[7];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;
bool flag = true;
float eye_x = 0,eye_y = 20,eye_z = 30;
float target_x = 0, target_y = 0, target_z = 0;
float up_x = 0, up_y = 1, up_z = 0;
float speed_angle;

Timer t60(1.0 / 60);

void views()
{
    // FOLLOW-CAM VIEW
    if(view == 1)
    {
        up_x = sin(plane.roll * M_PI / 180.0f);
        up_y = cos(plane.roll * M_PI / 180.0f);
        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z;
        camera_rotation_angle = plane.yaw + 90;
        eye_x = target_x + dist * cos(camera_rotation_angle * M_PI / 180.0f);
        eye_y = target_y + 15.0f;
        eye_z = target_z + dist * sin(camera_rotation_angle * M_PI / 180.0f);
    }
    // PLANE VIEW
    else if(view == 2)
    {
        camera_rotation_angle = plane.yaw + 90;
        target_x = plane.position.x - dist/3 * cos(camera_rotation_angle * M_PI/180.0f);
        target_y = plane.position.y + plane.len*sin(plane.pitch * M_PI / 180.0f)/2;
        target_z = plane.position.z - dist/3 * sin(camera_rotation_angle * M_PI/180.0f);
        eye_x = target_x + dist/2 * cos(camera_rotation_angle * M_PI / 180.0f);
        eye_y = target_y + dist/4 -  plane.len*sin(plane.pitch * M_PI / 180.0f);
        eye_z = target_z + dist/2 * sin(camera_rotation_angle * M_PI / 180.0f);
        up_x = sin(plane.roll * M_PI / 180.0f);
        up_y = cos(plane.roll * M_PI / 180.0f);
    }
    // TOP VIEW
    else if(view == 3)
    {
        up_x = 0;
        up_y = 1;
        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z;
        camera_rotation_angle = plane.yaw + 90;
        eye_x = target_x+10;
        eye_y = target_y + 5 * dist;
        eye_z = target_z-10;
    }
    // TOWER VIEW
    else if(view == 4)
    {
        up_x = 0;
        up_y = 1;
        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z;
		eye_x = plane.position.x + 4*dist*cos(plane.yaw*M_PI/180.0f);
		eye_y = plane.position.y + 3*dist;
		eye_z = plane.position.z + 4*dist*sin(plane.yaw*M_PI/180.0f);       
    }
    // HELICOPTER VIEW
    else if(view == 5)
    {
        up_x = 0;
        up_y = 1;
        glfwGetCursorPos(window, &xcur, &ycur);
        if(xcur > 2000) xcur = 2000;
        if(xcur < 0) xcur = 0;
        float x = ((width/2 - xcur)/width)*2;
        float y = ((height/2 - ycur)/height)*2;
        float z = (sqrt(2-x*x -y*y));
        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z;
        eye_x = plane.position.x - 2*dist * x;
        eye_y = plane.position.y -2*dist * y;
        eye_z = plane.position.z + 2*dist * z;
	}  
    // BONUS VIEW : HOVER AROUND VIEW
    else if(view == 6)
    {
        up_x = 0;
        up_y = 1;
        camera_rotation_angle += 1;
        target_x = plane.position.x;
        target_y = plane.position.y;
        target_z = plane.position.z;
        eye_x = target_x + dist * cos(camera_rotation_angle * M_PI / 180.0f);
        eye_y = target_y + dist/2;
        eye_z = target_z + dist * sin(camera_rotation_angle * M_PI / 180.0f);        
    }

}

void seven_segment_logic()
{
    ones = score % 10;
    tens = (score / 10) % 10;
    huns = (score / 100) % 10;
    thou = (score / 1000) % 10;
    onel = lives % 10;
    tenl = lives/10;
    a0   = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==7 || huns==8 || huns==9) ? 1: 0;
    a1   = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==7 || tens==8 || tens==9) ? 1: 0;
    a2   = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==7 || ones==8 || ones==9) ? 1: 0;
    b0   = (huns==0 || huns==2 || huns==3 || huns==1 || huns==4 || huns==7 || huns==8 || huns==9) ? 1: 0;
    b1   = (tens==0 || tens==2 || tens==3 || tens==1 || tens==4 || tens==7 || tens==8 || tens==9) ? 1: 0;
    b2   = (ones==0 || ones==2 || ones==3 || ones==1 || ones==4 || ones==7 || ones==8 || ones==9) ? 1: 0;
    c0   = (huns==0 || huns==1 || huns==3 || huns==4 || huns==5 || huns==6 || huns==7 || huns == 8 || huns == 9) ? 1: 0;
    c1   = (tens==0 || tens==1 || tens==3 || tens==4 || tens==5 || tens==6 || tens==7 || tens == 8 || tens == 9) ? 1: 0;
    c2   = (ones==0 || ones==1 || ones==3 || ones==4 || ones==5 || ones==6 || ones==7 || ones == 8 || ones == 9) ? 1: 0;
    d0   = (huns==0 || huns==2 || huns==3 || huns==5 || huns==6 || huns==8 || huns==9) ? 1: 0;
    d1   = (tens==0 || tens==2 || tens==3 || tens==5 || tens==6 || tens==8 || tens==9) ? 1: 0;
    d2   = (ones==0 || ones==2 || ones==3 || ones==5 || ones==6 || ones==8 || ones==9) ? 1: 0;
    e0   = (huns==0 || huns==2 || huns==6 || huns==8) ? 1 : 0;
    e1   = (tens==0 || tens==2 || tens==6 || tens==8) ? 1 : 0;
    e2   = (ones==0 || ones==2 || ones==6 || ones==8) ? 1 : 0;
    f0   = (huns==0 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
    f1   = (tens==0 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
    f2   = (ones==0 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;
    g0   = (huns==2 || huns==3 || huns==4 || huns==5 || huns==6 || huns==8 || huns==9) ? 1 : 0;
    g1   = (tens==2 || tens==3 || tens==4 || tens==5 || tens==6 || tens==8 || tens==9) ? 1 : 0;
    g2   = (ones==2 || ones==3 || ones==4 || ones==5 || ones==6 || ones==8 || ones==9) ? 1 : 0;
    a3   = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==7 || thou==8 || thou==9) ? 1: 0;
    b3   = (thou==0 || thou==2 || thou==3 || thou==1 || thou==4 || thou==7 || thou==8 || thou==9) ? 1: 0;
    c3   = (thou==0 || thou==1 || thou==3 || thou==4 || thou==5 || thou==6 || thou==7 || thou == 8 || huns == 9) ? 1: 0;
    d3   = (thou==0 || thou==2 || thou==3 || thou==5 || thou==6 || thou==8 || thou==9) ? 1: 0;
    e3   = (thou==0 || thou==2 || thou==6 || thou==8) ? 1 : 0;
    f3   = (thou==0 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;
    g3   = (thou==2 || thou==3 || thou==4 || thou==5 || thou==6 || thou==8 || thou==9) ? 1 : 0;
    
    al = (level==0 || level==2 || level==3 || level==5 || level==6 || level==7 || level==8 || level==9) ? 1: 0;
    bl = (level==0 || level==2 || level==3 || level==1 || level==4 || level==7 || level==8 || level==9) ? 1: 0;
    cl = (level==0 || level==1 || level==3 || level==4 || level==5 || level==6 || level==7 || level == 8 || level == 9) ? 1: 0;
    dl = (level==0 || level==2 || level==3 || level==5 || level==6 || level==8 || level==9) ? 1: 0;
    el = (level==0 || level==2 || level==6 || level==8) ? 1 : 0;
    fl = (level==0 || level==4 || level==5 || level==6 || level==8 || level==9) ? 1 : 0;
    gl = (level==2 || level==3 || level==4 || level==5 || level==6 || level==8 || level==9) ? 1 : 0;

    a4 = (tenl==0 || tenl==2 || tenl==3 || tenl==5 || tenl==6 || tenl==7 || tenl==8 || tenl==9) ? 1: 0;
    a5 = (onel==0 || onel==2 || onel==3 || onel==5 || onel==6 || onel==7 || onel==8 || onel==9) ? 1: 0;
    b4 = (tenl==0 || tenl==2 || tenl==3 || tenl==1 || tenl==4 || tenl==7 || tenl==8 || tenl==9) ? 1: 0;
    b5 = (onel==0 || onel==2 || onel==3 || onel==1 || onel==4 || onel==7 || onel==8 || onel==9) ? 1: 0;
    c4 = (tenl==0 || tenl==1 || tenl==3 || tenl==4 || tenl==5 || tenl==6 || tenl==7 || tenl == 8 || tenl == 9) ? 1: 0;
    c5 = (onel==0 || onel==1 || onel==3 || onel==4 || onel==5 || onel==6 || onel==7 || onel == 8 || onel == 9) ? 1: 0;
    d4 = (tenl==0 || tenl==2 || tenl==3 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1: 0;
    d5 = (onel==0 || onel==2 || onel==3 || onel==5 || onel==6 || onel==8 || onel==9) ? 1: 0;
    e4 = (tenl==0 || tenl==2 || tenl==6 || tenl==8) ? 1 : 0;
    e5 = (onel==0 || onel==2 || onel==6 || onel==8) ? 1 : 0;
    f4 = (tenl==0 || tenl==4 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1 : 0;
    f5 = (onel==0 || onel==4 || onel==5 || onel==6 || onel==8 || onel==9) ? 1 : 0;
    g4 = (tenl==2 || tenl==3 || tenl==4 || tenl==5 || tenl==6 || tenl==8 || tenl==9) ? 1 : 0;
    g5 = (onel==2 || onel==3 || onel==4 || onel==5 || onel==6 || onel==8 || onel==9) ? 1 : 0;
}
void draw() 
{
    timer++;
    timer %= 60;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);
    // -------VIEWS----------
    views();
    glm::vec3 eye ( eye_x, eye_y, eye_z);
    glm::vec3 target (target_x, target_y, target_z);
    glm::vec3 up (up_x, up_y, up_z);
    Matrices.view = glm::lookAt(eye, target,  up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::vec3 ey1 (0,0,1);
    glm::vec3 t1(0,0,-5);
    glm::vec3 u1(0,1,0);
    Matrices1.view = glm::lookAt(ey1, t1, u1);
    glm::mat4 VP1 = Matrices1.projection ;
    glm::mat4 MVP1;

    // Scene render
    speedometer.draw(VP1); needle.draw(VP1); fuelmeter.draw(VP1); 
    compass.draw(VP1);
    if(level!=9)arrow.draw(VP);
    plane.draw(VP); sea.draw(VP); 
    seven_segment_logic();
    scorr[0].draw(VP1, a0, b0, c0, d0, e0, f0, g0, 0);
    scorr[1].draw(VP1, a1, b1, c1, d1, e1, f1, g1, 0);
    scorr[2].draw(VP1, a2, b2, c2, d2, e2, f2, g2, 0);
    scorr[3].draw(VP1, a3, b3, c3, d3, e3, f3, g3, 0);
    
    levels[0].draw(VP1, 0, 0, 0, 1, 1, 1, 0, 0);
    levels[1].draw(VP1, 1, 0, 0, 1, 1, 1, 1, 0);
    levels[2].draw(VP1, 0, 0, 0, 0, 0, 0, 0, 1);
    levels[3].draw(VP1, 1, 0, 0, 1, 1, 1, 1, 0);
    levels[4].draw(VP1, 0, 0, 0, 1, 1, 1, 0, 0);
    levels[5].draw(VP1, al, bl, cl, dl, el, fl, gl, 0);
    
    live[0].draw(VP1, 0, 0, 0, 1, 1, 1, 0, 0);
    live[1].draw(VP1, 0, 1, 1, 0, 0, 0, 0, 0);
    live[2].draw(VP1, 0, 0, 0, 0, 0, 0, 0, 1);
    live[3].draw(VP1, 1, 0, 0, 1, 1, 1, 1, 0);
    live[4].draw(VP1, 1, 0, 1, 1, 0, 1, 1, 0);
    live[5].draw(VP1, a4, b4, c4, d4, e4, f4, g4, 0);
    live[6].draw(VP1, a5, b5, c5, d5, e5, f5, g5, 0);
    boundary[0].draw(VP1);
    boundary[1].draw(VP1);
    boundary[2].draw(VP1);
    boundary[3].draw(VP1);
    boundary[4].draw(VP1);
    boundary[5].draw(VP1);
    boundary[6].draw(VP1);
    boundary[7].draw(VP1);
    // for(int i=1;i<8;i++)
    // {
    //     boundary[i].draw(VP1);
    // }
    for(int i = 0 ; i < num_volcanoes ; ++i)
    {
        volcanoes[i].draw(VP);
        rings[i].draw(VP);
    }
    for(int i = 0 ; i < num_fuelups ; ++i)
    {
        if(!fuelups[i].taken) fuelups[i].draw(VP);
    }
    for(int i = 0 ; i < num_checkpoints ; ++i)
    {
        if(!checkpoints[i].taken)
        {
            checkpoints[i].draw(VP);
            cannons[i].draw(VP);
        }
        else  cannons[i].killed = true;
    }
    for(int i=0;i<num_checkpoints;i++)
    {
        if(!cannons[i].killed)
        {
            zinda_cannonballs[i] = true;
            if(zinda_cannonballs[i]) cannonballs[i].draw(VP);
        }
    }
    for(int i=0;i<num_missiles;++i)
    {
        if(zinda_missiles[i]) missiles[i].draw(VP);
    }
    for(int i=0;i<num_bombs;++i)
    {
        if(zinda_bombs[i]) bombs[i].draw(VP);
    }
    for(int i=0;i<num_parachutes;++i)
    {
        if(!parachutes[i].killed) parachutes[i].draw(VP);
    }
}

void tick_input(GLFWwindow *window) 
{
    plane.rise = false;
    plane.fall = false;
    roll_seedha = true;
    
    // movement keys
    int Q     = glfwGetKey(window, GLFW_KEY_Q);
    int E     = glfwGetKey(window, GLFW_KEY_E);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int W     = glfwGetKey(window, GLFW_KEY_W);
    int S     = glfwGetKey(window, GLFW_KEY_S);
    int A     = glfwGetKey(window, GLFW_KEY_A);
    int D     = glfwGetKey(window, GLFW_KEY_D);
    int X     = glfwGetKey(window, GLFW_KEY_X);
    int L     = glfwGetKey(window, GLFW_KEY_L);
    int B     = glfwGetKey(window, GLFW_KEY_B);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int down  = glfwGetKey(window, GLFW_KEY_DOWN);
    int enter  = glfwGetKey(window, GLFW_KEY_ENTER);

    // views
    int v1    = glfwGetKey(window, GLFW_KEY_1);
    int v2    = glfwGetKey(window, GLFW_KEY_2);
    int v3    = glfwGetKey(window, GLFW_KEY_3);
    int v4    = glfwGetKey(window, GLFW_KEY_4);
    int v5    = glfwGetKey(window, GLFW_KEY_5);
    int v6    = glfwGetKey(window, GLFW_KEY_6);
    int v7    = glfwGetKey(window, GLFW_KEY_7);

    // yaw+
    if(Q && !landed) 
    {
        plane.yaw -= 1;
        reset_screen();
    }
    // yaw-
    if(E && !landed) 
    {
        plane.yaw += 1; 
        reset_screen();
    }
    // speedup
    if(W) 
    {
        if(plane.speed < max_speed-1) plane.speed += 0.04;
        if(landed)
        {
            plane.speed = 2;
            plane.position.y += 0.2;
            landed = false;
        }
    }
    // chutiya cheez
    if(X && !landed) 
    {
        // plane.position.z += 2*plane.speed*cos(plane.yaw * M_PI / 180.0f);
        // plane.position.x -= 2*plane.speed*sin(plane.yaw * M_PI / 180.0f);
        plane.speed -= 0.02;
    }
    // pitch and rise
    if(space) 
    {
        plane.rise = true;
        if(landed)
        {
            plane.position.y += 0.3;
            if(plane.speed < 3)plane.speed += 0.2;
            landed = false;
        }
    }
    // looping the loop
    if(L && !landed) 
    {
        if(!looping_the_loop) score += 50;
        looping_the_loop = true;
    }
    // barrel roll
    if(B && !landed) 
    {
        if(!barrel_roll) score += 150;
        barrel_roll = true;
    }
    // altitude--
    if(S && !landed) 
    {
        // plane.position.y -= 1;
        plane.fall = true;
    }
    // roll right
    if(A && !landed) 
    {
        if(plane.roll > -35)
            plane.roll -= 0.7;
        roll_seedha = false;
    }
    // roll left
    if(D && !landed) 
    {
        roll_seedha = false;
        if(plane.roll < 35) plane.roll += 0.7;
    }
    // views
    if(v1) 
    {
        view = 1;
    }
    if(v2) 
    {
        view = 2;
    }
    if(v3) 
    {
        view = 3;
    }
    if(v4) 
    {
        view = 4;
    }
    if(v5) 
    { 
        view = 5;
    }
    if(v6) 
    {
        view = 6;
    }
    if(!timer % 30)
    {
        for(int i=0;i<num_checkpoints;i++)
        {
            cannonballs[i] = Cannonballs(cannons[i].position.x-7, cannons[i%num_checkpoints].position.y+7, cannons[i%num_checkpoints].position.z-7);
            zinda_cannonballs[cannonballs_zinda%num_cannonballs] = true;
            cannonballs[i].hit = false;
            cannonballs_zinda++;
        }
    }
    if(up)
    {
        missiles[missiles_zinda%num_missiles] = Missile(plane.position.x, plane.position.y, plane.position.z);
        missiles[missiles_zinda%num_missiles].yaw = plane.yaw;
        zinda_missiles[missiles_zinda%num_missiles] = true;
        missiles_zinda++;
    }
    if(enter && !timer%30)
    {
        bombs[bombs_zinda%num_bombs] = Bomb(plane.position.x-3*sin(plane.yaw*M_PI/180.0f), plane.position.y-5, plane.position.z+5*cos(plane.yaw*M_PI/180.0f));
        bombs[bombs_zinda%num_bombs].yaw = plane.yaw;
        zinda_bombs[bombs_zinda%num_bombs] = true;
        bombs_zinda++;
    }

}

void arrow_tick()
{
    arrow.position.x = target_x ;
    arrow.position.y = target_y + 10;
    arrow.position.z = target_z - 10;
    arrow.direction.x = (checkpoints[level-1].position.x - plane.position.x);
    arrow.direction.y = (checkpoints[level-1].position.y - plane.position.y);
    arrow.direction.z = (-plane.position.z + checkpoints[level-1].position.z);
}

void cannonballs_tick()
{
    for(int i=0;i<num_checkpoints * num_cannonballs;i++)
    {
        if(zinda_cannonballs[i]) 
        {
            cannonballs[i].position.x -= cannonballs[i].speed * (cannons[i].position.x - plane.position.x)/dis(plane.position.x, 0, plane.position.z, cannons[i].position.x, 0, cannons[i].position.z);
            cannonballs[i].position.z += cannonballs[i].speed * (cannons[i].position.z - plane.position.z)/dis(plane.position.x, 0, plane.position.z, cannons[i].position.x, 0, cannons[i].position.z);
            cannonballs[i].downspeed   = -2*cannonballs[i].speed * (cannons[i].position.y - plane.position.y)/dis(plane.position.x, plane.position.y, plane.position.z, cannons[i].position.x, cannons[i].position.y, cannons[i].position.z)+1;
            cannonballs[i].tick();
        }
        if(cannonballs[i].position.y < -140 && zinda_cannonballs[i]) 
        {
            cannonballs[i].hit = true;
            zinda_cannonballs[i] = false;
            cannonballs_zinda--;
        }
    }
}

void missiles_tick()
{
    for(int i=0;i<num_missiles;++i)
    {
        if(zinda_missiles[i]) 
        {
            missiles[i].position.x += missiles[i].speed * sin(missiles[i].yaw * M_PI/180.0f);
            missiles[i].position.z -= missiles[i].speed * cos(missiles[i].yaw * M_PI/180.0f);
        }
    }
}
void bombs_tick()
{
    for(int i=0;i<num_bombs;++i)
    {
        // cout<<bombs_zinda<<endl;
        if(zinda_bombs[i]) 
        {
            bombs[i].position.x += plane.speed * sin(bombs[i].yaw * M_PI/180.0f);
            bombs[i].position.z -= plane.speed * cos(bombs[i].yaw * M_PI/180.0f);
            bombs[i].tick();
        }
        if(bombs[i].position.y <= sea.position.y && zinda_bombs[i])
        {
            // cout << "mara" << endl;
            bombs[i].hit = true;
            zinda_bombs[i] = false;
            bombs_zinda--;
        }
    }
}

void collisions()
{
    // fuelup collision
    for(int i = 0 ; i < num_fuelups ; ++i)
    {
        if(abs(plane.position.x - fuelups[i].position.x) < 15)
        {
            if(abs(plane.position.y - fuelups[i].position.y) < 15)
            {
                if(abs(plane.position.z - fuelups[i].position.z) < 15)
                {
                    fuelups[i].taken = true;
                    fuelmeter.fuel = fuelmeter.length;
                }
            }
        }
    }
    // parachute collision
    for(int i = 0 ; i < num_parachutes ; ++i)
    {
        if(abs(plane.position.x - parachutes[i].position.x) <= parachutes[i].radius && !parachutes[i].killed)
        {
            if(parachutes[i].position.y - plane.position.y < 85)
            {
                if(abs(plane.position.z - parachutes[i].position.z) <= parachutes[i].radius)
                {
                    parachutes[i].killed = true;
                    lives--;
                }
            }
        }
        for(int i = 0 ; i < num_missiles ; i++)
        {
            if(abs(missiles[i].position.x - parachutes[i].position.x) <= parachutes[i].radius && !parachutes[i].killed)
            {
                if(parachutes[i].position.y - missiles[i].position.y < 85)
                {
                    if(abs(missiles[i].position.z - parachutes[i].position.z) <= parachutes[i].radius)
                    {
                        parachutes[i].killed = true;
                        score += 50;
                    }
                }
            }
        }
    }
    // bomb-checkpoint collision
    for(int i=0;i<num_checkpoints;++i)
    {
        for(int j=0;j<num_bombs;++j)
        {
            if(abs(checkpoints[i].position.x-bombs[j].position.x) < checkpoints[i].length && !checkpoints[i].taken && zinda_bombs[j])
            {
                if(abs(checkpoints[i].position.z-bombs[j].position.z) < checkpoints[i].length)
                {
                    if(bombs[j].position.y <= checkpoints[i].position.y)
                    {
                        cannons[i].killed = true;
                        if(i+1 == level)
                        {
                            checkpoints[i].taken = true;
                            bombs[j].hit = true;
                            zinda_bombs[j] = false;
                            level++;
                            fuelmeter.fuel = fuelmeter.length;
                            score += 500;
                        }
                    }
                }
            }
        }
    }
    // plane-rings
    for(int i = 0 ; i < num_volcanoes ; ++i)
    {
        if(abs(plane.position.x - rings[i].position.x) <= rings[i].r_out && !rings[i].scored)
        {
            if(abs(plane.position.y - rings[i].position.y) <= rings[i].r_out)
            {
                if(abs(plane.position.z-rings[i].position.z) <= 5)
                {
                    rings[i].scored = true;
                    score += 100;
                }
            }
        }
    }
    // volcano no-flying zone detection
    for(int i=0;i<num_volcanoes;++i)
    {
        if(plane.position.y - volcanoes[i].position.y <= 120)
        {
            if(abs(plane.position.x - volcanoes[i].position.x) <= 50)
            {
                if(abs(plane.position.z - volcanoes[i].position.z) <= 50)
                {
                    flying_close = true;
                }
            }
        }
    }
    // plane-cannonballs collision
    for(int i=0;i<num_checkpoints*num_cannonballs;i++)
    {
        if(zinda_cannonballs[i] && !cannonballs[i].hit && abs(plane.position.x-cannonballs[i].position.x) < 100)
        {
            if(abs(plane.position.z - cannonballs[i].position.z) < 100)
            {
                if(abs(plane.position.y - cannonballs[i].position.y) < 100)
                {
                    cannonballs[i].hit = true;
                    zinda_cannonballs[i] = false;
                    lives--;
                }
            }
        }
    }
}

void plane_ticks()
{
    if(plane.rise && plane.pitch <= 20)
    {
        plane.pitch += 0.3;
    }
    else if(!plane.rise && plane.pitch > 0)
    {
        plane.pitch -= 0.3;
    }
    if(plane.pitch < 0) plane.pitch = 0;
    if(barrel_roll) looping_the_loop = false;
    if(looping_the_loop) barrel_roll = false;
    if(looping_the_loop)
    {   
        if(!full_turn)
        {
            plane.pitch += 2;
            plane.speed += 0.01;
        }
        else 
        {
            plane.pitch = 0;
            looping_the_loop = false;
            full_turn = false;
        }
    }
    if(barrel_roll)
    {
        if(!full_turn) 
        {
            plane.pitch += 2;
            plane.speed += 0.01;
            plane.roll -= 1.83;
        }
        else 
        {
            plane.pitch = 0;
            plane.roll = 0;
            barrel_roll = false;
            full_turn = false;
        }
    }
    if(abs(plane.roll) >= 360)
    {
        plane.roll -= ((plane.roll > 0) ? 1 : -1) * 360;
        full_turn = true;
    }
    if(abs(plane.yaw) > 360)
    {
        plane.yaw -= ((plane.yaw > 0) ? 1 : -1) * 360;
    }
    if(plane.pitch > 360)
    {
        plane.pitch -= 360;
        full_turn = true;
    }
    if(roll_seedha && !barrel_roll && !looping_the_loop)
    {
        if(abs(plane.roll) > 0.1)
        {
            plane.roll -= plane.roll/40;
        }
        else 
        {
            plane.roll = 0;
            roll_seedha = false;
        }       
    }
    for(int i=0;i<num_checkpoints;i++)
    {
        if(abs(checkpoints[i].position.x-plane.position.x) < checkpoints[i].length && abs(checkpoints[i].position.z-plane.position.z) < checkpoints[i].length)
        {
            if(plane.position.y <= -88)
            {
                plane.position.y = -88;
                landed = true;
                break;
            }
        }
        landed = false;
    }
    if(landed )
    {
        if(plane.speed > 0)
            plane.speed -= 0.3;
        else plane.speed = 0;
    }
}
void tick_elements() {
    
    plane.tick();
    plane_ticks();
    speed_angle = (float)plane.speed*180/max_speed;
    needle.rot = -speed_angle;

    compass.rotate = -plane.yaw * M_PI/180.0f;
    arrow_tick();
    for(int i=0;i<num_volcanoes;i++)
    {
        rings[i].tick();
    }
    fuelmeter.tick();
    sea.position.x = plane.position.x;
    sea.position.z = plane.position.z;
    cannonballs_tick();
    missiles_tick();
    bombs_tick();
    collisions();
}

void initGL(GLFWwindow *window, int width, int height) {

    plane       = Plane(0, 0, 0, COLOR_PLANE);
    sea         = Sea(0, -100, 0);
    speedometer = Speedometer(-3.0, -2.9, -20);
    needle      = Needle(-3.0, -2.9, 0);
    fuelmeter   = Fuelmeter(-3.8, -3.8, -20);
    arrow       = Arrow(0,3.5,0);
    compass     = Compass(-3.0, -1.2, -20);
    scorr[0]    = Score(screen_center_x+4/screen_zoom-0.7, screen_center_y + 4/screen_zoom-0.1);
    scorr[1]    = Score(scorr[0].position.x + 0.3, scorr[0].position.y);
    scorr[2]    = Score(scorr[1].position.x + 0.3, scorr[1].position.y);
    scorr[3]    = Score(scorr[0].position.x - 0.3, scorr[0].position.y);

    levels[0]   = Score(screen_center_x-4/screen_zoom+0.5, screen_center_y + 4/screen_zoom-0.1);
    levels[1]   = Score(levels[0].position.x + 0.3, levels[0].position.y);
    levels[2]   = Score(levels[1].position.x + 0.3, levels[0].position.y);
    levels[3]   = Score(levels[2].position.x + 0.3, levels[0].position.y);
    levels[4]   = Score(levels[3].position.x + 0.3, levels[0].position.y);
    levels[5]   = Score(levels[3].position.x + 0.6, levels[0].position.y) ;

    live[0]     = Score(screen_center_x+4/screen_zoom-2.1, screen_center_y - 4/screen_zoom+0.7);
    live[1]     = Score(live[0].position.x + 0.3, live[0].position.y);
    live[2]     = Score(live[1].position.x + 0.3, live[0].position.y);
    live[3]     = Score(live[2].position.x + 0.3, live[0].position.y);
    live[4]     = Score(live[3].position.x + 0.3, live[0].position.y);
    live[5]     = Score(live[4].position.x + 0.4, live[0].position.y);
    live[6]     = Score(live[5].position.x + 0.3, live[0].position.y);

    boundary[0] = Boundary(-1.9,-0.2,0);
    boundary[1] = Boundary(-1.9,-0.2,0);
    boundary[1].rotation = 90;
    boundary[2] = Boundary(-1.7, 3.2, 0);
    boundary[3] = Boundary(-1.7, 8.2, 0);
    boundary[3].rotation = 90;
    boundary[4] = Boundary(2.6, 8.2, 0);
    boundary[4].rotation = 90;
    boundary[5] = Boundary(7.6, 3.2, 0);
    boundary[6] = Boundary(6.4, -3.2, 0);
    boundary[7] = Boundary(1.4+boundary[1].thic, -3.2, 0);
    boundary[7].rotation = 90;
    // volcanoes
    for(int i = 0 ; i < num_volcanoes ; i++)
    {
        volcanoes[i] = Volcano(0, -160, -200*i);
    }
    // smoke rings
    for(int i = 0 ; i < num_volcanoes ; i++)
    {
        rings[i] = Smoke(0, -150, -200*i);
    }
    //checkpoints and cannons
    for(int i = 0 ; i < num_checkpoints ; i++)
    {
        checkpoints[i] = Checkpoint(400*(i+1), -90, -600*(i+1));
        cannons[i]     = Cannon(checkpoints[i].position.x + 150, -150, checkpoints[i].position.z+150);
    }
    // fuelups
    for(int i = 0 ; i < num_fuelups ; ++i)
    {
        fuelups[i] = Fuel(250 * i + 40, 5, -200 * i);
    }
    // parachutes
    for(int i=0;i<num_parachutes;++i)
    {
        parachutes[i] = Parachute(200*(i+1), 50, -1000*(i+1));
    }
    // cannonballs
    for(int i=0;i<num_checkpoints;i++)
    {
        cannonballs[i] = Cannonballs(cannons[i].position.x-7, cannons[i%num_checkpoints].position.y+7, cannons[i%num_checkpoints].position.z-7);
        zinda_cannonballs[cannonballs_zinda%num_cannonballs] = true;
        cannonballs[i].hit = false;
        cannonballs_zinda++;
    }
    // missiles
    for(int i=0;i<num_missiles;++i)
    {
        missiles[i] = Missile(0,0,0);
        zinda_missiles[missiles_zinda%num_missiles] = true;
        missiles[i].hit = false;
        missiles_zinda++;
    }
    // bombs
    for(int i=0;i<num_bombs;++i)
    {
        bombs[i] = Bomb(0,0,0);
        zinda_bombs[bombs_zinda%num_bombs] = true;
        bombs[i].hit = false;
        bombs_zinda++;
    }


    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    Matrices1.MatrixID = glGetUniformLocation(programID, "MVP1");

    reshapeWindow (window, width, height);

    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
}


int main(int argc, char **argv) {
    srand(time(0));
    window = initGLFW(width, height);
    initGL (window, width, height);
    sprintf(display, "Link's Jet Plane!");
    glfwSetWindowTitle(window, display);

    while (!glfwWindowShouldClose(window) && lives && fuelmeter.fuel) {

        if (t60.processTick()) {
            draw();
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            if(lives == 0)
            {
                cout << "Lives Over. GAME ENDED :(" << endl;
                break;
            }
            if(flying_close)
            {
                cout << "Flying too close to the volcano. You die :-((" << endl;
                break;
            }
            if(fuelmeter.fuel <= 0)
            {
                cout << "Plane is out of fuel! CRASH!!" << endl;
                break;
            }
            if(level==9)
            {
                cout << "YOU WON!! ALL CHECKPOINTS HAVE BEEN CLAIMED ^_^" << endl;
                break;
            }
        }
        glfwPollEvents();
    }
    quit(window);
}   

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

float dis(float x1, float y1, float z1, float x2, float y2, float z2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z2-z1,2));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(45.0f, (right-left)/(top-bottom), 0.1f, 2000.0f);
    Matrices1.projection = glm::ortho(left, right, bottom, top, 0.0f, 500.0f);
}
