//
// Created by zhangkai on 2026/1/6.
//

#pragma once
#include <string>

class PhysicalRegister {
public:
  constexpr PhysicalRegister(int id) : id_(id) {
  }
  std::string GetName() const {
    switch (id_) {
      case 0:
        return "zero";
      case 1:
        return "ra";
      case 2:
        return "sp";
      case 3:
        return "gp";
      case 4:
        return "tp";
      case 5:
      case 6:
      case 7:
        return "t" + std::to_string(id_ - 5);
      case 8:
      case 9:
        return "s" + std::to_string(id_ - 8);
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
        return "a" + std::to_string(id_ - 10);
      case 18:
      case 19:
      case 20:
      case 21:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
        return "s" + std::to_string(id_ - 16);
      case 28:
      case 29:
      case 30:
      case 31:
        return "t" + std::to_string(id_ - 25);
     }
  }
private:
  int id_;
};

constexpr PhysicalRegister a(int id) {
  return {id + 10};
}

constexpr PhysicalRegister t(int id) {
  if (id <= 2) {
    return {id + 5};
  }
  return {id + 25};
}

constexpr PhysicalRegister x(int id) {
  return {id};
}

constexpr PhysicalRegister s(int id) {
  if (id <= 1) {
    return {id + 8};
  } else {
    return {id + 16};
  }
}
constexpr PhysicalRegister zero = PhysicalRegister(0);
constexpr PhysicalRegister ra = PhysicalRegister(1);
constexpr PhysicalRegister sp = PhysicalRegister(2);
constexpr PhysicalRegister gp = PhysicalRegister(3);
constexpr PhysicalRegister tp = PhysicalRegister(4);
inline constexpr PhysicalRegister caller_saved_registers[] = {a(0), a(1), a(2), a(3), a(4), a(5), a(6), a(7), t(3), t(4), t(5), t(6)};
inline constexpr PhysicalRegister callee_saved_registers[] = {x(3), x(4), s(0), s(1), s(2), s(3),  s(4),
                                               s(5), s(6), s(7), s(8), s(9), s(10), s(11)};