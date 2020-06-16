import re

class qState():
    def __init__(self, n):
        self.n = n  # number of qubits
        self.state = vector(SR,[1]+[0]*(2^n-1))

    def __repr__(self):
        for i in range(2^self.n):
            self.state[i] = self.state[i].simplify_trig()
        s = f"Number of qubits: {self.n}\nState: "
        for i in range(2^self.n):
            if self.state[i] == 0:
                continue
            s += f"({self.state[i]}) |" + bin(i)[2:].zfill(self.n) + "> + "
        return s[:-3]

    def addState(self, state):
        if log(state.degree())/log(2) not in ZZ:
            raise ValueError('Vector degree should be a poewr of 2')
        if abs(n(qbit.state.norm())-1)>0.0001:
            raise ValueError('Norm is not 1')
        self.n += log(state.degree()) / log(2)
        self.state = vector(self.state.tensor_product(state))

    def measure(self, n):
        prob0 = 0
        for i in range(2^self.n):
            if bin(i)[2:].zfill(self.n)[n] == '0':
                prob0 += self.state[i].norm()
        m = 0 if random() < prob0 else 1
        for i in range(2^self.n):
            if bin(i)[2:].zfill(self.n)[n] == str(1-m):
                self.state[i] = 0
        self.state = self.state/self.state.norm()
        return m

    def act_qbits(self, M, N):
        if not 2^len(N) == M.dimensions()[0] == M.dimensions()[1]:
            raise ValueError("Number of bits acted on must coorespond to size of matrix")
        Mn = Matrix(SR, 2^self.n, 2^self.n)
        for i in range(2^self.n):
            for j in range(2^self.n):
                if not all(k in N or bin(i^^j)[2:].zfill(self.n)[k] == '0' for k in range(self.n)):
                    Mn[i, j] = 0
                    continue
                Mn[i, j] = M[int(''.join(bin(i)[2:].zfill(self.n)[k] for k in N), 2), int(''.join(bin(j)[2:].zfill(self.n)[k] for k in N), 2)]
        self.state *= Mn

def parse(s):
    nq,s = s.split('\n')
    nq = int(nq[18:])
    s = s[7:]
    qbit = qState(nq)
    qbit.state[0]=0
    sqrtre = re.compile(r'sqrt\(\d+\)')
    while s!='':
        t = s.index('>')+1
        ps = s[:t]
        s = s[t:]
        qbit.state[int(ps[-nq-1:-1],2)]=SR(ps[:-nq-2])
    if abs(n(qbit.state.norm())-1)>0.0001:
        raise ValueError('Norm is not 1')
    return qbit

def cGate(M):
    cM = Matrix(SR, 4, 4)
    cM[0, 0] = cM[1, 1] = 1
    cM[2, 2] = M[0, 0]
    cM[2, 3] = M[0, 1]
    cM[3, 2] = M[1, 0]
    cM[3, 3] = M[1, 1]
    return cM

def R(th):
    return Matrix(2, 2, [cos(th),sin(th),-sin(th),cos(th)])

def pR(th):
    return Matrix(2, 2, [1,0,0,e^(I*th)])

def H():
    return 1/sqrt(2)*Matrix(2, 2, [1,1,1,-1])

def X():
    return Matrix(2, 2, [0,1,1,0])

def Y():
    return Matrix(2, 2, [0,-I,I,0])

def Z():
    return Matrix(2, 2, [1,0,0,-1])

qbit=qState(4)
qbit.act_qbits(cGate(pR(2)), [0,1])
qbit.act_qbits(cGate(Z()), [1,2])
qbit.act_qbits(cGate(Y()), [2,3])
qbit.act_qbits(X(), [0])
qbit.act_qbits(pR(1), [1])
qbit.act_qbits(H(), [2])
qbit.act_qbits(R(-1), [3])
print(qbit)
print(parse(str(qbit)))
print(qbit.measure(0))
print(qbit)
print(qbit.measure(1))
print(qbit)
print(qbit.measure(2))
print(qbit)
print(qbit.measure(3))
print(qbit)

