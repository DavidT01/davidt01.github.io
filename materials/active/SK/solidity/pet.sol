pragma solidity >= 0.8.0;

contract PetStore {

    struct Pet {
        uint id;
        string name;
        uint price;
        address owner;
        bool forSale;
    }

    mapping(uint => Pet) public ownedPets;

    uint public petCounter = 0;
    address public owner;

    event PetAdded();
    event PetBought();

    constructor() {
        owner = msg.sender;
    }


    modifier Owner{
        require(msg.sender == owner);
        _;
    }

    function addPet(_name, _price, _owner, _forSale) external Owner {
        
        Pet memory pet = Pet(petCounter, _name, _price, _owner, _forSale);
        ownedPets[petCounter] = pet;
        petCounter++;

        emit PetAdded();
    }

    function buyPet(_id) external payable{
        require(ownedPets[_id].price == msg.value);
        require(ownedPets[_id].forSale == true);

        ownedPets[_id].forSale = false;

        emit PetBought();
    }

    function getPet(blabla) external view returns(Pet){
        return ownedPets[_id];
    }

}