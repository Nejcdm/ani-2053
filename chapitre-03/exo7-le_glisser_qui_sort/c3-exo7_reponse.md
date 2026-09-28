# Exercice 7 — Le glisser qui sort — réponse

## Sans capture (`C` = OFF)

Tant que le curseur reste dans la zone client, les `NkMouseMoveEvent` arrivent
normalement pendant le glisser. Dès que le curseur **quitte** la fenêtre (bord franchi
pendant le drag), plus aucun événement de mouvement n'est reçu par cette fenêtre — le
programme n'a plus aucune idée d'où se trouve la souris tant qu'elle n'est pas
revenue à l'intérieur (et le relâchement du bouton, s'il a lieu dehors, peut même ne
jamais être vu). Du point de vue utilisateur : glisser un objet un peu trop vite sort
littéralement le geste "hors du radar" de l'application — c'est ce qui provoque les
glisser-déposer qui "se coincent" dans certaines applications mal écrites.

## Avec capture (`C` = ON, `CaptureMouse(true)` posé au press)

Les `NkMouseMoveEvent` continuent d'arriver même quand le curseur est physiquement
sorti de la fenêtre : `GetX()`/`GetY()` peuvent alors devenir négatifs ou dépasser la
largeur/hauteur de la fenêtre (coordonnées hors de `[0, largeur)` / `[0, hauteur)`), et
c'est normal — la capture ne "téléporte" pas le curseur dans la fenêtre, elle continue
juste de router les événements souris vers elle. C'est le mécanisme qui rend un
glisser-déposer robuste (sélection rectangle, redimensionnement de panneau, slider) :
l'utilisateur peut dépasser largement la zone sans perdre le contrôle du geste.

## Piège à ne pas oublier

`CaptureMouse` **survit au relâchement si on oublie de le désactiver** : toujours
appeler `CaptureMouse(false)` à la fin du glisser (et en filet de sécurité à la
fermeture), sous peine de laisser la fenêtre "aimanter" tous les événements souris
même après la fin du drag.
