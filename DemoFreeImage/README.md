Un fichier peut être utilisé pour décrire la scène désirée. Si aucun fichier n'est fourni au lancement du programme, une scène par défaut est utilisée.

Composition du fichier :


Chaque ligne correspond à un composant de la scène. L'ordre de définition des composants n'a pas d'incidence sur la scène, sauf pour les matériaux. Attention ! Les matériaux doivent être définis avant d'être utilisés dans les objets.

* Position et direction

   Les trois composantes d'une position ou d'une direction sont séparées par une étoile (*) et sont données dans l'ordre X, Y, Z sous forme d'entiers.

* Couleur

   Les trois composantes d'une couleur sont séparées par une étoile (*) et sont données dans l'ordre Rouge, Vert, Bleu sous forme d'entiers.

* Caméra

   Si la caméra n'est pas renseignée dans le fichier, une caméra par défaut sera assignée à la scène.
   

   La caméra définie par la ligne suivante :
   ``` c++
   Camera 10*10*0 0*0*1 2 1 100 4 640*480
   ```

   donne une caméra possédant les caractéristiques suivantes (dans l'ordre de déclaration) :
   
  |Caractéristique|Valeur|   
   | :---: | :---: |
   | **Position X** | 10 |
   | **Position Y** | 10 |
   | **Position Z** | 0 |
   | **Direction X** | 0 |
   | **Direction Y** | 0 |
   | **Direction Z** | 1 |
   | **Distance Focale** | 2 |
   | **Distance Plan Near** | 1 |
   | **Distance Plan Far** | 100 |
   | **Taille Image** | 4 |
   | **Résolution X** | 640 |
   | **Résolution Y** | 480 |


* Lumière

   Si aucune lumière n'est renseignée dans le fichier, une lumière par défaut sera assignée à la scène. Plusieurs lumières peuvent être définies.

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

* Matériau

   Chaque matériau doit être défini avant son utilisation dans un objet et est identifié par son nom. Attention, celui-ci doit être différent de ```d```.
   Le matériau défini par la ligne suivante :
   ``` c++
   Material red 255*0*0 0.3 0.3 0.3 50
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


* Plan

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

* Sphère

   Une sphère est définir par la position de son centre, un rayon et un matériau. Si la lettre ```d``` est utilisée à la place du nom d'un matériau ou si le matériau n'a pas précédemment été défini, le matériau par défaut sera appliqué à la sphère.

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



* Objets par défaut 