#pragma once

#include "StateMachine.hpp"
#include "../TypeDefinition/ns0/FiniteStateMachine.hpp"
#include <type_traits>
#include <algorithm>

namespace UmatiServerLib
{
  /**
   * @brief Enable helper functions for an instance of a state machine
   * 
   * Using the SetState-Method will set all associated valriables
   * 
   * @tparam STATEMACHINE_T 
   */
  template <typename STATEMACHINE_T>
  class StateMachineInstance : public StateMachine
  {
  public:
    StateMachineInstance(STATEMACHINE_T &stateMachineInstance, UA_Server *pServer)
        : m_stateMachineInstance(stateMachineInstance),
          StateMachine(refl::descriptor::get_attribute<UmatiServerLib::attribute::UaObjectType>(refl::reflect<STATEMACHINE_T>()).NodeId.UANodeId(pServer), pServer)
    {
      static_assert(std::is_base_of<ns0::FiniteStateMachine_t, STATEMACHINE_T>::value, "STATEMACHINE_T must inherit from ns0::FiniteStateMachine_t");
    }

    /**
     * @brief Set the State by it's id
     * 
     * @param id Id of the state
     */
    void SetState(std::uint32_t id)
    {
      auto it = std::find_if(m_states.begin(), m_states.end(), [&id](const State_t &x) { return x.Number == id; });
      if (it == m_states.end())
      {
        throw std::runtime_error("State not found.");
      }
      SetState(*it);
    }

  protected:
    void SetState(const State_t &state)
    {
      m_stateMachineInstance.CurrentState->Value = state.DispName;
      m_stateMachineInstance.CurrentState->Id = *state.Id.NodeId;
      m_stateMachineInstance.CurrentState->Number = state.Number;
    }

    STATEMACHINE_T &m_stateMachineInstance;
  };
} // namespace UmatiServerLib
