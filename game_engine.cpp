#include "game_engine.h"
#include "grid_map.h"
#include "creep.h"
#include "creep_config.h"
#include "creep_factory.h"
#include "tower.h"
#include "tower_config.h"
#include "tower_factory.h"
#include "bullet.h"
#include "bullet_config.h"
#include "bullet_factory.h"

#include <cstddef>
#include <ciso646>
#include <list>

GameEngine::GameEngine() {
    _grid_map = new GridMap(30, 30, 20);
    _creep_factory = new CreepFactory();    
    _tower_factory = new TowerFactory();
    _bullet_factory = new BulletFactory();
}

GameEngine::~GameEngine() {
    delete _grid_map;
    _grid_map = NULL;
}

void GameEngine::run() {
    for (;;) {
        // main loop here  
        _handleEvents();
        
        // update creeps

        // update towers
        _updateTowers();

    }
}

void GameEngine::_handleEvents() {
    // TODO: implement
}

void GameEngine::_updateCreeps() {
    // Update the creeps' positions
    for (std::list<Creep *>::iterator icreep = _creeps.begin();
         icreep != _creeps.end();
         ++icreep) {
        (*icreep)->update();
        // delete dead creeps
        if ((*icreep)->isDead()) {
            delete (*icreep);
            icreep = _creeps.erase(icreep);
        }
    }
}

void GameEngine::_updateTowers() {

    // For each tower check to see whether it can hit any creep
    for (std::list<Tower *>::iterator itower = _towers.begin();
         itower != _towers.end(); 
         ++itower) {

        for (std::list<Creep *>::iterator icreep = _creeps.begin();
             icreep != _creeps.end();
             ++icreep) {
            // If successfully attacked a creep, generate bullets
            // and break;
            if ((*itower)->attack(*icreep)) {
                Bullet *bullet = 
                    _bullet_factory->getBullet(*itower, *icreep);
                _bullets.push_back(bullet);
                break;
            }
        } 
    }

}

void GameEngine::_updateBullets() {
   for (std::list<Bullet *>::iterator ibullet = _bullets.begin();
        ibullet != _bullets.end();
        ++ibullet) {
        (*ibullet)->update();
        // delete dead bullets
        if ((*ibullet)->isDead()) {
            delete (*ibullet); 
            ibullet = _bullets.erase(ibullet);
        }
   } 
}
