#ifndef PLAYER_STATE
#define PLAYER_STATE

class playerState {
    public:
        playerState();
        int health = 100;
        int stamina = 100;
        int hunger = 100;
        int thirst = 100;

        void increaseHealth(int amount) {health += amount;}
        void decreaseHealth(int amount) {health -= amount;}

        void increaseStamina(int amount) {stamina += amount;}
        void decreaseStamina(int amount) {stamina -= amount;}

        void increaseHunger(int amount) {hunger += amount;}
        void decreaseHunger(int amount) {hunger -= amount;}

        void increaseThirst(int amount) {thirst += amount;}
        void decreaseThirst(int amount) {thirst -= amount;}
    private:
};

#endif