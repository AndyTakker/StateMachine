//==============================================================================
// Реализуем универсальную машину состояний, которая добавляется как дочерний объект
// к любому экземпляру класса, состоянием которого хотим управлять.
// Для управлемого объекта должна быть описана таблица допустимых переходов и
// выполняемое при переходе действие.
// Принцип работы:
// - При возникновении в системе какого-либо события, связанного с контролируемым объектом,
// вызывается функция handleEvent из машины состояний этого объекта.
// - Функция handleEvent ищет в таблице переходов переход, соответствующий текущему состоянию
// и произошедшему событию.
// - Если такой переход есть, то переходим в новое состояние и вызываем действие, если оно указано.
// - Если такого перехода нет, то ничего не делаем.
// Вызов действия при переходе осуществляется вызовом функции, указанной в параметре actionCallback,
// переданной в конструктор машины состояний.
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
