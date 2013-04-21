#include <SFML/Graphics.hpp>
#include <iostream>

#include "Poussin.h"
#include "terrain.h"

Poussin::Poussin(int a, int b, std::string couleur, sf::Key::Code u, sf::Key::Code l, sf::Key::Code r) {
    x = a;
    y = b;
    img = new sf::Image();
    img0 = new sf::Image();
    img1 = new sf::Image();
    img->LoadFromFile("./datas/poussin"+couleur+".png");
    img0->LoadFromFile("./datas/poussin"+couleur+"0.png");
    img1->LoadFromFile("./datas/poussin"+couleur+"1.png");
    sptmoves[0] = new sf::Sprite(*img0);
    sptmoves[1] = new sf::Sprite(*img1);
    spt = new sf::Sprite(*img);
    sptmoves[0]->SetCenter(16, 16);
    sptmoves[1]->SetCenter(16, 16);
    spt->SetCenter(16, 15);
    mvmt = 0;
    saut = 0, gauche = 0, droite = 0;
    up = u, left = l, right = r;
    pet.OpenFromFile("./datas/pet.ogg");
}

Poussin::~Poussin() {
}

sf::Sprite* Poussin::rafec(int terl, int terh, Terrain* terrain) {
    int mvbis = (int) mvmt;
    if ( gauche == 1 && droite == 0 ) {
        spt->FlipX(true);
        sptmoves[0]->FlipX(true);
        sptmoves[1]->FlipX(true);
    }
    if ( gauche == 0 && droite == 1 ) {
        spt->FlipX(false);
        sptmoves[0]->FlipX(false);
        sptmoves[1]->FlipX(false);
    }
    if (( gauche == 0 && droite == 0 ) || !( terrain->donnerPixel(x-12, y+15) == 0 || terrain->donnerPixel(x, y+15) == 0 || terrain->donnerPixel(x+12, y+15) == 0))  {
        spt->SetPosition(terl+x, terh+y);
        return spt;
    }
    else {
    sptmoves[mvbis]->SetPosition(terl+x, terh+y);
    mvmt += 0.35;
    if ( mvmt > 2 )
        mvmt = 0;
    return sptmoves[mvbis];
    }

}

void Poussin::mouvement(Terrain *terrain, Poussin* v1, Poussin* v2, Poussin* v3) {
    if (droite==1 && gauche==0)
        this->alleradroite(terrain, v1, v2, v3);
    if (droite==0 && gauche==1)
        this->alleragauche(terrain, v1, v2, v3);
    saut++;
    if ((terrain->donnerPixel(x-12, y-15)==0 || terrain->donnerPixel(x, y-15)==0 || terrain->donnerPixel(x+12, y-15)==0) && saut<0)
        saut = 0;
    if ((terrain->donnerPixel(x-12, y+15)==0 || terrain->donnerPixel(x, y+15)==0 || terrain->donnerPixel(x+12, y+15)==0) && saut>0)
        saut = 0;
    tomber(terrain, v1, v2, v3);
}

int Poussin::alleradroite(Terrain *terrain, Poussin* p1, Poussin* p2, Poussin* p3) {
    Poussin* vilains[] = {p1, p2, p3};
    Poussin* vilain;
    int i, j;
    for(i=0;i<6;i++) {
        if ( terrain->donnerPixel(x+14, y)==0 || terrain->donnerPixel(x+14, y+13)==0 || terrain->donnerPixel(x+14, y-13)==0)
            return 0;
        for(j=0;j<3;j++) {
            vilain = vilains[j];
            if (vilain->x-x > 0 && vilain->x-x < 30 && abs(vilain->y-y) < 30) {
                return 0;
            }
        }
        x++;
    }
    return 0;
}

int Poussin::alleragauche(Terrain *terrain, Poussin* p1, Poussin* p2, Poussin* p3) {
    Poussin* vilains[] = {p1, p2, p3};
    Poussin* vilain;
    int i, j;
    for(i=0;i<6;i++) {
        if ( terrain->donnerPixel(x-14, y)==0 || terrain->donnerPixel(x-14, y+13)==0 || terrain->donnerPixel(x-14, y-13)==0)
            return 0;
        for(j=0;j<3;j++) {
            vilain = vilains[j];
            if (vilain->x-x < 0 && -vilain->x+x < 30 && abs(vilain->y-y) < 30) {
                return 0;
            }
        }
        x--;
    }
    return 0;
}

void Poussin::tomber(Terrain *terrain, Poussin* p1, Poussin* p2, Poussin* p3) {
    Poussin* vilains[] = {p1, p2, p3};
    int stop = 1;
    int i, j;
    Poussin* vilain;
    for(i=0; i<abs(saut) ; i++) {
        if ( terrain->donnerPixel(x-12, y + 15*sign(saut)) == 0 || terrain->donnerPixel(x, y + 15*sign(saut)) == 0 || terrain->donnerPixel(x+12, y + 15*sign(saut)) == 0 ) {
            break;
        }
        for(j=0;j<3;j++) {
            vilain = vilains[j];
            if ( abs(x - vilain->x) < 28 && y-vilain->y < 0 && vilain->y - y < 30 ) {
                calculsaut();
                if (j==0)
                    vilain->respawn(terrain, this, p2, p3);
                if (j==1)
                    vilain->respawn(terrain, p1, this, p3);
                if (j==2)
                    vilain->respawn(terrain, p1, p2, this);
                stop = 0;
                break;
            }
            if ( abs(x - vilain->x) < 28 && y-vilain->y > 0 && y-vilain->y < 30 ) {
                vilain->calculsaut();
                respawn(terrain, p1, p2, p3);
                stop = 0;
                break;
            }
        }
        if (stop==0)
            break;
        y += sign(saut);
    }
}

void Poussin::calculsaut() {
    saut = min(-8, saut);
}

void Poussin::sauter(Terrain *terrain) {
    if ( terrain->donnerPixel(x-12, y+15) == 0 || terrain->donnerPixel(x, y+15) == 0 || terrain->donnerPixel(x+12, y+15) == 0)
        saut = -16;
}

void Poussin::respawn(Terrain *terrain, Poussin* p1, Poussin* p2, Poussin* p3) {
    pet.Play();
    Poussin* vilains[] = {p1,p2,p3};
    int positions[7][2] = {{172, 350}, {172, 184}, {356, 275}, {597, 175}, {742, 323}, {781, 255}, {996, 392}};
    int n, i;
    int continuer = 1;
    saut = 0;
    while ( continuer == 1) {
        continuer = 0;
        n = sf::Randomizer::Random(0,6);
        x = positions[n][0];
        y = positions[n][1];
        for(i=0 ; i<3 ; i++) {
            if (abs(x-vilains[i]->x) < 30 && abs(y-vilains[i]->y) < 32)
                continuer = 1;
        }
    }
}

void Poussin::bouger(sf::Key::Code touche, Terrain* terrain, int pressed) {
    if (pressed==1) {
        if ( touche == up )
            sauter(terrain);
        if ( touche == left )
            gauche = 1;
        if ( touche == right )
            droite = 1;
    }
    else {
        if (touche == left)
            gauche = 0;
        if (touche == right)
            droite = 0;
    }
}
