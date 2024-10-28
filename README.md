# PING² Project -sim

Bienvenue sur le dépôt GitHub du projet **PING²**. Ce projet est un jeu sur plateau avec des surfaces de rebond robotisées, conçu pour aider à la rééducation et à la stimulation de la motricité, notamment pour les personnes à mobilité réduite.

## Description du projet
PING² est un système modulaire composé de deux sous-systèmes principaux :
1. **ESP32** – Dirige la plateforme mécanique (moteurs, capteurs, solénoïdes).
2. **Raspberry Pi** – Gère le déroulement de l'activité (interfaces, reconnaissance de la balle, et gestion des joueurs).

# Branche principale

Cette branche contient les versions stables des différentes fonctionnalités et sera utilisée pour les tests d'intégration et les démonstrations.

## Autres branches
- `esp32-dev` : Développement du firmware de l'ESP32
- `raspberry-dev` : Développement du software sur Raspberry Pi

## Fonctionnalités principales
- Gestion des moteurs, solénoïdes et détecteurs de buts
- Estimation de la position de la balle grâce à la reconnaissance d'image
- Communication en temps réel entre l'ESP32 et le Raspberry Pi
- Interfaces de contrôle interactives pour les joueurs

## Avancement du projet

- [x] Initialisation du dépôt
- [x] Définition de l'architecture hardware
- [ ] Conception de la plateforme
- [ ] Implémentation du contrôle moteur
- [ ] Développement de l'estimation de position de la balle
- [ ] Reconnaissance d'image
- [ ] Tests d'intégration ESP32 et Raspberry
- [ ] Finalisation et validation des manettes
- [ ] Tests de performance et fiabilité
- [ ] Documentation technique et notice d'utilisation

## Documentation

Vous trouverez toute la documentation relative au projet dans le dossier [docs/](docs/).

## Installation
Les instructions d'installation spécifiques pour chaque partie du projet sont disponibles dans les branches respectives.

## Contribution
1. Clonez le dépôt
   ```bash
   git clone https://github.com/robinAZERTY/ping2.git
	```
## Licence

Ping² © 2024 by Antoine, Antoine, Robin, Simon, Thomas is licensed under [Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International](https://creativecommons.org/licenses/by-nc-nd/4.0/)
