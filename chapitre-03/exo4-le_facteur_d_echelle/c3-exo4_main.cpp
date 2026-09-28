#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo4";
    d.appVersion = "1.0.0";
    return d;
})());

namespace {

void Rapport(NkWindow& window, renderer::NkRenderWindow& rt, const char* raison) {
    const math::NkVec2u f = window.GetSize();
    const math::NkVec2u r = rt.GetSize();
    const float32 echelle = window.GetDpiScale();
    char t[200];
    std::snprintf(t, sizeof(t), "fenetre %ux%u | cible %ux%u | echelle x%.2f", f.x, f.y, r.x, r.y, echelle);
    window.SetTitle(t);
    std::printf("[%s] %s\n", raison, t);
}

} // namespace

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo4"; cfg.width = 1000; cfg.height = 600; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    NkContextDesc desc;
    desc.api = NkGraphicsApi::NK_GFX_API_AUTO;
    auto& alloc = memory::NkGetDefaultAllocator();
    auto* rt = alloc.New<renderer::NkRenderWindow>(window, desc);
    if (!rt || !rt->IsValid()) return -1;

    uint32 lastW = 0, lastH = 0;
    Rapport(window, *rt, "demarrage");

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (ev->Is<NkWindowDpiEvent>()) {
                Rapport(window, *rt, "changement DPI");
            }
        }
        // resize : on ne reagit que si la taille a REELLEMENT change (piege WM_SIZE a la creation)
        const math::NkVec2u sz = rt->GetSize();
        if (sz.x != lastW || sz.y != lastH) {
            if (lastW != 0 && sz.x > 0 && sz.y > 0) rt->OnResize(sz.x, sz.y);
            lastW = sz.x; lastH = sz.y;
            Rapport(window, *rt, "taille changee");
        }
        rt->Clear(math::NkColor{ 30, 34, 48, 255 });
        rt->Display();
    }
    alloc.Delete(rt);
    return 0;
}
