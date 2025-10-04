pragma solidity >=0.8.0;

contract Auction {

    struct AuctionItem {
        uint id;
        string name;
        uint minBid;
        uint highestBid;
        address highestBidder;
        bool active;
    }

    address payable public owner;
    AuctionItem[] public items;
    uint public itemCount;

    mapping (address => uint) public pendingReturns;

    constructor() {
        owner = payable(msg.sender);
    }

    modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }

    event HighestBidIncreased(uint _id, address _owner, uint _highestBid);

    function addItem(string memory _name, uint _minBid) onlyOwner public {
        items.push(AuctionItem(itemCount, _name, _minBid, 0, address(0), true));
        itemCount++;
    }

    function endAuction(uint _id) onlyOwner public {
        require(_id < itemCount, "Invalid item ID!");
        (bool success, ) = owner.call{value: items[_id].highestBid}("");
        require(success, "Failed to end auction for this item!");
        items[_id].active = false;
    }

    function bid(uint _id) payable public {
        require(_id < itemCount, "Invalid item ID!");
        require(items[_id].active, "This item is not on auction anymore!");
        require(msg.value >= items[_id].minBid && msg.value > items[_id].highestBid, "Not enough Ether for this item!");
        if(items[_id].highestBidder != address(0))
            pendingReturns[items[_id].highestBidder] += items[_id].highestBid;
        items[_id].highestBid = msg.value;
        items[_id].highestBidder = msg.sender;
        emit HighestBidIncreased(_id, msg.sender, msg.value);
    }

    function withdraw() public returns(bool) {
        uint amount = pendingReturns[msg.sender];
        if(amount == 0)
            return false;
        pendingReturns[msg.sender] = 0;
        (bool success, ) = msg.sender.call{value: amount}("");
        if(!success)
            pendingReturns[msg.sender] = amount;
        return success;
    }

}