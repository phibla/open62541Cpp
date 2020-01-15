///
/// \file BrowsePath.cpp
/// \author Christian von Arnim
/// \date 14.01.2020
///


#include "UA_BrowsePath.hpp"
#include <open62541/types_generated_handling.h>
namespace open62541Cpp {

UA_BrowsePath::~UA_BrowsePath() {
  if (BrowsePath != nullptr) {
    UA_BrowsePath_deleteMembers(BrowsePath);
    UA_BrowsePath_delete(BrowsePath);
  }
}
UA_BrowsePath::UA_BrowsePath(const ::UA_NodeId startNodeId, std::list<UA_RelativPathElement> pathElements) {
  BrowsePath = UA_BrowsePath_new();
  UA_NodeId_copy(&startNodeId, &BrowsePath->startingNode);
  BrowsePath->relativePath.elementsSize = pathElements.size();
  BrowsePath->relativePath.elements =
      reinterpret_cast<UA_RelativePathElement *>(UA_Array_new(BrowsePath->relativePath.elementsSize,
                                                              &UA_TYPES[UA_TYPES_RELATIVEPATHELEMENT]));

  int i = 0;
  for (const auto &el : pathElements) {
    UA_RelativePathElement_copy(el.RelativePathElement, &BrowsePath->relativePath.elements[i++]);
  }
}

UA_BrowsePath::UA_BrowsePath(const UA_BrowsePath &other) {
  BrowsePath = UA_BrowsePath_new();
  UA_BrowsePath_copy(other.BrowsePath, BrowsePath);
}
}
