#include <SFML/Graphics.hpp>
#include <iostream>

#include "terrain.h"
#include "Poussin.h"

int sign(int x);
int abs(int x);
int min(int x, int y);
void deplacerpoussins(Terrain* terrain, Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4);
void jeu(Terrain* terrain);


extern unsigned char _accueil[];
extern unsigned int _accueil_len;


