# Les intégrations par fusion et rejouer
cd C:\Users\Pc\OneDrive\Desktop\Nkentseu
mkdir comparaison-merge-rebase
cd comparaison-merge-rebase
git init
"Base" | Out-File taff.txt -Encoding utf8
git add taff.txt
git commit -m "Commit de base"
``création d'une nouvelle branche``
git switch -c fonctionnalite
``les commits sur la branche``
Add-Content taff.txt "Modification A"
git add taff.txt
git commit -m "Modification A"

Add-Content taff.txt "Modification B"
git add taff.txt
git commit -m "Modification B"
``retour sur master et mise en place dún commit différent``
git switch master

Add-Content taff.txt "Modification master"
git add taff.txt
git commit -m "Modification sur master"
``fusion``
git merge fonctionnalite -m "Fusion de fonctionnalite"
conflit rencontré
résolution du conflit puis 
git add taff.txt
git commit -m "Fusion de fonctionnalite"
fusion:
*   39ab62f (HEAD -> master) Fusion de fonctionnalite
|\  
| * bede6ec (fonctionnalite) Modification B
| * bdf03d8 Modification A
* | 915b42f Modification sur master
|/  
* ec5fa46 Commit de base
``création de branche pour le rebase``
git branch rebase-master 915b42f
git branch rebase-fonctionnalite bede6ec
basculez via
git switch rebase-master
``rebase``
git rebase rebase-fonctionnalite
conflit rencontré comme le merge
résolution du conflit:
interactive rebase in progress; onto bede6ec
Last command done (1 command done):
   pick 915b42f # Modification sur master
No commands remaining.
You are currently rebasing branch 'rebase-master' on 'bede6ec'.
  (all conflicts fixed: run "git rebase --continue")

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   taff.txt
``rebase terminee``
r=true rebase --continue
[detached HEAD d32294f] Modification sur master
 1 file changed, 3 insertions(+), 2 deletions(-)
Successfully rebased and updated refs/heads/rebase-master.
Deletion of directory '.git/rebase-merge' failed. Should I try again? (y/n) 
suppression du dossier temporaire du rebase
``sortie de la fusion``
*   39ab62f (master) Fusion de fonctionnalite
|\
| * bede6ec Modification B
| * bdf03d8 Modification A
* | 915b42f Modification sur master
|/
* ec5fa46 Commit de base
 ``sortie du rebase``
* d32294f (rebase-master) Modification sur master
* bede6ec Modification B
* bdf03d8 Modification A
* ec5fa46 Commit de base
# remarque
J’ai réalisé deux fois la même intégration à partir du même historique : une première fois avec `merge`, puis une seconde fois avec `rebase`.

Avec `merge`, Git conserve les deux branches et crée un commit de fusion `39ab62f`. Le graphe montre donc clairement la divergence puis la réunion des historiques. Avec `rebase`, le commit « Modification sur master » est rejoué après les commits de la branche `fonctionnalite`, ce qui produit le nouveau commit `d32294f` et un historique linéaire.

Je préfère lire le graphe obtenu avec `rebase`, car il est plus simple à suivre : les commits apparaissent dans un seul ordre chronologique et il n’y a pas de commit de fusion supplémentaire qui vient interrompre la lecture. Le graphe est donc plus lisible pour comprendre rapidement l’enchaînement des modifications.

  
