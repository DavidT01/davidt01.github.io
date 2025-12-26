pragma circom 2.1.6;

include "circomlib/poseidon.circom";
include "circomlib/comparators.circom";

template PogodiBroj() {
    signal input pokusaj;
    signal input resenje; 
    signal input resenjeCommitment;
    signal input salt;
    signal output odgovor;
    
    component hash = Poseidon(2);
    hash.inputs[0] <== resenje;
    hash.inputs[1] <== salt;
    resenjeCommitment === hash.out;
    
    component jednaki = IsEqual();
    jednaki.in[0] <== pokusaj;
    jednaki.in[1] <== resenje;
    odgovor <== jednaki.out;
}

component main {public [pokusaj, resenjeCommitment]} = PogodiBroj();