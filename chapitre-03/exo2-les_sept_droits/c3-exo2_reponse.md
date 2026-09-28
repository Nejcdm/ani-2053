# cfg.frame 
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.frame = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
        
    }

    return 0;
}
# cfg.resizable
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.resizable = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
# cfg.minimizable
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.minimalize = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
# cfg.movable
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.movable = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
# cfg.closable
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.closable = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
# cfg maximizable
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    cfg.maximizable = false ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
#cfg.canFullscreen
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"

using namespace nkentseu;

// Métadonnées de l'app — lues par le runtime AVANT nkmain().
// On passe une expression qui retourne un NkAppData (ici une lambda appelée).
NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "MonJeu";
    d.appVersion = "0.1.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    // 1) Décrire la fenêtre
    NkWindowConfig cfg;
    cfg.title  = "Hello NKWindow";
    cfg.width  = 1280;
    cfg.height = 720;
    #cfg.canFullscreen =  FALSE ;
    // 2) Créer la fenêtre
    NkWindow window;
    if (!window.Create(cfg)) {
        return -1;   // échec de création
    }

    // 3) Boucle principale (voir §3)
    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            // traiter les entrées — détaillé dans le guide NKEvent
        }
        // mettre à jour la logique, puis dessiner (NKCanvas)
    }

    return 0;
}
| Le droit | Effet attendu (valeur `false`) | Effet observé |
|---|---|---|
| `bool resizable = false;` | La fenêtre ne peut plus être redimensionnée : les bords ne permettent plus de changer la taille. | Rien ne se produit |
| `bool movable = false;` | La fenêtre ne peut plus être déplacée (glisser la barre de titre n'a aucun effet). | Rien ne se produit |
| `bool closable = false;` | Le bouton de fermeture (X) est désactivé ou inopérant. | Rien ne se produit |
| `bool minimizable = false;` | Le bouton de réduction est désactivé et la fenêtre ne peut plus être minimisée. | Rien ne se produit |
| `bool maximizable = false;` | Le bouton d'agrandissement est désactivé et la fenêtre ne peut plus être maximisée. | Rien ne se produit |
| `bool canFullscreen = false;` | Le passage en plein écran est impossible (bouton ou raccourci sans effet). | Rien ne se produit |
| `bool frame = false;` | La fenêtre est sans bordure : plus de barre de titre, de bords ni de boutons système. | Rien ne se produit |

