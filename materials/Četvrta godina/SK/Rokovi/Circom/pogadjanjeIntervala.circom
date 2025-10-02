pragma circom 2.1.6;

include "circomlib/comparators.circom";
include "circomlib/poseidon.circom";

template Igra(N) {
    signal input broj;
    signal input salt;
    signal input brojKomit;
    signal input a;
    signal input b;
    signal output izlaz;

    component hash = Poseidon(2);
    hash.inputs[0] <== broj;
    hash.inputs[1] <== salt;
    brojKomit === hash.out;

    component gt = GreaterEqThan(N);
    gt.in[0] <== broj;
    gt.in[1] <== a;

    component lt = LessEqThan(N);
    lt.in[0] <== broj;
    lt.in[1] <== b;

    izlaz <== lt.out * gt.out;
}

component main {public [brojKomit]} = Igra(20);