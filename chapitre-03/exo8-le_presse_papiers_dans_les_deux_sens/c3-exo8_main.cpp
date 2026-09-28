// c3-exo8 : presse-papiers dans les deux sens.
// T : lit le texte, le met en MAJUSCULES, le remet.
// I : lit l'image, inverse ses couleurs, la remet.
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKImage/NKImage.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo8";
    d.appVersion = "1.0.0";
    return d;
})());

// ===== COUCHE D'ADAPTATION : [API A CONFIRMER] =====
// Le presse-papiers n'est pas documente dans les guides. Verifier le nom reel
// (NkClipboard ? window.GetClipboard() ?) dans NKWindow et corriger UNIQUEMENT ici.
static bool LireTexte(NkWindow& w, NkString& out)        { return w.GetClipboardText(out); }
static bool EcrireTexte(NkWindow& w, const NkString& s)  { return w.SetClipboardText(s); }
static bool LireImage(NkWindow& w, NkImage& out)         { return w.GetClipboardImage(out); }
static bool EcrireImage(NkWindow& w, const NkImage& img) { return w.SetClipboardImage(img); }
// ====================================================

static void TexteEnMajuscules(NkWindow& w) {
    NkString s;
    if (!LireTexte(w, s) || s.Length() == 0) { std::printf("[texte] presse-papiers vide ou sans texte\n"); return; }
    for (usize i = 0; i < s.Length(); ++i) {
        char c = s[i];
        if (c >= 'a' && c <= 'z') s[i] = (char)(c - 'a' + 'A');   // ASCII seulement : les octets UTF-8 (>127) restent intacts
    }
    std::printf("[texte] %s\n", EcrireTexte(w, s) ? "remis en majuscules (ASCII)" : "ECHEC ecriture");
}

static void InverserImage(NkWindow& w) {
    NkImage img;
    if (!LireImage(w, img) || !img.IsValid()) { std::printf("[image] presse-papiers sans image\n"); return; }
    uint8* p = img.Pixels();                      // RGBA 8 bits (4 canaux)
    const usize n = (usize)img.Width() * (usize)img.Height();
    for (usize i = 0; i < n; ++i) {               // on inverse R,G,B ; on GARDE l'alpha
        p[i*4 + 0] = (uint8)(255 - p[i*4 + 0]);
        p[i*4 + 1] = (uint8)(255 - p[i*4 + 1]);
        p[i*4 + 2] = (uint8)(255 - p[i*4 + 2]);
    }
    std::printf("[image] %ux%u %s\n", img.Width(), img.Height(), EcrireImage(w, img) ? "inversee et remise" : "ECHEC ecriture");
}

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo8 - T = texte, I = image"; cfg.width = 640; cfg.height = 360; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;
    std::printf("Copiez un texte puis appuyez sur T ; copiez une image puis appuyez sur I.\n");

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) window.Close();
            else if (auto* kp = ev->As<NkKeyPressEvent>()) {
                if (kp->GetKey() == NkKey::NK_ESCAPE) window.Close();
                if (kp->GetKey() == NkKey::NK_T) TexteEnMajuscules(window);
                if (kp->GetKey() == NkKey::NK_I) InverserImage(window);
            }
        }
        NkChrono::Sleep((int64)16);
    }
    return 0;
}
