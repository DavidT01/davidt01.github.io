pragma circom 2.1.6;

include "circomlib/poseidon.circom";
include "circomlib/bitify.circom";
include "circomlib/comparators.circom";

template PogodiParnost(N) {
    assert(N <= 252);
    signal input broj;
    signal input parnost;
    signal input brojKomit;
    signal input salt;
    signal output izlaz;

    component hash = Poseidon(2);
    hash.inputs[0] <== broj;
    hash.inputs[1] <== salt;
    brojKomit === hash.out;

    component n2b = Num2Bits(N);
    n2b.in <== broj;

    component jednaki = IsEqual();
    jednaki.in[0] <== parnost;
    jednaki.in[1] <== n2b.out[0];
    izlaz <== jednaki.out;
}

component main {public [parnost, brojKomit]} = PogodiParnost(20);