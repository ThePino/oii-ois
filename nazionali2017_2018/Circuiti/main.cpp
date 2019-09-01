#include <bits/stdc++.h>

using namespace std;

// Ausilio Globale
const int MAXN = 1e4;
int numero_componente = 0;


string newVar(){
	string ret = "tmp[" + to_string(numero_componente) + "]";
	numero_componente++;
	return ret;
}

void ADD(string A, string B, string C){
	assert(A != "x" && B != "x" && C != "x");
	string ret = A + " = " + B + " + " + C + '\n';
	cout << ret;
}

void MAX(string A, string B, string C){
	assert(A != "x" && B != "x" && C != "x");
	string ret = A + " = " + B + " max " + C + '\n';
	cout << ret;
}

// Somma 
// Segment tree per le somme
string segmentSomma[MAXN];

void buildSomma(int node, int s, int e, int N){
	if(s == e){
		segmentSomma[node] = "in[" + to_string(s) + "]";
	}else{
		int lc = node * 2 + 1;
		int rc = node * 2 + 2;
		int mid = s + (e - s) / 2;
		// calcolo prima i figli
		buildSomma(lc, s, mid, N);
		buildSomma(rc, mid + 1, e, N);
		// calcolo il nodo attuale
		// utilizzo direttamente il registro se copro tutto il range
		if(s == 0 && e == N - 1){
			segmentSomma[node] = "out[0]";
		}else{
			segmentSomma[node] = newVar();
		}
		ADD(segmentSomma[node], segmentSomma[lc], segmentSomma[rc]);
	}
}

void somma(int N, int C){
	// inizializzazione
	numero_componente = 0;
	for(string &i : segmentSomma){
		i = "x";
	}
	// eseguo 
	buildSomma(0, 0, N - 1, N);
	return;
}

// Prefissi 
// prefissi già calcolati
bool done[MAXN];
// somme già calcolate
map <vector <int>, string> memo;
// nodi da sommare
vector <int> toAdd;

void buildPrefissi(int node, int s, int e){
	if(s == e){
		segmentSomma[node] = "in[" + to_string(s) + "]";
	}else{
		int lc = node * 2 + 1;
		int rc = node * 2 + 2;
		int mid = s + (e - s) / 2;
		// calcolo prima i figli
		buildPrefissi(lc, s, mid);
		buildPrefissi(rc, mid + 1, e);
		// calcolo il nodo attuale
		// utilizzo direttamente il registro se copro tutto il range
		if(s == 0){
			segmentSomma[node] = "out[" + to_string(e) + "]";
			done[e] = true;
		}else{
			segmentSomma[node] = newVar();
		}
		ADD(segmentSomma[node], segmentSomma[lc], segmentSomma[rc]);
	}
}

// ricavo i nodi da sommare per ottenere il range
void query(int node, int s, int e, int index){
	if(s > index)return;
	if(e <= index){
		toAdd.push_back(node);
	}else{
		int lc = node * 2 + 1;
		int rc = node * 2 + 2;
		int mid = s + (e - s) / 2;
		query(lc, s, mid, index);
		query(rc, mid + 1, e, index);
	}
}

string dp(vector <int> add, string name = ""){
	vector <int> state = add;
	// ho già calcolato questo stato 
	if(memo.find(state) != memo.end())return memo[state];
	// ho solo un elemento
	if(add.size() == 1){
		// se ho un nome allora unisco l'unico nodo
		if(name != ""){
			memo[state] = name;
			ADD(memo[state], name, "0");
			return memo[state];
		}else{
			// altrimenti lo passo alla prossima query
			return segmentSomma[state[0]];
		}
	}
	add.pop_back();
	// se ho il nome lo uso
	if(name != ""){
		memo[state] = name;
	}else{
		memo[state] = newVar();
	}
	ADD(memo[state], segmentSomma[state.back()], dp(add, ""));
	return memo[state];
}

void prefissi(int N, int C){
	// inizializzazione
	numero_componente = 0;
	for(string &i : segmentSomma){
		i = "x";
	}
	for(bool &i : done){
		i = false;
	}
	memo.clear();
	// eseguo
	// caso base
	ADD("out[0]", "0", "in[0]");
	buildPrefissi(0, 0, N - 1);
	for(int i = 1; i < N; i++){
		// ho calcolato precedentemente il prefisso che finisce in i
		if(done[i])continue;
		// ottengo i nodi da sommare
		query(0, 0, N - 1, i);
		// prendo il registro di out
		string cur = "out[" + to_string(i) + "]";
		// sommo 
		dp(toAdd,cur);
		// pulisco la lista
		toAdd.clear();
	}
	return;
}

// Massimo sotto array
string prefisso[MAXN], suffisso[MAXN], subarr[MAXN];

void buildMax_sottoarray(int node, int s, int e){
	if(s == e){
		string cur = "in[" + to_string(s) + "]";
		segmentSomma[node] = cur;
		prefisso[node] = cur;
		suffisso[node] = cur;
		subarr[node] = cur;
	}else{
		int lc = node * 2 + 1;
		int rc = node * 2 + 2;
		int mid = s + (e - s) / 2;
		buildMax_sottoarray(lc, s, mid);
		buildMax_sottoarray(rc, mid + 1, e);
		// calcolo la somma
		segmentSomma[node] = newVar();
		ADD(segmentSomma[node], segmentSomma[lc], segmentSomma[rc]);
		// il nuovo prefisso è dato dal max {
		// prefisso vecchio,
		// somma nodo sinistro + prefisso nodo destro
		// }
		string tmpSomma = newVar();
		ADD(tmpSomma, segmentSomma[lc], prefisso[rc]);
		prefisso[node] = newVar();
		MAX(prefisso[node], prefisso[lc], tmpSomma);
		// il nuovo suffisso è dato dal max {
		// suffisso vecchio,
		// somma nodo destro + suffisso nodo sinistro
		// }
		tmpSomma = newVar();
		ADD(tmpSomma, segmentSomma[rc], suffisso[lc]);
		suffisso[node] = newVar();
		MAX(suffisso[node], suffisso[rc], tmpSomma);
		// il massimo sotto array è dato{
		// sotto array massimo sinistro
		// sotto array massimo destro
		// somma del suffisso sinistro e destro
		// }
		tmpSomma = newVar();
		ADD(tmpSomma, suffisso[lc], prefisso[rc]);
		string tmpMax = newVar();
		MAX(tmpMax, subarr[lc], subarr[rc]);
		subarr[node] = newVar();
		MAX(subarr[node], tmpSomma, tmpMax);
	}
}

void massimo_sottoarray(int N, int C){
	// inizializzazione 
	numero_componente = 0;
	for(string &i : segmentSomma){
		i = "x";
	}
	// eseguo
	buildMax_sottoarray(0, 0, N - 1);
	// il massimo tra quello ottenuto e 0
	MAX("out[0]", "0", subarr[0]);
	return;
}

int main(){
	for(int i = 0; i < 10; i++){
		string File_in = "input_00" + to_string(i) + ".txt";
		string File_out = "output_00" + to_string(i) + ".txt";
		FILE *fr = freopen(File_in.c_str(), "r", stdin);
		FILE *fw = freopen(File_out.c_str(), "w", stdout);
		// mi assicuro che si aprono i file 
		assert(fr != NULL);
		assert(fw != NULL);
		// leggo 
		int T, N, C;
		cin >> T >> N >> C;
		switch(T){
			case 1: somma(N,C);break;
			case 2: prefissi(N,C);break;
			case 3: massimo_sottoarray(N,C);break;
			default: cout << "Nessuna scelta \n"; assert(false);break;
		}
		// chiudo i file
		fclose(fr);
		fclose(fw);
	}
	return 0;
}