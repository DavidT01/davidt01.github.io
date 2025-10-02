pragma solidity >=0.8.0;

contract Parrot {
    struct Slot {
        address owner;
        uint mins;
    }

    address public owner;
    bool private free;
    address private parrotOwner;
    uint private rentedUntil;
    uint private pricePerMinute;

    mapping (address => uint) private numRents;
    uint totalReservations = 0;

    uint[] private ratings;
    uint public rating;

    Slot[] private reservations;
    uint private start = 0;

    event parrotRented(address prtOwner);
    event excellentRating(string message);

    modifier Owner() {
        require(msg.sender == owner);
        _;
    }

    constructor() {
        owner = payable(msg.sender);
        free = true;
        parrotOwner = address(0);
        rentedUntil = block.timestamp;
        pricePerMinute = 10000;
    }

    function rentParrot(uint mins) payable public {
        uint price = numRents[msg.sender] > 3 ? (mins * pricePerMinute * 4) / 5 : mins * pricePerMinute;
        require(msg.value == price, "Not enough Ether! You need 10000 Wei for one minute!");

        if(block.timestamp > rentedUntil) {
            free = true;
            parrotOwner = address(0);
        }

        require(free, "Parrot is not free for renting!");

        if(reservations.length > start) {
            Slot memory nextReservation = getNextReservation();
            setNewOwner(nextReservation.owner, block.timestamp + nextReservation.mins * 60);
            (bool success, ) = msg.sender.call{value: msg.value}("");
            require(success, "Refund failed");
        }
        else {
            setNewOwner(msg.sender, block.timestamp + mins * 60);
        }
    }

    function releaseParrot() public {
        require(msg.sender == parrotOwner, "You are not the parrot owner!");
        free = true;
        parrotOwner = address(0);
        rentedUntil = block.timestamp;
        if(reservations.length > start) {
            Slot memory nextReservation = getNextReservation();
            setNewOwner(nextReservation.owner, block.timestamp + nextReservation.mins * 60);
        }
    }

    function withdraw() Owner public {
        uint balance = address(this).balance;
        (bool success, ) = owner.call{value: balance}("");
        require(success, "Failed to withdraw");
    }

    function getNextReservation() private returns(Slot memory) {
        start++;
        return reservations[start - 1];
    }

    function reserveParrot(uint mins) payable public {
        uint price = numRents[msg.sender] > 3 ? (mins * pricePerMinute * 4) / 5 : mins * pricePerMinute;
        require(msg.value == price, "Not enough Ether! You need 10000 Wei for one minute!");
        reservations.push(Slot(msg.sender, mins));
    }

    function setNewOwner(address _address, uint _rentedUntil) private {
        parrotOwner = _address;
        rentedUntil = _rentedUntil;
        free = false;
        numRents[_address]++;
        totalReservations++;
        emit parrotRented(_address);
    }

    function rateParrot(uint _rating) public {
        require(_rating >= 1 && _rating <= 5, "Rating must be between 1 and 5!");
        ratings.push(_rating);
        calcRating();
        if(_rating == 5) {
            emit excellentRating("Parrot was excellent!");
        }
    }

    function calcRating() private {
        rating = 0;
        for(uint i = 0; i < ratings.length; i++) {
            rating += ratings[i];
        }
        rating /= ratings.length;
    }

    function getData() public view returns(uint, uint) {
        return (totalReservations, rating);
    }
}