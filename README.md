# Arbre electromagnétique 09/23
Film et Outil de composition sonore et visuel via manipulation de champs magnétique réalisé par Noah Jachez, SungJoo Jeon, Yann Panet, Lorris Sahli, dans le cadre d'un workshop de cins jours aux Arts Décoratifs de paris (secteur Cinéma d'Animaiton), sous la direction de Romain Blanc-Tailleur et Antoine Petitrenaud. 


## Captation



https://github.com/LorrisEnsad/Arbre_electromagnetique/assets/106762643/02adb22a-6a0a-4dbd-a5ef-924c50c5eb76



A gauche, l'objet-interface. Sur l'écran de droite, le film réalisé image par image.

## Concept

Partant d'un objet sculptural évoquant un arbre, l'équipe s'est scindée en 2 groupes pour en explorer deux aspects distincts : 
- Comme marionnette animable en image par image,
- Comme moyen d'interaction en temps réel avce un dispositif audio-visuel. 


## Dispositif Technique 

Le dispositif est construit autour d'un ESP32C3, sur lequel sont branché trois capteurs éléctromagnétiques (Joy-iy KY-O35). L'ESP3 traite et envoit les valeurs mesurées à PureData via port série, qui les transmet à un ServerTCP hébergé localement et par lequel Godot les récupère. 
Les valeurs des cpateurs sont utilisées par PureData pour influer sur deux synthétiseurs, tandis que Godot les utilise pour générer procuéduralement des visuels via un code *shader*. 

![diagramm](https://github.com/LorrisEnsad/Arbre_electromagnetique/assets/106762643/c35a6763-b0a8-494a-ae2a-a0c2df121db0)

## Bilan Pistes d'améliorations

Avec ce projet nous avons proposés une solution générale d'interface entre Godot et un microcontroleur Arduino-compatible, via puredata. Si d'autres solution existent, elles ne sont souvent pas natives, et reposent sur des bibliothèques qui doivent être recompilées à chaque nouvelle version de Godot. La solution ici proposée à l'avantage d'être native Gdscript, et donc version-agnostique. 

Par ailleurs, PureDara propose via le module externe GEM ( https://puredata.info/downloads/gem ) la prise en charge de code *shader* GLSL. Il serait donc possible d'envisager une version similaire, plus élégante, se passant de Godot et du serveur TCP. 
