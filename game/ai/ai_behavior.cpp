/// ai_behavior.cpp - Implements AI behavior system
#include "ai_behavior.h"
#include <algorithm>

AIBehavior::AIBehavior() : m_CurrentState(nullptr) {}

AIBehavior::~AIBehavior()
{
    for (AIState* state : m_States)
    {
        delete state;
    }
    m_States.clear();
}

void AIBehavior::Initialize()
{
    if (m_CurrentState)
    {
        m_CurrentState->Enter();
    }
}

void AIBehavior::Update(float deltaTime)
{
    if (m_CurrentState)
    {
        m_CurrentState->Update(deltaTime);
    }
}

void AIBehavior::SetState(AIState* newState)
{
    if (m_CurrentState)
    {
        m_CurrentState->Exit();
    }
    m_CurrentState = newState;
    if (m_CurrentState)
    {
        m_CurrentState->Enter();
    }
}

AIState* AIBehavior::GetCurrentState() const
{
    return m_CurrentState;
}

void AIBehavior::AddState(AIState* state)
{
    if (state && std::find(m_States.begin(), m_States.end(), state) == m_States.end())
    {
        m_States.push_back(state);
    }
}

void AIBehavior::RemoveState(AIState* state)
{
    auto it = std::find(m_States.begin(), m_States.end(), state);
    if (it != m_States.end())
    {
        m_States.erase(it);
        if (m_CurrentState == state)
        {
            m_CurrentState = nullptr;
        }
        delete state;
    }
}

bool AIBehavior::HasState(AIState* state) const
{
    return std::find(m_States.begin(), m_States.end(), state) != m_States.end();
}
