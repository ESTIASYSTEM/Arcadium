# Arcadium

Dépôt  pour tous les codes concernant la borne d'arcade. Chaque dossier correspond
 à un périphérique (par exemple l'Arduino qui gère  les LEDs frontales). Le code
doit pouvoir être directement téléversable (même nom de fichier .ino et de dossier).
Les autres documents concernant le projet (CAO, décorations latérales, factures)
sont sur le drive (Adhérents ESTIA SYSTEM\Projets\Borne d'arcade.)

## Contribuer/ discuter

**==> le but est d'échanger sur des canaux communs pour éviter de poser plusieurs fois les mêmes questions.**

* Le travail restant est indiqué dans les TODOS.
* Discussion : n'hésitez pas à demander aux anciens [contributeurs](#contributeurs) via sur le
 [canal de discussion Teams](https://teams.microsoft.com/l/channel/19%3ac6530fff71bf4bde95c330e86a986969%40thread.skype/Arcadium?groupId=51a4f0eb-8336-4366-a786-f89c1c31cb50&tenantId=370d21bc-952a-493e-a2c9-13cfa1e63520).
* Bugs, documentation, demande d'aide, question... : vous pouvez ouvrir une [issue](https://github.com/ESTIASYSTEM/Arcadium/issues) :wink:.

## TODO

Par ordre de priorité décroissant

* [X] faire la structure
* [ ] faire le monnayeur [TODO coin acceptor](###TODO-Arduino-Coin-Acceptor)
* [ ] imprimer et coller les stickers décorations sur les côtés (cf drive ESTIA
 SYSTEM)

* [ ] gérer les périodes d'activités de la borne (mettre en veille, démarrer).
idée: faire un bash executé au démarrage ou prendre un soft existant pour programmer les heures.
* [ ] [TODO Marque light](###TODO-Arduino-Marquee-light) pour résoudre cette
[issue](https://github.com/ESTIASYSTEM/Arcadium/issues/1)
* [ ] [TODO rear lead](###TODO-Arduino-rear-LED)

![La borne d'arcade!](media/arcadium.jpg)

## Emulateur LaunchBox BigBox

[Utilisation de LaunchBox BigBox](https://www.launchbox-app.com/big-box)

## Arduino-Coin-Acceptor

### TODO Arduino-Coin-Acceptor

* [ ] faire passer l'Arduino pour un bouton avec un transistor NPN, puis faire une connection entre la Arduino et la carte Reyann Easyget [ça ressemble à ça où intervenir](https://www.amazon.fr/Reyann-LED-Illuminated-DIY-poussoirs/dp/B01G9UOJOC)
* [ ] faire le circuit proprement avec une VeroBoard et les supports, [cf brouillon schéma électronique](arduino_coin_acceptor\coin_acceptor_schematic\coin_acceptor_schematic.pdf)

Principe de fonctionnement actuel du bouton monnaie dans la borne:
Pour insérer des crédits, il faut actuellement appuyé sur un bouton. Un appui (impulsion) correspond à un crédit.

* Bouton non appuyé: fil jaune au potentiel 5V (même que rouge)
* Bouton appuyé: fil jaune au potentiel GND (fil noir) -> fermeture du circuit
Code pour la carte Arduino gérant le monnayeur. Le monnayeur envoie à l'Arduino via une connection RS232 la valeur de la pièce inséré (nombre arbitraire). La carte Arduino calcule un ratio en fonction du prix de la partie et renvoie un nombre d'impulsions vers le PC gérant l'émulateur. La connection se fait sur la carte Reyann via les connecteurs JST.
Plus de détails dans les commentaires du code.

Lien utiles:

* [Interfacing DG600F Coin Acceptor to Arduino](https://bigdanzblog.wordpress.com/2015/01/12/interfacing-dg600f-coin-acceptor-to-arduino/)
* [arduino-coin-acceptor](https://github.com/hxlnt/arduino-coin-acceptor)
* [DG600F Code examples](https://github.com/vvzen/coin-acceptor)
* [Make Money With Arduino](https://www.instructables.com/id/Make-Money-with-Arduino/)

### Configuration du monnayeur

Chaque pièce est associé à un numéro dans le monnayeur

* C1 : 2€       Valeur monnayeur    40
* C2 : 1€       Valeur monnayeur    20
* C3 : 0,50€    Valeur monnayeur    10
* C4 : 0,20€    Valeur monnayeur    4
* C5 : 0,10€    Valeur monnayeur    2
* C6 : 0,05€    Valeur monnayeur    1

La carte Arduino calcule un ratio avec la valeur suivante

```c
Valeur € = valeur monnayeur * 5
```

## Arduino-Marquee-light

### TODO Arduino-Marquee-light

* [ ] Tester le code NeoPixelCyclon pour savoir s'il s'agit du bon (tester sur une autre carte Arduino pour ne pas perdre le programme actuel !!!)
* [ ] Si ce n'est pas le bon, refaire le même à partie de l'exemple de la bibliothèque

Code pour la carte Arduino gérant les LEDs à adressage  de la face avant.

[Réutilisation d'un code d'exemple de ce dépot](https://github.com/Makuna/NeoPixelBus).
Il faut installer la bibliothèque dans l'IDE Arduino

## Arduino-rear-LED

### TODO Arduino-rear-LED

* [ ] retrouver la version du code qui fait scintiller les leds (fadding effect)
* [ ] supprimer la correction gamma

Code pour la carte Arduino Nano gérant les LEDs arrières. Ce programme contient :

* un PWM logiciel pour avoir 3 sorties PWM simultanées sur une carte Nano (contourner la limitation matérielle)
* une gestion des LEDs en mode RGB
* une correction du gamma (fonction pouvant être supprimé)

# Contributeurs

* [Raphaël OLLANDO](https://www.linkedin.com/in/ollando-raph/): conception, fabrication (CAO, électronique, sélection des logiciels), gestion de projet
* [Robin MOUNEU](https://www.linkedin.com/in/robin-mouneu-87345915a/): conception et fabrication mécanique
* [Flavien DUMAS](https://www.linkedin.com/in/flavien-dumas/): conception informatique, configuration Windows et LaunchBox BigBox
* [Pierre JESSEL](https://www.linkedin.com/in/pierre-jessel-0276b4151/): conception électronique, Marquee light
* [Sylvain GUTIERREZ](https://www.linkedin.com/in/sylvain-gutierrez-estia/): design Inkscape, décorations latérales
* [Adrien GAUCHÉ](https://www.linkedin.com/in/adrien-gauche/): monnayeur, rear LED, documentation