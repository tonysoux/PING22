# Projet PING²

Bienvenue sur le dépôt GitHub du projet **PING²**. Ce projet est un jeu de plateau interactif avec des surfaces de rebond robotisées, conçu pour aider à la rééducation et à la stimulation de la motricité, notamment pour les personnes à mobilité réduite.

## Description du projet

PING² est un système modulaire composé de deux sous-systèmes principaux :

1. **ESP32** – Dirige la plateforme mécanique, incluant les moteurs, capteurs et solénoïdes.
2. **Raspberry Pi** – Gère le déroulement de l'activité, les interfaces, la reconnaissance de la balle et la gestion des joueurs.

L'architecture est pensée pour évoluer facilement, avec un matériel modulaire permettant de nombreuses options de connexion.

## Branche principale

La branche principale contient les versions stables et testées des différentes fonctionnalités du projet. Assurez-vous de mettre à jour régulièrement pour profiter de la meilleure expérience de jeu.

## Autres branches

- `esp32-dev` : Développement du firmware pour l'ESP32.
- `raspberry-dev` : Développement du logiciel pour le Raspberry Pi.
- `test` : test d'intégration pour valider les différents codes afin de créer la version suivante de l'application.

## Documentation

Toute la documentation relative au projet se trouve dans le dossier [docs/](docs/).

## Installation

Pour la première installation, écrasez le contenu de la carte microSD du Raspberry Pi. Connectez la carte à votre PC, formatez-la, puis transférez-y l'image du système préalablement téléchargée. Si vous souhaitez que la plateforme se mette à jour automatiquement lorsqu'une mise à jour est disponible, connectez-la au Wi-Fi.

## Contribution

### Pour les contributeurs ayant accès au dépôt

Si vous faites partie de l’équipe de développement et avez accès en écriture, vous pouvez directement créer des branches pour de nouvelles fonctionnalités, effectuer des tests et soumettre des **pull requests** vers la branche concernée (esp32 ou rasp) une fois le code vérifié.

### Pour les contributeurs externes

PING² est un dépôt public, et toute personne souhaitant contribuer est la bienvenue ! Voici comment vous pouvez participer :

1. **Forker le dépôt** : Cliquez sur "Fork" en haut de cette page pour créer une copie de ce dépôt sur votre compte.
2. **Cloner votre fork** : Clonez votre fork sur votre machine avec la commande suivante :
   ```bash
   git clone https://github.com/votre-utilisateur/PING2.git
3. **Créer une nouvelle branche** : Pour ajouter une fonctionnalité ou corriger un bug, créez une nouvelle branche :
   ```bash
   git checkout -b ma-nouvelle-branche
4. **Faire vos modifications** : Apportez vos changements et validez-les dans votre branche.
5. **Soumettre une pull request** : Une fois les changements terminés, poussez votre branche vers votre fork et soumettez une pull request sur ce dépôt principal pour que nous puissions réviser votre travail.

Nous apprécions toute suggestion ou amélioration qui pourrait rendre PING² plus utile et performant. Pour discuter, un espace commentaire est disponible sur ce dépôt.

## Licence

Ping² © 2024 by Antoine, Antoine, Robin, Simon, Thomas is licensed under [Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International](https://creativecommons.org/licenses/by-nc-nd/4.0/)
