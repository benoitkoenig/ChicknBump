#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

class Terrain;
int sign(int x);
int abs(int x);
int min(int x, int y);


class Poussin {
public:
    Poussin(int x, int y, std::string couleur, sf::Key::Code u, sf::Key::Code l, sf::Key::Code r);
    ~Poussin();
    sf::Sprite* rafec(int, int, Terrain*);
    void mouvement(Terrain*, Poussin* v1, Poussin* v2, Poussin* v3);
    int alleradroite(Terrain*, Poussin* p1, Poussin* p2, Poussin* p3);
    int alleragauche(Terrain*, Poussin* p1, Poussin* p2, Poussin* p3);
    void tomber(Terrain*, Poussin* p1, Poussin* p2, Poussin* p3);
    void respawn(Terrain *terrain, Poussin* p1, Poussin* p2, Poussin* p3);
    void sauter(Terrain *terrain);
    void calculsaut();
    void bouger(sf::Key::Code touche, Terrain* terrain, int pressed);
private:
    int gauche, droite;
    int x, y;
    sf::Image* img;
    sf::Image* img0;
    sf::Image* img1;
    sf::Sprite* spt;
    sf::Sprite* sptmoves[2];
    float mvmt;
    int saut;
    sf::Key::Code up, down, left, right;
    sf::Music pet;
};
