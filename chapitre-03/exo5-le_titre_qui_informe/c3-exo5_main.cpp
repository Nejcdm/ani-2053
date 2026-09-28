
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo5";
    d.appVersion = "1.0.0";
    return d;
})());

namespace {

struct EtatTitre {
    bool   modifie = false;
    uint32 w = 0, h = 0;
    bool operator!=(const EtatTitre& o) const { return modifie != o.modifie || w != o.w || h != o.h; }
};

void AppliquerTitre(NkWindow& window, const char* doc, const EtatTitre& e) {
    char t[200];
    std::snprintf(t, sizeof(t), "%s%s - %ux%u", doc, e.modifie ? "*" : "", e.w, e.h);
    window.SetTitle(t);
    std::printf("titre mis a jour : %s\n", t);      // preuve : une ligne par CHANGEMENT reel
}

} // namespace

int nkmain(const NkEntryState& state) {
    (void)state;
    const char* DOC = "rapport.txt";
    NkWindowConfig cfg;
    cfg.title = DOC; cfg.width = 900; cfg.height = 500; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    EtatTitre affiche{}, courant{};
    courant.w = window.GetSize().x; courant.h = window.GetSize().y;
    AppliquerTitre(window, DOC, courant);
    affiche = courant;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (auto* rz = ev->As<NkWindowResizeEvent>()) {
                courant.w = rz->GetWidth(); courant.h = rz->GetHeight();
            } else if (auto* pr = ev->As<NkMouseButtonPressEvent>()) {
                if (pr->IsLeft()) courant.modifie = true;
            } else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_S && (kp->HasCtrl() || kp->HasSuper())) courant.modifie = false;
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
            }
        }
        if (courant != affiche) {               // le BON moment : seulement si quelque chose a change
            AppliquerTitre(window, DOC, courant);
            affiche = courant;
        }
        NkChrono::Sleep((int64)16);
    }
    return 0;
}
