#include <string>
#include "Controller.h"
#include "Hypha.h"

Hypha::Hypha(double srcX, double srcY, double nutrX, double nutrY) {
    srcLoc.x = srcX;
    srcLoc.y = srcY;
    nutrLoc.x = nutrX;
    nutrLoc.y = nutrY;
}

Hypha::Hypha(double srcX, double srcY, location_t nLoc) {
    srcLoc.x = srcX;
    srcLoc.y = srcY;
    nutrLoc = nLoc;
}

Hypha::Hypha(location_t sLoc, double nutrX, double nutrY) {
    srcLoc = sLoc;
    nutrLoc.x = nutrX;
    nutrLoc.y = nutrY;
}

Hypha::Hypha(location_t sLoc, location_t nLoc) {
    srcLoc = sLoc;
    nutrLoc = nLoc;
}

location_t Hypha::getLocation() {
    return nutrLoc;
}
