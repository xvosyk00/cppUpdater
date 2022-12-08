//
// Created by pavel on 12/5/22.
//

#include "Changes.hpp"

void serializeChange(std::ostream &os, const Change &c) {
  os << c.filename << " " << static_cast<int>(c.action) << std::endl;
}

Change deserializeChange(std::istream &is) {
  Change change;
  is >> change.filename;
  int action;
  is >> action;
  if(action < 0 || action > static_cast<int>(ProtocolUtil::fileUpdateAction::Change))
    throw std::runtime_error("Invalid action.");
  change.action = static_cast<ProtocolUtil::fileUpdateAction>(action);
  return change;
}

std::ostream &operator<<(std::ostream &os, const Changes &changes) {
  os << changes.size() << std::endl;
  for(auto& c : changes){
    serializeChange(os, c);
  }
  return os;
}

std::istream &operator>>(std::istream &is, Changes &changes) {
  Changes::size_type size;
  is >> size;
  if(!is)
    throw std::runtime_error("Unexpected end of file.");
  changes.reserve(size);
  for(auto i = 0; i < size; i++){
    changes.push_back(deserializeChange(is));
  }
  return is;
}
