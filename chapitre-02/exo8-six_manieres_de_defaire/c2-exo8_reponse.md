# mise en place situation des différentes situations
13733f2 (recuperation) Commit à retrouver.  
11edbe1 (refs/stash) On test-espace: Travail en cours avant reflog.  
adc527f index on test-espace: af07491 Revert "Modification à annuler".  
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) Revert "Modification à annuler".  
b57958f Fusion de test-espace après résolution du conflit.  
PS C:\Nkentseu\mon-depot> git status; git stash list; git reflog -12; git log --oneline --graph --decorate --all -15.  
On branch test-espace.  
nothing to commit, working tree clean.  
stash@{0}: On test-espace: Travail en cours avant reflog.  
stash@{1}: On test-espace: sauvegarde avant correction du rebase.  
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{0}: reset: moving to HEAD~1.  
13733f2 (recuperation) HEAD@{1}: commit: Commit à retrouver.  
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{2}: reset: moving to HEAD.  
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{3}: reset: moving to HEAD.  
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{4}: commit: Revert "Modification à annuler".  
b57958f HEAD@{5}: commit (merge): Fusion de test-espace après résolution du conflit.  
05cbd00 HEAD@{6}: commit: Modification à annuler.  
4df915b HEAD@{7}: commit: Nouveau message correct:.  
# Remarque que j'ai faites 
## Remarques

### 1. Annuler une modification non voulue — `git restore`

**But :** revenir à la dernière version enregistrée du fichier et supprimer une modification locale qui n’a pas encore été commitée.


Cette commande agit sur le **working directory**. Elle permet donc d’annuler une modification accidentelle avant qu’elle ne soit enregistrée dans l’historique Git.

---

### 2. Annuler un `add` de trop — `git restore --staged`

**But :** retirer un fichier de la zone de staging sans supprimer les modifications effectuées dans le fichier.



Le fichier reste modifié dans le répertoire de travail, mais il n’est plus préparé pour le prochain commit.

**Différence importante :**

* `git restore <fichier>` → annule la modification du fichier.
* `git restore --staged <fichier>` → retire le fichier du staging, mais conserve la modification.

---

### 3. Annuler un commit de trop — `git reset --soft HEAD~1`

**But :** supprimer le dernier commit de l’historique local tout en conservant les modifications dans le staging.


`HEAD~1` désigne le commit situé juste avant le commit actuel.

L'option `--soft` déplace simplement le pointeur `HEAD`. Les modifications du commit restent donc disponibles pour être éventuellement corrigées puis recommitées.

---

### 4. Annuler un commit déjà poussé — `git revert`

**But :** annuler les effets d’un commit qui a déjà été envoyé sur le dépôt distant sans réécrire l’historique partagé.



Contrairement à `reset`, `revert` ne supprime pas le commit original. Il crée **un nouveau commit** qui inverse ses modifications.

C’est particulièrement adapté lorsqu’un commit a déjà été partagé avec d’autres personnes.

Dans notre exercice, cela a produit :



### 5. Mettre un travail en cours de côté — `git stash`

**But :** sauvegarder temporairement des modifications non commitée afin de pouvoir travailler sur un dépôt propre sans créer immédiatement un commit.


Le travail est retiré du répertoire de travail et conservé temporairement par Git.

Pour le récupérer :



Cette commande réapplique les modifications et supprime normalement le stash correspondant lorsqu’il est appliqué avec succès.




### 6. Retrouver un commit « perdu » — `git reflog`

**But :** retrouver les anciennes positions de `HEAD`, notamment après un `reset`, un rebase ou une autre opération ayant modifié l’historique local.



Le `reflog` conserve une trace des déplacements récents de `HEAD`, même lorsqu’un commit n’est plus visible avec `git log`.

Dans notre exercice, le commit :


avait été rendu inaccessible depuis l’historique courant avec :

Le `reflog` nous a permis de retrouver son identifiant :

```text
13733f2
```

Puis nous l'avons sécurisé avec :

La branche `recuperation` pointe ainsi directement vers le commit retrouvé.

---

## Conclusion

Ces six opérations correspondent à six problèmes différents rencontrés lors de l’utilisation de Git :

* **`restore`** → annuler une modification locale ;
* **`restore --staged`** → corriger une erreur de staging ;
* **`reset --soft`** → revenir avant un commit tout en conservant son contenu ;
* **`revert`** → annuler un commit déjà partagé sans réécrire l’historique ;
* **`stash`** → mettre temporairement un travail de côté ;
* **`reflog`** → retrouver une ancienne position de `HEAD` et récupérer un commit devenu inaccessible dans l’historique courant.

L’exercice montre ainsi que Git permet de corriger différentes erreurs selon l’endroit où se trouve le changement : **working directory, staging area, historique local ou dépôt distant**.
