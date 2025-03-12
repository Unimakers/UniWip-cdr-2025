#include <AccelStepper.h>
#include <Arduino.h>

// Définition des pins du moteur
#define STEP1 12
#define DIR1 11
#define STEP2 14
#define DIR2 13

#define EN 46


// Création des objets AccelStepper
AccelStepper stepper1(1, STEP1, DIR1);
AccelStepper stepper2(1, STEP2, DIR2);


void nema_setup(AccelStepper &stepper, int SPEED, int MAX_SPEED, int ACCELERATION) {
  // Initialisation du moteur
  stepper.setSpeed(SPEED); // Vitesse du moteur en pas par seconde
  stepper.setMaxSpeed(MAX_SPEED);   // Vitesse maximale du moteur en pas par seconde
  stepper.setAcceleration(ACCELERATION); // Accélération du moteur en pas par seconde²
}

void nema_position(AccelStepper &stepper, int POSITION) {
  // Déplacement du moteur vers l'avant
  stepper.moveTo(POSITION);
}

void nema_start(AccelStepper &stepper1, AccelStepper &stepper2) {
  // Lancement des moteurs
  while (stepper1.distanceToGo() != 0 || stepper2.distanceToGo() != 0 /*|| stepper3.distanceToGo() != 0*/) {
    stepper1.run();
    stepper2.run();
  }
}

void setup(){
  Serial.begin(115200);
  Serial.println("Initialisation du programme");

  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);

  // Initialisation des moteurs
  nema_setup(stepper1, 1000, 2000, 2000);
  nema_setup(stepper2, 1000, 2000, 2000);
}

void loop(){
  // Déplacement des moteurs
  nema_position(stepper1, -30000);
  nema_position(stepper2, 30000);

  // Lancement des moteurs
  nema_start(stepper1, stepper2);
  delay(2000);
  // Déplacement des moteurs
  nema_position(stepper1, 0);
  nema_position(stepper2, 0);
  nema_start(stepper1, stepper2);

}