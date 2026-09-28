#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo7";
    d.appVersion = "1.0.0";
    return d;
})());

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo7 - capture OFF (C = basculer)"; cfg.width = 700; cfg.height = 450; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    bool capture = false, glisse = false;
    int nbMoves = 0;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
                if (kp->GetKey() == NkKey::NK_C && !glisse) {
                    capture = !capture;
                    window.SetTitle(capture ? "c3-exo7 - capture ON (C = basculer)" : "c3-exo7 - capture OFF (C = basculer)");
                    std::printf("--- capture %s ---\n", capture ? "ON" : "OFF");
                }
            } else if (auto* pr = ev->As<NkMouseButtonPressEvent>()) {
                if (pr->IsLeft()) {
                    glisse = true; nbMoves = 0;
                    if (capture) window.CaptureMouse(true);
                    std::printf("PRESS   (%d,%d)\n", (int)pr->GetX(), (int)pr->GetY());
                }
            } else if (auto* mv = ev->As<NkMouseMoveEvent>()) {
                if (glisse && (++nbMoves % 10 == 0))
                    std::printf("  move  (%d,%d)  [%d evenements]\n", (int)mv->GetX(), (int)mv->GetY(), nbMoves);
            } else if (auto* re = ev->As<NkMouseButtonReleaseEvent>()) {
                if (re->IsLeft() && glisse) {
                    glisse = false;
                    if (capture) window.CaptureMouse(false);
                    std::printf("RELEASE (%d,%d)  total %d moves\n", (int)re->GetX(), (int)re->GetY(), nbMoves);
                }
            }
        }
        NkChrono::Sleep((int64)16);
    }
    if (glisse) std::printf("ATTENTION : glisser jamais termine par un RELEASE recu\n");
    return 0;
}
