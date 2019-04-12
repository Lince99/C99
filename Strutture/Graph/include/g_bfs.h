/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef G_BFS_H
#define G_BFS_H

#include <stdio.h>
#include <stdlib.h>
#include "g_struct.h"
#include "common/colors.h"
#include "tree_nary.h"

//TODO implement bfs graph algorithm

/*
 * 0: nodo inziale diventa grigio
 * 1: controlla nodi vicini se sono bianchi
 * 2: passa al primo nodo bianco della lista e aggiungilo alla coda
 * 3: diventa grigio
 * 4: torna al passaggio 1
 * 5: se non ci sono piu' nodi bianchi, quello attuale diventa nero
 * 6: se la coda ha nodi, prendi il primo, e ripeti dal passaggio 0
 * 7: altrimenti passa al prossimo nodo non collegato
 */
/*
 * 1  procedure BFS(G,start_v):
 * 2      let S be a queue
 * 3      S.enqueue(start_v)
 * 4      while S is not empty
 * 5          v = S.dequeue()
 * 6          if v is the goal:
 * 7              return v
 * 8          for all edges from v to w in G.adjacentEdges(v) do
 * 9              if w is not labeled as discovered:
 * 10                 label w as discovered
 * 11                 w.parent = v
 * 12                 Q.enqueue(w)
 */

#endif //G_BFS_H
