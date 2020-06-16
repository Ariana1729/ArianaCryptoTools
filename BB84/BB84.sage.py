

# This file was *autogenerated* from the file BB84.sage
from sage.all_cmdline import *   # import sage library

_sage_const_1 = Integer(1); _sage_const_0 = Integer(0); _sage_const_2 = Integer(2); _sage_const_3 = Integer(3); _sage_const_0p0001 = RealNumber('0.0001'); _sage_const_18 = Integer(18); _sage_const_7 = Integer(7); _sage_const_4 = Integer(4)
import re

class qState():
    def __init__(self, n):
        self.n = n  # number of qubits
        self.state = vector(SR,[_sage_const_1 ]+[_sage_const_0 ]*(_sage_const_2 **n-_sage_const_1 ))

    def __repr__(self):
        for i in range(_sage_const_2 **self.n):
            self.state[i] = self.state[i].simplify_trig()
        s = f"Number of qubits: {self.n}\nState: "
        for i in range(_sage_const_2 **self.n):
            if self.state[i] == _sage_const_0 :
                continue
            s += f"({self.state[i]}) |" + bin(i)[_sage_const_2 :].zfill(self.n) + "> + "
        return s[:-_sage_const_3 ]

    def addState(self, state):
        if log(state.degree())/log(_sage_const_2 ) not in ZZ:
            raise ValueError('Vector degree should be a poewr of 2')
        if abs(n(qbit.state.norm())-_sage_const_1 )>_sage_const_0p0001 :
            raise ValueError('Norm is not 1')
        self.n += log(state.degree()) / log(_sage_const_2 )
        self.state = vector(self.state.tensor_product(state))

    def measure(self, n):
        prob0 = _sage_const_0 
        for i in range(_sage_const_2 **self.n):
            if bin(i)[_sage_const_2 :].zfill(self.n)[n] == '0':
                prob0 += self.state[i].norm()
        m = _sage_const_0  if random() < prob0 else _sage_const_1 
        for i in range(_sage_const_2 **self.n):
            if bin(i)[_sage_const_2 :].zfill(self.n)[n] == str(_sage_const_1 -m):
                self.state[i] = _sage_const_0 
        self.state = self.state/self.state.norm()
        return m

    def act_qbits(self, M, N):
        if not _sage_const_2 **len(N) == M.dimensions()[_sage_const_0 ] == M.dimensions()[_sage_const_1 ]:
            raise ValueError("Number of bits acted on must coorespond to size of matrix")
        Mn = Matrix(SR, _sage_const_2 **self.n, _sage_const_2 **self.n)
        for i in range(_sage_const_2 **self.n):
            for j in range(_sage_const_2 **self.n):
                if not all(k in N or bin(i^j)[_sage_const_2 :].zfill(self.n)[k] == '0' for k in range(self.n)):
                    Mn[i, j] = _sage_const_0 
                    continue
                Mn[i, j] = M[int(''.join(bin(i)[_sage_const_2 :].zfill(self.n)[k] for k in N), _sage_const_2 ), int(''.join(bin(j)[_sage_const_2 :].zfill(self.n)[k] for k in N), _sage_const_2 )]
        self.state *= Mn

def parse(s): # UNSAFE, HAS AN EVAL SOMEWHERE
    nq,s = s.split('\n')
    nq = int(nq[_sage_const_18 :])
    s = s[_sage_const_7 :]
    qbit = qState(nq)
    qbit.state[_sage_const_0 ]=_sage_const_0 
    sqrtre = re.compile(r'sqrt\(\d+\)')
    while s!='':
        t = s.index('>')+_sage_const_1 
        ps = s[:t]
        s = s[t:]
        pq = ps[-nq-_sage_const_1 :-_sage_const_1 ]
        pv = ps[:-nq-_sage_const_2 ]#sqrtre.sub(lambda x:x.group(0)[4:]+'^(1/2)',ps[:-n-2])
        qbit.state[int(pq,_sage_const_2 )]=sage_eval(pv) # UNSAFE
    if abs(n(qbit.state.norm())-_sage_const_1 )>_sage_const_0p0001 :
        raise ValueError('Norm is not 1')
    return qbit

def cGate(M):
    cM = Matrix(SR, _sage_const_4 , _sage_const_4 )
    cM[_sage_const_0 , _sage_const_0 ] = cM[_sage_const_1 , _sage_const_1 ] = _sage_const_1 
    cM[_sage_const_2 , _sage_const_2 ] = M[_sage_const_0 , _sage_const_0 ]
    cM[_sage_const_2 , _sage_const_3 ] = M[_sage_const_0 , _sage_const_1 ]
    cM[_sage_const_3 , _sage_const_2 ] = M[_sage_const_1 , _sage_const_0 ]
    cM[_sage_const_3 , _sage_const_3 ] = M[_sage_const_1 , _sage_const_1 ]
    return cM

def R(th):
    return Matrix(_sage_const_2 , _sage_const_2 , [cos(th),sin(th),-sin(th),cos(th)])

def pR(th):
    return Matrix(_sage_const_2 , _sage_const_2 , [_sage_const_1 ,_sage_const_0 ,_sage_const_0 ,e**(I*th)])

def H():
    return _sage_const_1 /sqrt(_sage_const_2 )*Matrix(_sage_const_2 , _sage_const_2 , [_sage_const_1 ,_sage_const_1 ,_sage_const_1 ,-_sage_const_1 ])

def X():
    return Matrix(_sage_const_2 , _sage_const_2 , [_sage_const_0 ,_sage_const_1 ,_sage_const_1 ,_sage_const_0 ])

def Y():
    return Matrix(_sage_const_2 , _sage_const_2 , [_sage_const_0 ,-I,I,_sage_const_0 ])

def Z():
    return Matrix(_sage_const_2 , _sage_const_2 , [_sage_const_1 ,_sage_const_0 ,_sage_const_0 ,-_sage_const_1 ])

qbit=qState(_sage_const_4 )
qbit.act_qbits(cGate(pR(_sage_const_2 )), [_sage_const_0 ,_sage_const_1 ])
qbit.act_qbits(cGate(Z()), [_sage_const_1 ,_sage_const_2 ])
qbit.act_qbits(cGate(Y()), [_sage_const_2 ,_sage_const_3 ])
qbit.act_qbits(X(), [_sage_const_0 ])
qbit.act_qbits(pR(_sage_const_1 ), [_sage_const_1 ])
qbit.act_qbits(H(), [_sage_const_2 ])
qbit.act_qbits(R(-_sage_const_1 ), [_sage_const_3 ])
print(qbit)
print(parse(str(qbit)))

