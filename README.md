# Arcadium
Dépot pour tous les codes concernant la borne d'arcade. Chaque dossier correspond à un périphérique (par exemple l'Arduino qui gére les LEDs frontals). Le code doit pouvoir être directement compilable une fois le dépot cloné (le nom du .ino doit être le même que son dossier).

[Lien vers l'article sur la borne](http://estiasystem.estia.fr/archives/2317)
![Une fine équipe!](borne.jpg)

## Arduino-Coin-Acceptor
Code pour la carte Arduino gérant le monnayeur

## Arduino-Marquee-light
Code pour la carte Arduino gérant les LEDs à addressage de la face avant

## Arduino-rear-LED
Code pour la carte Arduino Nano gérant les LEDs arriéres. Ce programme contient:
- un PWM logiciel pour avoir 3 sorties PWM simultanées sur une carte Nano (contourner la limitation matérielle)
- une gestion des LEDs en mode RGB
- une correction du gamma (peut être enlevé)
