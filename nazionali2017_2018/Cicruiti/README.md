# Soluzione di circuiti oii 2018

[Circuiti](https://training.olinfo.it/#/task/oii_circuiti/statement) è uno dei 3 problemi proposti alla seleziona nazionale delle oii 2018, ecco una breve commentata soluzione in python. Essendo un task output only, si può utilizzare qualsiasi linguaggio messo a disposizione. Ho scelto il python perché volevo provarlo e aveva delle  funzioni molto carine.

## Subtask1[30]: Somma

Per realizzare il primo subtask basta conoscere l'implementazione più banale del Segment tree. Implementando il Segment Tree bisogna impostare come foglie gli ingressi `in[0],in[1],...,in[N - 1]` mentre come radice l'output `out[0]`. Realizzando delle apposite funzioni per scrivere i registri e le somme,  la vita è molto più comoda.

Calcolo: *`O(N log(N))`*

Circuiti: *`O(N log(N))`*

## Subtask2[30]: Prefissi

Realizzando il semplice Segment Tree e implementando le query banalmente sui Prefissi si ottiene circa metà del punteggio disponibile. Per ottenere il punteggio massimo bisogna notare due cose:

1. Durante la costruzione del range tree si calcolo già determinati prefissi.
2. Se si osservano le somme dei nodi interpellati per realizzare un prefisso, si notano che vengono ripetute più e più volte.

Per la prima  osservazione basta cambiare il nome del registro usato nella costruzione nel registro che si sta calcolando. Per la seconda possiamo optare per una semplice **`dp`** che restituisce le somme già calcolate.

Calcolo: *`O(N log(N))`*

Circuiti: *`O(N log(N))`*

## Subtask3[40]: Massimo sottoarray

Per il terzo subtask basta implementare il classico Segment Tree adattato per risolvere le query di un massimo sotto array. Non bisogna prestare nessuna attenzione al risparmio di memoria o di tempo.

Calcolo: *`O(N log(N))`*

Circuiti: *`O(N log(N))`*
