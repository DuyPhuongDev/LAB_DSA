#include<iostream>
#include<string>
using namespace std;

class Character {
private:
    int x;
    int y;
protected:
    int hp;
public:
    Character();
    Character(int hp, int x, int y);
    int getHp();
    void setHp(int hp);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getManhattanDistTo(Character* other);
    void operator()();
};
class Player : private Character{
public:
    Player() : Character(){}
    Player(int hp, int x, int y):Character(hp,x,y){}\
    void printPlayerData(){
        cout<<hp<<"-"<<Character::getX()<<"-"<<Character::getY()<<"\n";
    }
    void moveTo(int x, int y){
        Character::setX(x);
        Character::setY(y);
    }
};
int main(){
    Player pl1(100, 3, 6);
    pl1.printPlayerData();
    return 0;
}