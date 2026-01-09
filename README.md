Introduction aux risques d'un code non protégé, plus particulièrement à propos de buffers avec possible overflow, à travers de petits exercices de recherche de failles de sécurité en ASM.

Le projet s'est effectué dans une VM minutieusement organisée par l'école, avec de très nombreuses sécurités désactivées, où l'élève doit chercher la faille avec son user actuel, et récupérer le mot de passe du suivant. Un compte rendu est écrit dans le ```walkthrough.md``` de chaque niveau, et une reconstruction du code C est présente dans le ```source.c``` fichier.

Failles de chaque niveau:

0. ASM ```cmp```
1. Stack-based buffer overflow - Fonction interne
2. Stack-based buffer overflow - Heap shellcode
3. printf format string - Variable globale
4. printf format string - Variable globale
5. printf format string - Global Offset Table
6. Heap-based buffer overflow - Fonction interne
7. Heap-based buffer overflow - Global Offset Table
8. Heap-based buffer overflow - Out-of-bound read
9. Heap-based buffer overflow - C++ vTable

Failles de chaque niveau bonus:

0. Stack-based buffer overflow - Unsafe ```strcpy```
1. Stack-based buffer overflow - Int overflow
2. Stack-based buffer overflow - Variable d'environnement
3. Erreur de logique

Crédits:  
[Alexis Payen](https://github.com/Alexioos95/) - Recherche de failles et écriture des comptes-rendus.  
[Eli Ewu](https://github.com/Uweile) - Recherche de failles et relecture des comptes-rendus.
