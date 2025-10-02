pragma circom 2.1.6;

include "circomlib/comparators.circom";
include "circomlib/poseidon.circom";

template Colorado(N) {
    signal input width;
    signal input length;
    signal input salt;
    signal input address;
    signal input addressCommitment;
    signal output out;
    signal tmp1;
    signal tmp2;
    
    component hash = Poseidon(2);
    hash.inputs[0] <== address;
    hash.inputs[1] <== salt; 
    addressCommitment === hash.out;
    
    component gtw = GreaterEqThan(N);
    gtw.in[0] <== width;
    gtw.in[1] <== 37;
    
    component gtl = GreaterEqThan(N);
    gtl.in[0] <== length;
    gtl.in[1] <== 102;
    
    component ltw = LessEqThan(N);
    ltw.in[0] <== width;
    ltw.in[1] <== 41;
    
    component ltl = LessEqThan(N);
    ltl.in[0] <== length;
    ltl.in[1] <== 109;
    
    tmp1 <== gtw.out * gtl.out;
    tmp2 <== tmp1 * ltw.out;
    out <== tmp2 * ltl.out;
}

component main {public [addressCommitment]} = Colorado(20);