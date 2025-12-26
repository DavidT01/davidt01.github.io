pragma circom 2.1.6;

include "circomlib/poseidon.circom";
include "circomlib/comparators.circom";

template PogodiHes() {
    signal input pokusaj;
    signal input hes;
    signal output izlaz;
    
    component hash = Poseidon(1);
    hash.inputs[0] <== pokusaj;
    
    component jednaki = IsEqual();
    jednaki.in[0] <== hes;
    jednaki.in[1] <== hash.out;
    izlaz <== jednaki.out;
}

component main {public [hes]} = PogodiHes();