# Exo 3 — Les bornes

- **Phase 1** — minimum imposé 400×300 : en réduisant la fenêtre, la plus petite taille de zone client observée est **À 400×300**.
- **Phase 2** — borne retirée (`minWidth = minHeight = 1`) : la plus petite taille acceptée par le système est ** 144 × 51**

**Lecture des résultats** :
- Le programme affiche la plus petite taille vue dans le titre et en console (via `NkWindowResizeEvent`).
- Sans borne explicite, la limite vient du gestionnaire de fenêtres/OS (largeur minimale de la barre de titre avec ses boutons), pas de mon code.
- La taille mesurée est celle de la **zone client**, sans bordure ni barre de titre. Un événement 0×0 (fenêtre réduite) est ignoré.
- Défaut du framework : `minWidth = 160`, `minHeight = 90` — ce qui explique qu'on ne descende pas à 1×1 même quand « on retire » la borne, si on ne la met pas explicitement à 1.
