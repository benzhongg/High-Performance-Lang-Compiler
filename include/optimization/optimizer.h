#pragma once
#include "instruction_generator.h"
#include "control_flow_graph.h"

//extendable to multiple intermediate instruction sets
class OptimizerBase
{

public:
    OptimizerBase() = default;
    virtual InstructionVector optimize(InstructionVector targetInstructionVector) = 0;

};

class OptimizerO1 : public OptimizerBase
{
private:
    ControlFlowGraphBase* m_controlFlowGraph { nullptr };
    ControlFlowGraphBase* m_buildCFG(InstructionVector targetInstructionVector);
    InstructionVector m_deconstructCFG(ControlFlowGraphBase* targetControlFlowGraph);

protected:
    bool deadCodeElimination        (ControlFlowGraphBase* targetCFG);
    bool constantFolding            (ControlFlowGraphBase* targetCFG);
    bool constantAndCopyPropogation (ControlFlowGraphBase* targetCFG);

public:
    InstructionVector optimize(InstructionVector targetInstructionVector) override;
};



