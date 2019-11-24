#parametros

param num_elementos;
param num_grupos;
set V := 1..num_elementos;
set G := 1..num_grupos;
param limite_inf {k in G};
param limite_sup {k in G};
param D {i in V, j in V};

#variaveis
var X {i in V, k in G} binary;
var Y {i in V, j in V, g in G} binary;

#função objetivo
maximize diversidade: sum {g in G, i in V, j in V:j != i} D[i,j] * Y[i,j,g];

#restrições
s.t. only_one_group{i in V}: sum{k in G} X[i,k] = 1;
s.t. min_grupo{k in G}: sum{i in V} X[i,k] >= limite_inf[k];
s.t. max_grupo{k in G}: sum{i in V} X[i,k] <= limite_sup[k];
s.t. same_group{k in G, i in V, j in V: j!=i}: X[i,k] + X[j,k] -1 <= Y[i,j,k];
s.t. ind_min_group{j in V,k in G}: sum{i in V: i != j} Y[i,j,k] >= (limite_inf[k]-1)*X[j,k];
s.t. ind_max_group{j in V,k in G}: sum{i in V: i != j} Y[i,j,k] <= (limite_sup[k]-1)*X[j,k];
s.t. equivalencias {k in G, i in V, j in V: i != j}: Y[i,j,k] == Y[j,i,k];


end;

