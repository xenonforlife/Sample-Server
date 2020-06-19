#pragma once
#include "../TypeDefiniton.hpp"
#include "Constants.hpp"
#include "ProductionProgram.hpp"

namespace machineTool
{

struct ProductionActiveProgram_t : public ProductionProgram_t
{
  BindableMemberValue<std::string> JobIdentifier;
  BindableMemberValue<UA_NodeId> JobNodeId;
};

} // namespace machineTool

REFL_TYPE(machineTool::ProductionActiveProgram_t,
          Bases<machineTool::ProductionProgram_t>(),
          open62541Cpp::attribute::UaObjectType{
              .NodeId = open62541Cpp::constexp::NodeId(constants::NsMachineToolUri, UA_MACHINETOOLID_PRODUCTIONACTIVEPROGRAMTYPE)})
//REFL_FIELD(State) // Override mandatory ///\todo requires fix in nodeset, i=5030 needs to be ProductionActiveProgramType not ProductionProgramType
REFL_FIELD(JobIdentifier, open62541Cpp::attribute::PlaceholderOptional())
REFL_FIELD(JobNodeId, open62541Cpp::attribute::PlaceholderOptional())
REFL_END