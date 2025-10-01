pragma solidity >=0.8.0;

contract PetStore {

    struct Pet {
        uint id;
        string name;
        uint price;
        address owner;
        bool forSale;
    }
    
    mapping (uint => Pet) pets;

    uint public petNum;
    address payable public storeOwner;

    constructor() {
        storeOwner = payable(msg.sender);
    }

    event PetAdded(uint _id);
    event PetBought(uint _id);

    modifier Owner() {
        require(msg.sender == storeOwner);
        _;
    }

    function addPet(string memory _name, uint _price, address _owner, bool _forSale) Owner public {
        uint id = petNum;
        pets[id] = Pet(id, _name, _price, _owner, _forSale);
        petNum++;
        emit PetAdded(id);
    }

    function buyPet(uint _id) payable public {
        require(msg.value == pets[_id].price, "Not enough Ether to buy this pet!");
        require(_id < petNum, "Invalid pet ID!");
        require(pets[_id].forSale == true, "This pet is not for sale!");
        pets[_id].owner = msg.sender;
        pets[_id].forSale = false;
        
        (bool success, ) = storeOwner.call{value: msg.value}("");
        require(success, "Failed to send Ether");

        emit PetBought(_id);
    }

    function getPet(uint _id) public view returns(Pet memory) {
        require(_id < petNum, "Invalid pet ID!");
        return pets[_id];
    }
}