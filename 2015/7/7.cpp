#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

enum class GateType : int
{
    ASSIGN,
    AND,
    OR,
    LSHIFT,
    RSHIFT,
    NOT,
};

class Gate
{
public:
    Gate(GateType type, const string& result, int id)
    : m_type(type)
    , m_result(result)
    , m_id(id)
    {}

    bool isUnary()
    {
        return m_type == GateType::ASSIGN || m_type == GateType::NOT;
    }

    void setOperand1(const string& regId);
    void setOperand2(const string& regId);
    void setOperand(const string& regId, unsigned short value);
    void setOperand1(unsigned short value);
    void setOperand2(unsigned short value);

    GateType getType()
    {
        return m_type;
    }

private:
    void calculate();

private:
    string m_operand1;
    string m_operand2;
    unsigned short m_operand1Value;
    unsigned short m_operand2Value;
    bool m_op1Set = false;
    bool m_op2Set = false;
    string m_result;
    GateType m_type;
    int m_id;
};

class Memory
{
public:
    bool hasValue(const string& regId) { return m_refRegisters.contains(regId); }
    unsigned short getValue(const string& regId);
    int nextId() { return m_gates.size(); }
    void setValue(const string& regId, unsigned short value);
    void addGate(unique_ptr<Gate>&& spGate) { m_gates.push_back(move(spGate)); }
    void addRegGate(const string& regId, int gateId);

private:
    unordered_map<string, unsigned short> m_refRegisters;
    unordered_map<string, vector<int>> m_registerGates;
    vector<unique_ptr<Gate>> m_gates;
};

Memory g_mem;

void Gate::setOperand1(const string& regId)
{
    if (g_mem.hasValue(regId))
    {
        setOperand1(g_mem.getValue(regId));
        return;
    }

    m_operand1 = regId;
    g_mem.addRegGate(regId, m_id);
}

void Gate::setOperand2(const string& regId)
{
    if (g_mem.hasValue(regId))
    {
        setOperand2(g_mem.getValue(regId));
        return;
    }

    m_operand2 = regId;
    g_mem.addRegGate(regId, m_id);
}

void Gate::setOperand(const string& regId, unsigned short value)
{
    if (m_operand1 == regId)
        setOperand1(value);

    if (m_operand2 == regId)
        setOperand2(value);
}

void Gate::setOperand1(unsigned short value)
{
    if (m_op1Set)
    {
        printf("Double setting op1!\n");
        return;
    }

    m_operand1Value = value;
    m_op1Set = true;
    if (isUnary() || m_op2Set)
        calculate();
}

void Gate::setOperand2(unsigned short value)
{
    if (m_op2Set)
    {
        printf("Double setting op2!\n");
        return;
    }

    if (isUnary())
    {
        printf("Setting op2 for unary operation %d\n", (int)m_type);
        return;
    }

    m_operand2Value = value;
    m_op2Set = true;
    if (m_op1Set)
        calculate();
}

void Gate::calculate()
{
    switch (m_type)
    {
        case GateType::ASSIGN:
            g_mem.setValue(m_result, m_operand1Value);
            break;
        case GateType::AND:
            g_mem.setValue(m_result, m_operand1Value & m_operand2Value);
            break;
        case GateType::OR:
            g_mem.setValue(m_result, m_operand1Value | m_operand2Value);
            break;
        case GateType::LSHIFT:
            g_mem.setValue(m_result, m_operand1Value << m_operand2Value);
            break;
        case GateType::RSHIFT:
            g_mem.setValue(m_result, m_operand1Value >> m_operand2Value);
            break;
        case GateType::NOT:
            g_mem.setValue(m_result, ~m_operand1Value);
            break;
    }
}

unsigned short Memory::getValue(const string& regId)
{
    if (m_refRegisters.contains(regId))
        return m_refRegisters[regId];

    printf("RegId not found: %s\n", regId.c_str());
    return 0;
}

void Memory::setValue(const string& regId, unsigned short value)
{
    if (m_refRegisters.contains(regId))
    {
        printf("Double setting reg %s!\n", regId.c_str());
        return;
    }

    m_refRegisters[regId] = value;
    if (m_registerGates.contains(regId))
    {
        for (int i = 0; i < m_registerGates[regId].size(); i++)
        {
            m_gates[m_registerGates[regId][i]]->setOperand(regId, value);
        }
    }
}

void Memory::addRegGate(const string& regId, int gateId)
{
    if (m_registerGates.contains(regId))
    {
        const vector<int>& gates = m_registerGates[regId];
        if (find(begin(gates), end(gates), gateId) == end(gates))
            m_registerGates[regId].push_back(gateId);
    }
    else
    {
        m_registerGates[regId] = vector<int>();
        m_registerGates[regId].push_back(gateId);
    }
}

void parseInstruction(const string& instruction)
{
    string::size_type pipe = instruction.find("->");
    string result = instruction.substr(pipe + 3);
    string firstHalf = instruction.substr(0, pipe - 1);

    // Look for instruction type
    if (firstHalf.find("AND") != string::npos)
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::AND, result, g_mem.nextId());
        string::size_type andPos = firstHalf.find("AND");
        string operand1 = firstHalf.substr(0, andPos - 1);
        string operand2 = firstHalf.substr(andPos + 4);

        if (isalpha(operand1[0]))
            spGate->setOperand1(operand1);
        else
            spGate->setOperand1(stoi(operand1));

        if (isalpha(operand2[0]))
            spGate->setOperand2(operand2);
        else
            spGate->setOperand2(stoi(operand2));

        g_mem.addGate(move(spGate));
    }
    else if (firstHalf.find("OR") != string::npos)
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::OR, result, g_mem.nextId());
        string::size_type orPos = firstHalf.find("OR");
        string operand1 = firstHalf.substr(0, orPos - 1);
        string operand2 = firstHalf.substr(orPos + 3);

        if (isalpha(operand1[0]))
            spGate->setOperand1(operand1);
        else
            spGate->setOperand1(stoi(operand1));

        if (isalpha(operand2[0]))
            spGate->setOperand2(operand2);
        else
            spGate->setOperand2(stoi(operand2));

        g_mem.addGate(move(spGate));
    }
    else if (firstHalf.find("LSHIFT") != string::npos)
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::LSHIFT, result, g_mem.nextId());
        string::size_type lshiftPos = firstHalf.find("LSHIFT");
        string operand1 = firstHalf.substr(0, lshiftPos - 1);
        string operand2 = firstHalf.substr(lshiftPos + 7);

        if (isalpha(operand1[0]))
            spGate->setOperand1(operand1);
        else
            spGate->setOperand1(stoi(operand1));

        if (isalpha(operand2[0]))
            spGate->setOperand2(operand2);
        else
            spGate->setOperand2(stoi(operand2));

        g_mem.addGate(move(spGate));
    }
    else if (firstHalf.find("RSHIFT") != string::npos)
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::RSHIFT, result, g_mem.nextId());
        string::size_type rshiftPos = firstHalf.find("RSHIFT");
        string operand1 = firstHalf.substr(0, rshiftPos - 1);
        string operand2 = firstHalf.substr(rshiftPos + 7);

        if (isalpha(operand1[0]))
            spGate->setOperand1(operand1);
        else
            spGate->setOperand1(stoi(operand1));

        if (isalpha(operand2[0]))
            spGate->setOperand2(operand2);
        else
            spGate->setOperand2(stoi(operand2));

        g_mem.addGate(move(spGate));
    }
    else if (firstHalf.find("NOT") != string::npos)
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::NOT, result, g_mem.nextId());
        string operand = firstHalf.substr(4);
        if (isalpha(operand[0]))
            spGate->setOperand1(operand);
        else
            spGate->setOperand1(stoi(operand));

        g_mem.addGate(move(spGate));
    }
    else
    {
        unique_ptr<Gate> spGate = make_unique<Gate>(GateType::ASSIGN, result, g_mem.nextId());
        if (isalpha(firstHalf[0]))
            spGate->setOperand1(firstHalf);
        else
            spGate->setOperand1(stoi(firstHalf));

        g_mem.addGate(move(spGate));
    }
}

int main()
{
    for (int i = 0; i < 339; i++)
    {
        string instruction;
        getline(cin, instruction);
        parseInstruction(instruction);
    }

    printf("%d\n", g_mem.getValue("a"));
}