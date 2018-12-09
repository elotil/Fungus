class Spore {
    private:
        location_t loc;
    public:
        Spore();
        Spore(location_t l);
        Spore(double x, double y);
        void germinate();
        location_t getLocation();
};
