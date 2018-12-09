typedef struct location {
    int x;
    int y;
    bool operator==(const struct location& o) const {
        return (x == o.x && y == o.y);
    }
    bool operator!=(const struct location& o) const {
        return (x != o.x || y != o.y);
    }
} location_t;

class Hypha;
class Spore;
class Controller {
    private:
        bool** blockBoard;
        bool** fungusBoard;
        int size;
        long int rs;
    public:
        void initBoard(int size);
        location_t searchForNutrients(location_t loc, int radius);
        Hypha createHypha(location_t src, location_t dst, int radius);
        Spore createRandSeed(location_t src, int radius);
        bool** getBoard();
        void closeBoard();
        void printBoard();
        void printBlocks();
        std::string printToFile(int initS, int searchR, int blockR);
};
