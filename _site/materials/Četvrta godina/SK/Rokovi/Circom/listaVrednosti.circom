pragma circom 2.1.6;

include "circomlib/poseidon.circom";
include "circomlib/comparators.circom";

template Lista(N) {
    signal input sifra;
    signal input lista[N];
    signal output izlaz;
    
    component hash = Poseidon(1);
    hash.inputs[0] <== sifra;
    
    component jednaki[N];
    
    var tmp = 0;
    
    for(var i = 0; i < N; i++) {
        jednaki[i] = IsEqual();
        jednaki[i].in[0] <== lista[i];
        jednaki[i].in[1] <== hash.out;
        tmp += jednaki[i].out;
    }
        
    izlaz <== tmp;
}
        
component main {public [lista]} = Lista(10);