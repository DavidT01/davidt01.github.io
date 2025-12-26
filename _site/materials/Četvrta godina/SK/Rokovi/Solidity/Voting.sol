pragma solidity >=0.8.0;

contract Voting {

    struct Candidate {
        address adr;
        string name;
        uint votes;
    }

    struct Voter {
        bool registered;
        bool voted;
    }

    address public admin;
    bool public voteInProgress;

    Candidate[] public candidates;

    mapping (address => Voter) public voters;
    uint public numVoted = 0;

    modifier onlyAdmin() {
        require(msg.sender == admin, "You are not the administrator!");
        _;
    }

    modifier onlyVoter() {
        require(voters[msg.sender].registered, "You are not registered to vote!");
        require(!voters[msg.sender].voted, "You can't vote twice!");
        _;
    }

    event CandidateAdded(address adr);
    event VoterRegistered(address adr);

    constructor() {
        admin = msg.sender;
        voteInProgress = false;
    }

    function addCandidate(address _adr, string memory _name) payable public onlyAdmin {
        require(msg.value == 0.01 * 10**18, "You need 0.01 Ether to add a candidate!");
        candidates.push(Candidate(_adr, _name, 0));
        emit CandidateAdded(_adr);
    }

    function registerVoter(address _adr) payable public onlyAdmin {
        require(msg.value == 0.005 * 10**18, "You need 0.005 Ether to add a voter!");
        require(!voters[_adr].registered, "This voter is already registered!");
        voters[_adr] = Voter(true, false);
        emit VoterRegistered(_adr);
    }

    function vote(uint _id) public onlyVoter {
        require(_id < candidates.length, "Invalid candidate ID!");
        require(voteInProgress, "Vote has ended!");
        candidates[_id].votes++;
        numVoted++;
        voters[msg.sender].voted = true;
    }

    function countVotes() public view onlyAdmin returns(string memory) {
        uint highestVotes = 0;
        string memory name;
        for(uint i = 0; i < candidates.length; i++)
            if(candidates[i].votes > highestVotes) {
                name = candidates[i].name;
                highestVotes = candidates[i].votes;
            }
        require(highestVotes > 0, "No candidate has at least 1 vote!");
        return name;
    }

    function distributeFunds() public onlyAdmin {
        require(!voteInProgress, "Vote is still in progress!");
        require(numVoted > 0, "No votes have been cast!");
        uint funds = address(this).balance;
        for(uint i = 0; i < candidates.length; i++) {
            (bool success, ) = candidates[i].adr.call{value: funds * (candidates[i].votes / numVoted)}("");
            require(success, "Failed to transfer funds!");
        }
    }

    function startVote() public onlyAdmin {
        voteInProgress = true;
    }

    function endVote() public onlyAdmin {
        voteInProgress = false;
    }

}