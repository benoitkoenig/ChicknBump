#include <SFML/Graphics.hpp>
#include <iostream>

class Poussin;

class Terrain {
public:
    Terrain();
    ~Terrain();
    void rafec(Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4);
    int donnerPixel(int, int);
    void interactions(sf::Event ev, int *continuer, Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4);
    int accueillir();
private:
    sf::RenderWindow* pfenetre;
    int terl;
    int terh;
    sf::Image *imgfond;
    sf::Image *img;
    sf::Image *imgfe;
    sf::Sprite* spt;
    sf::Sprite* sptfe;
};
