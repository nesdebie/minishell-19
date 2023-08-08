CD :
[SOLVED] SEGFAULT dossier parent "rm ../../d1"

EXPORT :
[SOLVED] probleme dans le nom de la clef, uniquement alpha numerique et le premier carractere ne peut etre un chiffre et aussi le _ aui est une exeption (unset as les memes problemes)
[SOLVED] -si la variable n'existe pas elle doit etre crée avec += comme avec =
[SOLVED] -SEGFAULT si espace n'est pas a la fin de la string exportée
[SOLVED] -SEGFAULT si export est envoyé avec une clef sans =

REDIRECTION :
[SOLVED] SEGFAULT : en premier avant la commade ">test ls" (peu importe la redirection)
cas d'erreur indefini : "echo hi >>./outfile01 | echo bye >>./outfile02" (probablement pipe et builtins)

HEREDOC :
bug d'affichage heredoc, espace devant prompt si "\n"
bug si mot clef pas tape entierement
bug si double heredoc l'une après l'autre : "cat <<"gnah" <<gnih"
BOUCLE INFINIE si simple redirection precedee de cat et suivie de heredoc : cat <gnouh <<gnah

PARSING :
[SOLVED] - gros probleme sur les builtins au niveau des strcmp, si on met le nom d'un builtin avant des carractere supplementaires, il l'interprete comme builtin
- ls >"./outfiles/outfile""1""2""3""4""5"
( -ecrit une newline quand "echo L|echo j" )

EXECUTION PIPE :
( cat minishell.h | grep ");"$     "si l'argument de cat n'existe pas, l'execution s'arrete" ) BUG
[SOLVED] exit ecrit exit, ce qui fait que le pipe recois un retour de exit et permet par exemple avec cette commande : "ls | exit | cat" d'ecrire exit

GESTION BUILTINS :
exit 42 world    "Erreur de message, mini affiche numeric argument required mais devrait afficher too many arguments"
beaucoup de message d'erreur son affichees sur la sortie standart alors qu'ils devraient etre affiches sur sortie d'erreur
[SOLVED] erreur sur export, si la clef n'est pas bonne, retourner message d'erreur : not a valid identifier)

SUBSTITUTION :
[SOLVED] GROSSE ERREUR NIVEAU SUBSTITUTION, PAS FAITE AU BON MOMENT, CELA DEVRAIT REGLER PLEIN D'ERREURS.
[SOLVED] arreter de chercher clef si $? exemple : echo $?HELLO devrait retourner 0HELLO mais retourne juste 0
[SOLVED] plusieurs cas d'erreur sur $? exemple : echo "exit_code ->$? user ->$USER home -> $HOME"
[SOLVED] substitution pas faite au bon moment, exemple : $FGDHGH echo gnah devrait remplacer par rien $FGDHGH et executer echo gnah
[SOLVED] si il y a des substitutions qui se suivent, il ne fait pas la substitution cela ne fonctionne donc pas

EXECUTION :
si commande avec chemin relatif verifier d'abord aue c'est un fichier et puis un dossier , actuellement c'est l'inverse

CRASH :
[SOLVED] - minishell se coupe si on alligne trop de pipe environ 1300 (1253) MAX 400 | ERROR_CODE 1

SIGNAUX :
si Plusieux minishell inception et que cat, les signaux font de la merde et on se retrouve avec le nombre d'instance = au nombre de \n
