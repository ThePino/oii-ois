# Massima N
MAXN = 2000
# Lista dei comandi
cmd = list()
# Vettore delle somme
somma = ["x"] * (MAXN * 4)
# arrays per prefissi
done = [False] * (MAXN * 4)
contTmp = 0
toAdd = list()
dp = dict()
# arrays per maxsubarray
prefisso = ["x"] * (MAXN * 4)
suffisso = ["x"] * (MAXN * 4)
maxsub = ["x"] * (MAXN * 4)

# Funzione ausiliare
def add(result, A, B):
    assert(A != "x" and B != "x")
    ret = result + " = " + A + " + " + B + '\n'
    cmd.append(ret)
    return


def MAX(result, A, B):
    assert (A != "x" and B != "x")
    ret = result + " = " + A + " max " + B + '\n'
    cmd.append(ret)
    return


def newVar():
    global  contTmp
    ret = "tmp[{}]".format(contTmp)
    contTmp = contTmp + 1
    return ret

# Subtask1: Somma totale
def build1(node, s, e, N):
    if s == e:
        somma[node] = "in[{}]".format(s)
    else:
        lc = node * 2 + 1
        rc = node * 2 + 2
        mid = s + (e - s) // 2
        build1(lc, s, mid, N)
        build1(rc, mid + 1, e, N)
        if s == 0 and e == N - 1:
            somma[node] = "out[0]"
        else:
            somma[node] = newVar()
        add(somma[node], somma[lc], somma[rc])


def solveSomme(N, C):
    # azzerrando il vettore delle somme
    global contTmp
    contTmp = 0
    for i in range(0, MAXN * 4):
        somma[i] = 'x'
    print("N " , N)
    # Risolvo
    build1(0, 0, N - 1, N)
    pass

# Subtask2: Somme Prefisse
def build2(node, s, e):
    if s == e:
        somma[node] = "in[{}]".format(s)
    else:
        lc = node * 2 + 1
        rc = node * 2 + 2
        mid = s + (e - s) // 2
        build2(lc, s, mid)
        build2(rc, mid + 1, e)
        if s == 0:
            somma[node] = "out[{}]".format(e)
            done[e] = True
        else:
            somma[node] = newVar()
        add(somma[node], somma[lc], somma[rc])



def query(node, s, e, eq):
    global  toAdd, dp
    if s > eq:
        return
    lc = node * 2 + 1
    rc = node * 2 + 2
    mid = s + (e - s) // 2
    if e <= eq:
        toAdd.append(node)
    else:
        query(lc, s, mid, eq)
        query(rc, mid + 1, e, eq)

# Sfrutto la ripetitivà del calcolo di alcuni nodi per non ricalcolari più e più volte
def getOut(Q, name = None):
    tmp = tuple(Q)
    value = dp.get(tmp)
    if value is not None:
        return value
    if len(Q) == 1:
        if name is not None:
            dp[tmp] = name
            add(dp[tmp], "0", Q[0])
            cmd.append(name + " = 0 + " + Q[0] + '\n')
        else:
            return somma[Q[0]]
    Q.pop()
    if name is None:
        dp[tmp] = newVar()
    else:
        dp[tmp] = name
    add(dp[tmp], somma[tmp[len(tmp) - 1]], getOut(Q, None))
    return dp[tmp]


def solvePrefix(N, C):
    # Azzero
    global toAdd, dp, contTmp
    for i in range(0, MAXN * 4):
        somma[i] = 'x'
    for i in range(0, len(done)):
        done[i] = False
    toAdd = list()
    dp = dict()
    contTmp = 0
    # Eseguo
    # Caso base
    add("out[0]", "0", "in[0]")
    build2(0, 0, N - 1)
    for i in range(1, N):
        if done[i]:
            continue
        query(0, 0, N - 1, i)
        cur = "out[{}]".format(i)
        getOut(toAdd, cur)
        toAdd = list()
    return

# Subtask3: massimo sottoarray
def build3(node, s, e, N):
    global cmd
    if s == e:
        # Essendo una foglia, la soluzione ottima è il dato in se
        somma[node] = "in[{}]".format(s)
        prefisso[node] = "in[{}]".format(s)
        suffisso[node] = "in[{}]".format(s)
        maxsub[node] = "in[{}]".format(s)
    else:
        # Costruisco i figli
        lc = node * 2 + 1
        rc = node * 2 + 2
        mid = s + (e - s) // 2
        build3(lc, s, mid, N)
        build3(rc, mid + 1, e, N)
        # Fondo le soluzioni
        # somma
            # La somma è data dalla somma dei figli
        somma[node] = newVar()
        add(somma[node], somma[lc], somma[rc])
        #######################
        # prefisso
            # Il nuovo prefisso è data dalla somma del nodo sinistro e il massimo del prefisso del nodo destro
        tmpSomma1 = newVar()
        add(tmpSomma1, somma[lc], prefisso[rc])
            # prendo il massimo dal prefisso attuale
        prefisso[node] = newVar()
        MAX(prefisso[node], prefisso[lc], tmpSomma1)
        #######################
        # suffisso
            # il nuovo suffisso è dato dalla somma del nodo destro più il prefisso del nodo sinistro
        tmpSomma2 = newVar()
        add(tmpSomma2, suffisso[lc], somma[rc])
            # prendo il maggiore da quello nuovo e il vecchio suffisso
        suffisso[node] = newVar()
        MAX(suffisso[node], tmpSomma2, suffisso[rc])
        #######################
        # maxsub array
        # il masssimo sotto array è dato dal massimo di 3 fattori: sotto array sinistro, sotto array destro, la fusione del suffisso e prefisso del figlio destro
            # Prendo il massimo dai figli
        tmpMax = newVar()
        MAX(tmpMax, maxsub[lc], maxsub[rc])
            # Sommo il suffisso del figlio sinistro e il prefisso del figlio destro
        tmpSomma3 = newVar()
        add(tmpSomma3, suffisso[lc], prefisso[rc])
          # prendo il massimo dai due massimi e la somma
        maxsub[node] = newVar()
        MAX(maxsub[node], tmpSomma3, tmpMax)
        # Salvo il risultato su out se copro tutto il range
        if s == 0 and e == N - 1:
            MAX("out[0]","0", maxsub[node])


def solveMaxSubArray(N, C):
    # Azzero
    global contTmp
    for i in range(0, MAXN * 4):
        somma[i] = "x"
        prefisso[i] = "x"
        suffisso[i] = "x"
        maxsub[i] = "x"
    contTmp = 0
    # Eseguo
    build3(0, 0, N - 1, N)
    pass


def main():
    for i in range(0, 10):
        cmd.clear()
        FileNameIn = "input_00{}.txt".format(i)
        FileNameOut = "output_00{}.txt".format(i)
        print("Leggo il file", FileNameIn)
        T, N, C = -1, -1, -1
        with open(FileNameIn, "r") as fin:
            T, N, C = map(int, fin.readline().split())
            if T == 1:
                solveSomme(N, C)
            elif T == 2:
                solvePrefix(N, C)
            elif T == 3:
                solveMaxSubArray(N, C)
            else:
                print("There is no choice for ", T)
                assert False
        print("Scrivo il file", FileNameOut)
        with open(FileNameOut, "w") as fout:
            for command in cmd:
                fout.write(command)

if __name__ == "__main__":
    main()
