/// ai_behavior.h - Defines AI behavior system for NPCs
#pragma once

#include <vector>
#include <string>
#include "ai_state.h"

class AIBehavior
{
public:
    AIBehavior();
    virtual ~AIBehavior();

    void Initialize();
    void Update(float deltaTime);
    void SetState(AIState* newState);
    AIState* GetCurrentState() const;

    void AddState(AIState* state);
    void RemoveState(AIState* state);
    bool HasState(AIState* state) const;

protected:
    AIState* m_CurrentState;
    std::vector<AIState*> m_States;
};
