# Exercice 9 — Les quatre dialogues — réponse

## Les quatre dialogues employés

| Touche | Dialogue                    | Résultat lu si `confirmed` |
|--------|------------------------------|------------------------------|
| O      | `NkDialogs::OpenFileDialog`  | `result.path`                |
| S      | `NkDialogs::SaveFileDialog`  | `result.path`                |
| D      | `NkDialogs::OpenFolderDialog`| `result.path`                |
| C      | `NkDialogs::ColorPicker`     | `result.color` (RGBA)        |

## Traiter l'annulation

`NkDialogResult` a un champ `confirmed` (booléen) qui est `false` si l'utilisateur a
fermé la boîte sans rien choisir (croix, Échap, bouton Annuler). Le programme teste
**systématiquement** `confirmed` avant de lire `path` ou `color` : dans le cas annulé,
`path` reste une chaîne vide et `color` sa valeur par défaut — les lire sans le test
n'aurait rien fait planter en soi, mais aurait affiché une information fausse (« fichier
choisi : » suivi de rien). Rien ne plante dans aucun des quatre cas testés.

## Remarque

Ces appels sont **synchrones** : le thread principal (et donc la boucle de la fenêtre)
est suspendu tant que la boîte de dialogue est ouverte. Sur desktop, ce n'est pas gênant
(comportement attendu). `NkDialogs` propose aussi des variantes `*Async` avec callback,
nécessaires sur iOS où les sélecteurs de documents sont intrinsèquement asynchrones
(une version synchrone y bloquerait la boucle système et provoquerait un blocage).
