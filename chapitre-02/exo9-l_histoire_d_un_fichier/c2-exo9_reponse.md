 `Applications/NKEditMeshHarness/src/main.cpp`.

Les trois plus gros changements sont bien déterminés par le `numstat` :

| Date  | Commit     | Volume modifié | Objet principal                                               |
| ----- | ---------- | -------------: | ------------------------------------------------------------- |
| 29/07 | `89eb9cab` |           +398 | Création du harnais de non-régression                         |
| 22/08 | `b0c5c8fd` |           +435 | Couverture des 19 dernières méthodes publiques                |
| 23/08 | `f20dacbb` |      +435 / −1 | Conservation des matériaux + mesures de performance           |
| 10/09 | `addf709d` |    +2571 / −13 | Intégration NKCode beta.8 → beta.11 et nombreuses corrections |

Pour `addf709d`, le message montre que le changement est beaucoup plus large : il regroupe notamment la vérification des codes clavier Android, la gestion des boutons système, la chaîne de compilation NKCode, les versions de Jenga, Python embarqué, les builds distants et plusieurs corrections de méthode. Il s'agit donc clairement du **plus gros changement en volume** dans l'histoire du fichier.


### Histoire de `Applications/NKEditMeshHarness/src/main.cpp`

Le fichier `Applications/NKEditMeshHarness/src/main.cpp` est enregistré le **29 juillet 2026**, avec le commit `89eb9cab`, intitulé *« Harnais de non-regression de NkEditMesh (prealable a la refonte BMesh) »*. Cette première version ajoute 398 lignes. Le fichier est donc créé comme un **banc de non-régression** destiné à sécuriser `NkEditMesh` avant sa refonte autour de BMesh. Les commits qui suivent montrent ensuite une extension progressive du banc pour vérifier les nouvelles fonctionnalités du moteur : création des arêtes, opérations de fusion , édition proportionnelle, symétrie, cycles radial et disque, aimantation et autres opérations.

Le premier des trois plus gros changements intervient le **22 août 2026**, avec `b0c5c8fd` (+435 lignes). Le commit complète fortement la couverture des tests : les **19 dernières méthodes publiques de `NkEditMesh`** obtiennent leur propre banc, portant la couverture à **94/94 méthodes**. Le message précise que chaque prédicat est testé dans deux situations, une où il doit répondre « oui » et une où il doit répondre « non ». La raison est d'éviter un faux succès : une fonction qui retournerait toujours `true` pourrait sinon passer les tests. Le changement vise donc surtout à rendre les tests réellement discriminants plutôt qu'à simplement augmenter leur nombre.

Le deuxième changement majeur arrive le **23 août 2026**, avec `f20dacbb` (+435 lignes et −1). Il concerne la **conservation du matériau par face** lors de plusieurs opérations : Mirror, Array, Triangulate, Build, Mask, Solidify et SpinSelected. Le message explique que le problème se trouvait principalement dans le banc de tests : les opérations concernées n'étaient pas réellement exercées par les cas existants. De nouveaux cas `matmod/` sont donc ajoutés et la référence passe de 260 à 269 cas. Les mesures montrent également que le transport du matériau coûte très peu par rapport au bruit de mesure. En revanche, le benchmark révèle un autre problème : `RebuildEdges` devient extrêmement coûteux lorsque le nombre de faces augmente, avec environ 1 580 ms pour 16 384 faces. Le banc ne sert donc plus seulement à confirmer une correction : il permet aussi de découvrir un problème de performance indépendant.

Enfin, le plus gros changement de l'histoire du fichier est le commit **`addf709d` du 10 septembre 2026**, avec **2 571 lignes ajoutées et 13 supprimées**, soit 2 584 lignes modifiées. Son message, *« NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86) »*, correspond à une importante intégration regroupant de nombreuses corrections et vérifications. Le commit traite notamment des codes clavier Android manquants, détecte des correspondances incorrectes comme `AKEYCODE_BRIGHTNESS_DOWN` associé à `NK_MEDIA_MUTE`, complète les tests des événements Android et documente les limites imposées par Android. Il contient également plusieurs évolutions de NKCode : compilateur configurable, outils POSIX, versions de Jenga, Python embarqué, builds distants, mise à jour indépendante de Jenga et vérifications de publication. Le message insiste à plusieurs reprises sur une même démarche : **mesurer et vérifier plutôt que supposer**, et conserver les erreurs découvertes dans la documentation et les tests.

Ainsi, l'histoire de ce fichier montre une évolution d'un simple **harnais de non-régression créé avant la refonte BMesh** vers un banc beaucoup plus large servant à vérifier la couverture fonctionnelle, la conservation des données du maillage, les performances et finalement plusieurs aspects de l'intégration et de la chaîne de développement. Les messages de commit montrent également une volonté constante de transformer les problèmes découverts en **tests reproductibles**, plutôt que de simplement corriger le symptôme.


