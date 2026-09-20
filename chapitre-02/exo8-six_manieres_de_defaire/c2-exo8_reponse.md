

# Mise en place des différentes situations

## Vérification finale des opérations

Après avoir réalisé les différentes situations, nous avons utilisé la commande suivante afin de vérifier l'état du dépôt, les stash, le reflog et l'historique :

```powershell
PS C:\Nkentseu\mon-depot> git status; git stash list; git reflog -12; git log --oneline --graph --decorate --all -15
```

### Sortie obtenue

```text
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
4df915b HEAD@{7}: commit: Nouveau message correct.
```

### Remarque

La première ligne :

```text
On branch test-espace.
nothing to commit, working tree clean.
```

indique que la branche `test-espace` est actuellement propre : aucune modification du working directory ou du staging n'est en attente.

---

## Vérification du `stash`

### Sortie obtenue

```text
stash@{0}: On test-espace: Travail en cours avant reflog.
stash@{1}: On test-espace: sauvegarde avant correction du rebase.
```

### Remarque

Ces deux lignes montrent que Git conserve les travaux temporairement mis de côté avec `git stash`.

Le premier stash :

```text
stash@{0}: On test-espace: Travail en cours avant reflog
```

correspond au travail mis de côté avant de commencer la situation concernant le `reflog`.

Le second :

```text
stash@{1}: On test-espace: sauvegarde avant correction du rebase
```

correspond à une sauvegarde effectuée précédemment pendant l'exercice.

Cela confirme que `git stash` permet de conserver temporairement des modifications sans créer de commit.

---

## Vérification du `reflog`

### Sortie obtenue

```text
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{0}: reset: moving to HEAD~1.
13733f2 (recuperation) HEAD@{1}: commit: Commit à retrouver.
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{2}: reset: moving to HEAD.
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{3}: reset: moving to HEAD.
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) HEAD@{4}: commit: Revert "Modification à annuler".
b57958f HEAD@{5}: commit (merge): Fusion de test-espace après résolution du conflit.
05cbd00 HEAD@{6}: commit: Modification à annuler.
4df915b HEAD@{7}: commit: Nouveau message correct.
```

### Remarque

Le `reflog` permet de consulter les déplacements précédents de `HEAD`.

La ligne :

```text
af07491 HEAD@{0}: reset: moving to HEAD~1
```

montre le `reset --hard HEAD~1` utilisé pour simuler la perte d'un commit.

La ligne :

```text
13733f2 (recuperation) HEAD@{1}: commit: Commit à retrouver
```

est particulièrement importante. Elle montre que le commit `13733f2`, qui avait été retiré de l'historique courant, est toujours identifiable grâce au `reflog`.

La branche :

```text
recuperation
```

pointe maintenant vers ce commit et permet donc de le conserver.

---

## Vérification du commit annulé avec `git revert`

### Sortie obtenue

```text
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) Revert "Modification à annuler".
```

### Remarque

Cette ligne confirme que le commit `05cbd00` a été annulé avec `git revert`.

Contrairement à `git reset`, `git revert` ne supprime pas le commit original. Il crée un nouveau commit :

```text
af07491 Revert "Modification à annuler"
```

Ce nouveau commit inverse les modifications du commit précédent.

Le fait que `HEAD` et `origin/test-espace` pointent tous les deux vers `af07491` montre également que l'annulation a été poussée vers le dépôt distant.

---

## Vérification de la fusion

### Sortie obtenue

```text
b57958f HEAD@{5}: commit (merge): Fusion de test-espace après résolution du conflit.
```

et :

```text
b57958f Fusion de test-espace après résolution du conflit.
```

### Remarque

Le commit `b57958f` correspond à la fusion réalisée après la résolution du conflit entre les différentes modifications de `test-espace`.

Le terme :

```text
commit (merge)
```

indique que ce commit est un commit de fusion possédant plusieurs parents.

---

## Vérification du commit qui devait être annulé

### Sortie obtenue

```text
05cbd00 HEAD@{6}: commit: Modification à annuler.
```

### Remarque

Cette ligne permet de constater que le commit `05cbd00` existe toujours dans l'historique du dépôt.

C'est justement le fonctionnement de `git revert` : le commit original n'est pas supprimé. Un nouveau commit, `af07491`, vient annuler ses effets.

---

## Vérification du commit récupéré avec `reflog`

Une autre sortie obtenue lors de la vérification est :

```text
13733f2 (recuperation) Commit à retrouver.
11edbe1 (refs/stash) On test-espace: Travail en cours avant reflog.
adc527f index on test-espace: af07491 Revert "Modification à annuler".
af07491 (HEAD -> test-espace, origin/test-espace, origin/HEAD) Revert "Modification à annuler".
b57958f Fusion de test-espace après résolution du conflit.
```

### Remarque

Cette sortie permet de visualiser simultanément plusieurs éléments importants de l'exercice.

Le commit :

```text
13733f2 (recuperation) Commit à retrouver
```

confirme que le commit considéré comme « perdu » a été retrouvé grâce au `reflog` et sauvegardé avec la branche `recuperation`.

La ligne :

```text
11edbe1 (refs/stash) On test-espace: Travail en cours avant reflog
```

correspond à la référence interne du stash contenant le travail temporairement mis de côté.

La ligne :

```text
adc527f index on test-espace: af07491 Revert "Modification à annuler"
```

correspond à l'état de l'index sauvegardé avec le stash.

Enfin :

```text
af07491 Revert "Modification à annuler"
```

confirme la présence du commit créé par `git revert`, tandis que :

```text
b57958f Fusion des modifications...
```

correspond au commit de fusion effectué précédemment.

---

# Correspondance entre les 6 situations et les opérations

| Situation                  | Opération utilisée            | But                                                              |
| -------------------------- | ----------------------------- | ---------------------------------------------------------------- |
| 1. Modification non voulue | `git restore`                 | Annuler une modification locale                                  |
| 2. `add` de trop           | `git restore --staged`        | Retirer un fichier du staging sans supprimer ses modifications   |
| 3. Commit de trop          | `git reset --soft HEAD~1`     | Annuler le dernier commit en conservant son contenu              |
| 4. Commit déjà poussé      | `git revert`                  | Annuler un commit partagé en créant un nouveau commit inverse    |
| 5. Travail en cours        | `git stash` / `git stash pop` | Mettre temporairement de côté puis récupérer des modifications   |
| 6. Commit « perdu »        | `git reflog`                  | Retrouver une ancienne position de `HEAD` et récupérer le commit |

## Conclusion

Les différentes sorties obtenues permettent de vérifier les six situations demandées. Le `status` confirme que le dépôt est propre, le `stash list` confirme la conservation des travaux temporaires, le `reflog` permet de retrouver les anciennes positions de `HEAD`, et le `log` permet de visualiser les commits, la fusion et le commit d'annulation.

**Cette fois, les lignes que tu as données sont bien intégrées dans le README**, notamment `13733f2`, `11edbe1`, `adc527f`, `af07491`, `b57958f`, ainsi que toute la sortie de `git status`, `git stash list` et `git reflog`.
