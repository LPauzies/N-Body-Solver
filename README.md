# Optimisation d’une simulation d’interactions gravitationnelles à N Corps

## Numéro de supercalculateur : 11

# Connexion Cesga
SSH : ` ssh eisti011@ft2.cesga.es `  
Password : ` e.st.011 `

Pour enregistrer sa clé ssh :
En local : `ssh -i id_rsa_cesga eisti011@ft2.cesga.es`  
Sur le serveur copier le `id_rsa_cesga.pub` dans `~/.ssh/authorized_keys`  
Connexion : `ssh -i ~/.ssh/id_rsa_cesga eisti011@ft2.cesga.es`

# Sujet
https://arel.eisti.fr/documents/56342/download/sujetProjetGSI_Pau_2017-2018.pdf

# Organisation
- **Scrum Master :** Antoine
- **Product Owner :** Juan
- **Dev Team :** Antoine / Lucas / Laurine

# Trello
https://trello.com/b/m20lVozi

# Themes & User Stories AGILE
- US1 : J’ai besoin d’un ou plusieurs jeux de données réelles.
- US2 : J’ai besoin de calculer la position et vélocité de chaque corps à partir de sa trajectoire et de l’influence des corps voisins.
- US3 : J’ai besoin d’optimiser le temps d’exécution selon la taille du problème.
- US4 : J’ai besoin d’optimiser le temps d’exécution selon le type d’architecture parallèle.
- US5 : J’ai besoin d’afficher les résultats de façon périodique.

# Dates importantes
- **Début du projet :** semaine du 5 février.
- **Fin du projet :** semaine du 30 mars.
- **Soutenance et rendu du dossier de synthèse :** à définir.

# Références
- https://fr.wikipedia.org/wiki/Probleme_a_N_corps
- https://www.drgoulu.com/2008/11/16/le-probleme-a-n-corps
- https://www.ids.ias.edu/~piet/act/comp/algorithms/starter
- http://lammps.sandia.gov/

# Architecture du projet
- agile : Retrospective
- app : Application C++ et Flask
- data : Fichier de test
