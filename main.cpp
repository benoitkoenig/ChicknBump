#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "main.h"

//Tu dois absoluement refaire le tour de ton code et suprimer les pointeurs quand ils ne sont plus utilisés

int main() {
    Terrain* terrain;
    terrain = new Terrain();
    while (terrain->accueillir()==1)
        jeu(terrain);
    return 0;
}

void jeu(Terrain* terrain) {
    Poussin* p1 = new Poussin(172, 350, "jaune", sf::Key::Up, sf::Key::Left, sf::Key::Right);   //Tu ne delete aucun poussin à la fin
    Poussin* p2 = new Poussin(356, 275, "rouge", sf::Key::Z, sf::Key::Q, sf::Key::D);
    Poussin* p3 = new Poussin(597, 175, "magenta", sf::Key::F, sf::Key::C, sf::Key::B);
    Poussin* p4 = new Poussin(742, 323, "vert", sf::Key::I, sf::Key::J, sf::Key::L);
    sf::Event ev;
    sf::Clock chrono;
    sf::Music son;
    int continuer = 1;
    int inutile = 0;

    son.OpenFromFile("./datas/musique.ogg");
    son.SetLoop(true);
    son.Play();

    while ( continuer == 1 ) {
        deplacerpoussins(terrain, p1, p2, p3, p4);
        terrain->rafec(p1,p2,p3,p4);
        while(chrono.GetElapsedTime() < 0.02) {
            inutile++;
            inutile %= 547093;
        }
        chrono.Reset();
        terrain->interactions(ev, &continuer, p1, p2, p3, p4);
    }
}

void deplacerpoussins(Terrain* terrain, Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4) {
    p1->mouvement(terrain, p2, p3, p4);
    p2->mouvement(terrain, p1, p3, p4);
    p3->mouvement(terrain, p1, p2, p4);
    p4->mouvement(terrain, p1, p2, p3);
}

int sign(int x) {
    if ( x > 0 )
        return 1;
    if ( x < 0 )
        return -1;
    return 0;

}

int abs(int x) {
    if (x>=0)
        return x;
    return -x;
}

int min(int x, int y) {
    if (x < y)
        return x;
    return y;
}
