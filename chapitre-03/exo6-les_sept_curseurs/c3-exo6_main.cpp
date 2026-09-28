// c3-exo6 : sept zones = sept formes de curseur.
// Mode A : le curseur est repose quand la zone survolee change.
// Mode B (Espace pour basculer) : le curseur n'est pose qu'UNE fois, au demarrage du mode.
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo6";
    d.appVersion = "1.0.0";
    return d;
})());

// ===== COUCHE D'ADAPTATION : [API A CONFIRMER] =====
// Les guides ne documentent pas l'API de curseur. Verifier dans NKWindow/NkWindow.h
// le nom reel (SetCursor ? NkCursorType ?) et corriger UNIQUEMENT ici.
enum class Forme { Fleche, Texte, Main, Croix, Attente, RedimH, RedimV };
static const char* NOMS[7] = { "fleche", "texte", "main", "croix", "attente", "redim-H", "redim-V" };

static void PoserCurseur(NkWindow& w, Forme f) {
    switch (f) {
        case Forme::Fleche:  w.SetCursor(NkCursorType::NK_CURSOR_ARROW);   break;
        case Forme::Texte:   w.SetCursor(NkCursorType::NK_CURSOR_IBEAM);   break;
        case Forme::Main:    w.SetCursor(NkCursorType::NK_CURSOR_HAND);    break;
        case Forme::Croix:   w.SetCursor(NkCursorType::NK_CURSOR_CROSS);   break;
        case Forme::Attente: w.SetCursor(NkCursorType::NK_CURSOR_WAIT);    break;
        case Forme::RedimH:  w.SetCursor(NkCursorType::NK_CURSOR_SIZE_WE); break;
        case Forme::RedimV:  w.SetCursor(NkCursorType::NK_CURSOR_SIZE_NS); break;
    }
}
// ====================================================

static int ZoneDe(float32 x, float32 largeur) {
    int z = (int)(x / (largeur / 7.f));
    return z < 0 ? 0 : (z > 6 ? 6 : z);
}

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo6 - mode A (Espace = mode B)"; cfg.width = 1120; cfg.height = 500; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    bool modeB = false;
    int  derniere = -1;
    std::printf("Mode A : 7 bandes verticales, une forme de curseur par bande.\n");

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
                if (kp->GetKey() == NkKey::NK_SPACE) {
                    modeB = !modeB;
                    derniere = -1;
                    window.SetTitle(modeB ? "c3-exo6 - mode B : pose UNE fois" : "c3-exo6 - mode A : pose a chaque changement de zone");
                    if (modeB) {
                        PoserCurseur(window, Forme::Main);          // pose unique
                        std::printf("Mode B : curseur pose une seule fois (main). Bougez, sortez, rentrez, redimensionnez...\n");
                    }
                }
            } else if (auto* mv = ev->As<NkMouseMoveEvent>()) {
                if (!modeB) {
                    const int z = ZoneDe((float32)mv->GetX(), (float32)window.GetSize().x);
                    if (z != derniere) {                            // on ne repose que si la zone change
                        derniere = z;
                        PoserCurseur(window, (Forme)z);
                        std::printf("zone %d -> %s\n", z + 1, NOMS[z]);
                    }
                }
            }
        }
        NkChrono::Sleep((int64)16);
    }
    return 0;
}
