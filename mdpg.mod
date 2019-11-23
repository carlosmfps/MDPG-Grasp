#parametros

param num_elements;
param num_groups;
param group_type;
set I := 1..num_elements;
set G := 1..num_groups;

param limite :=
param D:=
#variaveis

var X{i in I, k in G} binary >= 0;
Var Y{i in I, j in I, k in G} binary >=0;

Maximize diver: sum{k in G} sum{i in I} sum{j in I != i} Y[i,j,k]*D[i,j];

#restrições
s.t. only_one_group{i in I}: sum{k in G} X[i,k] = 1;
s.t. min_grupo{k in G}: sum{i in I} X[i,g] >= limite[k,1];
s.t. max_grupo{k in G}: sum{i in I} X[i,g] <= limite[k,2];
s.t. same_group{k in G, i in I, j in I}: X[i,k] + X[j,k] -1 <= Y[i,j,k];
s.t. ind_min_group{j in I,k in G}: sum{i in I} Y[i,j,k] >= (limite[k,1]-1)*X[j,k];
s.t. ind_max_group{j in I,k in G}: sum{i in I} Y[i,j,k] <= (limite[k,2]-1)*X[j,k];
