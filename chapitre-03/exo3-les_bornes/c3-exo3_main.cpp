
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo3";
    d.appVersion = "1.0.0";
    return d;
})());

namespace {

void Phase(const char* nom, uint32 minW, uint32 minH) {
    NkWindowConfig cfg;
    cfg.width     = 800;
    cfg.height    = 600;
    cfg.centered  = true;
    cfg.resizable = true;
    cfg.minWidth  = minW;
    cfg.minHeight = minH;
    cfg.title     = nom;

    NkWindow window;
    if (!window.Create(cfg)) { std::printf("%s : creation impossible\n", nom); return; }

    math::NkVec2u init = window.GetSize();
    uint32 plusPetitW = init.x, plusPetitH = init.y;
    std::printf("== %s (min demande %ux%u) : reduisez la fenetre a la main ==\n", nom, minW, minH);

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
            } else if (auto* rz = ev->As<NkWindowResizeEvent>()) {
                const uint32 w = rz->GetWidth(), h = rz->GetHeight();
                if (w > 0 && h > 0) {                       // ignore l'etat minimise (0x0)
                    if (w < plusPetitW) plusPetitW = w;
                    if (h < plusPetitH) plusPetitH = h;
                }
                char t[160];
                std::snprintf(t, sizeof(t), "%s | actuelle %ux%u | plus petite %ux%u", nom, w, h, plusPetitW, plusPetitH);
                window.SetTitle(t);
            }
        }
        NkChrono::Sleep((int64)16);
    }
    std::printf("-> %s : plus petite zone client observee = %ux%u\n", nom, plusPetitW, plusPetitH);
}

} // namespace

int nkmain(const NkEntryState& state) {
    (void)state;
    Phase("Phase 1 - min 400x300", 400, 300);
    Phase("Phase 2 - borne retiree", 1, 1);
    return 0;
}
