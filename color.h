#ifndef __COLOR_H
#define __COLOR_H
/**
    This file is part of exactcolors.

    exactcolors is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    exactcolors is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with exactcolors.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "color_defs.h"

typedef struct COLORset {
    int count;
    int age;
    int *members;
    struct COLORset *next;
} COLORset;


typedef struct COLORproblem COLORproblem;

#define COLOR_PRANDMAX 1000000007

typedef struct COLORrandstate {
    int a;
    int b;
    int arr[55];
} COLORrandstate;


void COLORproblem_init(COLORproblem* problem);
void COLORproblem_free(COLORproblem* problem);

/* find a greedy coloring.*/
int COLORgreedy (int ncount, int ecount, int *elist, int *ncolors,
                 COLORset **colorclasses);
/* find a greedy coloring using the DSATUR algorithm.*/
int COLORdsatur(int ncount, int ecount, int *elist, int *ncolors,
                COLORset **colorclasses);

/* transform colorclasses (a covering of the vertices by stable sets)
   into a coloring (a partition of the vertices into stable sets from colorclasses).
*/
int COLORtransform_into_coloring(int ncount, int *ncolors,
                                COLORset **colorclasses);

int COLORtransform_into_maximal (int ncount, int ecount, int *elist, int ncolors,
                                 COLORset *cclasses);

int COLORclique_enum (COLORset** newsets, int *nnewsets, int ncount,
        int ecount, int *elist, int *weights, int cutoff, int *pval);

/**
   Run Ostergards cliquer algorithms to find a stable set of size >= cutoff
   withing timelimit cpu seconds.
   Parameters:

   newsets:  array of found stable sets (usually one)
   nnewsets: # of stable sets in newsets
   ncount:   #vertices
   ecount:   #edges
   elist:    array of edges (array of size 2*edges)),
   weights:  node weights
   cutoff:   the algorithm may stop once a stable set of this weight was found
   pval:     weight of the best found solution

   nrbranches: maximum number of root branches. Ostergard's algorithm
               creates ncount toplevel branches, one for every
               node. This number can be restricted to use the
               algorirthm as a heuristic. This implementation
               will branch with the first min(ncount, nrbranches)
               branches.
*/
int COLORclique_ostergard (COLORset **newsets, int *nnewsets, int ncount,
                           int ecount, int *elist, int *weights, int cutoff, int *pval,
                           int nbranches);

void COLORinit_set (COLORset *s);
void COLORfree_set (COLORset *s);
void COLORfree_sets (COLORset **s,int* nsets);
int  COLORcopy_sets (COLORset **dsts,int* nsets,
                     const COLORset *src_s, int src_nsets);
void COLORunique_sets (COLORset **s,int* nsets);
int  COLORcheck_set(COLORset* set, int ncount, int ecount, const int elist[]);

/** Test whether (set,ncount) defines a feasible coloring for (ncount,elist,ecount).*/
int  COLORcheck_coloring(COLORset* set, int ccount, int ncount, int ecount, const int elist[]);

void COLORutil_sprand (int seed, COLORrandstate *r);
int COLORutil_lprand (COLORrandstate *r);
double COLORutil_zeit (void);
void COLORutil_quicksort (int *len, int n);
void COLORutil_quicksort_reverse (int *len, int n);
void COLORutil_perm_quicksort (int *perm, int *len, int n);

void COLORset_quicksort (COLORset *cclasses, int ccount);

int COLORprogram_header(int ac, char **av);




#endif  /* __COLOR_H */
