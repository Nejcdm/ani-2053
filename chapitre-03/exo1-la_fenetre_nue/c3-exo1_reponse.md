## Correspondance ligne par ligne

| # | Code (du cours) | Code  (code minimal demandé) | Remarque |
|---|---|---|---|
| 1 | `#include "NKWindow/NKWindow.h"` | `#include "NKWindow/NKWindow.h"` | Identique |
| 2 | `#include "NKWindow/NKMain.h"` | `#include "NKWindow/NKMain.h"` | Identique |
| 3 | *(absent)* | `using namespace nkentseu;` | Code demandé seulement : évite de préfixer les types par `nkentseu::` |
| 4 | *(absent)* | `NKENTSEU_DEFINE_APP_DATA(([]() { NkAppData d{}; d.appName = "MonJeu"; d.appVersion = "0.1.0"; return d; })());` | Code demandé seulement : métadonnées de l'app (nom, version), lues par le runtime **avant** `nkmain()` |
| 5 | `int nkmain(const NkEntryState &state) {` | `int nkmain(const NkEntryState& state) {` | Identique (seul le style de l'espace autour de `&` change) |
| 6 | `NkWindowConfig cfg;` | `NkWindowConfig cfg;` | Identique : on décrit la fenêtre |
| 7 | `cfg.title = "Ma fenetre";` | `cfg.title = "Hello NKWindow";` | Même rôle, seule la valeur du titre change |
| 8 | `cfg.width = 1280;` | `cfg.width = 1280;` | Identique |
| 9 | `cfg.height = 720;` | `cfg.height = 720;` | Identique |
| 10 | `NkWindow window(cfg);` | `NkWindow window;` puis `window.Create(cfg)` (dans le `if`) | Code du cours crée la fenêtre **via le constructeur** ; code demandé la déclare vide puis la crée avec `Create()` |
| 11 | `if (!window.IsOpen()) { logger.Error("[app] creation fenetre echouee"); return -1; }` | `if (!window.Create(cfg)) { return -1; }` | Vérification d'échec : code du cours teste `IsOpen()` et journalise l'erreur ; code demandé teste le retour booléen de `Create()` sans log |
| 12 | `while (window.IsOpen()) { /* les evenements arrivent ici */ }` | `while (window.IsOpen()) { ... }` | Même boucle principale |
| 13 | *(commentaire seulement)* | `while (NkEvent* ev = NkEvents().PollEvent()) { ... }` | Code demandé détaille la récupération des événements (entrées clavier/souris, etc.) |
| 14 | *(absent)* | `// mettre à jour la logique, puis dessiner (NKCanvas)` | Code demandé seulement : emplacement de la mise à jour et du rendu |
| 15 | `return 0;` | `return 0;` | Identique : fin normale du programme |

## Différences principales

- **Création de la fenêtre** : constructeur + test `IsOpen()` (code du cours) contre `Create()` avec test du booléen (code demandé).
- **Gestion d'erreur** : le code du cours affiche un message via `logger.Error`, le code demandé quitte simplement avec `-1`.
- **Métadonnées de l'application** : présentes uniquement dans le code demandé (`NKENTSEU_DEFINE_APP_DATA`).
- **Boucle principale** : le code 1 la laisse vide, le code 2 y ajoute la boucle d'événements (`PollEvent`) et l'emplacement pour la logique et le dessin.

Dans le code du cours , `logger` n'est pas déclaré et il n'y a pas de `using namespace nkentseu;` : selon la bibliothèque, ces éléments peuvent être fournis par les en-têtes inclus, sinon le code ne compilera pas tel quel.  
nombre de lignes de code du code demandées : 37 lignes.  
