#include "game_engine.h"
#include "grid_map.h"
#include "creep.h"
#include "creep_config.h"
#include "creep_factory.h"
#include "tower.h"
#include "tower_config.h"
#include "tower_factory.h"

#include <cstddef>
#include <ciso646>
#include <list>

GameEngine::GameEngine() {
    _grid_map = new GridMap(30, 30, 20);
}

GameEngine::~GameEngine() {
    delete _grid_map;
    _grid_map = NULL;
}

void GameEngine::loop() {
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
    }
}

void GameEngine::_updateTowers() {

        // For each tower check to see, whether it can hit any creep
        for (std::list<Tower *>::iterator itower = _towers.begin();
             itower != _towers.end(); 
             ++itower) {

            for (std::list<Creep *>::iterator icreep = _creeps.begin();
                 icreep != _creeps.end();
                 ++icreep) {
                // If successfully attacked a creep, generate bullets
                // and break;
                // TODO: implement bullets
                if ((*itower)->attack(*icreep)) {
                    break;
                }
            } 
        }

}
