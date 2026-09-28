// c3-exo9 : les quatre dialogues natifs, annulation geree dans chacun.
// 1 = message (Oui/Non/Annuler)  2 = ouvrir un fichier  3 = enregistrer sous  4 = choisir un dossier.
// Fermer la boite sans rien choisir ne doit jamais faire planter : on teste TOUJOURS le retour.
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include <cstdio>

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]() {
    NkAppData d{};
    d.appName    = "c3-exo9";
    d.appVersion = "1.0.0";
    return d;
})());

// ===== COUCHE D'ADAPTATION : [API A CONFIRMER] =====
// Les dialogues natifs ne sont pas documentes dans les guides. Verifier les noms reels
// (NkDialogs::... ?) et le type de retour d'annulation, puis corriger UNIQUEMENT ici.
// Contrat de cette couche : renvoie false si l'utilisateur annule / ferme sans choisir.
enum class Reponse { Oui, Non, Annule };
static Reponse DialogueMessage(NkWindow& w)              { return (Reponse)NkDialogs::MessageBox(w, "Question", "Continuer ?", NkDialogs::NK_YES_NO_CANCEL); }
static bool    DialogueOuvrir(NkWindow& w, NkString& out){ return NkDialogs::OpenFile(w, "Ouvrir un fichier", out); }
static bool    DialogueEnregistrer(NkWindow& w, NkString& out) { return NkDialogs::SaveFile(w, "Enregistrer sous", out); }
static bool    DialogueDossier(NkWindow& w, NkString& out)     { return NkDialogs::PickFolder(w, "Choisir un dossier", out); }
// ====================================================

int nkmain(const NkEntryState& state) {
    (void)state;
    NkWindowConfig cfg;
    cfg.title = "c3-exo9 - touches 1 a 4"; cfg.width = 640; cfg.height = 360; cfg.centered = true;
    NkWindow window;
    if (!window.Create(cfg)) return -1;

    while (window.IsOpen()) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (ev->Is<NkWindowCloseEvent>()) { window.Close(); continue; }
            auto* kp = ev->As<NkKeyPressEvent>();
            if (!kp) continue;
            NkString chemin;
            switch (kp->GetKey()) {
                case NkKey::NK_ESCAPE: window.Close(); break;
                case NkKey::NK_1: {
                    const Reponse r = DialogueMessage(window);
                    std::printf("message : %s\n", r == Reponse::Oui ? "Oui" : (r == Reponse::Non ? "Non" : "ANNULE / ferme"));
                    break;
                }
                case NkKey::NK_2:
                    if (DialogueOuvrir(window, chemin)) std::printf("ouvrir : %s\n", chemin.CStr());
                    else std::printf("ouvrir : ANNULE (aucun fichier)\n");
                    break;
                case NkKey::NK_3:
                    if (DialogueEnregistrer(window, chemin)) std::printf("enregistrer : %s\n", chemin.CStr());
                    else std::printf("enregistrer : ANNULE (rien ecrit)\n");
                    break;
                case NkKey::NK_4:
                    if (DialogueDossier(window, chemin)) std::printf("dossier : %s\n", chemin.CStr());
                    else std::printf("dossier : ANNULE (aucun dossier)\n");
                    break;
                default: break;
            }
        }
        NkChrono::Sleep((int64)16);
    }
    return 0;
}
