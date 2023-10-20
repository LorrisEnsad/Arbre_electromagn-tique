

/* Programme  d'acquisition et de traitement de capteurs de champs electromagnétiques SEN-KY035.
Réalisé par Noah Jachez et Lorris Sahli dans le cadre  du workshop "Volume et Videomapping encadré par Antoine Petit-Renaud et Romain Blanc-Tailleur du 25 au 29 Septembre 2023.
La documentaiont du projet est disponible sur la page github outil_de_composition_sonore_et_visuelle_electromagnetique
____________________________________________________________________________________________________________________________________________________*/

// Temps d'attente entre chaque itération de la boucle principale (en ms). 
//Plus le temps est cours, plus la résolution temporelle de la mesure est grande, mais plus le "bruit" de la mesure est visible. Peut être compensé en augmantant la TAILLE_BUFFER au prix d'un peu de latance. 
#define DELAY 5

// Pins d'entrée des capturs. Les pin indiqués doivent supporter la conversion analogique --> numérique (ADC)
int sensorPin = 2;  
int sensorPin2 = 3;
int sensorPin3 = 4;

//Nombre de valeurs gardées en mémoire pour calculer la moyenne mobile de la valeur mesurée :
//Plus la valeur et grande,  plus la mesure esst "lisse" et "continue", mais plus le temps de réponse est grand (particulièrement lors d'un changement brutal de valeur mesurée). Peut être compenser en diminuant DELAY au prix de plus de bruit.
#define TAILLE_BUFFER 10

int v_buffer[TAILLE_BUFFER];
int v_buffer2[TAILLE_BUFFFER];

//Variables nécessaires à la calibration des capteurs analogiques. S'assurer de bien les tenir endehors de tout champs  éléctromagnétique pendant la phase de calibration.
float zero_calibration = .0;
int compte = 0;
int nbr_cycles_calibration = 10;
int v_buffer_calibration[TAILLE_BUFFER];


float zero_calibration2 = .0;
int compte2 = 0;
int nbr_cycles_calibration2 = 10;
int v_buffer_calibration2[10];

//______________________________________

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < TAILLE_BUFFER; i++) {
    v_buffer[i] = 0;
  }
}

float ajuster(float value, float zero) {
  float result = value - zero;
  return result;
}

//Boucle principale
void loop() {
  //Acquisition de la valeur
  int rawValue = analogRead(sensorPin);
  int rawValue2 = analogRead(sensorPin2);
  int rawValue3 = digitalRead(sensorPin3);

  String output = "";

  //phase de calibration
  if (nbr_cycles_calibration > 0) {
    v_buffer_calibration[nbr_cycles_calibration - 1] = rawValue;
    nbr_cycles_calibration -= 1;
    if (nbr_cycles_calibration == 0) {
      for (int i = 0; i < TAILLE_BUFFER; i++) {
        zero_calibration += float(v_buffer_calibration[i]);
      }
      zero_calibration = zero_calibration / float(TAILLE_BUFFER);

      //Serial.print("Zero de calibration : "); //Print de debugg
      //Serial.println(zero_calibration);
    }
  }

  if (nbr_cycles_calibration2 > 0) {
    v_buffer_calibration2[nbr_cycles_calibration2 - 1] = rawValue2;
    nbr_cycles_calibration2 -= 1;
    if (nbr_cycles_calibration2 == 0) {
      for (int i = 0; i < TAILLE_BUFFER; i++) {
        zero_calibration2 += float(v_buffer_calibration2[i]);
      }
      zero_calibration2 = zero_calibration2 / float(TAILLE_BUFFER);

      //Serial.print("Zero de calibration2 : ");
      //Serial.println(zero_calibration2);
    }
  }

  //Actualisation du v_buffer
  for (int i = 0; i < TAILLE_BUFFER - 1; i++) {
    v_buffer[i] = v_buffer[i + 1];
  }
  v_buffer[TAILLE_BUFFER - 1] = ajuster(rawValue,zero_calibration);

  for (int i = 0; i < TAILLE_BUFFER - 1; i++) {
    v_buffer2[i] = v_buffer2[i + 1];
  }
  v_buffer2[TAILLE_BUFFER - 1] = ajuster(rawValue2,zero_calibration2);

  //Calculde la moyenne mobile

  int somme = v_buffer[0];
  for (int i = 1; i < TAILLE_BUFFER; i++) {
    somme = somme + v_buffer[i];
  }
  float moyenne = float(somme) / float(TAILLE_BUFFER);
  //Serial.println(moyenne);//Print de debugg
  
  //Constitution du print de sortie port série
  output.concat(String(moyenne));
  output.concat(" ");


  somme = v_buffer2[0];
  for (int i = 1; i < TAILLE_BUFFER; i++) {
    somme = somme + v_buffer2[i];
  }
  moyenne = float(somme) / float(TAILLE_BUFFER);
  //Serial.print(moyenne);
  //Serial.print(" ");
  
  //Constitution du print de sortie port série
  output.concat(String(moyenne));
  output.concat(" ");

  //Serial.print(rawValue3); //print de debugg
  output.concat(String(rawValue3));

  //Envois des données par port série, sous la forme de "valuer1 valeur2 valeur3".
  Serial.println(output);
  
  //Divers print de debugg
  //Serial.println(rawValue);
  //Serial.println(ajuster(rawValue));
  //Serial.println("---------------------------------------");

  //Delay definissant le taux d'échantillonnage 
  delay(DELAY);
}
