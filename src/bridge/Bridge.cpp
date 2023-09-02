//
// Created by axelmans on 1/09/23.
//

#include <iostream>
#include <memory>
using namespace std;

/*
 * Bridge: separate abstraction and implementation
 */

/*
 * Example: 2 characters and a weapon picker and equipment giver.
 * Instead of needing to define separate weapon picking and equipment giving
 * functions for both characters, we can separate the abstraction (= characters)
 * from the implementation (= weapon picking and equipment giving).
 *
 * This way, the implementation does not need to be defined per abstraction;
 * plus if the implementation would need to be altered, we don't need to alter it
 * for each and every abstraction.
 *
 */

namespace BridgePattern{


    /*
     * Equipper interface and 2 concrete classes.
     */
    struct Equipper{
        virtual void equip() = 0;
        ~Equipper() = default;
    };

    struct WeaponPicker: Equipper{
        void equip() override {
            cout << " was given a weapon";
        }
        ~WeaponPicker() = default;
    };

    struct ArtifactGiver: Equipper{
        void equip() override {
            cout << " and some of artifacts.\n";
        }
        ~ArtifactGiver() = default;
    };

    /*
     * Character interface and 2 concrete classes.
     */
    struct Character{
        unique_ptr<Equipper> w_e;
        unique_ptr<Equipper> a_g;
        string name;
        Character(){
            w_e = make_unique<WeaponPicker>();
            a_g = make_unique<ArtifactGiver>();
        }
        void ready() const {
            cout << name << " was called and";
            w_e->equip();
            a_g->equip();
        };
        ~Character() = default;
    };

    struct Yanfei: Character{
        Yanfei() : Character() {
            name = "Yanfei";
        }
    };

    struct Candace: Character{
        Candace() : Character() {
            name = "Candace";
        }
    };

    /*
     * Test scenario
     */
    static int main() {
        unique_ptr<Character> y(new Yanfei());
        y->ready();
        unique_ptr<Character> c(new Candace());
        c->ready();
        return 0;
    }

}