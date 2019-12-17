///
/// \file NodeValue.cpp
/// \author Christian von Arnim
/// \date 17.12.2019
///


#include "NodeValue.hpp"

void NodeValue::operator=(std::function<UA_Variant()> F) {
  fCallback = F;
}

UA_Variant NodeValue::Value() {
  return fCallback();
}