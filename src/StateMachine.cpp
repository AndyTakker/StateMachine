//============================================================= (с) A.Kolesov ==
// Универсальная машина состояний.
//------------------------------------------------------------------------------
#include "StateMachine.h"

StateMachine::StateMachine(uint8_t initialState,
                           const Transition *trans,
                           uint8_t count,
                           ActionCallback action,
                           void *ctx)
    : currentState(initialState),
      transitions(trans),
      numTransitions(count),
      actionCallback(action),
      context(ctx) {}

void StateMachine::handleEvent(uint8_t event) {
  for (int i = 0; i < numTransitions; i++) {
    // Ищем, есть ли указанное событие для текущего состояния
    uint8_t fromState = transitions[i].from;
    uint8_t ev = transitions[i].event;

    if (fromState == currentState && ev == event) {
      // Если есть, то переходим в новое состояние
      uint8_t actionId = transitions[i].actionId;
      currentState = transitions[i].to;
      // Вызываем действие, если оно указано
      if (actionCallback && actionId >= 0) {
        actionCallback(actionId, context);
      }
      return;
    }
  }
}

// Получить текущее состояние объекта
int StateMachine::getState() const { return currentState; }

void StateMachine::setActionDispatcher(ActionCallback action, void *context) {
  actionCallback = action;
  this->context = context;
}
