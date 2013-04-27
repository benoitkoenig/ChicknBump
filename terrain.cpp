#include "terrain.h"
#include "Poussin.h"

Terrain::Terrain() {
    pfenetre = new sf::RenderWindow(sf::VideoMode(1024, 512), "Chick&Bump", sf::Style::Close);
    pfenetre->SetFramerateLimit(32);
    terl = pfenetre->GetWidth()/2 - 512;
    terh = pfenetre->GetHeight()/2 - 256;
    img = new sf::Image();
    imgfond = new sf::Image();
    imgfe = new sf::Image();
    img->LoadFromFile("./datas/image de fond.png");
    imgfond->LoadFromFile("./datas/background.png");
    imgfe->LoadFromFile("./datas/fonddecran.png");
    spt = new sf::Sprite(*img);
    sptfe = new sf::Sprite(*imgfe);
    spt->SetPosition(terl, terh);
    sptfe->SetPosition(terl, terh);

}

Terrain::~Terrain() {
    pfenetre->Close();
}

int Terrain::donnerPixel(int x, int y) {
    if ( imgfond->GetPixel(x, y).a == 0 )
        return 1;
    return 0;
}

void Terrain::rafec(Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4) {//Toujours pas de delete sur les pointeurs
    Poussin* poussins[] = {p1, p2, p3, p4};
    int i;
    pfenetre->Clear(sf::Color::Black);
    pfenetre->Draw(*sptfe);
    for (i=0;i<4;i++) {
        pfenetre->Draw(*(poussins[i]->rafec(terl, terh, this)));
    }
    pfenetre->Draw(*spt);
    pfenetre->Display();
}

void Terrain::interactions(sf::Event ev, int *continuer, Poussin* p1, Poussin* p2, Poussin* p3, Poussin* p4) {
    while (pfenetre->GetEvent(ev)) {
        if (ev.Type == sf::Event::KeyPressed) {
            if (ev.Key.Code == sf::Key::Escape)
                *continuer = 0;
            p1->bouger(ev.Key.Code, this, 1);
            p2->bouger(ev.Key.Code, this, 1);
            p3->bouger(ev.Key.Code, this, 1);
            p4->bouger(ev.Key.Code, this, 1);
        }
        if (ev.Type == sf::Event::KeyReleased) {
            p1->bouger(ev.Key.Code, this, 0);
            p2->bouger(ev.Key.Code, this, 0);
            p3->bouger(ev.Key.Code, this, 0);
            p4->bouger(ev.Key.Code, this, 0);
        }
        if (ev.Type == sf::Event::Closed)
            *continuer = 0;
    }
}

/*
    Tu utilise cette méthode à chaque frame, ça veut dire qu'à chaque
    frame tu créés un nouveau pointeur sur image, un nouveau pointeur
    sur sprite et tu recharges l'image en mémoire.
    Tu devrais mettre ces variables comme variables de classe, tu as
    d'énorme fuites de mémoire (tu ne delete aucun pointeur !) ici
    en plus d'un chargement d'image par frame qui te fait perdre du
    tempsen calcul.
*/
int Terrain::accueillir() {
    sf::Image* img;
    sf::Sprite* spt;
    sf::Event ev;
    img = new sf::Image();
    img->LoadFromFile("./datas/accueil.png");
    spt = new sf::Sprite(*img);
    pfenetre->Draw(*spt);
    while (1) {
        while(pfenetre->GetEvent(ev)) {
            if (ev.Type == sf::Event::KeyPressed) {
                if (ev.Key.Code == sf::Key::Escape)
                    return 0;
                return 1;
            }
            if (ev.Type == sf::Event::Closed)
                return 0;
        }
        pfenetre->Display();
    }
}
