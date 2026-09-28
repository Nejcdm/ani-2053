# Exo 5 — Le titre qui informe

Format : `nom[*] - LxH`, ex. `rapport.txt* - 900x500`.

**Le bon moment** : le titre n'est réécrit que lorsque l'état affiché change — document modifié/enregistré (clic gauche /
Ctrl+S) ou taille réelle modifiée (`NkWindowResizeEvent`). Le programme garde `affiche` (ce qui est à l'écran) et
`courant` (l'état voulu) et ne fait `SetTitle` que si `courant != affiche`.

**Pourquoi pas à chaque image** : `SetTitle` passe par le système de fenêtres (appel OS) ; à 60 images/s cela ferait
60 appels inutiles par seconde pour un texte identique. La console imprime une ligne par changement réel : on voit que le
titre n'est pas réécrit quand rien ne bouge.

