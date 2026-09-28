#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKUI/NKUI.h"
#include "NKCanvas/UI/NkUICanvasBackend.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo10";
    d.appVersion = "1.0.0";
    return d;
})());

namespace {

constexpr float32 BARRE_H = 36.f, BTN_W = 46.f;
enum Bouton { AUCUN = -1, REDUIRE = 0, AGRANDIR = 1, FERMER = 2 };

// Bouton sous le point (x,y) ; -1 si aucun. Le bouton FERMER est le plus a droite.
int BoutonSous(float32 x, float32 y, float32 W) {
    if (y < 0.f || y >= BARRE_H) return AUCUN;
    if (x >= W - BTN_W)       return FERMER;
    if (x >= W - 2 * BTN_W)   return AGRANDIR;
    if (x >= W - 3 * BTN_W)   return REDUIRE;
    return AUCUN;
}

void Centrer(nkui::NkUIDrawList& dl, nkui::NkUIFont* f, const char* s, float32 x, float32 y, float32 w, float32 h) {
    if (!f) return;
    const float32 tw = f->MeasureWidth(s);
    f->RenderText(dl, math::NkVec2f{ x + (w - tw) * 0.5f, y + (h - f->metrics.lineHeight) * 0.5f + f->metrics.ascender },
                  s, math::NkColor{ 235, 235, 235, 255 });
}

} // namespace

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo10"; cfg.width = 900; cfg.height = 520; cfg.centered = true;
    cfg.frame = false;                                   // pas de bordure ni de barre systeme
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    NkContextDesc desc; desc.api = NkGraphicsApi::NK_GFX_API_AUTO;
    auto& alloc = memory::NkGetDefaultAllocator();
    auto* rt = alloc.New<renderer::NkRenderWindow>(window, desc);
    if (!rt || !rt->IsValid()) return -1;

    nkui::NkUIFontConfig fc; fc.yAxisUp = false; fc.enableAtlas = true; fc.defaultFontSize = 20.f;
    auto* ui = alloc.New<nkui::NkUIContext>();
    ui->Init((int32)cfg.width, (int32)cfg.height, fc);
    auto* back = alloc.New<renderer::NkUICanvasBackend>();
    back->Init(rt->GetRenderer());
    const int32 fid = ui->fontManager.LoadEmbedded(nkui::NkEmbeddedFontId::DroidSans, 48.f);
    nkui::NkUIFont* font = ui->fontManager.Get(fid < 0 ? 0 : (uint32)fid);

    nkui::NkUIInputState in;
    float32 mx = 0.f, my = 0.f;              // souris en coordonnees client
    float32 sx = 0.f, sy = 0.f;              // souris en coordonnees ecran
    bool deplace = false, agrandie = false;
    float32 offX = 0.f, offY = 0.f;          // decalage de saisie (ecran - position fenetre)
    int enfonce = AUCUN;

    while (window.IsOpen()) {
        in.BeginFrame();
        const float32 W = (float32)window.GetSize().x;
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) {
                window.Close();
            } else if (auto* mv = ev->As<NkMouseMoveEvent>()) {
                mx = (float32)mv->GetX(); my = (float32)mv->GetY();
                sx = (float32)mv->GetScreenX(); sy = (float32)mv->GetScreenY();
                in.SetMousePos(mx, my);
                if (deplace) window.SetPosition((int32)(sx - offX), (int32)(sy - offY));
            } else if (auto* pr = ev->As<NkMouseButtonPressEvent>()) {
                if (!pr->IsLeft() || my >= BARRE_H) continue;
                enfonce = BoutonSous(mx, my, W);
                if (enfonce == AUCUN && !agrandie) {         // debut du deplacement (barre hors boutons)
                    deplace = true;
                    offX = sx - (float32)window.GetPosition().x;
                    offY = sy - (float32)window.GetPosition().y;
                    window.CaptureMouse(true);
                }
            } else if (auto* re = ev->As<NkMouseButtonReleaseEvent>()) {
                if (!re->IsLeft()) continue;
                if (deplace) { deplace = false; window.CaptureMouse(false); }
                if (enfonce != AUCUN && enfonce == BoutonSous(mx, my, W)) {   // clic valide = relache sur le meme bouton
                    if (enfonce == REDUIRE) window.Minimize();
                    else if (enfonce == AGRANDIR) { if (agrandie) window.Restore(); else window.Maximize(); agrandie = !agrandie; }
                    else if (enfonce == FERMER) window.Close();
                }
                enfonce = AUCUN;
            } else if (auto* dbl = ev->As<NkMouseDoubleClickEvent>()) {
                if (dbl->IsLeft() && my < BARRE_H && BoutonSous(mx, my, W) == AUCUN) {
                    deplace = false; window.CaptureMouse(false);
                    if (agrandie) window.Restore(); else window.Maximize();
                    agrandie = !agrandie;
                }
            }
        }
        if (!window.IsOpen()) break;

        const math::NkVec2u sz = rt->GetSize();
        const float32 Wr = (float32)sz.x;
        rt->Clear(math::NkColor{ 30, 34, 48, 255 });
        ui->BeginFrame(in, 0.f);
        nkui::NkUIDrawList& dl = *ui->dl;

        dl.AddRectFilled(math::NkFloatRect{ 0.f, 0.f, Wr, BARRE_H }, math::NkColor{ 45, 49, 66, 255 }, 0.f, 0.f);
        if (font) font->RenderText(dl, math::NkVec2f{ 14.f, (BARRE_H - font->metrics.lineHeight) * 0.5f + font->metrics.ascender },
                                   "Ma barre de titre", math::NkColor{ 235, 235, 235, 255 });
        const int survol = BoutonSous(mx, my, Wr);
        const char* etiq[3] = { "-", agrandie ? "o" : "[]", "x" };
        for (int b = 0; b < 3; ++b) {
            const float32 bx = Wr - (3 - b) * BTN_W;
            math::NkColor c = (survol == b) ? (b == FERMER ? math::NkColor{ 200, 60, 60, 255 } : math::NkColor{ 70, 75, 100, 255 })
                                            : math::NkColor{ 45, 49, 66, 255 };
            dl.AddRectFilled(math::NkFloatRect{ bx, 0.f, BTN_W, BARRE_H }, c, 0.f, 0.f);
            Centrer(dl, font, etiq[b], bx, 0.f, BTN_W, BARRE_H);
        }
        ui->EndFrame();
        back->Submit(*ui, sz.x, sz.y);
        rt->Display();
    }
    alloc.Delete(back); alloc.Delete(ui); alloc.Delete(rt);
    return 0;
}
