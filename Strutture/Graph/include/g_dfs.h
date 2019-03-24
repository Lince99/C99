/*
 * Copyright 2019 Lince99
 * for the license refer to the prject's license
 */

#ifndef G_DFS_H
#define G_DFS_H

#include <stdio.h>
#include <stdlib.h>
#include "g_struct.h"
#include "common/colors.h"
#include "tree_nary.h"

//TODO implement dfs graph algorithm

/*
 * 0: nodo inziale diventa grigio e aggiungilo alla coda
 * 1: controlla se ci sono nodi bianchi vicino
 * 2: se ci sono prendi il primo e ripeti dal passo 0
 * 3: altrimenti il nodo corrente diventa nero e estrai dalla coda, ripeti da 0
 */
/*
 * 1  procedure DFS(G,v):
 * 2      label v as discovered
 * 3      for all edges from v to w in G.adjacentEdges(v) do
 * 4          if vertex w is not labeled as discovered then
 * 5              recursively call DFS(G,w)
 */
/*
 * 1  procedure DFS-iterative(G,v):
 * 2      let S be a stack
 * 3      S.push(v)
 * 4      while S is not empty
 * 5          v = S.pop()
 * 6          if v is not labeled as discovered:
 * 7              label v as discovered
 * 8              for all edges from v to w in G.adjacentEdges(v) do
 * 9                  S.push(w)
 */

#endif //G_DFS_H
