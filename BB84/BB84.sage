load('../Quantum algs/qubits.sage')

def mz(q,n):
    m = q.measure(n)
    return m

def mx(q,n):
    q.act_qbits(R(-pi/4),[n])
    m = q.measure(n)
    q.act_qbits(R(pi/4),[n])
    return m

N = 100
alice_basis = bin(randint(0,2^N))[2:].zfill(N)
bob_basis = bin(randint(0,2^N))[2:].zfill(N)
alice_measured = []
bob_measured = []
qbits = [bell() for _ in range(N)]

# alice turn
print('Alice measuring')
for i in range(N):
    q = qbits[i]
    m = mz(q,0) if alice_basis[i]=='0' else mx(q,0)
    alice_measured.append(m)
    #print(i,m,str(q))

print('Bob measuring')
for i in range(N):
    q = qbits[i]
    m = mz(q,0) if bob_basis[i]=='0' else mx(q,0)
    bob_measured.append(m)
    #print(i,m,str(q))

print('Key from exchanging measurement states')
for i in range(N):
    if alice_basis[i]==bob_basis[i]:
        print(alice_measured[i],bob_measured[i])
