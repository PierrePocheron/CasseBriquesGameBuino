#include <Gamebuino-Meta.h>

// ======== V A R  &  C O N S T ===========

// ======== B A R R E ===========

//  Taille barre
const int barreSizeX = 40;
const int barreSizeY = 2;
//  Vitesse barre
const int barreSpeedX = 5;
//  Position barre 1
int barrePositionX1 = gb.display.width()/2;
int barrePositionY1 = gb.display.height() - barreSizeY;
//  Déplacement max barre
int barreMaxPositionXGauche =  0 ;
int barreMaxPositionXDroite = gb.display.width() - barreSizeX;


// ======== B A L L E ===========

//  Vitesse balle
int balleSpeedX = 1;
int balleSpeedY = 1;
//  Objet balle
int ballePositionX = gb.display.width()/2;
int ballePositionY = gb.display.height()/2;
const int balleSize = 2;
//  Rebond balle
const int ballePixelBoundX = gb.display.width() - balleSize;
const int ballePixelBoundY = gb.display.height() - balleSize;


// ======== B R I Q U E ===========

//  Nombre de brique
const int briqueNombre = 5;
int tableauBriqueLigne[briqueNombre];
//  Taille initaial Brique
const int briqueSizeX = gb.display.width() / briqueNombre -2;
const int briqueSizeY = 3;


//  Compteur
int compteurScore1 = 0;
int compteurReb1 = 0;

// ======== F U N C ===========

void reinitialiser() 
{
  for (int i = 0; i < briqueNombre; i++)
  {
    tableauBriqueLigne[i] = 1;
  }
}

void maj()
{
  ballePositionY += balleSpeedY;
  ballePositionX += balleSpeedX;
  

  //  Vérification balle rebond gauche
  if(ballePositionX < 0)
  {
    balleSpeedX = 1;
    gb.sound.playTick();
  }

  //  Vérification balle rebond droite
  if(ballePositionX > ballePixelBoundX)
  {
    balleSpeedX = -1;
    gb.sound.playTick();
  }
  

  //  Vérification balle rebond bas
  if(ballePositionY > ballePixelBoundY)
  {
    //  Vérification balle collision barre 2
    if (gb.collide.rectRect(barrePositionX1, barrePositionY1, barreSizeX, barreSizeY,ballePositionX, ballePositionY, balleSize, balleSize))
    {
      balleSpeedX = -1;
      gb.sound.playTick();
    }
    else
    {
      gb.sound.playOK();
      compteurScore1++;
      delay(1000);
      ballePositionX = gb.display.width()/2;
    }
  }


  //  Déplacement balle Y
  if (ballePositionY < 0) {balleSpeedY = 1;}
  if (ballePositionY > ballePixelBoundY) {balleSpeedY = -1;}


  //  Déplacement barre 1
  if (gb.buttons.pressed(BUTTON_LEFT)) 
  {
    if(barrePositionX1 > barreMaxPositionXGauche)
    {
      barrePositionX1 -= barreSpeedX;
    }
  }
  
  if (gb.buttons.pressed(BUTTON_RIGHT)) 
  {
    if(barrePositionX1 < barreMaxPositionXDroite)
    {
      barrePositionX1 += barreSpeedX;
    }
  }


  //  Collision avec les briques
  for (int i = 0; i < briqueNombre; i++)
  {
    // Verifier qu'il reste encore des briques
    bool briquesRestanteBool = false;

    for (int i = 0; i < briqueNombre; i++)
    {
      if (tableauBriqueLigne[i] == 1)
      {
         briquesRestanteBool = true;
      }
    }
    if (briquesRestanteBool == false)
    {
      reinitialiser();
    }
    
    if (tableauBriqueLigne[i] == 0)
    {
      continue;
    }
    
    int briquePositionX = i * (briqueSizeX + 2) + 1;
    int briquePositionY = 10;
    if (gb.collide.rectRect(ballePositionX, ballePositionY, balleSize, balleSize, briquePositionX, briquePositionY, briqueSizeX, briqueSizeY)) 
    {
      balleSpeedX *= -1;
      tableauBriqueLigne[i] = 0; 
    }
  }
}

void affichageGraphique()
{
  //  Affichage de la balle
  gb.display.fillRect(ballePositionX, ballePositionY, balleSize, balleSize);

  //  Affichage de la raquette 1
  gb.display.setColor(BLUE);
  gb.display.fillRect(barrePositionX1, barrePositionY1, barreSizeX, barreSizeY);
  
  //  Affichage Score
  //gb.display.printf("Score balle =  %d", compteurScore1);



  //Affichage Ligne Brique
  for (int i =0; i < briqueNombre; i++)
  {
    if (tableauBriqueLigne[i] == 0)
    {
      continue;
    }
    
    int briquePositionX = i * (briqueSizeX + 2) + 1;
    int briquePositionY = 10;
    gb.display.fillRect(briquePositionX, briquePositionY, briqueSizeX, briqueSizeY);
  }



  //  rebond
  //gb.display.printf("\nReb 1   =  %d ", compteurReb1);
}






//  Func Setup
void setup() {
  gb.begin();
}



//  Func Loop
void loop() {
  while (!gb.update());
  gb.display.clear();

  
  maj();
  affichageGraphique();
  

}
