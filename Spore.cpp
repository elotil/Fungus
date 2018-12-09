#include <string>
#include "Controller.h"
#include "Spore.h"

Spore::Spore() {
    loc.x = 0;
    loc.y = 0;
}

Spore::Spore(location_t l) {
    loc = l;
}

Spore::Spore(double x, double y) {
    loc.x = x;
    loc.y = y;
}

void Spore::germinate() {

}

location_t Spore::getLocation() {
    return loc;
}
