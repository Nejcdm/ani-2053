# Création du dépôt distant et des deux répertoires de travail
(dépot distant)Cloning into bare repository '..\depot-distant.git'...
done .   
définition de ce dépôt comme origine .   
origin  ..\depot-distant.git (fetch)
origin  ..\depot-distant.git (push)
(répertoire A)Cloning into '..\depot-A'...
done.  
(répertoire B) Cloning into '..\depot-B'...
done.  
# modification de la ligne du fichier dans un répertoire (A)
git commit -m "Modification depuis A".  
[test-espace 53274a8] Modification depuis A.  
 1 file changed, 1 insertion(+), 1 deletion(-). 
 ##sortie: 
 work hard.  
Stay focus.  

won.  


discpline.  
Deuxième modification.  
Discipline.  
Modification depuis A.  
 git push origin test-espace.  
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 12 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 337 bytes | 337.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
To C:/Nkentseu/mon-depot/..\depot-distant.git
   558f003..53274a8  test-espace -> test-espace
   # modification de la même ligne du fichier dans le second répertoire (B)
    Modification depuis B
 1 file changed, 1 insertion(+), 1 deletion(-)
 # sortie :
 work hard.  
Stay focus.  

won.  


discpline.  
Deuxième modification.  
Discipline.  
Modification depuis A.  
PS C:\Nkentseu\depot-B> git push origin test-espace
# Refus du push (car les modifications de A ne sont pas présentes dans le répertoire B)
error: failed to push some refs to 'C:/Nkentseu/mon-depot/..\depot-distant.git'
hint: Updates were rejected because the remote contains work that you do not
hint: have locally. This is usually caused by another repository pushing to
hint: the same ref. If you want to integrate the remote changes, use
hint: 'git pull' before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
PS C:\Nkentseu\depot-B> git pull
remote: Enumerating objects: 5, done.
remote: Counting objects: 100% (5/5), done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 3 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (3/3), 317 bytes | 24.00 KiB/s, done.
From C:/Nkentseu/mon-depot/..\depot-distant
   558f003..53274a8  test-espace -> origin/test-espace
Auto-merging taff1.txt
# Conflit après récupération des modifications du répertoire A avec git pull.
# sortie :
work hard.  
Stay focus.  

won.  


discpline.  
Deuxième modification.  
Discipline.  
<<<<<<< HEAD
Modification depuis B
=======
Modification depuis A
>>>>>>> 53274a8.  
CONFLICT (content): Merge conflict in taff1.txt
Automatic merge failed; fix conflicts and then commit the result.
# Résolution du conflit 
suppréssion de la modification depuis B
sortie :
 work hard.  
Stay focus.  

won.  


discpline.  
Deuxième modification.  
Discipline.  
Modification depuis A .  
puis add , commit et push.  
sortie :
git push origin test-espace
Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 12 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 635 bytes | 158.00 KiB/s, done.
Total 6 (delta 2), reused 0 (delta 0), pack-reused 0 (from 0)
To C:/Nkentseu/mon-depot/..\depot-distant.git
   53274a8..8ba7513  test-espace -> test-espace
   merci pour la remarque Mr je n'avais pas compris que la présence des marqueurs était une remarque de git de la modification de la même ligne dans un fichier depuis des répertoires différents
