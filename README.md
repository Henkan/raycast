# Imagerie Numérique - Projet

## Description
Ce programme permet d'obtenir une image à partir de la description d'une scène grâce à l'algorithme du raytracing. Il a été développé en C++ avec la librairie FreeImage sur l'environnement Visual Studio 2019.

Pour exécuter le projet, exécuter la commande :
```
DemoFreeImage.exe ./scene.txt
```
Cela va créer l'image décrite dans la scène passée en paramètre. L'image de sortie se nommera `out.bmp` et elle sera affichée dans une fenêtre.
___
## Fonctionnalités implémentées

* Lancer de rayons avec un modèle de matériau de Blinn-Phong
* Gestion des plans, des sphères et des triangles
* Sauvegarde de l'image de sortie dans un fichier
* Affichage de l'image calculée dans une fenêtre (librairie SFML)
* Chargement d'une scène depuis un fichier
* Gestion de la réflection avec un niveau
* Antialiasing
___
## Particularité d'implémentation

* Nous avons ajouté un coefficient fixe lors du calcul du specular afin de rendre le résultat plus beau
* Plan near : si le plan coupe un objet, on affiche la partie après le plan
* Réflexion : étant donné que la réflexion n'utilise qu'un seul niveau de réursivité, si deux miroirs (coefficient de réflexion à 1) sont faces à faces, la couleur réfléchie sera la couleur ambiente du matériau.
___
## Problèmes courants

* Il arrive que la fenêtre affiche une image noire. L'image est bien générée, seul l'affichage rencontre un problème. Malgré des recherches sur le sujet, nous n'avons trouvé aucune solution.
* Parfois la fenêtre affiche l'image plus sombre qu'elle ne l'est vraiment. L'image est malgré tout générée convenablement.
___
## Utilisation

Le programme peut être utilisé avec ou sans fichier d'entrée. Le fichier d'entrée contient la scène à afficher. Si aucun fichier n'est fourni, une scène par défaut contenant un plan et trois sphères sera utilisée.

___
## Composition du fichier décrivant la scène

Chaque ligne correspond à un composant de la scène. L'ordre de définition des composants n'a pas d'incidence sur la scène, sauf pour les matériaux. Attention ! Les matériaux doivent être définis avant d'être utilisés dans les objets.

* **Position et direction**

   Les trois composantes d'une position ou d'une direction sont séparées par une étoile (*) et sont données dans l'ordre X, Y, Z sous forme d'entiers.

* **Couleur**

   Les trois composantes d'une couleur sont séparées par une étoile (*) et sont données dans l'ordre Rouge, Vert, Bleu sous forme d'entiers.

* **Caméra**

   Si la caméra n'est pas renseignée dans le fichier, une caméra par défaut sera assignée à la scène.
   

   La caméra définie par la ligne suivante :
   ``` c++
   Camera 10*10*0 2 1 100 4 640*480
   ```

   donne une caméra possédant les caractéristiques suivantes (dans l'ordre de déclaration) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Position X** | 10 |
   | **Position Y** | 10 |
   | **Position Z** | 0 |
   | **Distance Focale** | 2 |
   | **Distance Plan Near** | 1 |
   | **Distance Plan Far** | 100 |
   | **Taille Image** | 4 |
   | **Résolution X** | 640 |
   | **Résolution Y** | 480 |


* **Lumière**

   Plusieurs lumières peuvent être définies.

    La lumière définie par la ligne suivante :
   ``` c++
   Light 0*0*-100 255*255*255
   ```

   donne une lumière possédant les caractéristiques suivantes (dans l'ordre d'apparition) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Position X** | 0 |
   | **Position Y** | 0 |
   | **Position Z** | -100 |
   | **Rouge** | 255 |
   | **Vert** | 255 |
   | **Bleu** | 255 |

* **Matériau**

   Chaque matériau doit être défini avant son utilisation dans un objet et est identifié par son nom. Attention, celui-ci doit être différent de ```d```, matériau par défaut.
   Le matériau défini par la ligne suivante :
   ``` c++
   Material red 255*0*0 0.3 0.3 0.3 50 0.5
   ```

   donne un matériau possédant les caractéristiques suivantes (dans l'ordre d'apparition) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Rouge** | 255 |
   | **Vert** | 0 |
   | **Bleu** | 0 |
   | **Diffus** | 0.3 |
   | **Ambient** | 0.3 |
   | **Spéculaire** | 0.3 |
   | **Brillance** | 50 |
   | **Réflexion** | 0.5 |


* **Plan**

   Un plan est défini par une position, une normale et un matériau. Si la lettre ```d``` est utilisée à la place du nom d'un matériau ou si le matériau n'a pas précédemment été défini, le matériau par défaut sera appliqué au plan.

   Le plan défini par la ligne suivante :
   ``` c++
   Plane 0*0*1 0*1*0 red
   ```

   donne un plan possédant les caractéristiques suivantes (dans l'ordre d'apparition) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Position X** | 0 |
   | **Position Y** | 0 |
   | **Position Z** | 1 |
   | **Normale X** | 0 |
   | **Normale Y** | 1 |
   | **Normale Z** | 0 |
   | **Matériau** | red |

* **Sphère**

   Une sphère est définie par la position de son centre, un rayon et un matériau. Si la lettre ```d``` est utilisée à la place du nom d'un matériau ou si le matériau n'a pas précédemment été défini, le matériau par défaut sera appliqué à la sphère.

   La sphère définie par la ligne suivante :
   ``` c++
   Sphere 0*0*1 10 red
   ```

   donne une sphère possédant les caractéristiques suivantes (dans l'ordre d'apparition) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Centre X** | 0 |
   | **Centre Y** | 0 |
   | **Centre Z** | 1 |
   | **Rayon** | 10 |
   | **Matériau** | red |

* **Triangle**

   Un triangle est défini par la position de ses trois sommets et un matériau. Si la lettre ```d``` est utilisée à la place du nom d'un matériau ou si le matériau n'a pas précédemment été défini, le matériau par défaut sera appliqué au triangle.

   Le triangle défini par la ligne suivante :
   ``` c++
   Triangle 0*0*1 0*1*0 0*1*1 red
   ```
   donne un triangle possédant les caractéristiques suivantes (dans l'ordre d'apparition) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Sommet 1 X** | 0 |
   | **Sommet 1 Y** | 0 |
   | **Sommet 1 Z** | 1 |
   | **Sommet 2 X** | 0 |
   | **Sommet 2 Y** | 1 |
   | **Sommet 2 Z** | 0 |
   | **Sommet 3 X** | 0 |
   | **Sommet 3 Y** | 1 |
   | **Sommet 3 Z** | 1 |
   | **Matériau** | red |
