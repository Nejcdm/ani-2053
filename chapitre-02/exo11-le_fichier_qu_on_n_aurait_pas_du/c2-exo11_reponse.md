# Commit d'un fichier de 10mo  dans mom dépôt 
``taille `de .Git au départ``
0,0430850982666016 Mo
``creation du fichier``
Name          Length    
----          ------
fichier.bin 10485760  
``commmit du fichier``
git commit -m "ajout de fichier"                      
[rebase-master 8ec4618] ajout de fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 ``après le commit taille de .Git``
 10,0463733673096
 ``supression de fichier``
 [rebase-master b396e18] Suppression de fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 delete mode 100644 fichier.bin
 git add -u
>> git commit -m "Suppression de fichier"
On branch rebase-master
nothing to commit, working tree clean
 ``taille de .Git après suppression``
 10,0468101501465
 # Remarque
 pour ma part je conclu que même après avoir supprimé un fichier après un commit , le fichier est toujours dans l'historique de Git et disponible à partir de l'ancien commit 
 
