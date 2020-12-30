#include "affichage.h"
#include <stdio.h>
#include <stdbool.h>
#include "bouge.h"
#include "alea.h"
#include "partie.h"

//Je crée une fonction qui va me permettre d'entrer un message d'erreur

void SDL_ExitError(char*messageerreur){
    SDL_Log("ERREUR : %s > %s\n", messageerreur,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_ExitErrorWindowRender(char* messageerreur, SDL_Window *fenetre, SDL_Renderer *rendu){
    SDL_Log("ERREUR : %s > %s\n", messageerreur,SDL_GetError());
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
//Création d'une fonction permettant de laisser la fenêtre ouverte tant qu'elle n'est pas fermée manuellement par l'utilisateur
void SDL_Pause_Fenetre(void){
    SDL_Event event;
    bool stop = false;
    do{
        while (SDL_PollEvent (&event)){
            if (event.type == SDL_QUIT){
                stop = true;
            }
        }
    }
    while (!stop);
}

void affichageRendu(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu){
    SDL_Surface *surfaceMenu = NULL;
    SDL_Texture *textureMenu = NULL;

    surfaceMenu = SDL_LoadBMP(cheminImage);

    if(surfaceMenu == NULL){
        SDL_ExitErrorWindowRender("La surface n'a pas pu être créée.", fenetre, rendu);
    }

    textureMenu = SDL_CreateTextureFromSurface(rendu,surfaceMenu);
    SDL_FreeSurface(surfaceMenu);
    if(textureMenu == NULL){
        SDL_ExitErrorWindowRender("La texture n'a pas pu être créée.", fenetre, rendu);
    }

    //Création du rectangle pour afficher la texture
    SDL_Rect rectangleMenu;

    //Je charge l'image dans la mémoire
    if(SDL_QueryTexture(textureMenu, NULL, NULL, &rectangleMenu.w,&rectangleMenu.h)!=0){
        SDL_ExitErrorWindowRender("Erreur pendant le chargement de la texture", fenetre, rendu);
    }

    rectangleMenu.x = (Largeur - rectangleMenu.w)/2;
    rectangleMenu.y = (Hauteur - rectangleMenu.h)/2;
    
    //Affichage de l'image du menu
    if(SDL_RenderCopy(rendu, textureMenu, NULL, &rectangleMenu)!=0){
        SDL_ExitErrorWindowRender("Erreur lors de l'affichage des textures", fenetre, rendu);
    }
    //Rendu :
    SDL_RenderPresent(rendu);
}

void affichageRenduCoordonnees(char* cheminImage, SDL_Window *fenetre, SDL_Renderer *rendu, int x, int y){
    SDL_Surface *surfaceMenu = NULL;
    SDL_Texture *textureMenu = NULL;

    surfaceMenu = SDL_LoadBMP(cheminImage);

    if(surfaceMenu == NULL){
        SDL_ExitErrorWindowRender("La surface n'a pas pu être créée.", fenetre, rendu);
    }

    textureMenu = SDL_CreateTextureFromSurface(rendu,surfaceMenu);
    SDL_FreeSurface(surfaceMenu);
    if(textureMenu == NULL){
        SDL_ExitErrorWindowRender("La texture n'a pas pu être créée.", fenetre, rendu);
    }

    //Création du rectangle pour afficher la texture
    SDL_Rect rectangleMenu;

    //Je charge l'image dans la mémoire
    if(SDL_QueryTexture(textureMenu, NULL, NULL, &rectangleMenu.w,&rectangleMenu.h)!=0){
        SDL_ExitErrorWindowRender("Erreur pendant le chargement de la texture", fenetre, rendu);
    }

    rectangleMenu.x = x;
    rectangleMenu.y = y;
    
    //Affichage de l'image du menu
    if(SDL_RenderCopy(rendu, textureMenu, NULL, &rectangleMenu)!=0){
        SDL_ExitErrorWindowRender("Erreur lors de l'affichage des textures", fenetre, rendu);
    }
    //Rendu :
    SDL_RenderPresent(rendu);
}

void SDL_affichageTexte(char* texte, SDL_Window *fenetre, SDL_Renderer *rendu, int x, int y){

}


void SDL_Menu(){
    //Pointeurs à déclarer :
    SDL_Window *fenetre = NULL; 
    SDL_Renderer *rendu = NULL;
    //Initialisation de la SDL

    //Si l'initialisation n'est pas à 0, cela veut dire qu'elle présente une erreur. Alors, un message d'erreur s'affiche.
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_ExitError("Erreur lors de l'initialisation de la SDL");
    }

    //Je crée une fenêtre avec son nom, la position en x, la position en y, sa largeur, sa hauteur, et son mode d'affichage)
    fenetre = SDL_CreateWindow("Tachi-ai !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280,720,0); 

    //Encore une fois, je teste s'il n'y a pas eu d'erreur dans la création de la fenêtre.
    if(fenetre == NULL){
        SDL_ExitError("Erreur lors de la création de l'écran");
    }

    rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_SOFTWARE);
    if(rendu == NULL){
        SDL_ExitError("Erreur lors de la création du rendu");
    }

    affichageRendu("assets/menujeu.bmp",fenetre,rendu);
    //Cas de passage aux autres affichages du menu
    SDL_Event event;
    bool stop = false;
    do {
        while (SDL_PollEvent (&event)){
            switch (event.type){
                case SDL_QUIT :
                    stop = true;
                    break;
                
                case SDL_KEYDOWN :{
                    switch (event.key.keysym.sym){
                        case SDLK_ESCAPE :
                            stop = true;
                            break;

                        case SDLK_1 :{
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/reglesjeu.bmp",fenetre,rendu);
                            bool retour = false;
                            do {
                                while(SDL_PollEvent (&event)){
                                    switch (event.key.keysym.sym){
                                        case SDLK_m :
                                            retour=true;
                                            break;

                                        case SDLK_ESCAPE :
                                            retour=true;
                                            stop=true;
                                            break;

                                        case SDL_QUIT :
                                            retour = true;
                                            stop = true;
                                            break;

                                    }
                                }
                            }while(!retour);
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/menujeu.bmp",fenetre,rendu);
                        }
                        break;
                        case SDLK_SPACE :{
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/modesjeu.bmp",fenetre,rendu);
                            bool retour = false;
                            do {
                                while(SDL_PollEvent (&event)){
                                    switch (event.key.keysym.sym){
                                        case SDLK_m :
                                            retour=true;
                                            break;

                                        case SDLK_0:{ //Jeu solo choisi
                                            affichageRendu("assets/difficulte.bmp",fenetre,rendu);
                                            switch(event.key.keysym.sym){   
                                                case SDLK_2 :
                                                    SDL_RenderClear(rendu);
                                                    SDL_partieSolo(2,fenetre,rendu);
                                                    break;
                                                case SDLK_3 :
                                                    SDL_partieSolo(3,fenetre,rendu);
                                                    break;

                                                case SDL_QUIT :
                                                    stop = true;
                                                    break;
                                                
                                                case SDLK_ESCAPE :
                                                    stop = true;
                                            } 
                                            break;
                                        }
                                        case SDLK_2 ://Jeu multi choisi
                                            SDL_RenderClear(rendu);
                                            SDL_partie(fenetre,rendu);
                                            break;
                                        case SDLK_ESCAPE :
                                            retour=true;
                                            break;

                                        case SDL_QUIT :
                                            retour = true;
                                            break;
                                    }
                                }
                            }while(!retour);
                            SDL_RenderClear(rendu);
                            affichageRendu("assets/menujeu.bmp",fenetre,rendu);
                            bool stop = false;
                        }
                        break;
                    }   
                }
                break;  
            }
        }   
    }
    while(!stop);
}
int SDL_partieSolo(int difficulte, SDL_Window *fenetre, SDL_Renderer *rendu){
    int idJoueur = 2;
    if(difficulte == 2){
        initTab();
        bool gagne = false;
        int cpJoueur = 0;
        while(!gagne){
            if(idJoueur == 1){
                idJoueur++;
                tourOrdi(difficulte);
            } else {
                idJoueur--;
                SDL_tour(idJoueur,fenetre,rendu);
            }
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[i][j].joueurPresent){
                        cpJoueur++;
                    }
                }
            }
            if(cpJoueur == 1){
                gagne = true;
            }
            cpJoueur = 0;
        }
    } else if(difficulte == 3){
        initTabMurs();
        bool gagne = false;
        int cpJoueur = 0;
        while(!gagne){
            if(idJoueur == 1){
                idJoueur++;
                tourOrdi(difficulte);
            } else {
                idJoueur--;
                SDL_tour(idJoueur,fenetre,rendu);
            }
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[i][j].joueurPresent){
                        cpJoueur++;
                    }
                }
            }
            if(cpJoueur == 1){
                gagne = true;
            }
            cpJoueur = 0;
        }
    }

    SDL_afficheGrid(fenetre,rendu);
    switch (idJoueur){
        case 1 :
            affichageRendu("assets/victoirejoueur1.bmp",fenetre,rendu);
            break;
        case 2 :
            affichageRendu("assets/victoirejoueur2.bmp",fenetre,rendu);
            break;
    }
    return idJoueur;
}

void SDL_afficheGrid(SDL_Window *fenetre, SDL_Renderer *rendu){
    int ac1 = 0, ac2 = 0, ac3 = 0, ac4 = 0, bc1=0, bc2=0, bc3=0 ,bc4=0;
    affichageRendu("assets/ecranjeu.bmp",fenetre,rendu);
    for(int i = 0; i<SIZE; i++){
        //Pour chaque case on teste s'il y a un mur/un joueur ou non
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.orientation == 0){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("assets/sumotoridosbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("assets/sumotoridosrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                }else if(t[j][i].joueur.orientation == 1){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("assets/sumotoriestbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("assets/sumotoriestrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                }else if(t[j][i].joueur.orientation == 2){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("assets/sumotorifacebleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("assets/sumotorifacerouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                }else if(t[j][i].joueur.orientation == 3){
                    if(t[j][i].joueur.id == 1){
                        affichageRenduCoordonnees("assets/sumotoriouestbleu.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }else{
                        affichageRenduCoordonnees("assets/sumotoriouestrouge.bmp",fenetre,rendu,(100*j+350),(100*i+70));
                    }
                }
            }else if(t[j][i].capa != NULL){
                affichageRenduCoordonnees("assets/capa.bmp",fenetre,rendu,(100*j+350),(100*i+70));
            }
            if(t[j][i].murEst){
                affichageRenduCoordonnees("assets/murvertical.bmp",fenetre,rendu,100*j+430,100*i+60);
            }else if (t[j][i].murOuest){
                affichageRenduCoordonnees("assets/murvertical.bmp",fenetre,rendu,100*j+340,100*i+60);
            }else if (t[j][i].murNord){
                affichageRenduCoordonnees("assets/murhorizontal.bmp", fenetre,rendu,j*100+340,i*100+60);
            }else if (t[j][i].murSud){
                affichageRenduCoordonnees("assets/murhorizontal.bmp",fenetre,rendu,j*100+340,i*100+150);
            }
        }
    }
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == 1){
                    //On a trouvé le bon joueur
                    capacite *cap1 = t[j][i].joueur.capacite.p;
                    //On compte chaque capacité
                    while(cap1 != NULL){
                        switch (cap1->type)
                        {
                            case 0:
                                ac1++;
                                break;
                                
                            case 1:
                                ac2++;
                                break;

                            case 2:
                                ac3++;
                                break;
                                
                            case 3:
                                ac4++;
                                break;
                                
                        }
                            cap1 = cap1->s;
                    }
                    break;
                }else{
                    capacite *cap2 = t[j][i].joueur.capacite.p;
                    //On compte chaque capacité
                    while(cap2 != NULL){
                        switch (cap2->type)
                        {
                            case 0:
                                bc1++;
                                break;
                                
                            case 1:
                                bc2++;
                                break;

                            case 2:
                                bc3++;
                                break;
                                
                            case 3:
                                bc4++;
                                break;
                                
                        }
                            cap2 = cap2->s;
                    }
                    break;
                }
            }
        }
    }
/*        SDL_affichageTexte(": " + (char)(ac1+48)), fenetre, rendu, 190, 210);
        SDL_affichageTexte(": " + (char)(ac2+48)), fenetre, rendu, 190, 210);
        SDL_affichageTexte(": " + (char)(ac3+48)), fenetre, rendu, 190, 210);
        SDL_affichageTexte(": " + (char)(ac4+48)), fenetre, rendu, 190, 210);
        SDL_affichageTexte(": " + (char)(bc1+48)), fenetre, rendu, 190, 1120);
        SDL_affichageTexte(": " + (char)(bc2+48)), fenetre, rendu, 190, 1120);
        SDL_affichageTexte(": " + (char)(bc3+48)), fenetre, rendu, 190, 1120);
        SDL_affichageTexte(": " + (char)(bc4+48)), fenetre, rendu, 190, 1120);*/
}

bool SDL_avance(int id, SDL_Window *fenetre, SDL_Renderer *rendu){
    //On crée un posX et posY permettant de stocker l'emplacement du joueur
    int posX = 0, posY = 0;
    Joueur p;
    //On recherche la position du joueur j et on le sauvegarde (orientation, et id).
    for(int i = 0; i<SIZE; i++){
        for(int j = 0; j<SIZE; j++){
            if(t[j][i].joueurPresent){
                if(t[j][i].joueur.id == id){
                    posX = j;
                    posY = i;
                    p = t[j][i].joueur;
                    break;
                }
            }
        }
    }
    
    //On regarde l'orientation du joueur pour agir en conséquence    
    switch (p.orientation)
    {
    case 0:
        //Dans chaque cas, on vérifie qu'un mur n'empêche pas l'action
        if(!t[posX][posY].murNord){
            t[posX][posY-1].joueur = p;
            t[posX][posY-1].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX][posY-1].capa != NULL){
                capacite *capa = t[posX][posY-1].capa;
                //printf("Capacite %d ramassee !\n", capa->type+1);           /*A traduire en SDl*/
                t[posX][posY-1].capa = NULL;
                capacite *courant = t[posX][posY-1].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            //Si un mur bloque l'action, on renvoie false et on ne fait pas bouger le joueur.
            return false;
        }
        break;
    
    case 1:
        if(!t[posX][posY].murEst){
            t[posX+1][posY].joueur = p;
            t[posX+1][posY].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX+1][posY].capa != NULL){
                capacite *capa = t[posX+1][posY].capa;
                //printf("Capacite %d ramassee !\n", capa->type+1);                   /* A traduire en SDL*/
                t[posX+1][posY].capa = NULL;
                capacite *courant = t[posX+1][posY].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;

    case 2:
        if(!t[posX][posY].murSud){
            t[posX][posY+1].joueur = p;
            t[posX][posY+1].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX][posY+1].capa != NULL){
                capacite *capa = t[posX][posY+1].capa;
                //printf("Capacite %d ramassee !\n", capa->type+1);               /*A traduire en SDL*/
                t[posX][posY+1].capa = NULL;
                capacite *courant = t[posX][posY+1].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;
    case 3:
        if(!t[posX][posY].murOuest){
            t[posX-1][posY].joueur = p;
            t[posX-1][posY].joueurPresent = true;
            t[posX][posY].joueurPresent = false;
            //Test si une capacité est sur la nouvelle case
            if(t[posX-1][posY].capa != NULL){
                capacite *capa = t[posX-1][posY].capa;
                //printf("Capacite %d ramassee !\n", capa->type+1);                           /*A traduire en SDL*/
                t[posX-1][posY].capa = NULL;
                capacite *courant = t[posX-1][posY].joueur.capacite.p;
                //On se place à la fin de la liste de capacité du joueur
                while(courant->s != NULL){
                    courant = courant->s;
                }
                //On met la nouvelle capacité à la fin de la liste du joueur
                courant->s = capa;
            }
            return true;
        }else{
            return false;
        }
        break;
    }
}

void SDL_tour(int id, SDL_Window *fenetre, SDL_Renderer *rendu){
    //On affiche la grille au début du tour.
    SDL_afficheGrid(fenetre,rendu);
    SDL_Event event;
    bool stop = false;
    int capa;

    do{
        while (SDL_PollEvent (&event)){
            switch (event.type){
                case SDL_QUIT :
                    stop=true;
                    break;
                
                case SDL_KEYDOWN :{
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            stop=true;
                            break;
                        case SDLK_o:{
                            do{
                                while(SDL_PollEvent (&event)){    
                                    switch(event.key.keysym.sym){
                                        case SDLK_1:
                                            SDL_RenderClear(rendu);
                                            SDL_afficheGrid(fenetre,rendu);
                                            SDL_useCapa(1, capa-1,fenetre,rendu);
                                            break;
                                
                                        case SDLK_2:
                                            SDL_RenderClear(rendu);
                                            SDL_afficheGrid(fenetre,rendu);
                                            SDL_useCapa(2, capa-1,fenetre,rendu);
                                            break;
                                
                                        case SDLK_3:
                                            SDL_RenderClear(rendu);
                                            SDL_afficheGrid(fenetre,rendu);
                                            SDL_useCapa(3, capa-1,fenetre,rendu);

                                            break;
                                
                                        case SDLK_4:
                                            SDL_RenderClear(rendu);
                                            SDL_afficheGrid(fenetre,rendu);
                                            SDL_useCapa(4, capa-1,fenetre,rendu);
                                            break;
                                
                                        case SDLK_ESCAPE:
                                            stop=true;
                                            break;

                                        case SDL_QUIT:
                                            stop=true;
                                            break;
                                    }
                                }
                            }while(!stop);
                        }
                    }   
                }
            }
        }   
    }while(!stop);

    //Passage à la gestion classique du tour
        do{
            while (SDL_PollEvent (&event)){
                switch (event.type){
                    case SDL_QUIT:{
                        stop=true;
                        break;
                        do{
                            while(SDL_PollEvent (&event)){
                                switch(event.key.keysym.sym){
                                    case SDLK_z:
                                        SDL_RenderClear(rendu);
                                        SDL_avance(id,fenetre,rendu);
                                        SDL_afficheGrid(fenetre,rendu);
                                        break;
                        
                                    case SDLK_q:
                                        SDL_RenderClear(rendu);
                                        tourne(id, -1);
                                        SDL_afficheGrid(fenetre,rendu);
                                        break;

                                    case SDLK_d:
                                        SDL_RenderClear(rendu);
                                        tourne(id,1);
                                        SDL_afficheGrid(fenetre,rendu);
                                        break;
                            
                                    case SDLK_ESCAPE:
                                        stop=true;
                                        break;

                                    case SDL_QUIT:
                                        stop=true;
                                        break;
                                }
                            }
                        }while(!stop);
                    }
                }
            }
        }while(!stop);

    time_t tps;
    srand((unsigned) time(&tps));
    int nbAlea = rand()%10;
    //Une chance sur 10 qu'une nouvelle capacité apparaisse sur la carte
    if(nbAlea == 1){
        //On crée alors une position pour notre nouvelle capacité
        int posX = rand()%SIZE;
        int posY = rand()%SIZE;
        capacite *capa = (capacite *)malloc(sizeof(capacite));
        capa->s = NULL;
        //On génère un type aléatoirement
        capa->type = rand()%4;
        t[posX][posY].capa = capa;
    }  
}

int SDL_partie(SDL_Window *fenetre, SDL_Renderer *rendu){
    //On fait un tableau neuf au début d'une partie
    initTab();
    bool gagne = false;
    int cpJoueur = 0, idJoueur = 2;
    while(!gagne){
        //On commence par changer de joueur
        if(idJoueur == 1){
            idJoueur++;
        }else{
            idJoueur--;
        }

        SDL_tour(idJoueur, fenetre, rendu);
        //Après un tour, on compte le nombre de joueurs sur le plateau
        for(int i = 0; i<SIZE; i++){
            for(int j = 0; j<SIZE; j++){
                if(t[i][j].joueurPresent){
                    cpJoueur++;
                }
            }
        }
        //Si on a un joueur (donc qu'il a gagné) alors on notifie la victoire
        if(cpJoueur == 1){
            gagne = true;
        }
        cpJoueur = 0;
    }
    SDL_afficheGrid(fenetre,rendu);
    if(idJoueur==1){
        affichageRendu("assets/victoirejoueur1.bmp",fenetre,rendu);
    }else{
        affichageRendu("assets/victoirejoueur2.bmp",fenetre,rendu);
    }
    return idJoueur;
}

void SDL_useCapa(int id, int n, SDL_Window *fenetre, SDL_Renderer *rendu){
    bool possible = false;
    switch (n)
    {
        case 0:{
            /* Création Mur */
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[j][i].joueurPresent){
                        if(t[j][i].joueur.id == id){
                            capacite *c = (capacite *)malloc(sizeof(capacite));
                            c = t[j][i].joueur.capacite.p;
                            capacite *prec = (capacite *)malloc(sizeof(capacite));
                            prec = t[j][i].joueur.capacite.p;
                            //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                            while(c != NULL){
                                if(c->type == n){
                                    possible = true;
                                    //Si on pointe sur la tête de la liste, alors il ne faut pas oublier de changer la tête avant de la supprimer
                                    if(prec == c){
                                        t[j][i].joueur.capacite.p = c->s; 
                                    }
                                    prec->s = c->s;
                                    free(c);
                                    break;
                                }
                                prec = c;
                                c = c->s;
                            }
                        }
                    }
                }
            }
            if(possible){
                int posY, posX;
                bool stop = false;
                SDL_Event event;
                //SDL_affichageTexte("Entrez une lettre entre a et f",fenetre,rendu,440,15);
                do{
                    while (SDL_PollEvent (&event)){
                        switch (event.type){
                            case SDL_QUIT:{
                                stop=true;
                                break;
                                switch(event.key.keysym.sym){
                                    case SDLK_a :
                                        posX = 0;
                                        break;
                            
                                    case SDLK_b:
                                        posX = 1;
                                        break;
                            
                                    case SDLK_c:
                                        posX = 2;
                                        break;
                            
                                    case SDLK_d:
                                        posX = 3;
                                        break;
                            
                                    case SDLK_e:
                                        posX = 4;
                                        break;
                            
                                    case SDLK_f:
                                        posX = 5;
                                        break;

                                    case SDLK_ESCAPE:
                                        stop=true;
                                        break;
                                }
                            }
                        }
                    }
                }while(!stop);
                SDL_RenderClear(rendu);
                SDL_afficheGrid(fenetre,rendu);
                //SDL_affichageTexte("Entrez un chiffre entre 1 et 6",fenetre,rendu,440,15);
                do{
                    while (SDL_PollEvent (&event)){
                        switch (event.type){
                            case SDL_QUIT:{
                                stop=true;
                                break;
                                switch(event.key.keysym.sym){
                                    case SDLK_1 :
                                        posY = 0;
                                        break;
                            
                                    case SDLK_2:
                                        posY = 1;
                                        break;
                            
                                    case SDLK_3:
                                        posY = 2;
                                        break;
                            
                                    case SDLK_4:
                                        posY = 3;
                                        break;
                            
                                    case SDLK_5:
                                        posX = 4;
                                        break;
                            
                                    case SDLK_6:
                                        posX = 5;
                                        break;
                                    
                                    case SDLK_ESCAPE:
                                        stop=true;
                                        break;
                                
                                }
                            }
                        }
                    }
                }while(!stop);
                SDL_RenderClear(rendu);
                SDL_afficheGrid(fenetre,rendu);
                //On va maintenant convertir la lettre en chiffre correspondant à la case
                //SDL_affichageTexte("Entrez l'orientation du mur",fenetre,rendu,440,15);
                do{
                    while (SDL_PollEvent (&event)){
                        switch (event.type){
                            case SDL_QUIT:{
                                stop=true;
                                break;
                                switch(event.key.keysym.sym){
                                    case SDLK_n :
                                        t[posX][posY].murNord = true;
                                        t[posX][posY-1].murSud = true;
                                        break;
                            
                                    case SDLK_s:
                                        t[posX][posY].murSud = true;
                                        t[posX][posY+1].murNord = true;
                                        break;
                            
                                    case SDLK_e:
                                        t[posX][posY].murEst = true;
                                        t[posX+1][posY].murOuest = true;
                                        break;
                            
                                    case SDLK_o:
                                        t[posX][posY].murOuest = true;
                                        t[posX-1][posY].murEst = true;
                                        break;
                                    
                                    case SDLK_ESCAPE:
                                        stop=true;
                                        break;
                                }
                            }
                        }
                    }
                }while(!stop);
            }
        }
        case 1:
            /* Recule adversaire */
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[j][i].joueurPresent){
                        if(t[j][i].joueur.id == id){
                            capacite *c = (capacite *)malloc(sizeof(capacite));
                            c = t[j][i].joueur.capacite.p;
                            capacite *prec = (capacite *)malloc(sizeof(capacite));
                            prec = t[j][i].joueur.capacite.p;
                            //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                            while(c != NULL){
                                if(c->type == n){
                                    possible = true;
                                    if(prec == c){
                                        t[j][i].joueur.capacite.p = c->s; 
                                    }
                                    prec->s = c->s;
                                    free(c);
                                    break;
                                }
                                prec = c;
                                c = c->s;
                            }
                        }
                    }
                }
            }
            if(possible){
                for(int i = 0; i<SIZE; i++){
                    for(int j = 0; j<SIZE; j++){
                        if(t[j][i].joueurPresent){
                            //Si le joueur présent est j+1 ou j-1 (l'autre joueur) on fait l'action
                            if(t[j][i].joueur.id == id+1 || t[j][i].joueur.id == id-1){
                                if(t[j][i].joueur.id == id+1){
                                    tourne(id+1, -1);
                                    tourne(id+1, -1);
                                    SDL_avance(id+1,fenetre,rendu);
                                    tourne(id+1, -1);
                                    tourne(id+1, -1);
                                    i = SIZE;
                                    j = SIZE;
                                    break;
                                }else{
                                    tourne(id-1, -1);
                                    tourne(id-1, -1);
                                    SDL_avance(id-1,fenetre,rendu);
                                    tourne(id-1, -1);
                                    tourne(id-1, -1);
                                    i = SIZE;
                                    j = SIZE;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            break;
        
        case 2:{
            /* Demi-tour */
            //On cherche le joueur dans le tableau
            for(int i = 0; i<SIZE; i++){
                for(int j = 0; j<SIZE; j++){
                    if(t[j][i].joueurPresent){
                        if(t[j][i].joueur.id == id){
                            capacite *c = (capacite *)malloc(sizeof(capacite));
                            c = t[j][i].joueur.capacite.p;
                            capacite *prec = (capacite *)malloc(sizeof(capacite));
                            prec = t[j][i].joueur.capacite.p;
                            //On parcourt les capacités jusqu'au bout
                            while(c != NULL){
                                //Si le joueur a la capacité, on execute l'action
                                if(c->type == n){
                                    tourne(id, 1);
                                    tourne(id, 1);
                                    possible = true;
                                    if(prec == c){
                                        t[j][i].joueur.capacite.p = c->s; 
                                    }
                                    prec->s = c->s;
                                    free(c);
                                    break;
                                }
                                prec = c;
                                c = c->s;
                            }
                        }
                    }
                }
            }
        break;

        case 3:
            {
                for(int i = 0; i<SIZE; i++){
                    for(int j = 0; j<SIZE; j++){
                        if(t[j][i].joueurPresent){
                            if(t[j][i].joueur.id == id){
                                capacite *c = (capacite *)malloc(sizeof(capacite));
                                c = t[j][i].joueur.capacite.p;
                                capacite *prec = (capacite *)malloc(sizeof(capacite));
                                prec = t[j][i].joueur.capacite.p;
                                //Si le joueur a la capacité, on notifie que l'action est possible et on supprime la capacité de l'inventaire
                                while(c != NULL){
                                    if(c->type == n){
                                        possible = true;
                                        if(prec == c){
                                            t[j][i].joueur.capacite.p = c->s; 
                                        }
                                        prec->s = c->s;
                                        free(c);
                                        break;
                                    }
                                    prec = c;
                                    c = c->s;
                                }
                            }
                        }
                    }
                }

                if(possible){
                    SDL_tour(id,fenetre,rendu);
                }
                break;
            }
        }
    }
}