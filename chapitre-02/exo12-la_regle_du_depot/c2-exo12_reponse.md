# règles d'un projet à plusieurs ( cas de 4 étudiants)
chacun d'eux doit créer sa branche et les branches ne sont pas créé au hasard chacun d'eux hérite d'une branche qui définit une partie des tâches qui doivent être faites pour la réalisation du projet .
les commits doivent être cohérent avec l'amélioration du travail.  
``Les interdits`` .  
on ne travaille jamais sur la branche principale
tout commit doit être relu par au moins un autre étudiant avant d'arriver à la branche principale. un commit contient de base le contenu( l'état des fichiers suivis) , l'auteur , la date et les commits d'avants  
interdit de modifier le travail d'un autre sans son accord 
interdit partager des informations sensibles ( mot de passe ...) pouvant donner accès à d'autres individus au travail 
interdit de modifier les même lignes d'un même fichier sur des dépôt différents pour éviter les conflits.  
`` en cas de casse de la branche principale`` .  
La personne qui constate le problème prévient le groupe et indique :
ce qui ne fonctionne plus 
le commit qui semble être à l'origine du problème ;
les messages d'erreur éventuels.
Si possible, on corrige rapidement dans une branche, puis on fait relire la correction avant de la fusionner.
Si le problème vient clairement du dernier commit et qu'il faut simplement revenir à l'état précédent, on privilégie :git revert <commit>
On travaille dans sa branche, on fait des commits propres, on fait relire avant d'intégrer et on protège la branche principale.
En cas de doute, on demande au groupe avant de modifier l'historique partagé avant de prendre une décision
