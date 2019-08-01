# Arcadium
Dépôt  pour tous les codes concernant la borne d'arcade. Chaque dossier correspond à un périphérique (par exemple l'Arduino qui gère  les LEDs frontales). Le code doit pouvoir être directement compilable une fois le dépot cloné (le nom du .ino doit être le même que son dossier).


[Lien vers l'article sur la borne](http://estiasystem.estia.fr/archives/2317)
![Une fine équipe!](borne.jpg)

## Emulateur LaunchBox BigBox
[Utilisation de LaunchBox BigBox](https://www.launchbox-app.com/big-box)

## Arduino-Coin-Acceptor
Code pour la carte Arduino gérant le monnayeur.
Lien utiles:
- [Interfacing DG600F Coin Acceptor to Arduino](https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/)
- [arduino-coin-acceptor
](https://github.com/hxlnt/arduino-coin-acceptor)
- [DG600F Code examples](https://github.com/vvzen/coin-acceptor)
- [Make Money With Arduino](https://www.instructables.com/id/Make-Money-with-Arduino/)

TODO
- faire la VeroBoard et les supports
- se connecter au bouton du PC


[Sur les boutons de la borne](https://www.amazon.fr/Reyann-LED-Illuminated-DIY-poussoirs/dp/B01G9UOJOC)
venir faire passer l'Arduino pour un bouton avec un transistor NPN
Bouton non appuyé: fil jaune au potentiel 5V (même que rouge)
Bouton appuyé: fil jaune au potentiel GND
-> fermeture du circuit


### Configuration du monnayeur
Chaque pièce est associé à un numéro dans le monnayeur
- C1 : 2€       Valeur monnayeur    40
- C2 : 1€       Valeur monnayeur    20
- C3 : 0,50€    Valeur monnayeur    10
- C4 : 0,20€    Valeur monnayeur    4
- C5 : 0,10€    Valeur monnayeur    2
- C6 : 0,05€    Valeur monnayeur    1

Valeur € = valeur monnayeur x 5



## Arduino-Marquee-light
Code pour la carte Arduino gérant les LEDs à adressage  de la face avant.
[Réutilisation d'un code d'exemple de ce dépot](https://github.com/Makuna/NeoPixelBus)
Il faut installer la bibliothéque dans l'IDE Arduino

## Arduino-rear-LED
Code pour la carte Arduino Nano gérant les LEDs arrières. Ce programme contient :

- un PWM logiciel pour avoir 3 sorties PWM simultanées sur une carte Nano (contourner la limitation matérielle)
- une gestion des LEDs en mode RGB
- une correction du gamma (TODO fonction pouvant être supprimé)
