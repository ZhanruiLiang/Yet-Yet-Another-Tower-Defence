#ifndef TOWER_H
#define TOWER_H

#include <set>

// Forward declarations
class Creep;


// Base tower class
class Tower {

    public:
        
        Tower();
        virtual ~Tower();

        // Try to attack a creep 
        // Return true if the cooldown count has reached 0,
        // and the creep is within the tower's range
        bool attack(Creep *creep);

        // Set the coordinate of this tower on the grid map
        // Note: this method should only be called by GridMap
        void setCoord(int x, int y);

        // Set the attack range of this tower
        void setRange(double range);

        // Set the attack damage of this tower
        void setDamage(int damage);

        // Set the cooldown (attack interval) of the tower
        void setCooldown(int cooldown);

        // Get the attack range 
        double getRange() const;

        int getDamage() const;

        // Get the x and y coordinates of this tower on the grid map
        int getX() const;
        int getY() const;

    protected:

        int _x, _y;          // x and y coordinates

        double _range;       // attack range

        int _damage;      // attack damage

        int _cooldown;       // cooldown (attack interval)
        int _cooldown_count; // cooldown count
                             // the attack method will actually
                             // fire a bullet only when this count
                             // drops to zero
};

#endif
