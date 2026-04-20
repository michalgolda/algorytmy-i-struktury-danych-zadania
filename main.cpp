#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct President;
struct ListNode;

std::string* split(std::string s, std::string delimiter);
void insertData(ListNode*& rootListNode, President* p);
void parseData(ListNode*& rootListNode, char* filePath);
void printData(ListNode* rootListNode);


int main(int argc, char* argv[]) {

    if (argc > 2 || argc == 1)
    {
        std::cout << "Correct usage: main <data-file-path>" << std::endl;
        exit(0);
    }

    char* filePath = argv[1];

    ListNode* rootListNode = nullptr;
    parseData(rootListNode, filePath);
    printData(rootListNode);

    delete rootListNode;

    return 0;
}

struct President
{
    std::string firstName;
    std::string lastName;
    int startYear;
    int endYear;
    std::string politicalParty;

    friend std::ostream& operator<<(std::ostream& s, const President& p)
    {
        s << "President(firstName=" << p.firstName << ", lastName=" << p.lastName << ", startYear=" << p.startYear << ", endYear=" << p.endYear << ", " << "politicalParty=" << p.politicalParty << ")";
        return s;
    }
};

struct ListNode
{
    President* p = nullptr;
    ListNode* next = nullptr;
};

std::string* split(std::string s, std::string delimiter)
{

    int pos_start = 0;
    int pos_end;
    int delim_len = delimiter.length();

    std::string token;
    static std::string buffer[10];

    int idx = 0;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {

        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;

        buffer[idx] = token;
        idx++;
    }

    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    buffer[idx] = token;

    return buffer;
}

void insertData(ListNode*& rootListNode, President* p)
{
    // ListNode newListNode = new ListNode{p, nullptr}; - The code below is same, but this approach uses aggregate initialization
    ListNode* newListNode = new ListNode;
    newListNode->p = p;
    newListNode->next = nullptr;

    if (rootListNode == nullptr)
    {
        rootListNode = newListNode;
        return;
    }

    ListNode *currNode = rootListNode;
    while (currNode->next != nullptr)
    {
        currNode = currNode->next;
    }

    currNode->next = newListNode;
}

void parseData(ListNode*& rootListNode, char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Something went wrong during data file opening." << std::endl;
        exit(0);
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        int startYear, endYear;

        std::string firstName, lastName, period, politicalParty;
        ss >> firstName >> lastName >> period >> politicalParty;

        std::string* splittedPeriod = split(period, "-");
        startYear = std::atoi(splittedPeriod[0].c_str());
        endYear  = std::atoi(splittedPeriod[1].c_str());

        President* p = new President{firstName, lastName, startYear, endYear, politicalParty};

        insertData(rootListNode, p);
    }
}

void printData(ListNode* rootListNode)
{
    ListNode* currNode = rootListNode;
    while (currNode->next != nullptr)
    {
        std::cout << *currNode->p << std::endl;
        currNode = currNode->next;
    }

    std::cout << *currNode->p << std::endl;
}
