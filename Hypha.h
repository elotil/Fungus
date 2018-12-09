class Hypha {
    private:
        location_t srcLoc;
        location_t nutrLoc;
    public:
        Hypha(double srcX, double srcY, double nutrX, double nutrY);
        Hypha(double srcX, double srcY, location_t nLoc);
        Hypha(location_t sLoc, double nutrX, double nutrY);
        Hypha(location_t sLoc, location_t nLoc);
        location_t getLocation();
};
